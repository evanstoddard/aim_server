/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file tlv_decoder.h
 * @author Evan Stoddard
 * @brief 
 */

#ifndef TLV_DECODER_H_
#define TLV_DECODER_H_

#include "tlv.h"
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
 * @brief Decode base TLV from buffer
 * 
 * @param tlv Pointer to write TLV to
 * @param buffer Buffer to parse TLV from
 * @param buffer_size Size of buffer
 * @return true Able to parse TLV
 * @return false Unable to parse TLV
 */
bool tlv_decode(tlv_t *tlv, void *buffer, ssize_t buffer_size);


#ifdef __cplusplus
}
#endif
#endif /* TLV_DECODER_H_ */