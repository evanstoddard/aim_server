/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file model_types.h
 * @author Evan Stoddard
 * @brief Various model types
 */

#ifndef MODEL_TYPES_H_
#define MODEL_TYPES_H_

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
 * @brief User info typedef
 * 
 */
typedef struct user_info_t {
    char *uin;
    char *email;
    uint8_t md5_password[16];
} user_info_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* MODEL_TYPES_H_ */