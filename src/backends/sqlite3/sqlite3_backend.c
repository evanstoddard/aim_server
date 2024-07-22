/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file sqlite3_backend.c
 * @author Evan Stoddard
 * @brief SQLite3 based data backend
 */

#include "sqlite3_backend.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "md5.h"

#include "logging.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

#define SQLITE3_MAX_QUERY_SIZE 256

#define SQLITE3_BACKEND_QUERY_UIN_STATEMENT         "SELECT rowid,uin,email,md5_password FROM users WHERE uin = :uin LIMIT 1"
#define SQLITE3_BACKEND_QUERY_EMAIL_STATEMENT       "SELECT rowid,uin,email,md5_password FROM users WHERE email = :email LIMIT 1"
#define SQLITE3_BACKEND_INSERT_USER_STATEMENT       "INSERT INTO users (uin, email, md5_password) VALUES(:uin, :email, :md5_password)"

#define SQLITE3_BACKEND_UIN_COL_NAME    "uin"
#define SQLITE3_BACKEND_EMAIL_COL_NAME  "email"

/*****************************************************************************
 * Variables
 *****************************************************************************/

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/**
 * @brief Connect API functions pointers to base
 * 
 * @param inst Instance
 */
static void prv_sqlite3_backend_connect_api(sqlite3_backend_t *inst);

/**
 * @brief Fetch user info with given UIN
 * 
 * @param backend Pointer to backend instance
 * @param uin UIN to look for
 * @param cb Pointer to callback
 * @param ctx Context to pass to callback
 */

/**
 * @brief Fetch user info with given uin
 * 
 * @param backend Pointer to backend instance
 * @param uin UIN to look for
 * @param user_info Struct to write user info to
 * @return backend_ret_t Status of query
 */
static backend_ret_t prv_sqlite3_backend_fetch_user_info_with_uin(struct backend_t *backend, char *uin, user_info_t *user_info);

/**
 * @brief Fetch user info with given email address
 * 
 * @param backend Pointer to backend instance
 * @param email Email address to look for
 * @param user_info Struct to write user info to
 * @return backend_ret_t Status of query
 */
static backend_ret_t prv_sqlite3_backend_fetch_user_info_with_email(struct backend_t *backend, char *email, user_info_t *user_info);

/**
 * @brief With given statement, populate user info struct
 * 
 * @param backend Pointer to backend
 * @param stmt SQLite3 statement
 * @param user_info Pointer to user info
 * @return backend_ret_t Status of query
 */
static backend_ret_t prv_sqlite_backend_fill_user_info(struct backend_t *backend, sqlite3_stmt *stmt, user_info_t *user_info);

/**
 * @brief Function to check if user exists with given UIN
 * 
 * @param backend Pointer to backend instance
 * @param uin UIN to check for
 * @return true User exists with UIN
 * @return false User does not exist with UIN
 */
static bool prv_sqlite3_backend_user_exists_with_uin(struct backend_t *backend, char *uin);

/**
 * @brief Function to check if user exists with given email
 * 
 * @param backend Pointer to backend instance
 * @param uin Email to check for
 * @return true User exists with Email
 * @return false User does not exist with Email
 */
static bool prv_sqlite3_backend_user_exists_with_email(struct backend_t *backend, char *email);

/**
 * @brief Create user with provided UIN and email
 * 
 * @param backend Pointer to backend instance
 * @param uin UIN of new user
 * @param email Email address of new user
 * @param password Password of new user
 * @return backend_ret_t Status of request
 */
static backend_ret_t prv_sqlite_backend_create_user(struct backend_t *backend, char *uin, char *email, char *password);

/**
 * @brief SQLite3 callback for fetching user info
 * 
 * @param ctx Context (user info struct)
 * @param argc Number of columns
 * @param col_data Column data
 * @param col_name Column name
 * @return backend_ret_t Return of callback
 */
static int prv_sqlite_backend_user_info_query_cb(void *ctx, int argc, char **col_data, char **col_name);

/*****************************************************************************
 * Private Functions
 *****************************************************************************/

static void prv_sqlite3_backend_connect_api(sqlite3_backend_t *inst) {
    inst->base.api.fetch_user_info_with_uin = prv_sqlite3_backend_fetch_user_info_with_uin;
    inst->base.api.fetch_user_info_with_email = prv_sqlite3_backend_fetch_user_info_with_email;
    inst->base.api.create_user = prv_sqlite_backend_create_user;
}

static backend_ret_t prv_sqlite3_backend_fetch_user_info_with_uin(struct backend_t *backend, char *uin, user_info_t *user_info) {
    if (
        backend == NULL || 
        uin == NULL || 
        user_info == NULL
    ) {
        return BACKEND_RET_BAD_ARGS;
    }
    
    sqlite3_backend_t *inst = (sqlite3_backend_t *)backend;
    
    // Generate statement
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(inst->db, SQLITE3_BACKEND_QUERY_UIN_STATEMENT, -1, &stmt, NULL);
    
    // Bind arguments
    int uin_idx = sqlite3_bind_parameter_index(stmt, ":uin");
    sqlite3_bind_text(stmt, uin_idx, uin, -1, NULL);
    
    return prv_sqlite_backend_fill_user_info(backend, stmt, user_info);
}

static backend_ret_t prv_sqlite3_backend_fetch_user_info_with_email(struct backend_t *backend, char *email, user_info_t *user_info) {
    if (
        backend == NULL || 
        email == NULL || 
        user_info == NULL
    ) {
        return BACKEND_RET_BAD_ARGS;
    }
    
    sqlite3_backend_t *inst = (sqlite3_backend_t *)backend;
    
    // Generate statement
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(inst->db, SQLITE3_BACKEND_QUERY_EMAIL_STATEMENT, -1, &stmt, NULL);
    
    // Bind arguments
    int email_idx = sqlite3_bind_parameter_index(stmt, ":email");
    sqlite3_bind_text(stmt, email_idx, email, -1, NULL);
    
    return prv_sqlite_backend_fill_user_info(backend, stmt, user_info);
}

static backend_ret_t prv_sqlite_backend_fill_user_info(struct backend_t *backend, sqlite3_stmt *stmt, user_info_t *user_info) {
    // Execute Query
    int step_ret = sqlite3_step(stmt);
    
    int ret = BACKEND_RET_SUCCESS;
    
    switch(step_ret) {
    case SQLITE_ROW:
        break;
    case SQLITE_DONE:
        sqlite3_finalize(stmt);
        return BACKEND_RET_NO_RESULT;
    default:
        LOG_ERR("SQLite Backend Fetch Error: %d", ret);
        return BACKEND_RET_BACKEND_ERROR;
    }
    
    // Get values
    const char * uin = sqlite3_column_text(stmt, 1);
    const char * email = sqlite3_column_text(stmt, 2);
    const uint8_t *md5_password = sqlite3_column_blob(stmt, 3);
    int blob_size = sqlite3_column_bytes(stmt, 3);
    
    if (blob_size != sizeof(user_info->md5_password)) {
        sqlite3_finalize(stmt);
        return BACKEND_RET_DATA_ERROR;
    }
    
    if (uin == NULL || email == NULL) {
        sqlite3_finalize(stmt);
        return BACKEND_RET_DATA_ERROR;
    }
    
    user_info->uin = calloc(sizeof(char), strlen(uin) + 1);
    user_info->email = calloc(sizeof(char), strlen(email) + 1);
    memcpy(user_info->md5_password, md5_password, blob_size);
    
    if (
        user_info->email == NULL ||
        user_info->uin == NULL
    ) {
        sqlite3_finalize(stmt);
        return BACKEND_RET_OTHER_ERROR;
    }
    
    strcpy(user_info->uin, uin);
    strcpy(user_info->email, email);
    
    sqlite3_finalize(stmt);
    
    return BACKEND_RET_SUCCESS;
}

static bool prv_sqlite3_backend_user_exists_with_uin(struct backend_t *backend, char *uin) {
    if (
        backend == NULL ||
        uin == NULL
    ) {
        return BACKEND_RET_BAD_ARGS;
    }
    
    user_info_t user_info = {0};
    bool exists = false;
    
    // Attempt to get user info with UIN
    backend_ret_t ret = prv_sqlite3_backend_fetch_user_info_with_uin(backend, uin, &user_info);
    
    // Check if there's a backend error
    if (ret != BACKEND_RET_SUCCESS) {
        exists = false;
    }
    
    // Check for entries and free allocated memory
    if (user_info.uin != NULL) {
        exists = true;
        free(user_info.uin);
    }
    
    if (user_info.email != NULL) {
        free(user_info.email);
    }
    
    return exists;
}

static bool prv_sqlite3_backend_user_exists_with_email(struct backend_t *backend, char *email) {
    if (
        backend == NULL ||
        email == NULL
    ) {
        return BACKEND_RET_BAD_ARGS;
    }
    
    user_info_t user_info = {0};
    bool exists = false;
    
    // Attempt to get user info with UIN
    backend_ret_t ret = prv_sqlite3_backend_fetch_user_info_with_email(backend, email, &user_info);
    
    // Check if there's a backend error
    if (ret != BACKEND_RET_SUCCESS) {
        exists = false;
    }
    
    // Check for entries and free allocated memory
    if (user_info.uin != NULL) {
        exists = true;
        free(user_info.uin);
    }
    
    if (user_info.email != NULL) {
        free(user_info.email);
    }
    
    return exists;
}

static backend_ret_t prv_sqlite_backend_create_user(struct backend_t *backend, char *uin, char *email, char *password) {
    if (
        backend == NULL || 
        uin == NULL || 
        email == NULL ||
        password == NULL
    ) {
        return BACKEND_RET_BAD_ARGS;
    }
    
    // Check if user already exists with UIN
    if (prv_sqlite3_backend_user_exists_with_uin(backend, uin)) {
        return BACKEND_RET_USER_ALREADY_EXISTS;
    }
    
    // Check if user already exists with email
    if (prv_sqlite3_backend_user_exists_with_email(backend, email)) {
        return BACKEND_RET_EMAIL_ALREADY_EXISTS;
    }
    
    // Create MD5 hash of password (so at least not stored in plaintext)
    MD5Context md5_ctx = {0};
    md5Init(&md5_ctx);
    md5Update(&md5_ctx, password, strlen(password));
    md5Finalize(&md5_ctx);
    
    // Create statement
    sqlite3_backend_t *inst = (sqlite3_backend_t *)backend;

    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(inst->db, SQLITE3_BACKEND_INSERT_USER_STATEMENT, -1, &stmt, NULL);
    
    // Bind params
    sqlite3_bind_blob(
        stmt,
        sqlite3_bind_parameter_index(stmt, ":md5_password"),
        md5_ctx.digest, 
        sizeof(md5_ctx.digest),
        NULL
    );
    
    sqlite3_bind_text(
        stmt,
        sqlite3_bind_parameter_index(stmt, ":uin"),
        uin, 
        strlen(uin),
        NULL
    );
    
    sqlite3_bind_text(
        stmt,
        sqlite3_bind_parameter_index(stmt, ":email"),
        email, 
        strlen(email),
        NULL
    );
    
    int ret = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    if (ret != SQLITE_DONE) {
        LOG_ERR("Failed to create new user. (%d)", ret);
        return BACKEND_RET_BACKEND_ERROR;
    }
    
    return BACKEND_RET_SUCCESS;
}

/*****************************************************************************
 * Public Functions
 *****************************************************************************/

bool sqlite3_backend_init(sqlite3_backend_t *inst, char *db_path) {
    if (inst == NULL) {
        return false;
    }
    
    int ret = sqlite3_open(db_path, &inst->db);
    
    if (ret != 0) {
        LOG_ERR("Failed to open SQLite3 database: %s", sqlite3_errmsg(inst->db));
        sqlite3_close(inst->db);
        return false;
    }
    
    prv_sqlite3_backend_connect_api(inst);
    
    return true;
}