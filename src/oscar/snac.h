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
    SNAC_FOODGROUP_ID_OSERVICE      = 0x0001,
    SNAC_FOODGROUP_ID_LOCATE        = 0x0002,
    SNAC_FOODGROUP_ID_BUDDY         = 0x0003,
    SNAC_FOODGROUP_ID_ICBM          = 0x0004,
    SNAC_FOODGROUP_ID_ADVERT        = 0x0005,
    SNAC_FOODGROUP_ID_INVITE        = 0x0006,
    SNAC_FOODGROUP_ID_ADMIN         = 0x0007,
    SNAC_FOODGROUP_ID_POPUP         = 0x0008,
    SNAC_FOODGROUP_ID_PD            = 0x0009,
    SNAC_FOODGROUP_ID_USER_LOOKUP   = 0x000A,
    SNAC_FOODGROUP_ID_STATS         = 0x000B,
    SNAC_FOODGROUP_ID_TRANSLATE     = 0x000C,
    SNAC_FOODGROUP_ID_CHATNAV       = 0x000D,
    SNAC_FOODGROUP_ID_CHAT          = 0x000E,
    SNAC_FOODGROUP_ID_ODIR          = 0x000F,
    SNAC_FOODGROUP_ID_BART          = 0x0010,
    SNAC_FOODGROUP_ID_FEEDBAG       = 0x0013,
    SNAC_FOODGROUP_ID_ICQ           = 0x0015,
    SNAC_FOODGROUP_ID_BUCP          = 0x0017,
    SNAC_FOODGROUP_ID_ALERT         = 0x0018,
    SNAC_FOODGROUP_ID_PLUGIN        = 0x0022,
    SNAC_FOODGROUP_ID_MDIR          = 0x0025,
    SNAC_FOODGROUP_ID_ARS           = 0x004A,
} snac_foodgroup_id_t;

/*****************************************************************************
 * Foodgroup Sub IDs
 *****************************************************************************/

/**
 * @brief OSERVICE Foodgroup Sub IDs
 * 
 */
typedef enum {  
    OSERVICE_ERR                    = 0x0001,
    OSERVICE_CLIENT_ONLINE          = 0x0002,
    OSERVICE_HOST_ONLINE            = 0x0003,
    OSERVICE_SERVICE_REQUEST        = 0x0004,
    OSERVICE_SERVICE_RESPONSE       = 0x0005,
    OSERVICE_RATE_PARAMS_QUERY      = 0x0006,
    OSERVICE_RATE_PARAMS_REPLY      = 0x0007,
    OSERVICE_RATE_PARAMS_SUB_ADD    = 0x0008,
    OSERVICE_RATE_DEL_PARAM_SUB     = 0x0009,
    OSERVICE_RATE_PARAM_CHANGE      = 0x000A,
    OSERVICE_PAUSE_REQ              = 0x000B,
    OSERVICE_PAUSE_ACK              = 0x000C,
    OSERVICE_RESUME                 = 0x000D,
    OSERVICE_USER_INFO_QUERY        = 0x000E,
    OSERVICE_USER_INFO_UPDATE       = 0x000F,
    OSERVICE_EVIL_NOTIFICATION      = 0x0010,
    OSERVICE_IDLE_NOTIFICATION      = 0x0011,
    OSERVICE_MIGRATE_GROUPS         = 0x0012,
    OSERVICE_MOTD                   = 0x0013,
    OSERVICE_SET_PRIVACY_FLAGS      = 0x0014,
    OSERVICE_WELL_KNOWN_URLS        = 0x0015,
    OSERVICE_NOOP                   = 0x0016,
    OSERVICE_CLIENT_VERSIONS        = 0x0017,
    OSERVICE_HOST_VERSIONS          = 0x0018,
    OSERVICE_MAX_CONFIG_QUERY       = 0x0019,
    OSERVICE_MAX_CONFIG_REPLY       = 0x001A,
    OSERVICE_STORE_CONFIG           = 0x001B,
    OSERVICE_CONFIG_QUERY           = 0x001C,
    OSERVICE_CONFIG_REPLY           = 0x001D,
    OSERVICE_SET_USERINFO_FIELDS    = 0x001E,
    OSERVICE_PROBE_REQ              = 0x001F,
    OSERVICE_PROBE_ACK              = 0x0020,
    OSERVICE_BART_REPLY             = 0x0021,
    OSERVICE_BART_QUERY2            = 0x0022,
    OSERVICE_BART_REPLY2            = 0x0023,
} oservice_subgroup_id_t;

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