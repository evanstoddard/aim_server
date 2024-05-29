/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file socket_server.h
 * @author Evan Stoddard
 * @brief Socket Server
 */

#ifndef SOCKET_SERVER_H_
#define SOCKET_SERVER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

#define SOCKET_SERVER_MAX_WRITE_BUFFER_BYTES    1024U
#define SOCKET_SERVER_MAX_READ_BUFFER_BYTES     1024U
#define SOCKET_SERVER_MAX_CONNECTIONS           8U

/**
 * @brief Status codes for 
 * 
 */
typedef enum {
    SOCKET_SERVER_STATUS_SUCCESS = 0,
    SOCKET_SERVER_STATUS_BAD_INSTANCE,
    SOCKET_SERVER_BIND_ERROR,
    SOCKET_SERVER_LISTEN_ERROR,
    SOCKET_SERVER_CONNECTION_ERROR
} socket_server_status_t;

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/**
 * @brief Forward declaration of socket server type
 * 
 */
struct socket_server_t;

/**
 * @brief Callbacks definitions for socket server
 * 
 */
typedef struct socket_server_callbacks_t {
    void(*new_connection)(struct socket_server_t *instance, int conn);
} socket_server_callbacks_t;

/**
 * @brief Socket server instance type defintion
 * 
 */
typedef struct socket_server_t {
    int socket_fd;
    socket_server_callbacks_t callbacks;
} socket_server_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief 
 * 
 * @param instance Pointer to instance
 * @param port Port number to bind to
 * @return socket_server_status_t Return status
 */
socket_server_status_t socket_server_init(
    socket_server_t *instance, 
    uint16_t port
);

/**
 * @brief Start listening for connections
 * 
 * @param instance Pointer to instance
 * @return socket_server_status_t Return status
 */
socket_server_status_t socket_server_start(socket_server_t *instance);

#ifdef __cplusplus
}
#endif
#endif /* SOCKET_SERVER_H_ */