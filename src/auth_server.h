/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file auth_server.h
 * @author Evan Stoddard
 * @brief Auth server implementation
 */

#ifndef AUTH_SERVER_H_
#define AUTH_SERVER_H_

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
 * @brief Handle new connection to auth server
 * 
 * @param conn Connection
 */
void auth_server_handle_new_connection(connection_t *conn);

/**
 * @brief Handle event from connection
 * 
 * @param conn Connection
 */
void auth_server_handle_event(connection_t *conn);

#ifdef __cplusplus
}
#endif
#endif /* AUTH_SERVER_H_ */