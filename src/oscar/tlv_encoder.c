/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file tlv_encoder.c
 * @author Evan Stoddard
 * @brief TLV Encoder Module
 */

#include "tlv_encoder.h"

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

/**
 * @brief Encode TLV Header
 * 
 * @param header Pointer to header
 * @param tlv_id ID of TLV
 * @param length Length of TLV
 */
static void prv_tlv_encode_header(tlv_header_t *header, uint16_t tlv_id, uint16_t length);

/*****************************************************************************
 * Private Functions
 *****************************************************************************/

static void prv_tlv_encode_header(tlv_header_t *header, uint16_t tlv_id, uint16_t length) {
    header->tag = htons(tlv_id);
    header->length = htons(length);
}

/*****************************************************************************
 * Public Functions
 *****************************************************************************/

ssize_t tlv_encode_screen_name(tlv_t *tlv, char *screen_name) {
    ssize_t total_size = sizeof(tlv_header_t);
    
    // Determine length of screen name
    size_t payload_len = strlen(screen_name);
    total_size += payload_len;
    
    prv_tlv_encode_header(&tlv->header, TLV_TAG_SCREEN_NAME, payload_len);
    tlv->payload = screen_name;
    
    return total_size;
}

ssize_t tlv_encode_email_address(tlv_t *tlv, char *email_address) {
    ssize_t total_size = sizeof(tlv_header_t);
    
    // Determine length of screen name
    size_t payload_len = strlen(email_address);
    total_size += payload_len;
    
    prv_tlv_encode_header(&tlv->header, TLV_TAG_CLIENT_EMAIL_ADDR, payload_len);
    tlv->payload = email_address;
    
    return total_size;
}

ssize_t tlv_encode_bos_address(tlv_t *tlv, char *bos_address) {
    ssize_t total_size = sizeof(tlv_header_t);
    
    // Determine length of BOS address
    size_t payload_len = strlen(bos_address);
    total_size += payload_len;
    
    prv_tlv_encode_header(&tlv->header, TLV_TAG_BOS_ADDRESS, payload_len);
    tlv->payload = bos_address;
    
    return total_size;
}

ssize_t tlv_encode_login_cookie(tlv_t *tlv, char *login_cookie) {
    ssize_t total_size = sizeof(tlv_header_t);
    
    // Determine length of login cookie
    size_t payload_len = strlen(login_cookie);
    total_size += payload_len;
    
    prv_tlv_encode_header(&tlv->header, TLV_TAG_LOGIN_COOKIE, payload_len);
    tlv->payload = login_cookie;
    
    return total_size;
}