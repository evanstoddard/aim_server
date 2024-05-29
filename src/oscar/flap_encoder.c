/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file flap_encoder.c
 * @author Evan Stoddard
 * @brief FLAP Encoder Module
 */

#include "flap_encoder.h"

#include <arpa/inet.h>

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Variables
 *****************************************************************************/

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Functions
 *****************************************************************************/

flap_t flap_encode(uint8_t frame_type, uint16_t sequence_number, uint16_t payload_length) {
    flap_t flap;
    
    flap.start_marker = FLAP_START_MARKER;
    flap.frame_type = frame_type;
    flap.sequence_number = htons(sequence_number);
    flap.payload_length = htons(payload_length);
    
    return flap;
}