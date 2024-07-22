/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file random.h
 * @author Evan Stoddard
 * @brief Functions for generating random data
 */

#ifndef RANDOM_H_
#define RANDOM_H_

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

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief Generate stream of random bytes
 * 
 * @param dest Destination
 * @param bytes Number of random bytes
 */
void generate_random_stream(uint8_t *dest, uint32_t bytes);

#ifdef __cplusplus
}
#endif
#endif /* RANDOM_H_ */