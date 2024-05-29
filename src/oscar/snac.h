/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file snac.h
 * @author Evan Stoddard
 * @brief 
 */

#ifndef SNAC_H_
#define SNAC_H_

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

typedef struct snac_t {
    uint16_t foodgroup_id;
    uint16_t subgroup_id;
    uint16_t flags;
    uint32_t request_id;
} __attribute__((packed)) snac_t;

/**
 * @brief Food Group IDs
 * 
 */
typedef enum {
    SNAC_FOOTGROUP_ID_LOCATE        = 0x0002,
    SNAC_FOOTGROUP_ID_OSERVICE      = 0x0001,
    SNAC_FOOTGROUP_ID_BUDDY         = 0x0003,
    SNAC_FOOTGROUP_ID_ICBM          = 0x0004,
    SNAC_FOOTGROUP_ID_ADVERT        = 0x0005,
    SNAC_FOOTGROUP_ID_INVITE        = 0x0006,
    SNAC_FOOTGROUP_ID_ADMIN         = 0x0007,
    SNAC_FOOTGROUP_ID_POPUP         = 0x0008,
    SNAC_FOOTGROUP_ID_PD            = 0x0009,
    SNAC_FOOTGROUP_ID_USER_LOOKUP   = 0x000A,
    SNAC_FOOTGROUP_ID_STATS         = 0x000B,
    SNAC_FOOTGROUP_ID_TRANSLATE     = 0x000C,
    SNAC_FOOTGROUP_ID_CHATNAV       = 0x000D,
    SNAC_FOOTGROUP_ID_CHAT          = 0x000E,
    SNAC_FOOTGROUP_ID_ODIR          = 0x000F,
    SNAC_FOOTGROUP_ID_BART          = 0x0010,
    SNAC_FOOTGROUP_ID_FEEDBAG       = 0x0013,
    SNAC_FOOTGROUP_ID_ICQ           = 0x0015,
    SNAC_FOOTGROUP_ID_BUCP          = 0x0017,
    SNAC_FOOTGROUP_ID_ALERT         = 0x0018,
    SNAC_FOOTGROUP_ID_PLUGIN        = 0x0022,
    SNAC_FOOTGROUP_ID_MDIR          = 0x0025,
    SNAC_FOOTGROUP_ID_ARS           = 0x004A,
} snac_foodgroup_id_t;

/*****************************************************************************
 * Foodgroup Sub IDs
 *****************************************************************************/

/**
 * @brief BUCP Foodgroup Sub IDs
 * 
 */
typedef enum {
    BUCP_ERR                    = 0x0001,
    BUCP_LOGIN_REQUEST          = 0x0002,
    BUCP_LOGIN_RESPONSE         = 0x0003,
    BUCP_REGISTER_REQUEST       = 0x0004,
    BUCP_REGISTER_RESPONSE      = 0x0005,
    BUCP_CHALLENGE_REQUEST      = 0x0006,
    BUCP_CHALLENGE_RESPONSE     = 0x0007,
    BUCP_ASASN_REQUEST          = 0x0008,
    BUCP_ASASN_RESPONSE         = 0x0009,
    BUCP_SECURID_REQUEST        = 0x000A,
    BUCP_SECURID_RESPONSE       = 0x000B,
    BUCP_REGISTRATION_IMAGE     = 0x000C,
    BUCP_REGISTRATION_RESPONSE  = 0x000D,
} bucp_subgroup_id_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* SNAC_H_ */