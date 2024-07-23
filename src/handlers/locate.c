/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file locate.c
 * @author Evan Stoddard
 * @brief 
 */

#include "locate.h"

#include "oscar/flap.h"
#include "oscar/tlv.h"

#include "oscar/flap_decoder.h"
#include "oscar/snac_decoder.h"
#include "oscar/tlv_decoder.h"
#include "oscar/tlv_encoder.h"

#include "oscar/flap_encoder.h"
#include "oscar/snac_encoder.h"

#include "memory/buffer.h"

#include "logging.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

#define LOCATE_MAX_SIGNATURE_LEN    127

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/**
 * @brief LOCATE TLV Class tag IDs
 * 
 */
typedef enum {
    LOCATE_TLV_TAGS_RIGHTS_MAX_SIG_LEN                 = 0x01,
    LOCATE_TLV_TAGS_RIGHTS_MAX_CAPABILITIES_LEN        = 0x02,
    LOCATE_TLV_TAGS_RIGHTS_MAX_FIND_BY_EMAIL_LIST      = 0x03,
    LOCATE_TLV_TAGS_RIGHTS_MAX_CERTS_LEN               = 0x04,
    LOCATE_TLV_TAGS_RIGHTS_MAX_MAX_SHORT_CAPABILITIES  = 0x05,
} locate_tlv_tag_t;

/*****************************************************************************
 * Variables
 *****************************************************************************/

/**
 * @brief List of capability UUIDs supported by server
 *        (See https://wiki.nina.chat/wiki/Protocols/OSCAR/UUIDs)
 * 
 */
static uint8_t prv_locate_capabilities[][16] = {
};

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/**
 * @brief Handle Rights Query request
 * 
 * @param conn Connection
 * @param frame Frame
 */
void prv_locate_handle_rights_query(connection_t *conn, frame_t *frame);

/**
 * @brief Send Rights Query Reply
 * 
 * @param conn Connection
 */
void prv_locate_send_rights_reply(connection_t *conn);

/*****************************************************************************
 * Private Functions
 *****************************************************************************/

void prv_locate_handle_rights_query(connection_t *conn, frame_t *frame) {
    prv_locate_send_rights_reply(conn);
}

void prv_locate_send_rights_reply(connection_t *conn) {
    uint16_t payload_length =  sizeof(snac_t);
    size_t buffer_size = sizeof(flap_t);
    
    // Encode SNAC
    snac_t snac = snac_encode(SNAC_FOODGROUP_ID_LOCATE, LOCATE_RIGHTS_REPLY, 0, 0);
    
    // Create TLVs
    tlv_uint16_t sig_len_tlv = tlv_uint16_encode(LOCATE_TLV_TAGS_RIGHTS_MAX_SIG_LEN, LOCATE_MAX_SIGNATURE_LEN);
    payload_length += sizeof(tlv_uint16_t);
    
    tlv_uint16_t capabilities_tlv = tlv_uint16_encode(LOCATE_TLV_TAGS_RIGHTS_MAX_CAPABILITIES_LEN, 0);
    payload_length += sizeof(tlv_uint16_t);
    
    tlv_uint16_t email_count_tlv = tlv_uint16_encode(LOCATE_TLV_TAGS_RIGHTS_MAX_FIND_BY_EMAIL_LIST, 0xA);
    payload_length += sizeof(tlv_uint16_t);
    
    tlv_uint16_t cert_len_tlv = tlv_uint16_encode(LOCATE_TLV_TAGS_RIGHTS_MAX_CERTS_LEN, 0x1000);
    payload_length += sizeof(tlv_uint16_t);
    
    buffer_size += payload_length;
    
    // Encode flap
    uint16_t sequence_number = conn->last_outbound_seq_num + 1;
    conn->last_outbound_seq_num = sequence_number;
    flap_t flap = flap_encode(FLAP_FRAME_TYPE_DATA, sequence_number, payload_length);
    
    // Create outbound buffer
    buffer_t buffer = buffer_init();
    
    buffer_write(buffer, &flap, sizeof(flap_t));
    buffer_write(buffer, &snac, sizeof(snac_t));
    buffer_write(buffer, &sig_len_tlv, sizeof(sig_len_tlv));
    buffer_write(buffer, &capabilities_tlv, sizeof(capabilities_tlv));
    buffer_write(buffer, &email_count_tlv, sizeof(email_count_tlv));
    buffer_write(buffer, &cert_len_tlv, sizeof(cert_len_tlv));
    
    if (connection_write(conn, buffer_ptr(buffer), buffer_size) == false) {
        LOG_ERR("Failed to write to connection.");
    }
    
    buffer_deinit(buffer);
}

/*****************************************************************************
 * Public Functions
 *****************************************************************************/

void locate_handle_frame(connection_t *conn, frame_t *frame) {
    switch(frame->snac.subgroup_id) {
    case LOCATE_ERR:
        // TODO: Implement LOCATE_ERR
        LOG_INFO("LOCATE_ERR handler not implemented.");
        break;
    case LOCATE_RIGHTS_QUERY:
        prv_locate_handle_rights_query(conn, frame);
        break;
    case LOCATE_RIGHTS_REPLY:
        // TODO: Implement LOCATE_RIGHTS_REPLY
        LOG_INFO("LOCATE_RIGHTS_REPLY handler not implemented.");
        break;
    case LOCATE_SET_INFO:
        // TODO: Implement LOCATE_SET_INFO
        LOG_INFO("LOCATE_SET_INFO handler not implemented.");
        break;
    case LOCATE_USER_INFO_QUERY:
        // TODO: Implement LOCATE_USER_INFO_QUERY
        LOG_INFO("LOCATE_USER_INFO_QUERY handler not implemented.");
        break;
    case LOCATE_USER_INFO_REPLY:
        // TODO: Implement LOCATE_USER_INFO_REPLY
        LOG_INFO("LOCATE_USER_INFO_REPLY handler not implemented.");
        break;
    case LOCATE_WATCHER_SUB_REQUEST:
        // TODO: Implement LOCATE_WATCHER_SUB_REQUEST
        LOG_INFO("LOCATE_WATCHER_SUB_REQUEST handler not implemented.");
        break;
    case LOCATE_WATCHER_NOTIFICATION:
        // TODO: Implement LOCATE_WATCHER_NOTIFICATION
        LOG_INFO("LOCATE_WATCHER_NOTIFICATION handler not implemented.");
        break;
    case LOCATE_SET_DIR_INFO:
        // TODO: Implement LOCATE_SET_DIR_INFO
        LOG_INFO("LOCATE_SET_DIR_INFO handler not implemented.");
        break;
    case LOCATE_SET_DIR_REPLY:
        // TODO: Implement LOCATE_SET_DIR_REPLY
        LOG_INFO("LOCATE_SET_DIR_REPLY handler not implemented.");
        break;
    case LOCATE_GET_DIR_INFO:
        // TODO: Implement LOCATE_GET_DIR_INFO
        LOG_INFO("LOCATE_GET_DIR_INFO handler not implemented.");
        break;
    case LOCATE_GET_DIR_REPLY:
        // TODO: Implement LOCATE_GET_DIR_REPLY
        LOG_INFO("LOCATE_GET_DIR_REPLY handler not implemented.");
        break;
    case LOCATE_GROUP_CAPABILITY_QUERY:
        // TODO: Implement LOCATE_GROUP_CAPABILITY_QUERY
        LOG_INFO("LOCATE_GROUP_CAPABILITY_QUERY handler not implemented.");
        break;
    case LOCATE_GROUP_CAPABILITY_REPLY:
        // TODO: Implement LOCATE_GROUP_CAPABILITY_REPLY
        LOG_INFO("LOCATE_GROUP_CAPABILITY_REPLY handler not implemented.");
        break;
    case LOCATE_SET_KEYWORD_INFO:
        // TODO: Implement LOCATE_SET_KEYWORD_INFO
        LOG_INFO("LOCATE_SET_KEYWORD_INFO handler not implemented.");
        break;
    case LOCATE_SET_KEYWORD_REPLY:
        // TODO: Implement LOCATE_SET_KEYWORD_REPLY
        LOG_INFO("LOCATE_SET_KEYWORD_REPLY handler not implemented.");
        break;
    case LOCATE_GET_KEYWORD_INFO:
        // TODO: Implement LOCATE_GET_KEYWORD_INFO
        LOG_INFO("LOCATE_GET_KEYWORD_INFO handler not implemented.");
        break;
    case LOCATE_GET_KEYWORD_REPLY:
        // TODO: Implement LOCATE_GET_KEYWORD_REPLY
        LOG_INFO("LOCATE_GET_KEYWORD_REPLY handler not implemented.");
        break;
    case LOCATE_FIND_LIST_BY_EMAIL:
        // TODO: Implement LOCATE_FIND_LIST_BY_EMAIL
        LOG_INFO("LOCATE_FIND_LIST_BY_EMAIL handler not implemented.");
        break;
    case LOCATE_FIND_LIST_REPLY:
        // TODO: Implement LOCATE_FIND_LIST_REPLY
        LOG_INFO("LOCATE_FIND_LIST_REPLY handler not implemented.");
        break;
    case LOCATE_USER_INFO_QUERY2:
        // TODO: Implement LOCATE_USER_INFO_QUERY2
        LOG_INFO("LOCATE_USER_INFO_QUERY2 handler not implemented.");
        break;
    default:
        LOG_INFO("Unknown LOCATE Sub ID: 0x%04X", frame->snac.subgroup_id);
        break;
    }
}