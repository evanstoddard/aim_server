/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file backend.c
 * @author Evan Stoddard
 * @brief Data backend abstraction
 */

#include "backend.h"

#include <stddef.h>

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Variables
 *****************************************************************************/

/**
 * @brief Pointer to active backend
 * 
 */
static backend_t *prv_backend = NULL;

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Functions
 *****************************************************************************/

void backend_set_backend(backend_t *backend) {
    prv_backend = backend;
}

backend_ret_t backend_fetch_user_info_with_uin(char *uin, user_info_t *user_info) {
    if (prv_backend == NULL) {
        return BACKEND_RET_BACKEND_ERROR;
    }
    
    return prv_backend->api.fetch_user_info_with_uin(prv_backend, uin, user_info);
}

backend_ret_t backend_fetch_user_info_with_email(char *email, user_info_t *user_info) {
    if (prv_backend == NULL) {
        return BACKEND_RET_BACKEND_ERROR;
    }
    
    return prv_backend->api.fetch_user_info_with_email(prv_backend, email, user_info);
}

backend_ret_t backend_create_user(char *uin, char *email, char *password) {
    if (prv_backend == NULL) {
        return BACKEND_RET_BACKEND_ERROR;
    }
    
    return prv_backend->api.create_user(prv_backend, uin, email, password);
}