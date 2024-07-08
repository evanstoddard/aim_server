/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file data_types.h
 * @author Evan Stoddard
 * @brief Various data types
 */

#ifndef DATA_TYPES_H_
#define DATA_TYPES_H_

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
 * @brief 
 * 
 */
typedef struct string8_t {
    uint8_t len;
    char *str;
} string8_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* DATA_TYPES_H_ */