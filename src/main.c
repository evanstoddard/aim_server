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

#include "backends/backend.h"
#include "backends/sqlite3/sqlite3_backend.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Variables
 *****************************************************************************/

static sqlite3_backend_t data_backend;

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Functions
 *****************************************************************************/

int main(int argc, char **argv) {
    LOG_INFO("Application started.")
    
    // Initialize backend
    if (!sqlite3_backend_init(&data_backend, "aim_db.db")) {
        LOG_FATAL("Failed to initialize backend.");
        return 1;
    }
    
    backend_set_backend((backend_t *)&data_backend);
    
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