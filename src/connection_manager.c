/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file connection_manager.c
 * @author Evan Stoddard
 * @brief Spins up socket servers and manages connections
 */

#include <poll.h>
#include <unistd.h>
#include <sys/socket.h>

#include "connection_manager.h"
#include "connection.h"
#include "socket_server/socket_server.h"

#include "auth_server.h"
#include "bos_server.h"

#include "logging.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

#define CONNECTION_MANAGER_MAX_TOTAL_CONNECTIONS ( \
            CONNECTION_MANAGER_MAX_AUTH_CONNECTIONS + \
            CONNECTION_MANAGER_MAX_BOSS_CONNECTIONS \
        )

#define CONNECTION_MANAGER_AUTH_IDX 0U
#define CONNECTION_MANAGER_BOSS_IDX 1U

#define CONNECTION_MANAGER_SERVER_FD_COUNT (CONNECTION_MANAGER_BOSS_IDX + 1)

#define CONNECTION_MANAGER_POLL_TIMEOUT INT32_MAX

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/*****************************************************************************
 * Variables
 *****************************************************************************/

/**
 * @brief Private static instance of connection manager
 * 
 */
static struct {
    connection_t *connections[CONNECTION_MANAGER_MAX_TOTAL_CONNECTIONS];
    
    // Need a pollfds for each connection plus one for each socket server fd
    struct pollfd pollfds[CONNECTION_MANAGER_MAX_TOTAL_CONNECTIONS + 2];
    
    socket_server_t auth_socket_server;
    socket_server_t boss_socket_server;
    
    nfds_t active_fds;
} prv_inst;

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/**
 * @brief Socket polling event loop
 * 
 */
static void prv_connection_manager_polling_loop(void);

/**
 * @brief Service server FDs on poll events
 * 
 */
static void prv_connection_manager_service_server_fds(void);

/**
 * @brief Service client FDs on poll events
 * 
 */
static void prv_connection_manager_service_client_fds(void);

/**
 * @brief Handle new client
 * 
 * @param fd_idx Index of FD
 */
static void prv_connection_manager_handle_new_client(uint32_t fd_idx);

/**
 * @brief Callback called when connection closed
 * 
 * @param conn Connection
 */
static void prv_connection_manager_on_connection_closed(connection_t *conn);

/*****************************************************************************
 * Functions
 *****************************************************************************/

bool connection_manager_init(uint16_t auth_port, uint16_t boss_port) {
    // Initialize socket servers
    socket_server_status_t ret = socket_server_init(
        &prv_inst.auth_socket_server, 
        auth_port)
    ;
    
    if (ret != SOCKET_SERVER_STATUS_SUCCESS) {
        LOG_ERR("Failed to initialize auth socket server. (%u)", ret);
        return false;
    }
    
    ret = socket_server_init(
        &prv_inst.boss_socket_server,
        boss_port
    );
    
    if (ret != SOCKET_SERVER_STATUS_SUCCESS) {
        LOG_ERR("Failed to initialize BOSS socket server. (%u)", ret);
        return false;
    }
    
    return true;
}

void connection_manager_start(void) {
    // Start Socket servers
    socket_server_status_t ret = socket_server_start(&prv_inst.auth_socket_server);
    
    if (ret != SOCKET_SERVER_STATUS_SUCCESS) {
        LOG_FATAL("Failed to start auth socket server. (%u)", ret);
        return;
    }
    
    ret = socket_server_start(&prv_inst.boss_socket_server);
    
    if (ret != SOCKET_SERVER_STATUS_SUCCESS) {
        LOG_FATAL("Failed to start BOSS socket server. (%u)", ret);
        return;
    }
    
    // Set up polling
    prv_inst.pollfds[CONNECTION_MANAGER_AUTH_IDX].fd = prv_inst.auth_socket_server.socket_fd;
    prv_inst.pollfds[CONNECTION_MANAGER_BOSS_IDX].fd = prv_inst.boss_socket_server.socket_fd;
    
    prv_inst.pollfds[CONNECTION_MANAGER_AUTH_IDX].events = POLLIN | POLLPRI;
    prv_inst.pollfds[CONNECTION_MANAGER_BOSS_IDX].events = POLLIN | POLLPRI;
    
    prv_inst.active_fds = 2;

    // This shouldn't return
    prv_connection_manager_polling_loop();
    
    LOG_INFO("Server sockets closed.");
}

void prv_connection_manager_on_connection_closed(connection_t *connection) {
    if (connection == NULL) {
        return;
    }
    
    int idx = -1;
    
    // Attempt to find index of connection
    for (int i = 0; i < CONNECTION_MANAGER_MAX_TOTAL_CONNECTIONS; i++) {
        if (connection != prv_inst.connections[i]) {
            continue;
        }
        
        idx = i;
        
        prv_inst.connections[i] = NULL;
    }
    
    // Something went wrong. Pointer passed in could be bad.
    // Not going to call deinit for risk of double-free...
    // Just going to warn and return...
    // This should never happen unless something really bad happens...
    if (idx == -1) {
        LOG_WARN("Something went wrong... possible memory leak?");
        return;
    }
    
    prv_inst.pollfds[idx + 2].fd = 0;
    prv_inst.pollfds[idx + 2].events = 0;
    prv_inst.pollfds[idx + 2].revents = 0;
    prv_inst.active_fds--;
    
    LOG_INFO("Connection %i closed.", idx);
    
    // Deinit client
    connection_deinit(connection);
}

static void prv_connection_manager_polling_loop(void) {
    while (true) {
        int poll_result = poll(
            prv_inst.pollfds, 
            prv_inst.active_fds, 
            CONNECTION_MANAGER_POLL_TIMEOUT
        );
        
        // Check if events occurred
        if (poll_result > 0) {
            prv_connection_manager_service_server_fds();
            prv_connection_manager_service_client_fds();
        }
        
        LOG_INFO("Active connections: %lu", prv_inst.active_fds - 2);
    }
}

static void prv_connection_manager_service_server_fds(void) {
    for (uint32_t i = 0; i < CONNECTION_MANAGER_SERVER_FD_COUNT; i++) {
        if (prv_inst.pollfds[i].revents & POLLIN) {
            prv_connection_manager_handle_new_client(i);
        }
    }
}

static void prv_connection_manager_service_client_fds(void) {
    for (int i = 2; i < CONNECTION_MANAGER_MAX_TOTAL_CONNECTIONS + 2; i++) {
        connection_t *conn = prv_inst.connections[i - 2];
        
        if (
            (prv_inst.pollfds[i].fd > 0) && 
            (prv_inst.pollfds[i].revents & POLLIN)
        ) {
            conn->callbacks.on_event(conn);
        }
    }
}

static void prv_connection_manager_handle_new_client(uint32_t fd_idx) {
    int server_fd = prv_inst.pollfds[fd_idx].fd;
    int client_fd = accept(
        server_fd, 
        NULL, 
        NULL
    );
    
    // Something went wrong accepting client.
    if (client_fd == -1) {
        LOG_ERR("Failed to connect to accept client socket.");
        return;
    }
    
    // Check if we have enough space for new client
    if ((prv_inst.active_fds - 2) == CONNECTION_MANAGER_MAX_TOTAL_CONNECTIONS) {
        LOG_WARN("No room at the Inn :/");
        close(client_fd);
        return;
    }
    
    // Create new connection instance
    connection_t *conn = connection_init(client_fd);
    
    if (conn == NULL) {
        LOG_ERR("Unable to create connection. Out of memory?");
        close(client_fd);
        return;
    }
    
    // Set on closed callback
    conn->callbacks.connection_closed = prv_connection_manager_on_connection_closed;
    
    // Add socket fd to polling list and add
    for (int i = 2; i < CONNECTION_MANAGER_MAX_TOTAL_CONNECTIONS + 2; i++) {
        // Skip if slot is already used
        if (prv_inst.pollfds[i].fd != 0) {
            continue;
        }
        
        prv_inst.pollfds[i].fd = client_fd;
        prv_inst.pollfds[i].events = POLLIN | POLLPRI; 
        
        prv_inst.connections[i - 2] = conn;
        prv_inst.active_fds++;
            
        break;
    }
    
    switch (fd_idx) {
    case CONNECTION_MANAGER_AUTH_IDX:
        auth_server_handle_new_connection(conn);
        break;
    case CONNECTION_MANAGER_BOSS_IDX:
        bos_server_handle_new_connection(conn);
        break;
    default:
        connection_close(conn);
        break;
    }
}