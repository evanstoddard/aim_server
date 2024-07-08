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
#include <stdbool.h>

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

/*
 * TODO: Annoyingly, TLV tag IDs are reused... is there a better 
 * solution to this?
 */

/**
 * @brief TLV Tag IDs
 * 
 */
typedef enum {
    TLV_TAG_SCREEN_NAME         = 0x1,
    TLV_TAG_USER_CLASS          = 0x1,
    TLV_TAG_CLIENT_NAME         = 0x3,
    TLV_TAG_SIGNON_TIME         = 0x3,
    TLV_TAG_BOS_ADDRESS         = 0x5,
    TLV_TAG_MEMBER_SINCE        = 0x5,
    TLV_TAG_LOGIN_COOKIE        = 0x6,
    TLV_TAG_USER_STATUS         = 0x6,
    TLV_TAG_EXT_IP_ADDR         = 0xA,
    TLV_TAG_CLIENT_COUNTRY      = 0xE,
    TLV_TAG_CLIENT_LANG         = 0xF,
    TLV_TAG_CLIENT_IDLE_TIME    = 0xF,
    TLV_TAG_CLIENT_EMAIL_ADDR   = 0x11,
    TLV_TAG_DIST_NUMBER         = 0x14,
    TLV_TAG_CLIENT_ID           = 0x16,
    TLV_TAG_VERSION_MAJOR       = 0x17,
    TLV_TAG_VERSION_MINOR       = 0x18,
    TLV_TAG_VERSION_LESSER      = 0x19,
    TLV_TAG_UNDEFINED           = 0x1E, // This is unknown... not denoting unknown
    TLV_TAG_BUILD_NUM           = 0x1A,
    TLV_TAG_MD5_HASHED_PASSWORD = 0x25,
    TLV_TAG_SSI_FLAG            = 0x4A,
    TLV_TAG_CLIENT_RECONNECT    = 0x148,
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
 * @brief uint16_t tlv
 * 
 */
typedef struct tlv_uint16_t {
    tlv_header_t header;
    uint16_t val;
} __attribute__((packed)) tlv_uint16_t;

/**
 * @brief uint32_t tlv
 * 
 */
typedef struct tlv_uint32_t {
    tlv_header_t header;
    uint32_t val;
} __attribute__((packed)) tlv_uint32_t;

/**
 * @brief TLV Definition
 * 
 */
typedef struct tlv_t {
    tlv_header_t header;
    void *payload;
} tlv_t;

/*****************************************************************************
 * Fixed Size TLV Payload Definitions
 *****************************************************************************/

/**
 * @brief Client ID TLV
 * 
 */
typedef struct tlv_client_id_f_t {
    uint16_t client_id;
} __attribute__((packed)) tlv_client_id_f_t;

/**
 * @brief Client Version Major TLV
 * 
 */
typedef struct tlv_client_version_major_f_t {
    uint16_t version_major;
} __attribute__((packed)) tlv_client_version_major_f_t;

/**
 * @brief Client Version Minor TLV
 * 
 */
typedef struct tlv_client_version_minor_f_t {
    uint16_t version_minor;
} __attribute__((packed)) tlv_client_version_minor_f_t;

/**
 * @brief Client Version Lesser TLV
 * 
 */
typedef struct tlv_client_version_lesser_f_t {
    uint16_t version_lesser;
} __attribute__((packed)) tlv_client_version_lesser_f_t;

/**
 * @brief Client Build Number TLV
 * 
 */
typedef struct tlv_client_build_number_f_t {
    uint16_t build_number;
} __attribute__((packed)) tlv_client_build_number_f_t;

/**
 * @brief Client Distribution Number TLV
 * 
 */
typedef struct tlv_client_dist_number_f_t {
    uint16_t dist_number;
} __attribute__((packed)) tlv_client_dist_number_f_t;

/**
 * @brief Client Language TLV
 * 
 */
typedef struct tlv_client_language_f_t {
    char language[2];
} __attribute__((packed)) tlv_client_language_f_t;

/**
 * @brief Client Country TLV
 * 
 */
typedef struct tlv_client_country_f_t {
    char country[2];
} __attribute__((packed)) tlv_client_country_f_t;

/**
 * @brief Client SSI Flag TLV
 * 
 */
typedef struct tlv_client_ssi_flag_f_t {
    uint8_t ssi_flag;
} __attribute__((packed)) tlv_client_ssi_flag_f_t;

/*****************************************************************************
 * Dynamic Size TLV Payload Definitions
 *****************************************************************************/

/**
 * @brief Screen name TLV
 * 
 */
typedef struct tlv_screen_name_d_t {
    char *screen_name;
} tlv_screen_name_d_t;

/**
 * @brief Client ID String TLV
 * 
 */
typedef struct tlv_client_id_str_d_t {
    char *client_id_str;
} tlv_client_id_str_d_t;

/**
 * @brief MD5 Hashed Password
 * 
 */
typedef struct tlv_md5_hashed_password_d_t {
    char *hashed_password;
} tlv_md5_hashed_password_d_t;

#ifdef __cplusplus
}
#endif
#endif /* TLV_H_ */