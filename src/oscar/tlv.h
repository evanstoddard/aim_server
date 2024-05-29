/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file tlv.h
 * @author Evan Stoddard
 * @brief TLV Defintion
 */

#ifndef TLV_H_
#define TLV_H_

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

/**
 * @brief Forward declaration of tlv struct
 * 
 */
struct tlv_t;

/**
 * @brief TLV Tag IDs
 * 
 */
typedef enum {
    TLV_TAG_SCREEN_NAME         = 1,
    TLV_TAG_CLIENT_NAME         = 3,
    TLV_TAG_LOGIN_COOKIE        = 6,
    TLV_TAG_MAJOR_VERSION       = 23,
    TLV_TAG_MINOR_VERSION       = 24,
    TLV_TAG_POINT_VERSION       = 25,
    TLV_TAG_BUILD_NUM           = 26,
    TLV_TAG_MULTICONN_FLAGS     = 74,
    TLV_TAG_CLIENT_RECONNECT    = 148,
} tlv_tag_t;

/**
 * @brief TLV Header
 * 
 */
typedef struct tlv_header_t {
    uint16_t tag;
    uint16_t length;
} __attribute__((packed)) tlv_header_t;

/**
 * @brief TLV Definition
 * 
 */
typedef struct tlv_t {
    tlv_header_t header;
    void *data;
} tlv_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* TLV_H_ */