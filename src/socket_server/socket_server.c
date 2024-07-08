/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file socket_server.c
 * @author Evan Stoddard
 * @brief Socket Server
 */

#include "socket_server.h"
#include "logging.h"
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include "oscar/flap.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Variables
 *****************************************************************************/

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Functions
 *****************************************************************************/

socket_server_status_t socket_server_init(
    socket_server_t *instance, 
    uint16_t port
) {
    if (!instance) {
        return SOCKET_SERVER_STATUS_BAD_INSTANCE;
    }
    
    // Clear callbacks
    memset(&instance->callbacks, 0, sizeof(socket_server_callbacks_t));
    
    // Create socket
    instance->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(instance->socket_fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    setsockopt(instance->socket_fd, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int));
    
    // Setup Address and port
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    
    // Attempt to bind socket to port
    int ret = bind(instance->socket_fd, (struct sockaddr*)&addr, sizeof(addr));
    
    if (ret == -1) {
        return SOCKET_SERVER_BIND_ERROR;
    }
    
    return SOCKET_SERVER_STATUS_SUCCESS;
}

socket_server_status_t socket_server_start(socket_server_t *instance) {
    if (!instance) {
        return SOCKET_SERVER_STATUS_BAD_INSTANCE;
    }
    
    // Start listening
    int ret = listen(instance->socket_fd, SOCKET_SERVER_MAX_CONNECTIONS);
    
    if (ret == -1) {
        return SOCKET_SERVER_LISTEN_ERROR;
    }
    
    return SOCKET_SERVER_STATUS_SUCCESS;
}