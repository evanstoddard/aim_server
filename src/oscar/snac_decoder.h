/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file snac_decoder.h
 * @author Evan Stoddard
 * @brief SNAC Payload Decoder
 */

#ifndef SNAC_DECODER_H_
#define SNAC_DECODER_H_

#include "snac.h"
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
 * @brief Decode SNAC data
 * 
 * @param snac Pointer to write SNAC to
 * @param buffer Buffer to parse SNAC from
 * @param buffer_size Size of buffer
 * @return true Able to parse SNAC
 * @return false Unable to parse SNAC
 */
bool snac_decode(snac_t *snac, void *buffer, ssize_t buffer_size);

#ifdef __cplusplus
}
#endif
#endif /* SNAC_DECODER_H_ */