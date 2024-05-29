/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file flap_encoder.h
 * @author Evan Stoddard
 * @brief FLAP Encoder Module
 */

#ifndef FLAP_ENCODER_H_
#define FLAP_ENCODER_H_

#include "flap.h"

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
 * @brief Encode FLAP
 * 
 * @param frame_type Frame number
 * @param sequence_number Sequence Number
 * @param payload_length Payload length
 * @return flap_t Encoded FLAP
 */
flap_t flap_encode(uint8_t frame_type, uint16_t sequence_number, uint16_t payload_length);

#ifdef __cplusplus
}
#endif
#endif /* FLAP_ENCODER_H_ */