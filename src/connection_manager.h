/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file connection_manager.h
 * @author Evan Stoddard
 * @brief Spins up socket servers and manages connections
 */

#ifndef CONNECTION_MANAGER_H_
#define CONNECTION_MANAGER_H_

#include <stdint.h>
#include <stdbool.h>
#include "connection.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

#define CONNECTION_MANAGER_MAX_AUTH_CONNECTIONS 10U
#define CONNECTION_MANAGER_MAX_BOSS_CONNECTIONS 10U

#define CONNECTION_MANAGER_DEFAULT_AUTH_PORT    5190U
#define CONNECTION_MANAGER_DEFAULT_BOSS_PORT    5191U

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief Initialize connection manager
 * 
 * @param auth_port Port for auth socket
 * @param boss_port Port for BOSS socket
 * @return true Able to spin up sockets
 * @return false Unable to spin up sockets
 */
bool connection_manager_init(uint16_t auth_port, uint16_t boss_port);

/**
 * @brief Start connection manager and socket servers
 * 
 */
void connection_manager_start(void);

#ifdef __cplusplus
}
#endif
#endif /* CONNECTION_MANAGER_H_ */