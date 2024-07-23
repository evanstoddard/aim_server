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

#ifdef _cplusplus
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

/**
 * @brief LOCATE Foodgroup Sub IDs
 * 
 */
typedef enum {
    LOCATE_ERR                      = 0x0001,
    LOCATE_RIGHTS_QUERY             = 0x0002,
    LOCATE_RIGHTS_REPLY             = 0x0003,
    LOCATE_SET_INFO                 = 0x0004,
    LOCATE_USER_INFO_QUERY          = 0x0005,
    LOCATE_USER_INFO_REPLY          = 0x0006,
    LOCATE_WATCHER_SUB_REQUEST      = 0x0007,
    LOCATE_WATCHER_NOTIFICATION     = 0x0008,
    LOCATE_SET_DIR_INFO             = 0x0009,
    LOCATE_SET_DIR_REPLY            = 0x000A,
    LOCATE_GET_DIR_INFO             = 0x000B,
    LOCATE_GET_DIR_REPLY            = 0x000C,
    LOCATE_GROUP_CAPABILITY_QUERY   = 0x000D,
    LOCATE_GROUP_CAPABILITY_REPLY   = 0x000E,
    LOCATE_SET_KEYWORD_INFO         = 0x000F,
    LOCATE_SET_KEYWORD_REPLY        = 0x0010,
    LOCATE_GET_KEYWORD_INFO         = 0x0011,
    LOCATE_GET_KEYWORD_REPLY        = 0x0012,
    LOCATE_FIND_LIST_BY_EMAIL       = 0x0013,
    LOCATE_FIND_LIST_REPLY          = 0x0014,
    LOCATE_USER_INFO_QUERY2         = 0x0015,
} locate_subgroup_id_t;

/**
 * @brief Feedback subgroup IDs
 * 
 */
typedef enum {
    FEEDBAG_ERR                            = 0x0001,
    FEEDBAG_RIGHTS_QUERY                   = 0x0002,
    FEEDBAG_RIGHTS_REPLY                   = 0x0003,
    FEEDBAG_QUERY                          = 0x0004,
    FEEDBAG_QUERY_IF_MODIFIED              = 0x0005,
    FEEDBAG_REPLY                          = 0x0006,
    FEEDBAG_USE                            = 0x0007,
    FEEDBAG_INSERT_ITEM                    = 0x0008,
    FEEDBAG_UPDATE_ITEM                    = 0x0009,
    FEEDBAG_DELETE_ITEM                    = 0x000A,
    FEEDBAG_INSERT_CLASS                   = 0x000B,
    FEEDBAG_UPDATE_CLASS                   = 0x000C,
    FEEDBAG_DELETE_CLASS                   = 0x000D,
    FEEDBAG_STATUS                         = 0x000E,
    FEEDBAG_REPLY_NOT_MODIFIED             = 0x000F,
    FEEDBAG_DELETE_USER                    = 0x0010,
    FEEDBAG_START_CLUSTER                  = 0x0011,
    FEEDBAG_END_CLUSTER                    = 0x0012,
    FEEDBAG_AUTHORIZE_BUDDY                = 0x0013,
    FEEDBAG_PRE_AUTHORIZE_BUDDY            = 0x0014,
    FEEDBAG_PRE_AUTHORIZED_BUDDY           = 0x0015,
    FEEDBAG_REMOVE_ME                      = 0x0016,
    FEEDBAG_REMOVE_ME2                     = 0x0017,
    FEEDBAG_REQUEST_AUTHORIZE_TO_HOST      = 0x0018,
    FEEDBAG_REQUEST_AUTHORIZE_TO_CLIENT    = 0x0019,
    FEEDBAG_RESPOND_AUTHORIZE_TO_HOST      = 0x001A,
    FEEDBAG_RESPOND_AUTHORIZE_TO_CLIENT    = 0x001B,
    FEEDBAG_BUDDY_ADDED                    = 0x001C,
    FEEDBAG_REQUEST_AUTHORIZE_TO_BADOG     = 0x001D,
    FEEDBAG_RESPOND_AUTHORIZE_TO_BADOG     = 0x001E,
    FEEDBAG_BUDDY_ADDED_TO_BADOG           = 0x001F,
    FEEDBAG_TEST_SNAC                      = 0x0021,
    FEEDBAG_FORWARD_MSG                    = 0x0022,
    FEEDBAG_IS_AUTH_REQUIRED_QUERY         = 0x0023,
    FEEDBAG_IS_AUTH_REQUIRED_REPLY         = 0x0024,
    FEEDBAG_RECENT_BUDDY_UPDATE            = 0x0025,
} feedback_subgroup_id_t;

/**
 * @brief ICBM SNAC Subgroup IDs
 * 
 */
typedef enum {
    ICBM_ERR                    = 0x0001,
    ICBM_ADD_PARAMETERS         = 0x0002,
    ICBM_DEL_PARAMETERS         = 0x0003,
    ICBM_PARAMETER_QUERY        = 0x0004,
    ICBM_PARAMETER_REPLY        = 0x0005,
    ICBM_CHANNEL_MSG_TOHOST     = 0x0006,
    ICBM_CHANNEL_MSG_TOCLIENT   = 0x0007,
    ICBM_EVIL_REQUEST           = 0x0008,
    ICBM_EVIL_REPLY             = 0x0009,
    ICBM_MISSED_CALLS           = 0x000A,
    ICBM_CLIENT_ERR             = 0x000B,
    ICBM_HOST_ACK               = 0x000C,
    ICBM_SIN_STORED             = 0x000D,
    ICBM_SIN_LIST_QUERY         = 0x000E,
    ICBM_SIN_LIST_REPLY         = 0x000F,
    ICBM_SIN_RETRIEVE           = 0x0010,
    ICBM_SIN_DELETE             = 0x0011,
    ICBM_NOTIFY_REQUEST         = 0x0012,
    ICBM_NOTIFY_REPLY           = 0x0013,
    ICBM_CLIENT_EVENT           = 0x0014,
    ICBM_SIN_REPLY              = 0x0017,
} icbm_subgroup_id_t;

/**
 * @brief BUDDY SNAC Subgroup ID
 * 
 */
typedef enum {
    BUDDY_ERR                      = 0x0001,
    BUDDY_RIGHTS_QUERY             = 0x0002,
    BUDDY_RIGHTS_REPLY             = 0x0003,
    BUDDY_ADD_BUDDIES              = 0x0004,
    BUDDY_DEL_BUDDIES              = 0x0005,
    BUDDY_WATCHER_LIST_QUERY       = 0x0006,
    BUDDY_WATCHER_LIST_RESPONSE    = 0x0007,
    BUDDY_WATCHER_SUB_REQUEST      = 0x0008,
    BUDDY_WATCHER_NOTIFICATION     = 0x0009,
    BUDDY_REJECT_NOTIFICATION      = 0x000A,
    BUDDY_ARRIVED                  = 0x000B,
    BUDDY_DEPARTED                 = 0x000C,
    BUDDY_ADD_TEMP_BUDDIES         = 0x000F,
    BUDDY_DEL_TEMP_BUDDIES         = 0x0010,
 } buddy_subgroup_id_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef _cplusplus
}
#endif
#endif /* SNAC_H_ */