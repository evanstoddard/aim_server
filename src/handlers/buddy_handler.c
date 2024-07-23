/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file buddy_handler.c
 * @author Evan Stoddard
 * @brief BUDDY SNAC Handler
 */

#include "buddy_handler.h"
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

/*****************************************************************************
 * Functions
 *****************************************************************************/

void buddy_handler_handle_frame(connection_t *conn, frame_t *frame) {
    switch(frame->snac.subgroup_id) {
    case BUDDY_ERR:
        // TODO: Implement BUDDY_ERR
        LOG_INFO("BUDDY_ERR not implemented.");
        break;
    case BUDDY_RIGHTS_QUERY:
        // TODO: Implement BUDDY_RIGHTS_QUERY
        LOG_INFO("BUDDY_RIGHTS_QUERY not implemented.");
        break;
    case BUDDY_RIGHTS_REPLY:
        // TODO: Implement BUDDY_RIGHTS_REPLY
        LOG_INFO("BUDDY_RIGHTS_REPLY not implemented.");
        break;
    case BUDDY_ADD_BUDDIES:
        // TODO: Implement BUDDY_ADD_BUDDIES
        LOG_INFO("BUDDY_ADD_BUDDIES not implemented.");
        break;
    case BUDDY_DEL_BUDDIES:
        // TODO: Implement BUDDY_DEL_BUDDIES
        LOG_INFO("BUDDY_DEL_BUDDIES not implemented.");
        break;
    case BUDDY_WATCHER_LIST_QUERY:
        // TODO: Implement BUDDY_WATCHER_LIST_QUERY
        LOG_INFO("BUDDY_WATCHER_LIST_QUERY not implemented.");
        break;
    case BUDDY_WATCHER_LIST_RESPONSE:
        // TODO: Implement BUDDY_WATCHER_LIST_RESPONSE
        LOG_INFO("BUDDY_WATCHER_LIST_RESPONSE not implemented.");
        break;
    case BUDDY_WATCHER_SUB_REQUEST:
        // TODO: Implement BUDDY_WATCHER_SUB_REQUEST
        LOG_INFO("BUDDY_WATCHER_SUB_REQUEST not implemented.");
        break;
    case BUDDY_WATCHER_NOTIFICATION:
        // TODO: Implement BUDDY_WATCHER_NOTIFICATION
        LOG_INFO("BUDDY_WATCHER_NOTIFICATION not implemented.");
        break;
    case BUDDY_REJECT_NOTIFICATION:
        // TODO: Implement BUDDY_REJECT_NOTIFICATION
        LOG_INFO("BUDDY_REJECT_NOTIFICATION not implemented.");
        break;
    case BUDDY_ARRIVED:
        // TODO: Implement BUDDY_ARRIVED
        LOG_INFO("BUDDY_ARRIVED not implemented.");
        break;
    case BUDDY_DEPARTED:
        // TODO: Implement BUDDY_DEPARTED
        LOG_INFO("BUDDY_DEPARTED not implemented.");
        break;
    case BUDDY_ADD_TEMP_BUDDIES:
        // TODO: Implement BUDDY_ADD_TEMP_BUDDIES
        LOG_INFO("BUDDY_ADD_TEMP_BUDDIES not implemented.");
        break;
    case BUDDY_DEL_TEMP_BUDDIES:
        // TODO: Implement BUDDY_DEL_TEMP_BUDDIES
        LOG_INFO("BUDDY_DEL_TEMP_BUDDIES not implemented.");
        break;
    default:
        LOG_INFO("Unknown BUDDY Sub ID: 0x%04X", frame->snac.subgroup_id);
        break;
    }
}