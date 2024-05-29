/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file auth_handler.h
 * @author Evan Stoddard
 * @brief Handlers for auth requests
 */

#ifndef AUTH_HANDLER_H_
#define AUTH_HANDLER_H_

#include "connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief Handle new connection to auth socket
 * 
 * @param conn Connection
 */
void auth_handler_handle_new_connection(connection_t *conn);

/**
 * @brief Receive data from connection
 * 
 * @param conn Connection
 */
void auth_handler_connection_receive(connection_t *conn);

#ifdef __cplusplus
}
#endif
#endif /* AUTH_HANDLER_H_ */