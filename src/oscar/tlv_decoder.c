/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file tlv_decoder.c
 * @author Evan Stoddard
 * @brief 
 */

#include "tlv_decoder.h"
#include <stddef.h>
#include <arpa/inet.h>
#include <string.h>
#include "logging.h"

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

bool tlv_decode(tlv_t *tlv, void *buffer, ssize_t buffer_size) {
    if (tlv == NULL) {
        return false;
    }
    
    if (buffer == NULL) {
        return false;
    }
    
    if (buffer_size < sizeof(tlv_header_t)) {
        return false;
    }
    
    if (tlv != buffer) {
        memcpy(tlv, buffer, sizeof(tlv_t));
    }
    
    tlv->header.length = ntohs(tlv->header.length);
    tlv->header.tag = ntohs(tlv->header.tag);
    
    // Bytes remaining in buffer after TLV header
    ssize_t remaining_bytes = buffer_size - sizeof(tlv_header_t);
    
    if (tlv->header.length) {
        if (remaining_bytes < tlv->header.length) {
            return false;
        }
        
        uint8_t *_buffer = (uint8_t*)buffer;
        tlv->data = &_buffer[sizeof(tlv_header_t)];
    }
    
    return true;
}