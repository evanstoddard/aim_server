/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file connection.h
 * @author Evan Stoddard
 * @brief Client connection module
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <stdint.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/**
 * @brief Forward declaration of connection type
 * 
 */
struct connection_t;

/**
 * @brief Defines what type of connection socket is
 * 
 */
typedef enum {
    CONNECTION_TYPE_NONE,
    CONNECTION_TYPE_AUTH,
    CONNECTION_TYPE_BOSS,
    CONNECTION_TYPE_UNKNOWN
} connection_type_t;

/**
 * @brief Connection callbacks typedef
 * 
 */
typedef struct connection_callbacks_t {
    void(*connection_closed)(struct connection_t *conn);
} connection_callbacks_t;

/**
 * @brief Connection instance typedef
 * 
 */
typedef struct connection_t {
    connection_type_t type;
    int socket;
    uint16_t last_inbound_seq_num;
    uint16_t last_outbound_seq_num;
    connection_callbacks_t callbacks;
    char screenname[20];
} connection_t;

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief Create new connection from socket and socket type
 * 
 * @param socket Socket file descriptor
 * @param type Type of socket
 * @return connection_t* Pointer to newly created connection
 */
connection_t* connection_init(int socket, connection_type_t type);

/**
 * @brief Deinitialize connection
 * 
 * @param conn Connection to deinitialize
 */
void connection_deinit(connection_t *conn);

/**
 * @brief Handle new data
 * 
 */
void connection_handle_new_data(connection_t *conn);

/**
 * @brief Read from socket and automatically handle socket errors/closures
 * 
 * @param conn Connection
 * @param buffer Buffer to read into
 * @param size Max size 
 * @return ssize_t Size of data read
 */
ssize_t connection_read(connection_t *conn, void *buffer, ssize_t size);

/**
 * @brief Write to socket and automatically handle socket errors/closures
 * 
 * @param conn Connection
 * @param buffer Buffer to write to socket
 * @param size Size of buffer
 * @return ssize_t Size written
 */
ssize_t connection_write(connection_t *conn, void *buffer, ssize_t size);

/**
 * @brief Close connection
 * 
 * @param conn Connection
 */
void connection_close(connection_t *conn);

#ifdef __cplusplus
}
#endif
#endif /* CONNECTION_H_ */