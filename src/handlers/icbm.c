/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file icbm.c
 * @author Evan Stoddard
 * @brief ICBM SNAC Handler
 */

#include "icbm.h"

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

void icbm_handle_frame(connection_t *conn, frame_t *frame) {
    switch(frame->snac.subgroup_id) {
    case ICBM_ERR:
        // TODO: Implement ICBM_ERR
        LOG_INFO("ICBM_ERR not implemented.");
        break;
    case ICBM_ADD_PARAMETERS:
        // TODO: Implement ICBM_ADD_PARAMETERS
        LOG_INFO("ICBM_ADD_PARAMETERS not implemented.");
        break;
    case ICBM_DEL_PARAMETERS:
        // TODO: Implement ICBM_DEL_PARAMETERS
        LOG_INFO("ICBM_DEL_PARAMETERS not implemented.");
        break;
    case ICBM_PARAMETER_QUERY:
        // TODO: Implement ICBM_PARAMETER_QUERY
        LOG_INFO("ICBM_PARAMETER_QUERY not implemented.");
        break;
    case ICBM_PARAMETER_REPLY:
        // TODO: Implement ICBM_PARAMETER_REPLY
        LOG_INFO("ICBM_PARAMETER_REPLY not implemented.");
        break;
    case ICBM_CHANNEL_MSG_TOHOST:
        // TODO: Implement ICBM_CHANNEL_MSG_TOHOST
        LOG_INFO("ICBM_CHANNEL_MSG_TOHOST not implemented.");
        break;
    case ICBM_CHANNEL_MSG_TOCLIENT:
        // TODO: Implement ICBM_CHANNEL_MSG_TOCLIENT
        LOG_INFO("ICBM_CHANNEL_MSG_TOCLIENT not implemented.");
        break;
    case ICBM_EVIL_REQUEST:
        // TODO: Implement ICBM_EVIL_REQUEST
        LOG_INFO("ICBM_EVIL_REQUEST not implemented.");
        break;
    case ICBM_EVIL_REPLY:
        // TODO: Implement ICBM_EVIL_REPLY
        LOG_INFO("ICBM_EVIL_REPLY not implemented.");
        break;
    case ICBM_MISSED_CALLS:
        // TODO: Implement ICBM_MISSED_CALLS
        LOG_INFO("ICBM_MISSED_CALLS not implemented.");
        break;
    case ICBM_CLIENT_ERR:
        // TODO: Implement ICBM_CLIENT_ERR
        LOG_INFO("ICBM_CLIENT_ERR not implemented.");
        break;
    case ICBM_HOST_ACK:
        // TODO: Implement ICBM_HOST_ACK
        LOG_INFO("ICBM_HOST_ACK not implemented.");
        break;
    case ICBM_SIN_STORED:
        // TODO: Implement ICBM_SIN_STORED
        LOG_INFO("ICBM_SIN_STORED not implemented.");
        break;
    case ICBM_SIN_LIST_QUERY:
        // TODO: Implement ICBM_SIN_LIST_QUERY
        LOG_INFO("ICBM_SIN_LIST_QUERY not implemented.");
        break;
    case ICBM_SIN_LIST_REPLY:
        // TODO: Implement ICBM_SIN_LIST_REPLY
        LOG_INFO("ICBM_SIN_LIST_REPLY not implemented.");
        break;
    case ICBM_SIN_RETRIEVE:
        // TODO: Implement ICBM_SIN_RETRIEVE
        LOG_INFO("ICBM_SIN_RETRIEVE not implemented.");
        break;
    case ICBM_SIN_DELETE:
        // TODO: Implement ICBM_SIN_DELETE
        LOG_INFO("ICBM_SIN_DELETE not implemented.");
        break;
    case ICBM_NOTIFY_REQUEST:
        // TODO: Implement ICBM_NOTIFY_REQUEST
        LOG_INFO("ICBM_NOTIFY_REQUEST not implemented.");
        break;
    case ICBM_NOTIFY_REPLY:
        // TODO: Implement ICBM_NOTIFY_REPLY
        LOG_INFO("ICBM_NOTIFY_REPLY not implemented.");
        break;
    case ICBM_CLIENT_EVENT:
        // TODO: Implement ICBM_CLIENT_EVENT
        LOG_INFO("ICBM_CLIENT_EVENT not implemented.");
        break;
    case ICBM_SIN_REPLY:
        // TODO: Implement ICBM_SIN_REPLY
        LOG_INFO("ICBM_SIN_REPLY not implemented.");
        break;
    default:
        LOG_INFO("Unknown ICBM Sub ID: 0x%04X", frame->snac.subgroup_id);
        break;
    }
}