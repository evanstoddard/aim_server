/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file backend.h
 * @author Evan Stoddard
 * @brief Data backend abstraction
 */

#ifndef BACKEND_H_
#define BACKEND_H_

#include "model/model_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

struct backend_t;

/**
 * @brief Backend return codes
 * 
 */
typedef enum {
    BACKEND_RET_SUCCESS = 0,
    BACKEND_RET_BAD_ARGS,
    BACKEND_RET_NO_RESULT,
    BACKEND_RET_DATA_ERROR,
    BACKEND_RET_BACKEND_ERROR,
    BACKEND_RET_USER_ALREADY_EXISTS,
    BACKEND_RET_EMAIL_ALREADY_EXISTS,
    BACKEND_RET_OTHER_ERROR,
} backend_ret_t;

/**
 * @brief API function pointers
 * 
 */
typedef struct backend_api_t {
    backend_ret_t (*fetch_user_info_with_uin)(struct backend_t *backend, char *uin, user_info_t *user_info);
    backend_ret_t (*fetch_user_info_with_email)(struct backend_t *backend, char *email, user_info_t *user_info);
    backend_ret_t (*create_user)(struct backend_t *backend, char *uin, char *email, char *password);
} backend_api_t;

/**
 * @brief Base backend definition
 * 
 */
typedef struct backend_t {
    backend_api_t api;
} backend_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief Set backend
 * 
 * @param backend Pointer to backend
 */
void backend_set_backend(backend_t *backend);

/**
 * @brief Fetch user info with given UIN
 * 
 * @param uin User UIN
 * @param user_info Pointer to write user info to
 * @return backend_ret_t Return status
 */
backend_ret_t backend_fetch_user_info_with_uin(char *uin, user_info_t *user_info);

/**
 * @brief Fetch user info with given email address
 * 
 * @param email User email address
 * @param user_info Pointer to write user info to
 * @return backend_ret_t Return status
 */
backend_ret_t backend_fetch_user_info_with_email(char *email, user_info_t *user_info);

/**
 * @brief Create new user
 * 
 * @param uin UIN of new user
 * @param email Email of new user
 * * @param email Password of new user
 * @return backend_ret_t Return status
 */
backend_ret_t backend_create_user(char *uin, char *email, char *password);

#ifdef __cplusplus
}
#endif
#endif /* BACKEND_H_ */