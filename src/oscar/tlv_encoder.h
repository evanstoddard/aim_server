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
#include <unistd.h>

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
 * @brief Encode screenname TLV
 * 
 * @param tlv Pointer to TLV struct
 * @param screen_name Screenname
 * @return ssize_t Size of final payload
 */
ssize_t tlv_encode_screen_name(tlv_t *tlv, char *screen_name);

/**
 * @brief 
 * 
 * @param tlv 
 * @param bos_address 
 * @return ssize_t 
 */
ssize_t tlv_encode_bos_address(tlv_t *tlv, char *bos_address);

/**
 * @brief 
 * 
 * @param tlv 
 * @param login_cookie 
 * @return ssize_t 
 */
ssize_t tlv_encode_login_cookie(tlv_t *tlv, char *login_cookie);

/**
 * @brief 
 * 
 */
ssize_t tlv_encode_email_address(tlv_t *tlv, char *email_address);

#ifdef __cplusplus
}
#endif
#endif /* TLV_ENCODER_H_ */