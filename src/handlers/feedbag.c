/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file feedbag.c
 * @author Evan Stoddard
 * @brief Feedback SNAC Handler
 */

#include "feedbag.h"

#include <arpa/inet.h>

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

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/**
 * @brief FEEDBAG TLV Class tag IDs
 * 
 */
typedef enum {
    FEEDBAG_RIGHTS_MAX_CLASS_ATTRS          = 0x02,
    FEEDBAG_RIGHTS_MAX_ITEM_ATTRS           = 0x03,
    FEEDBAG_RIGHTS_MAX_ITEMS_BY_CLASS       = 0x04,
    FEEDBAG_RIGHTS_MAX_CLIENT_ITEMS         = 0x05,
    FEEDBAG_RIGHTS_MAX_ITEM_NAME_LEN        = 0x06,
    FEEDBAG_RIGHTS_MAX_RECENT_BUDDIES       = 0x07,
    FEEDBAG_RIGHTS_INTERACTION_BUDDIES      = 0x08,
    FEEDBAG_RIGHTS_INTERACTION_HALF_LIFE    = 0x09,
    FEEDBAG_RIGHTS_INTERACTION_MAX_SCORE    = 0x0A,
    FEEDBAG_RIGHTS_MAX_UNKNOWN_0B           = 0x0B,
    FEEDBAG_RIGHTS_MAX_BUDDIES_PER_GROUP    = 0x0C,
    FEEDBAG_RIGHTS_MAX_MEGA_BOTS            = 0x0D,
    FEEDBAG_RIGHTS_MAX_SMART_GROUPS         = 0x0E,
} feedback_tlv_tag_t;

/*****************************************************************************
 * Variables
 *****************************************************************************/

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/**
 * @brief Handler for rights query
 * 
 * @param conn Connection
 * @param frame Frame
 */
void feedback_handle_rights_query(connection_t *conn, frame_t *frame);

/**
 * @brief Send rights reply
 * 
 * @param conn Connection
 */
void feedback_send_rights_reply(connection_t *conn);

/*****************************************************************************
 * Private Functions
 *****************************************************************************/

void feedback_handle_rights_query(connection_t *conn, frame_t *frame) {
    feedback_send_rights_reply(conn);
}

void feedback_send_rights_reply(connection_t *conn) {
    uint16_t payload_length =  sizeof(snac_t);
    size_t buffer_size = sizeof(flap_t);
    
    // Encode SNAC
    snac_t snac = snac_encode(SNAC_FOODGROUP_ID_FEEDBAG, FEEDBAG_RIGHTS_REPLY, 0, 0);
    
    // Create TLVs
    
    // Don't love this. Maybe refactor in the future
    uint16_t max_items_tlv[] = {
        htons(FEEDBAG_RIGHTS_MAX_ITEMS_BY_CLASS),
        htons(21),
        htons(200),
        htons(61),
        htons(50),
        htons(150),
        htons(0x1),
        htons(0x1),
        htons(0x32),
        htons(0),
        htons(0),
        htons(0x3),
        htons(0),
        htons(0),
        htons(0),
        htons(0x80),
        htons(0),
        htons(0),
        htons(0x0014),
        htons(0x00C8),
        htons(0x0001),
        htons(0x0000),
        htons(0x0001),
        htons(0x0000),
        htons(0x0002),
        htons(0x0002),
        htons(0x00FE),
        htons(0x0003),
        htons(0x0002),
        htons(0x01FC),
    };
    
    tlv_uint16_t max_client_items_tlv = tlv_uint16_encode(FEEDBAG_RIGHTS_MAX_CLIENT_ITEMS, 0);
    payload_length += sizeof(tlv_uint16_t);
    
    tlv_uint16_t max_item_name_len = tlv_uint16_encode(FEEDBAG_RIGHTS_MAX_ITEM_NAME_LEN, 0x61);
    payload_length += sizeof(tlv_uint16_t);
    
    tlv_uint16_t max_recent_buddies_len = tlv_uint16_encode(FEEDBAG_RIGHTS_MAX_RECENT_BUDDIES, 0xA);
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
    buffer_write(buffer, &max_client_items_tlv, sizeof(max_client_items_tlv));
    buffer_write(buffer, &max_item_name_len, sizeof(max_item_name_len));
    buffer_write(buffer, &max_recent_buddies_len, sizeof(max_recent_buddies_len));
    
    if (connection_write(conn, buffer_ptr(buffer), buffer_size) == false) {
        LOG_ERR("Failed to write to connection.");
    }
    
    buffer_deinit(buffer);

}

/*****************************************************************************
 * Functions
 *****************************************************************************/

void feedback_handle_frame(connection_t *conn, frame_t *frame) {
    switch(frame->snac.subgroup_id) {
    case FEEDBAG_ERR:
        // TODO: Implement FEEDBAG_ERR
        LOG_INFO("FEEDBAG_ERR handler not implemented.");
        break;
    case FEEDBAG_RIGHTS_QUERY:
        feedback_handle_rights_query(conn, frame);
        break;
    case FEEDBAG_RIGHTS_REPLY:
        // TODO: Implement FEEDBAG_RIGHTS_REPLY
        LOG_INFO("FEEDBAG_RIGHTS_REPLY handler not implemented.");
        break;
    case FEEDBAG_QUERY:
        // TODO: Implement FEEDBAG_QUERY
        LOG_INFO("FEEDBAG_QUERY handler not implemented.");
        break;
    case FEEDBAG_QUERY_IF_MODIFIED:
        // TODO: Implement FEEDBAG_QUERY_IF_MODIFIED
        LOG_INFO("FEEDBAG_QUERY_IF_MODIFIED handler not implemented.");
        break;
    case FEEDBAG_REPLY:
        // TODO: Implement FEEDBAG_REPLY
        LOG_INFO("FEEDBAG_REPLY handler not implemented.");
        break;
    case FEEDBAG_USE:
        // TODO: Implement FEEDBAG_USE
        LOG_INFO("FEEDBAG_USE handler not implemented.");
        break;
    case FEEDBAG_INSERT_ITEM:
        // TODO: Implement FEEDBAG_INSERT_ITEM
        LOG_INFO("FEEDBAG_INSERT_ITEM handler not implemented.");
        break;
    case FEEDBAG_UPDATE_ITEM:
        // TODO: Implement FEEDBAG_UPDATE_ITEM
        LOG_INFO("FEEDBAG_UPDATE_ITEM handler not implemented.");
        break;
    case FEEDBAG_DELETE_ITEM:
        // TODO: Implement FEEDBAG_DELETE_ITEM
        LOG_INFO("FEEDBAG_DELETE_ITEM handler not implemented.");
        break;
    case FEEDBAG_INSERT_CLASS:
        // TODO: Implement FEEDBAG_INSERT_CLASS
        LOG_INFO("FEEDBAG_INSERT_CLASS handler not implemented.");
        break;
    case FEEDBAG_UPDATE_CLASS:
        // TODO: Implement FEEDBAG_UPDATE_CLASS
        LOG_INFO("FEEDBAG_UPDATE_CLASS handler not implemented.");
        break;
    case FEEDBAG_DELETE_CLASS:
        // TODO: Implement FEEDBAG_DELETE_CLASS
        LOG_INFO("FEEDBAG_DELETE_CLASS handler not implemented.");
        break;
    case FEEDBAG_STATUS:
        // TODO: Implement FEEDBAG_STATUS
        LOG_INFO("FEEDBAG_STATUS handler not implemented.");
        break;
    case FEEDBAG_REPLY_NOT_MODIFIED:
        // TODO: Implement FEEDBAG_REPLY_NOT_MODIFIED
        LOG_INFO("FEEDBAG_REPLY_NOT_MODIFIED handler not implemented.");
        break;
    case FEEDBAG_DELETE_USER:
        // TODO: Implement FEEDBAG_DELETE_USER
        LOG_INFO("FEEDBAG_DELETE_USER handler not implemented.");
        break;
    case FEEDBAG_START_CLUSTER:
        // TODO: Implement FEEDBAG_START_CLUSTER
        LOG_INFO("FEEDBAG_START_CLUSTER handler not implemented.");
        break;
    case FEEDBAG_END_CLUSTER:
        // TODO: Implement FEEDBAG_END_CLUSTER
        LOG_INFO("FEEDBAG_END_CLUSTER handler not implemented.");
        break;
    case FEEDBAG_AUTHORIZE_BUDDY:
        // TODO: Implement FEEDBAG_AUTHORIZE_BUDDY
        LOG_INFO("FEEDBAG_AUTHORIZE_BUDDY handler not implemented.");
        break;
    case FEEDBAG_PRE_AUTHORIZE_BUDDY:
        // TODO: Implement FEEDBAG_PRE_AUTHORIZE_BUDDY
        LOG_INFO("FEEDBAG_PRE_AUTHORIZE_BUDDY handler not implemented.");
        break;
    case FEEDBAG_PRE_AUTHORIZED_BUDDY:
        // TODO: Implement FEEDBAG_PRE_AUTHORIZED_BUDDY
        LOG_INFO("FEEDBAG_PRE_AUTHORIZED_BUDDY handler not implemented.");
        break;
    case FEEDBAG_REMOVE_ME:
        // TODO: Implement FEEDBAG_REMOVE_ME
        LOG_INFO("FEEDBAG_REMOVE_ME handler not implemented.");
        break;
    case FEEDBAG_REMOVE_ME2:
        // TODO: Implement FEEDBAG_REMOVE_ME2
        LOG_INFO("FEEDBAG_REMOVE_ME2 handler not implemented.");
        break;
    case FEEDBAG_REQUEST_AUTHORIZE_TO_HOST:
        // TODO: Implement FEEDBAG_REQUEST_AUTHORIZE_TO_HOST
        LOG_INFO("FEEDBAG_REQUEST_AUTHORIZE_TO_HOST handler not implemented.");
        break;
    case FEEDBAG_REQUEST_AUTHORIZE_TO_CLIENT:
        // TODO: Implement FEEDBAG_REQUEST_AUTHORIZE_TO_CLIENT
        LOG_INFO("FEEDBAG_REQUEST_AUTHORIZE_TO_CLIENT handler not implemented.");
        break;
    case FEEDBAG_RESPOND_AUTHORIZE_TO_HOST:
        // TODO: Implement FEEDBAG_RESPOND_AUTHORIZE_TO_HOST
        LOG_INFO("FEEDBAG_RESPOND_AUTHORIZE_TO_HOST handler not implemented.");
        break;
    case FEEDBAG_RESPOND_AUTHORIZE_TO_CLIENT:
        // TODO: Implement FEEDBAG_RESPOND_AUTHORIZE_TO_CLIENT
        LOG_INFO("FEEDBAG_RESPOND_AUTHORIZE_TO_CLIENT handler not implemented.");
        break;
    case FEEDBAG_BUDDY_ADDED:
        // TODO: Implement FEEDBAG_BUDDY_ADDED
        LOG_INFO("FEEDBAG_BUDDY_ADDED handler not implemented.");
        break;
    case FEEDBAG_REQUEST_AUTHORIZE_TO_BADOG:
        // TODO: Implement FEEDBAG_REQUEST_AUTHORIZE_TO_BADOG
        LOG_INFO("FEEDBAG_REQUEST_AUTHORIZE_TO_BADOG handler not implemented.");
        break;
    case FEEDBAG_RESPOND_AUTHORIZE_TO_BADOG:
        // TODO: Implement FEEDBAG_RESPOND_AUTHORIZE_TO_BADOG
        LOG_INFO("FEEDBAG_RESPOND_AUTHORIZE_TO_BADOG handler not implemented.");
        break;
    case FEEDBAG_BUDDY_ADDED_TO_BADOG:
        // TODO: Implement FEEDBAG_BUDDY_ADDED_TO_BADOG
        LOG_INFO("FEEDBAG_BUDDY_ADDED_TO_BADOG handler not implemented.");
        break;
    case FEEDBAG_TEST_SNAC:
        // TODO: Implement FEEDBAG_TEST_SNAC
        LOG_INFO("FEEDBAG_TEST_SNAC handler not implemented.");
        break;
    case FEEDBAG_FORWARD_MSG:
        // TODO: Implement FEEDBAG_FORWARD_MSG
        LOG_INFO("FEEDBAG_FORWARD_MSG handler not implemented.");
        break;
    case FEEDBAG_IS_AUTH_REQUIRED_QUERY:
        // TODO: Implement FEEDBAG_IS_AUTH_REQUIRED_QUERY
        LOG_INFO("FEEDBAG_IS_AUTH_REQUIRED_QUERY handler not implemented.");
        break;
    case FEEDBAG_IS_AUTH_REQUIRED_REPLY:
        // TODO: Implement FEEDBAG_IS_AUTH_REQUIRED_REPLY
        LOG_INFO("FEEDBAG_IS_AUTH_REQUIRED_REPLY handler not implemented.");
        break;
    case FEEDBAG_RECENT_BUDDY_UPDATE:
        // TODO: Implement FEEDBAG_RECENT_BUDDY_UPDATE
        LOG_INFO("FEEDBAG_RECENT_BUDDY_UPDATE handler not implemented.");
        break;
    default:
        LOG_INFO("Unknown FEEDBAG Sub ID: 0x%04X", frame->snac.subgroup_id);
        break;
    }
}