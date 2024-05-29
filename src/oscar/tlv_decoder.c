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

/**
 * @brief Decode payload of TLV
 * 
 * @param id TLV ID
 * @param buffer Buffer of payload
 */
static void prv_tlv_decode_payload(uint16_t id, void *buffer);

/**
 * @brief Decode client ID TLV
 * 
 * @param buffer Buffer
 */
static void prv_tlv_decode_client_id(void *buffer);

/**
 * @brief Decode client version major
 * 
 * @param buffer Buffer
 */
static void prv_tlv_decode_client_version_major(void *buffer);

/**
 * @brief Decode client version minor
 * 
 * @param buffer Buffer
 */
static void prv_tlv_decode_client_version_minor(void *buffer);

/**
 * @brief Decode client version lesser
 * 
 * @param buffer Buffer
 */
static void prv_tlv_decode_client_version_lesser(void *buffer);

/**
 * @brief Decode client build number
 * 
 * @param buffer Buffer
 */
static void prv_tlv_decode_client_build_number(void *buffer);

/**
 * @brief Decode client distribution number
 * 
 * @param buffer Buffer
 */
static void prv_tlv_decode_client_dist_number(void *buffer);

/**
 * @brief Decode client language
 * 
 * @param buffer Buffer
 */
static void prv_tlv_decode_client_language(void *buffer);

/**
 * @brief Decode client country
 * 
 * @param buffer Buffer
 */
static void prv_tlv_decode_client_country(void *buffer);

/**
 * @brief Decode client SSI Flag
 * 
 * @param buffer Buffer
 */
static void prv_tlv_decode_client_ssi_flag(void *buffer);

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
    
    // Parse payload if one exists (I've seen 0 length TLVs before...)
    if (tlv->header.length) {
        
        // Ensure there are enough bytes to cover reported payload size
        if (remaining_bytes < tlv->header.length) {
            return false;
        }
        
        // Get pointer to buffer at TLV payload
        void *_buffer = buffer + sizeof(tlv_header_t);
        tlv->payload = _buffer;
        
        // Decode payload
        prv_tlv_decode_payload(tlv->header.tag, _buffer);
    }
    
    return true;
}

static void prv_tlv_decode_payload(uint16_t id, void *buffer) {
    switch(id) {
    case TLV_TAG_CLIENT_ID:
        prv_tlv_decode_client_id(buffer);
        break;
    case TLV_TAG_VERSION_MAJOR:
        prv_tlv_decode_client_version_major(buffer);
        break;
    case TLV_TAG_VERSION_MINOR:
        prv_tlv_decode_client_version_minor(buffer);
        break;
    case TLV_TAG_VERSION_LESSER:
        prv_tlv_decode_client_version_lesser(buffer);
        break;
    case TLV_TAG_BUILD_NUM:
        prv_tlv_decode_client_build_number(buffer);
        break;
    case TLV_TAG_DIST_NUMBER:
        prv_tlv_decode_client_dist_number(buffer);
        break;
        break;
    default:
        break;
    }
}

static void prv_tlv_decode_client_id(void *buffer) {
    tlv_client_id_f_t *payload = (tlv_client_id_f_t *)buffer;
    payload->client_id = ntohs(payload->client_id);
}

static void prv_tlv_decode_client_version_major(void *buffer) {
    tlv_client_version_major_f_t *payload = (tlv_client_version_major_f_t *)buffer;
    payload->version_major = ntohs(payload->version_major);
}

static void prv_tlv_decode_client_version_minor(void *buffer) {
    tlv_client_version_minor_f_t *payload = (tlv_client_version_minor_f_t *)buffer;
    payload->version_minor = ntohs(payload->version_minor);
}

static void prv_tlv_decode_client_version_lesser(void *buffer) {
    tlv_client_version_lesser_f_t *payload = (tlv_client_version_lesser_f_t *)buffer;
    payload->version_lesser = ntohs(payload->version_lesser);
}

static void prv_tlv_decode_client_build_number(void *buffer) {
    tlv_client_build_number_f_t *payload = (tlv_client_build_number_f_t *)buffer;
    payload->build_number = ntohs(payload->build_number);
}

static void prv_tlv_decode_client_dist_number(void *buffer) {
    tlv_client_dist_number_f_t *payload = (tlv_client_dist_number_f_t *)buffer;
    payload->dist_number = ntohs(payload->dist_number);
}