/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file flap_decoder.c
 * @author Evan Stoddard
 * @brief Implements FLAP decoder
 */

#include "flap_decoder.h"
#include <string.h>
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

bool flap_decode(flap_t *flap, void *buffer, ssize_t size) {
    if (flap == NULL) {
        return false;
    }
    
    if (buffer == NULL) {
        return false;
    }
    
    if (size < sizeof(flap_t)) {
        return false;
    }
    
    // Copy buffer into flap if needed
    if (flap != buffer) {
        memcpy(flap, buffer, sizeof(flap_t));
    }
    
    if (flap->start_marker != FLAP_START_MARKER) {
        return false;
    }
    
    flap->sequence_number = ntohs(flap->sequence_number);
    flap->payload_length = ntohs(flap->payload_length);
    
    return true;
}