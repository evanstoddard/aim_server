/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file main.c
 * @author Evan Stoddard
 * @brief AIM Server
 */

#include "logging.h"
#include "connection_manager.h"

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

int main(int argc, char **argv) {
    LOG_INFO("Application started.")
    
    // Initialize connection manager
    bool ret = connection_manager_init(
        CONNECTION_MANAGER_DEFAULT_AUTH_PORT,
        CONNECTION_MANAGER_DEFAULT_BOSS_PORT
    );
    
    if (!ret) {
        LOG_FATAL("Failed to initialize connection manager.");
        return 1;
    }
    
    connection_manager_start();
    
    return 0;
}