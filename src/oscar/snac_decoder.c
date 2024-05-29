/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file snac_decoder.c
 * @author Evan Stoddard
 * @brief SNAC Payload Decoder
 */

#include "snac_decoder.h"
#include <stddef.h>
#include <arpa/inet.h>
#include <string.h>

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

bool snac_decode(snac_t *snac, void *buffer, ssize_t buffer_size) {
    
    if (snac == NULL) {
        return false;
    }
    
    if (buffer == NULL) {
        return false;
    }
    
    if (buffer_size < sizeof(snac_t)) {
        return false;
    }
    
    if (snac != buffer) {
        memcpy(snac, buffer, sizeof(snac_t));
    }
    
    snac->foodgroup_id = ntohs(snac->foodgroup_id);
    snac->subgroup_id = ntohs(snac->subgroup_id);
    snac->flags = ntohs(snac->flags);
    snac->request_id = ntohl(snac->flags);
    
    return true;
}