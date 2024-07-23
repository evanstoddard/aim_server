/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file locate.c
 * @author Evan Stoddard
 * @brief 
 */

#include "locate.h"

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
 * @brief Handle Rights Query request
 * 
 * @param conn Connection
 * @param frame Frame
 */
void prv_locate_handle_rights_query(connection_t *conn, frame_t *frame);

/*****************************************************************************
 * Private Functions
 *****************************************************************************/

void prv_locate_handle_rights_query(connection_t *conn, frame_t *frame) {
    LOG_DEBUG("Rights Query Request Blob: ");
    printf("\t");
    
    uint8_t *blob = frame->snac_blob;
    for (int i = 0; i < frame->flap.payload_length - sizeof(snac_t); i++) {
        printf("%02X ", blob[i]);
    }
    
    puts("");
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