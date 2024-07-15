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

#include "logging.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

#define SQLITE3_MAX_QUERY_SIZE 256

#define SQLITE3_BACKEND_QUERY_USERNAME_STATEMENT    "SELECT * FROM users WHERE uin='%s' LIMIT 1"
#define SQLITE3_BACKEND_QUERY_EMAIL_STATEMENT       "SELECT * FROM users WHERE email='%s' LIMIT 1"

#define SQLITE3_BACKEND_INSERT_USER_STATEMENT       "INSERT INTO users (uin, email) VALUES('%s', '%s')"

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
 * @return backend_ret_t Status of request
 */
static backend_ret_t prv_sqlite_backend_create_user(struct backend_t *backend, char *uin, char *email);

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
    
    // Query
    char query[SQLITE3_MAX_QUERY_SIZE] = {0};
    snprintf(query, SQLITE3_MAX_QUERY_SIZE - 1, SQLITE3_BACKEND_QUERY_USERNAME_STATEMENT, uin);
    
    int ret = -1;
    
    char *err = 0;
    ret = sqlite3_exec(inst->db, query, prv_sqlite_backend_user_info_query_cb, user_info, &err);
    
    if (err != NULL) {
        LOG_ERR("%s", err);
    }
    
    if (ret != BACKEND_RET_SUCCESS) {
        return ret;
    }
    
    return BACKEND_RET_SUCCESS;
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
    
    // Query
    char query[SQLITE3_MAX_QUERY_SIZE] = {0};
    snprintf(query, SQLITE3_MAX_QUERY_SIZE - 1, SQLITE3_BACKEND_QUERY_EMAIL_STATEMENT, email);
    
    int ret = -1;
    
    ret = sqlite3_exec(inst->db, query, prv_sqlite_backend_user_info_query_cb, user_info, NULL);
    
    if (ret != BACKEND_RET_SUCCESS) {
        return ret;
    }
    
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

static backend_ret_t prv_sqlite_backend_create_user(struct backend_t *backend, char *uin, char *email) {
    if (
        backend == NULL || 
        uin == NULL || 
        email == NULL
    ) {
        return BACKEND_RET_BAD_ARGS;
    }
    
    user_info_t user_info = {0};
    
    // Check if user already exists with UIN
    if (prv_sqlite3_backend_user_exists_with_uin(backend, uin)) {
        return BACKEND_RET_USER_ALREADY_EXISTS;
    }
    
    // Check if user already exists with email
    if (prv_sqlite3_backend_user_exists_with_email(backend, email)) {
        return BACKEND_RET_EMAIL_ALREADY_EXISTS;
    }
    
}

static int prv_sqlite_backend_user_info_query_cb(void *ctx, int argc, char **col_data, char **col_name) {
    // If number of columns is less than data requested, return error
    if (argc < 2) {
        return BACKEND_RET_DATA_ERROR;
    }
    
    user_info_t *user_info = (user_info_t *)ctx;
    
    for (int i = 0; i < argc; i++) {
        if (!strcmp(col_name[i], SQLITE3_BACKEND_UIN_COL_NAME)) {
            user_info->uin = calloc(sizeof(char), strlen(col_data[i]) + 1);
            
            if (user_info->uin == NULL) {
                return BACKEND_RET_BACKEND_ERROR;
            }
            
            strcpy(user_info->uin, col_data[i]);
        } else if (!strcmp(col_name[i], SQLITE3_BACKEND_EMAIL_COL_NAME)) {
            user_info->email = calloc(sizeof(char), strlen(col_data[i]) + 1);
            
            if (user_info->email == NULL) {
                return BACKEND_RET_BACKEND_ERROR;
            }
            
            strcpy(user_info->email, col_data[i]);
        }
    }
    
    /*
    TODO:   Need to refactor code above and below to appropriately verify that
            all user info fields are accounted for in query...
    */
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