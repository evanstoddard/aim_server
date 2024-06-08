/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file connection.c
 * @author Evan Stoddard
 * @brief Client connection module
 */

#include "connection.h"
#include <unistd.h>
#include <stddef.h>
#include "logging.h"
#include "connection_manager.h"
#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Variables
 *****************************************************************************/

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/**
 * @brief Helper function to call on closed callback
 * 
 * @param conn Connection
 */
static inline void prv_connection_call_on_closed_callback(connection_t *conn);

/*****************************************************************************
 * Functions
 *****************************************************************************/

connection_t* connection_init(int socket) {
    // Allocate memory for new connection
    connection_t *conn = malloc(sizeof(connection_t));
    
    if (conn == NULL) {
        return NULL;
    }
    
    memset(conn, 0, sizeof(connection_t));
    
    conn->socket = socket;
    
    return conn;
}

void connection_deinit(connection_t *conn) {
    if (conn == NULL) {
        return;
    }
    
    LOG_DEBUG("Deinitializing connection...");
    
    if (conn->client) {
        client_deinit(conn->client);
    }
    
    free(conn);
}

ssize_t connection_read(connection_t *conn, void *buffer, ssize_t size) {
    ssize_t read_bytes = read(conn->socket, buffer, size);
    
    if (read_bytes == 0 || read_bytes == -1) {
        connection_close(conn);
    }
    
    return read_bytes;
}

ssize_t connection_write(connection_t *conn, void *buffer, ssize_t size) {
    ssize_t written_bytes = write(conn->socket, buffer, size);
    
    if (written_bytes == 0 || written_bytes == -1) {
        connection_close(conn);
    }
    
    return written_bytes;
}

void connection_close(connection_t *conn) {
    if (conn == NULL) {
        return;
    }
    
    // Close socket
    close(conn->socket);
    
    // Call connection closed callback
    prv_connection_call_on_closed_callback(conn);
}

static inline void prv_connection_call_on_closed_callback(connection_t *conn) {
    if (conn == NULL) {
        return;
    }
    
    if (conn->callbacks.connection_closed) {
        conn->callbacks.connection_closed(conn);
    }
}