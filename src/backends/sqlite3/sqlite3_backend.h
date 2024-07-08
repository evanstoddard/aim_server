/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file sqlite3_backend.h
 * @author Evan Stoddard
 * @brief SQLite3 based data backend
 */

#ifndef SQLITE3_BACKEND_H_
#define SQLITE3_BACKEND_H_

#include "backends/backend.h"

#include <stdbool.h>
#include <sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/**
 * @brief SQLite3 Backend typedef
 * 
 */
typedef struct sqlite3_backend_t {
    backend_t base;
    sqlite3 *db;
} sqlite3_backend_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief Initialize SQLite3 backend
 * 
 * @param inst Instance
 * @param db_path Path to database file
 * @return true Able to initialize backend
 * @return false Unable to initialize backend
 */
bool sqlite3_backend_init(sqlite3_backend_t *inst, char *db_path);

#ifdef __cplusplus
}
#endif
#endif /* SQLITE3_BACKEND_H_ */