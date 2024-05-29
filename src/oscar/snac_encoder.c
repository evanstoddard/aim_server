/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file snac_encoder.c
 * @author Evan Stoddard
 * @brief SNAC Encoder Module
 */

#include "snac_encoder.h"
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

/**
 * @brief 
 * 
 * @param foodgroup_id Foodgroup ID
 * @param subgroup_id Subgroup ID
 * @param flags Flags
 * @param request_id Request ID
 * @return snac_t Encoded snac
 */
snac_t snac_encode(uint16_t foodgroup_id, uint16_t subgroup_id, uint16_t flags, uint32_t request_id) {
    snac_t snac;
    
    snac.foodgroup_id = htons(foodgroup_id);
    snac.subgroup_id = htons(subgroup_id);
    snac.flags = htons(flags);
    snac.request_id = htonl(request_id);
    
    return snac;
}