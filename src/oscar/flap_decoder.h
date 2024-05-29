/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file flap_decoder.h
 * @author Evan Stoddard
 * @brief Implements FLAP decoder
 */

#ifndef FLAP_DECODER_H_
#define FLAP_DECODER_H_

#include "flap.h"
#include <unistd.h>
#include <stdbool.h>

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
 * @brief Decode FLAP from buffer
 * 
 * @param flap Pointer to write flap to
 * @param buffer Buffer to parse
 * @param size Size of buffer
 * @return true Able decode FLAP
 * @return false Unable to decode FLAP
 */
bool flap_decode(flap_t *flap, void *buffer, ssize_t size);

#ifdef __cplusplus
}
#endif
#endif /* FLAP_DECODER_H_ */