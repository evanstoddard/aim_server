/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file auth_types.h
 * @author Evan Stoddard
 * @brief Type definitions for authorization
 */

#ifndef AUTH_TYPES_H_
#define AUTH_TYPES_H_

#include "oscar_constants.h"
#include <stdint.h>

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
 * @brief Authorization cookie type
 * 
 */
typedef struct auth_cookie_t {
    char screenname[SCREENNAME_MAX_LEN];
    uint8_t md5_magic[16];
} auth_cookie_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* AUTH_TYPES_H_ */