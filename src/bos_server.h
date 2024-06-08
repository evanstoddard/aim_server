/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file bos_server.h
 * @author Evan Stoddard
 * @brief BOSS server implementation
 */

#ifndef BOS_SERVER_H_
#define BOS_SERVER_H_

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
 * @brief Handle new connection to BOSS server
 * 
 * @param conn Connection
 */
void bos_server_handle_new_connection(connection_t *conn);

/**
 * @brief Handle event from connection
 * 
 * @param conn Connection
 */
void bos_server_handle_event(connection_t *conn);

#ifdef __cplusplus
}
#endif
#endif /* BOS_SERVER_H_ */