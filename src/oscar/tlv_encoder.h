/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file tlv_encoder.h
 * @author Evan Stoddard
 * @brief TLV Encoder Module
 */

#ifndef TLV_ENCODER_H_
#define TLV_ENCODER_H_

#include "tlv.h"

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
 * @brief Encode TLV Header
 * 
 * @param tag Tag ID
 * @param length Length of payload
 * @return tlv_header_t 
 */
tlv_header_t tlv_encode_header(uint16_t tag, uint16_t length);

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* TLV_ENCODER_H_ */