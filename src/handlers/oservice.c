/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file oservice.c
 * @author Evan Stoddard
 * @brief OSERVICE SNAC Foodgroup Handlers
 */

#include "oservice.h"

#include "oscar/snac.h"
#include "oscar/snac_encoder.h"
#include "oscar/snac_decoder.h"

#include "oscar/flap_encoder.h"
#include "oscar/flap_decoder.h"

#include "oscar/tlv.h"
#include "oscar/tlv_encoder.h"
#include "oscar/tlv_decoder.h"

#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "logging.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

// TODO: Move this somewhere else?

/**
 * @brief Struct to define snac version
 * 
 */
typedef struct snac_version_t {
    uint16_t snac_id;
    uint16_t version;
} snac_version_t;

/**
 * @brief Definition of rate parameters
 * 
 */
typedef struct rate_params_t {
    uint16_t class_id;
    uint32_t window_size;
    uint32_t clear_threshold;
    uint32_t alert_threshold;
    uint32_t limit_threshold;
    uint32_t disconnect_threshold;
    uint32_t current_average;
    uint32_t max_average;
    uint32_t last_arrival_delta;
    uint8_t dropping_snacs;
} __attribute__((packed)) rate_params_t;

/**
 * @brief Rate Class Members header
 * 
 */
typedef struct rate_class_members_t {
    uint16_t id;
    uint16_t num_members;
} __attribute__((packed)) rate_class_members_t;

/*****************************************************************************
 * Variables
 *****************************************************************************/

// TODO: Move this somewhere else?
/**
 * @brief SNACs supported by the server
 * 
 */
static uint16_t prv_oservice_supported_snacs[] = {
    SNAC_FOODGROUP_ID_OSERVICE,
    SNAC_FOODGROUP_ID_FEEDBAG,
    SNAC_FOODGROUP_ID_LOCATE,
    SNAC_FOODGROUP_ID_OSERVICE,
    SNAC_FOODGROUP_ID_ICBM,
    SNAC_FOODGROUP_ID_INVITE,
    SNAC_FOODGROUP_ID_USER_LOOKUP,
    SNAC_FOODGROUP_ID_CHAT,
    SNAC_FOODGROUP_ID_BART    
};

// TODO: Move this somewhere else?
/**
 * @brief List of supported SNACs and their version number
 * 
 */
static snac_version_t prv_oservice_snac_versions[] = {
    {
        .snac_id = SNAC_FOODGROUP_ID_OSERVICE,
        .version = 0x3,
    },
    {
        .snac_id = SNAC_FOODGROUP_ID_FEEDBAG,
        .version = 0x3,
    },
    {
        .snac_id = SNAC_FOODGROUP_ID_LOCATE,
        .version = 0x1,
    },
    {
        .snac_id = SNAC_FOODGROUP_ID_OSERVICE,
        .version = 0x1,
    },
    {
        .snac_id = SNAC_FOODGROUP_ID_ICBM,
        .version = 0x1,
    },
    {
        .snac_id = SNAC_FOODGROUP_ID_INVITE,
        .version = 0x1,
    },
    {
        .snac_id = SNAC_FOODGROUP_ID_USER_LOOKUP,
        .version = 0x1,
    },
    {
        .snac_id = SNAC_FOODGROUP_ID_CHAT,
        .version = 0x1,
    },
    {
        .snac_id = SNAC_FOODGROUP_ID_BART,
        .version = 0x1,
    },
};

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/**
 * @brief Send supported SNACs and versions
 * 
 * @param conn Connection
 */
void prv_oserver_send_host_versions(connection_t *conn);

/**
 * @brief Send response to rate params query
 * 
 * @param conn Connection
 */
void prv_oserver_send_rate_params_response(connection_t *conn);

/**
 * @brief Send user info query response
 * 
 * @param conn Connection
 */
void prv_oserver_send_user_info_repsonse(connection_t *conn);

/*****************************************************************************
 * Private Functions
 *****************************************************************************/

/*****************************************************************************
 * Handlers
 *****************************************************************************/

/**
 * @brief Handle client versions message
 * 
 * @param conn Connection
 * @param frame Frame
 */
void prv_oservice_handle_client_versions(connection_t *conn, frame_t *frame) {
    // TODO: Do something with the received version list...
    prv_oserver_send_host_versions(conn);
}

/**
 * @brief Handle rate params query
 * 
 * @param conn Connection
 * @param frame Frame
 */
void prv_oservice_handle_rate_params_query(connection_t *conn, frame_t *frame) {
    // Send response
    prv_oserver_send_rate_params_response(conn);
}

/**
 * @brief Handle uder info query
 * 
 * @param conn Connection
 * @param frame Frame
 */
void prv_oserver_handle_user_info_query(connection_t *conn, frame_t *frame) {
    prv_oserver_send_user_info_repsonse(conn);
}

/*****************************************************************************
 * Responses
 *****************************************************************************/

void prv_oserver_send_host_versions(connection_t *conn) {
    size_t frame_size = sizeof(flap_t);
    frame_size += sizeof(snac_t);
    frame_size += sizeof(prv_oservice_snac_versions);
    
    uint8_t *buffer = malloc(frame_size);
    
    if (buffer == NULL) {
        LOG_ERR("Unable to malloc output buffer. Out of memory?");
        connection_close(conn);
    }
    
    snac_version_t *version_arr = (snac_version_t *)&buffer[sizeof(flap_t) + sizeof(snac_t)];
    memcpy(version_arr, prv_oservice_snac_versions, sizeof(prv_oservice_snac_versions));
    
    for (uint32_t i = 0; i < (sizeof(prv_oservice_supported_snacs)/sizeof(snac_version_t)); i++) {
        version_arr[i].snac_id = htonl(version_arr[i].snac_id);
        version_arr[i].version = htonl(version_arr[i].version);
    }
    
    conn->last_outbound_seq_num++;
    flap_t flap = flap_encode(FLAP_FRAME_TYPE_DATA, conn->last_outbound_seq_num, frame_size - sizeof(flap));
    
    snac_t snac = snac_encode(SNAC_FOODGROUP_ID_OSERVICE, OSERVICE_HOST_VERSIONS, 0, 0);
    
    memcpy(buffer, &flap, sizeof(flap));
    memcpy(&buffer[sizeof(flap_t)], &snac, sizeof(snac));
    
    connection_write(conn, buffer, frame_size);
    
    free(buffer);
}

/*
 * TODO: Move this data to the server instance and dynamically bring it in.
 */
void prv_oserver_send_rate_params_response(connection_t *conn) {
    size_t frame_size = sizeof(flap_t);
    frame_size += sizeof(snac_t);
    
    uint16_t payload_size = frame_size - sizeof(flap_t);
    
    // TODO: Actually implement rate limiting
    snac_t snac = snac_encode(SNAC_FOODGROUP_ID_OSERVICE, OSERVICE_RATE_PARAMS_REPLY, 0, 0);
    
    // Create rate params
    rate_params_t params;
    params.class_id = htons(1);
    params.window_size = 0xFFFF;
    params.clear_threshold = htonl(10);
    params.alert_threshold = htonl(100);
    params.limit_threshold = htonl(50);
    params.disconnect_threshold = htonl(200);
    params.current_average = htonl(0);
    params.max_average = htonl(100);
    params.last_arrival_delta = htonl(100);
    params.dropping_snacs = 0;
    
    frame_size += sizeof(rate_params_t) + sizeof(uint32_t);
    payload_size += sizeof(rate_params_t) + sizeof(uint32_t);
    
    // Create class member header
    rate_class_members_t class_members;
    class_members.id = htons(1);
    class_members.num_members = htons(sizeof(prv_oservice_supported_snacs)/sizeof(uint16_t));
    
    frame_size += sizeof(rate_class_members_t);
    payload_size += sizeof(rate_class_members_t);
    
    // Create buffer
    uint16_t num_members = sizeof(prv_oservice_supported_snacs)/sizeof(uint16_t);
    frame_size += sizeof(prv_oservice_supported_snacs);
    payload_size += sizeof(prv_oservice_supported_snacs);
    uint8_t *buffer = malloc(frame_size);
    
    if (buffer == NULL) {
        LOG_ERR("Unable to malloc output buffer. Out of memory?");
        connection_close(conn);
        return;
    }
    
    // Create flap
    conn->last_outbound_seq_num++;
    flap_t flap = flap_encode(FLAP_FRAME_TYPE_DATA, conn->last_outbound_seq_num, payload_size);
    
    size_t offset = 0;
    memcpy(&buffer[offset], &flap, sizeof(flap_t));
    offset += sizeof(flap_t);
    
    memcpy(&buffer[offset], &snac, sizeof(snac_t));
    offset += sizeof(snac_t);
    
    uint32_t *num_rate_classes = (uint32_t *)&buffer[offset];
    *num_rate_classes = htonl(1);
    offset += sizeof(uint32_t);
    
    memcpy(&buffer[offset], &params, sizeof(rate_params_t));
    offset += sizeof(rate_params_t);
    
    memcpy(&buffer[offset], &class_members, sizeof(rate_class_members_t));
    offset += sizeof(rate_class_members_t);
    
    memcpy(&buffer[offset], prv_oservice_supported_snacs, sizeof(prv_oservice_supported_snacs));
    
    uint16_t *members = (uint16_t*)&buffer[offset];
    for (uint32_t i = 0; i < num_members; i++) {
        members[i] = htons(members[i]);
    }
   
    connection_write(conn, buffer, frame_size);
    
    free(buffer);
}

void prv_oserver_send_user_info_repsonse(connection_t *conn) {
    size_t frame_size = sizeof(flap_t);
    frame_size += sizeof(snac_t);
    
    uint16_t payload_size = frame_size - sizeof(flap_t);
    
    // TODO: Actually implement rate limiting
    snac_t snac = snac_encode(SNAC_FOODGROUP_ID_OSERVICE, OSERVICE_USER_INFO_UPDATE, 0, 0);
    
    char uin[] = "neatoaspeedo";
    
    // UIN payload
    uint8_t uin_len = sizeof(uin) - 1;
    payload_size += sizeof(uint8_t);
    frame_size += sizeof(uint8_t);
    
    payload_size += uin_len;
    frame_size += uin_len;
    
    // Warning level
    uint16_t warning_level = 0;
    payload_size += sizeof(uint16_t);
    frame_size += sizeof(uint16_t);
    
    // TLV Count
    uint16_t tlv_count = 0;
    payload_size += sizeof(uint16_t);
    frame_size += sizeof(uint16_t);

    tlv_uint32_t user_class_tlv = tlv_uint32_encode(0x1, 0x100);
    tlv_count++;
    payload_size += sizeof(tlv_uint32_t);
    frame_size += sizeof(tlv_uint32_t);
    
    tlv_uint32_t user_status_tlv = tlv_uint32_encode(0x6, 0x0);
    tlv_count++;
    payload_size += sizeof(tlv_uint32_t);
    frame_size += sizeof(tlv_uint32_t);
    
    tlv_uint32_t ext_ip_addr_tlv = tlv_uint32_encode(0x0A, 0x0);
    tlv_count++;
    payload_size += sizeof(tlv_uint32_t);
    frame_size += sizeof(tlv_uint32_t);
    
    tlv_uint32_t client_idle_time_tlv = tlv_uint32_encode(0x0F, 0x0);
    tlv_count++;
    payload_size += sizeof(tlv_uint32_t);
    frame_size += sizeof(tlv_uint32_t);
    
    tlv_uint32_t client_signon_time_tlv = tlv_uint32_encode(0x03, 0x0);
    tlv_count++;
    payload_size += sizeof(tlv_uint32_t);
    frame_size += sizeof(tlv_uint32_t);
    
    tlv_uint32_t unknown_tlv = tlv_uint32_encode(0x1E, 0x0);
    tlv_count++;
    payload_size += sizeof(tlv_uint32_t);
    frame_size += sizeof(tlv_uint32_t);
    
    tlv_uint32_t member_since_tlv = tlv_uint32_encode(0x05, 0x0);
    tlv_count++;
    payload_size += sizeof(tlv_uint32_t);
    frame_size += sizeof(tlv_uint32_t);
    
    conn->last_outbound_seq_num++;
    flap_t flap = flap_encode(FLAP_FRAME_TYPE_DATA, conn->last_outbound_seq_num, payload_size);
    
    uint8_t *buffer = malloc(frame_size);
    if (buffer == NULL) {
        LOG_ERR("Unable to alloc output buffer. Out of memory?");
        connection_close(conn);
        return;
    }
    
    uint32_t offset = 0;
    
    memcpy(&buffer[offset], &flap, sizeof(flap));
    offset += sizeof(flap);
    
    memcpy(&buffer[offset], &snac, sizeof(snac));
    offset += sizeof(snac);
    
    memcpy(&buffer[offset], &uin_len, sizeof(uin_len));
    offset += sizeof(uin_len);
    
    memcpy(&buffer[offset], uin, uin_len);
    offset += uin_len;
    
    memcpy(&buffer[offset], &warning_level, sizeof(warning_level));
    offset += sizeof(warning_level);
    
    tlv_count = htons(tlv_count);
    memcpy(&buffer[offset], &tlv_count, sizeof(tlv_count));
    offset += sizeof(tlv_count);
    
    memcpy(&buffer[offset], &user_class_tlv, sizeof(user_class_tlv));
    offset += sizeof(user_class_tlv);
    
    memcpy(&buffer[offset], &user_status_tlv, sizeof(user_status_tlv));
    offset += sizeof(user_status_tlv);
    
    memcpy(&buffer[offset], &ext_ip_addr_tlv, sizeof(ext_ip_addr_tlv));
    offset += sizeof(ext_ip_addr_tlv);
    
    memcpy(&buffer[offset], &client_idle_time_tlv, sizeof(client_idle_time_tlv));
    offset += sizeof(client_idle_time_tlv);
    
    memcpy(&buffer[offset], &client_signon_time_tlv, sizeof(client_signon_time_tlv));
    offset += sizeof(client_signon_time_tlv);
    
    memcpy(&buffer[offset], &unknown_tlv, sizeof(unknown_tlv));
    offset += sizeof(unknown_tlv);
    
    memcpy(&buffer[offset], &member_since_tlv, sizeof(member_since_tlv));
    offset += sizeof(member_since_tlv);
    
    connection_write(conn, buffer, frame_size);
    free(buffer);
}

/*****************************************************************************
 * Public Functions
 *****************************************************************************/

void oservice_handle_frame(connection_t *conn, frame_t *frame) {
    switch(frame->snac.subgroup_id) {
    case OSERVICE_ERR:
        // TODO: Implement OSERVICE_ERR
        LOG_INFO("OSERVICE_ERR handler not implemented.");
        break;
    case OSERVICE_CLIENT_ONLINE:
        // TODO: Implement OSERVICE_CLIENT_ONLINE
        LOG_INFO("OSERVICE_CLIENT_ONLINE handler not implemented.");
        break;
    case OSERVICE_HOST_ONLINE:
        // TODO: Implement OSERVICE_HOST_ONLINE
        LOG_INFO("OSERVICE_HOST_ONLINE handler not implemented.");
        break;
    case OSERVICE_SERVICE_REQUEST:
        // TODO: Implement OSERVICE_SERVICE_REQUEST
        LOG_INFO("OSERVICE_SERVICE_REQUEST handler not implemented.");
        break;
    case OSERVICE_SERVICE_RESPONSE:
        // TODO: Implement OSERVICE_SERVICE_RESPONSE
        LOG_INFO("OSERVICE_SERVICE_RESPONSE handler not implemented.");
        break;
    case OSERVICE_RATE_PARAMS_QUERY:
        prv_oservice_handle_rate_params_query(conn, frame);
        break;
    case OSERVICE_RATE_PARAMS_REPLY:
        // TODO: Implement OSERVICE_RATE_PARAMS_REPLY
        LOG_INFO("OSERVICE_RATE_PARAMS_REPLY handler not implemented.");
        break;
    case OSERVICE_RATE_PARAMS_SUB_ADD:
        // TODO: Implement OSERVICE_RATE_PARAMS_SUB_ADD
        LOG_INFO("OSERVICE_RATE_PARAMS_SUB_ADD handler not implemented.");
        break;
    case OSERVICE_RATE_DEL_PARAM_SUB:
        // TODO: Implement OSERVICE_RATE_DEL_PARAM_SUB
        LOG_INFO("OSERVICE_RATE_DEL_PARAM_SUB handler not implemented.");
        break;
    case OSERVICE_RATE_PARAM_CHANGE:
        // TODO: Implement OSERVICE_RATE_PARAM_CHANGE
        LOG_INFO("OSERVICE_RATE_PARAM_CHANGE handler not implemented.");
        break;
    case OSERVICE_PAUSE_REQ:
        // TODO: Implement OSERVICE_PAUSE_REQ
        LOG_INFO("OSERVICE_PAUSE_REQ handler not implemented.");
        break;
    case OSERVICE_PAUSE_ACK:
        // TODO: Implement OSERVICE_PAUSE_ACK
        LOG_INFO("OSERVICE_PAUSE_ACK handler not implemented.");
        break;
    case OSERVICE_RESUME:
        // TODO: Implement OSERVICE_RESUME
        LOG_INFO("OSERVICE_RESUME handler not implemented.");
        break;
    case OSERVICE_USER_INFO_QUERY:
        prv_oserver_handle_user_info_query(conn, frame);
        break;
    case OSERVICE_USER_INFO_UPDATE:
        // TODO: Implement OSERVICE_USER_INFO_UPDATE
        LOG_INFO("OSERVICE_USER_INFO_UPDATE handler not implemented.");
        break;
    case OSERVICE_EVIL_NOTIFICATION:
        // TODO: Implement OSERVICE_EVIL_NOTIFICATION
        LOG_INFO("OSERVICE_EVIL_NOTIFICATION handler not implemented.");
        break;
    case OSERVICE_IDLE_NOTIFICATION:
        // TODO: Implement OSERVICE_IDLE_NOTIFICATION
        LOG_INFO("OSERVICE_IDLE_NOTIFICATION handler not implemented.");
        break;
    case OSERVICE_MIGRATE_GROUPS:
        // TODO: Implement OSERVICE_MIGRATE_GROUPS
        LOG_INFO("OSERVICE_MIGRATE_GROUPS handler not implemented.");
        break;
    case OSERVICE_MOTD:
        // TODO: Implement OSERVICE_MOTD
        LOG_INFO("OSERVICE_MOTD handler not implemented.");
        break;
    case OSERVICE_SET_PRIVACY_FLAGS:
        // TODO: Implement OSERVICE_SET_PRIVACY_FLAGS
        LOG_INFO("OSERVICE_SET_PRIVACY_FLAGS handler not implemented.");
        break;
    case OSERVICE_WELL_KNOWN_URLS:
        // TODO: Implement OSERVICE_WELL_KNOWN_URLS
        LOG_INFO("OSERVICE_WELL_KNOWN_URLS handler not implemented.");
        break;
    case OSERVICE_NOOP:
        // TODO: Implement OSERVICE_NOOP
        LOG_INFO("OSERVICE_NOOP handler not implemented.");
        break;
    case OSERVICE_CLIENT_VERSIONS:
        prv_oservice_handle_client_versions(conn, frame);
        break;
    case OSERVICE_HOST_VERSIONS:
        // TODO: Implement OSERVICE_HOST_VERSIONS
        LOG_INFO("OSERVICE_HOST_VERSIONS handler not implemented.");
        break;
    case OSERVICE_MAX_CONFIG_QUERY:
        // TODO: Implement OSERVICE_MAX_CONFIG_QUERY
        LOG_INFO("OSERVICE_MAX_CONFIG_QUERY handler not implemented.");
        break;
    case OSERVICE_MAX_CONFIG_REPLY:
        // TODO: Implement OSERVICE_MAX_CONFIG_REPLY
        LOG_INFO("OSERVICE_MAX_CONFIG_REPLY handler not implemented.");
        break;
    case OSERVICE_STORE_CONFIG:
        // TODO: Implement OSERVICE_STORE_CONFIG
        LOG_INFO("OSERVICE_STORE_CONFIG handler not implemented.");
        break;
    case OSERVICE_CONFIG_QUERY:
        // TODO: Implement OSERVICE_CONFIG_QUERY
        LOG_INFO("OSERVICE_CONFIG_QUERY handler not implemented.");
        break;
    case OSERVICE_CONFIG_REPLY:
        // TODO: Implement OSERVICE_CONFIG_REPLY
        LOG_INFO("OSERVICE_CONFIG_REPLY handler not implemented.");
        break;
    case OSERVICE_SET_USERINFO_FIELDS:
        // TODO: Implement OSERVICE_SET_USERINFO_FIELDS
        LOG_INFO("OSERVICE_SET_USERINFO_FIELDS handler not implemented.");
        break;
    case OSERVICE_PROBE_REQ:
        // TODO: Implement OSERVICE_PROBE_REQ
        LOG_INFO("OSERVICE_PROBE_REQ handler not implemented.");
        break;
    case OSERVICE_PROBE_ACK:
        // TODO: Implement OSERVICE_PROBE_ACK
        LOG_INFO("OSERVICE_PROBE_ACK handler not implemented.");
        break;
    case OSERVICE_BART_REPLY:
        // TODO: Implement OSERVICE_BART_REPLY
        LOG_INFO("OSERVICE_BART_REPLY handler not implemented.");
        break;
    case OSERVICE_BART_QUERY2:
        // TODO: Implement OSERVICE_BART_QUERY2
        LOG_INFO("OSERVICE_BART_QUERY2 handler not implemented.");
        break;
    case OSERVICE_BART_REPLY2:
        // TODO: Implement OSERVICE_BART_REPLY2
        LOG_INFO("OSERVICE_BART_REPLY2 handler not implemented.");
        break;
    default:
        LOG_INFO("Unknown OSERVICE Sub ID: 0x%04X", frame->snac.subgroup_id);
    }
}

void oservice_send_host_online_response(connection_t *conn) {
    size_t frame_size = sizeof(flap_t);
    frame_size += sizeof(snac_t);
    frame_size += sizeof(prv_oservice_supported_snacs);
    
    uint8_t *buffer = malloc(frame_size);
    
    if (buffer == NULL) {
        LOG_ERR("Unable to malloc output buffer. Out of memory?");
        connection_close(conn);
    }
    
    uint16_t *tlv_array = (uint16_t *)&buffer[sizeof(flap_t) + sizeof(snac_t)];
    memcpy(tlv_array, prv_oservice_supported_snacs, sizeof(prv_oservice_supported_snacs));
    
    for (uint32_t i = 0; i < (sizeof(prv_oservice_supported_snacs)/sizeof(uint16_t)); i++) {
        tlv_array[i] = htons(tlv_array[i]);
    }
    
    conn->last_outbound_seq_num++;
    flap_t flap = flap_encode(FLAP_FRAME_TYPE_DATA, conn->last_outbound_seq_num, frame_size - sizeof(flap));
    
    snac_t snac = snac_encode(SNAC_FOODGROUP_ID_OSERVICE, OSERVICE_HOST_ONLINE, 0, 0);
    
    memcpy(buffer, &flap, sizeof(flap));
    memcpy(&buffer[sizeof(flap_t)], &snac, sizeof(snac));
    
    connection_write(conn, buffer, frame_size);
    
    free(buffer);
}