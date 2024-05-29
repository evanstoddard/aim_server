/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file snac_encoder.h
 * @author Evan Stoddard
 * @brief SNAC Encoder Module
 */

#ifndef SNAC_ENCODER_H_
#define SNAC_ENCODER_H_

#include "snac.h"

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
 * @brief 
 * 
 * @param foodgroup_id Foodgroup ID
 * @param subgroup_id Subgroup ID
 * @param flags Flags
 * @param request_id Request ID
 * @return snac_t Encoded snac
 */
snac_t snac_encode(uint16_t foodgroup_id, uint16_t subgroup_id, uint16_t flags, uint32_t request_id);


#ifdef __cplusplus
}
#endif
#endif /* SNAC_ENCODER_H_ */