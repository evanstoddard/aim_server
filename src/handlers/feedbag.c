/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file feedbag.c
 * @author Evan Stoddard
 * @brief Feedback SNAC Handler
 */

#include "feedbag.h"

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

void feedback_handle_frame(connection_t *conn, frame_t *frame) {
    switch(frame->snac.subgroup_id) {
    case FEEDBAG_ERR:
        // TODO: Implement FEEDBAG_ERR
        LOG_INFO("FEEDBAG_ERR handler not implemented.");
        break;
    case FEEDBAG_RIGHTS_QUERY:
        // TODO: Implement FEEDBAG_RIGHTS_QUERY
        LOG_INFO("FEEDBAG_RIGHTS_QUERY handler not implemented.");
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