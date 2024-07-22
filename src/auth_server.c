/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file auth_server.c
 * @author Evan Stoddard
 * @brief Auth server implementation
 */

#include "auth_server.h"

#include "oscar/auth_types.h"

#include "oscar/flap.h"
#include "oscar/frame.h"
#include "oscar/snac.h"

#include "oscar/flap_decoder.h"
#include "oscar/snac_decoder.h"

#include "oscar/flap_encoder.h"
#include "oscar/snac_encoder.h"

#include "model/client.h"

#include "handlers/bucp.h"

#include <stddef.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

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
 * @brief Handle new frame
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_auth_server_handle_frame(connection_t *conn, frame_t *frame);

/**
 * @brief Handle signon frame
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_auth_server_handle_signon_frame(connection_t *conn, frame_t *frame);

/**
 * @brief Handle data frame
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_auth_server_handle_data_frame(connection_t *conn, frame_t *frame);

/*****************************************************************************
 * Private Functions
 *****************************************************************************/

static void prv_auth_server_handle_frame(connection_t *conn, frame_t *frame) {
    // Parse FLAP type
    switch(frame->flap.frame_type) {
    case FLAP_FRAME_TYPE_SIGNON:
        prv_auth_server_handle_signon_frame(conn, frame);
        break;
    case FLAP_FRAME_TYPE_DATA:
        prv_auth_server_handle_data_frame(conn, frame);
        break;
    default:
        break;
    }
}

static void prv_auth_server_handle_signon_frame(connection_t *conn, frame_t *frame) {
    // TODO: Implement Handle Signon Frame
}

static void prv_auth_server_handle_data_frame(connection_t *conn, frame_t *frame) {
    // Parse snac
    bool ret = snac_decode(&frame->snac, frame->payload, frame->flap.payload_length);
    
    if (!ret) {
        LOG_ERR("Unable to parse SNAC. Malformed frame.");
        connection_close(conn);
        return;
    }
    
    frame->snac_blob = frame->payload + sizeof(snac_t);
    
    switch(frame->snac.foodgroup_id) {
    case SNAC_FOODGROUP_ID_LOCATE:
        // TODO: Implement SNAC_FOODGROUP_ID_LOCATE handler
        LOG_WARN("SNAC_FOODGROUP_ID_LOCATE handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_OSERVICE:
        // TODO: Implement SNAC_FOODGROUP_ID_OSERVICE handler
        LOG_WARN("SNAC_FOODGROUP_ID_OSERVICE handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_BUDDY:
        // TODO: Implement SNAC_FOODGROUP_ID_BUDDY handler
        LOG_WARN("SNAC_FOODGROUP_ID_BUDDY handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_ICBM:
        // TODO: Implement SNAC_FOODGROUP_ID_ICBM handler
        LOG_WARN("SNAC_FOODGROUP_ID_ICBM handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_ADVERT:
        // TODO: Implement SNAC_FOODGROUP_ID_ADVERT handler
        LOG_WARN("SNAC_FOODGROUP_ID_ADVERT handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_INVITE:
        // TODO: Implement SNAC_FOODGROUP_ID_INVITE handler
        LOG_WARN("SNAC_FOODGROUP_ID_INVITE handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_ADMIN:
        // TODO: Implement SNAC_FOODGROUP_ID_ADMIN handler
        LOG_WARN("SNAC_FOODGROUP_ID_ADMIN handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_POPUP:
        // TODO: Implement SNAC_FOODGROUP_ID_POPUP handler
        LOG_WARN("SNAC_FOODGROUP_ID_POPUP handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_PD:
        // TODO: Implement SNAC_FOODGROUP_ID_PD handler
        LOG_WARN("SNAC_FOODGROUP_ID_PD handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_USER_LOOKUP:
        // TODO: Implement SNAC_FOODGROUP_ID_USER_LOOKUP handler
        LOG_WARN("SNAC_FOODGROUP_ID_USER_LOOKUP handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_STATS:
        // TODO: Implement SNAC_FOODGROUP_ID_STATS handler
        LOG_WARN("SNAC_FOODGROUP_ID_STATS handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_TRANSLATE:
        // TODO: Implement SNAC_FOODGROUP_ID_TRANSLATE handler
        LOG_WARN("SNAC_FOODGROUP_ID_TRANSLATE handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_CHAT:
        // TODO: Implement SNAC_FOODGROUP_ID_CHAT handler
        LOG_WARN("SNAC_FOODGROUP_ID_CHAT handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_ODIR:
        // TODO: Implement SNAC_FOODGROUP_ID_ODIR handler
        LOG_WARN("SNAC_FOODGROUP_ID_ODIR handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_BART:
        // TODO: Implement SNAC_FOODGROUP_ID_BART handler
        LOG_WARN("SNAC_FOODGROUP_ID_BART handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_FEEDBAG:
        // TODO: Implement SNAC_FOODGROUP_ID_FEEDBAG handler
        LOG_WARN("SNAC_FOODGROUP_ID_FEEDBAG handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_ICQ:
        // TODO: Implement SNAC_FOODGROUP_ID_ICQ handler
        LOG_WARN("SNAC_FOODGROUP_ID_ICQ handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_BUCP:
        bucp_handle_frame(conn, frame);
        break;
    case SNAC_FOODGROUP_ID_ALERT:
        // TODO: Implement SNAC_FOODGROUP_ID_ALERT handler
        LOG_WARN("SNAC_FOODGROUP_ID_ALERT handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_PLUGIN:
        // TODO: Implement SNAC_FOODGROUP_ID_PLUGIN handler
        LOG_WARN("SNAC_FOODGROUP_ID_PLUGIN handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_MDIR:
        // TODO: Implement SNAC_FOODGROUP_ID_MDIR handler
        LOG_WARN("SNAC_FOODGROUP_ID_MDIR handler not implemented.");
        break;
    case SNAC_FOODGROUP_ID_ARS:
        // TODO: Implement SNAC_FOODGROUP_ID_ARS handler
        LOG_WARN("SNAC_FOODGROUP_ID_ARS handler not implemented.");
        break;
    default:
        LOG_WARN("Unknown SNAC ID.");
        break;
    }
}

/*****************************************************************************
 * Public Functions
 *****************************************************************************/

void auth_server_handle_new_connection(connection_t *conn) {
    if (conn == NULL) {
        return;
    }
    LOG_INFO("Handling new auth connection.");
    
    conn->client = client_init();
    
    if (conn->client == NULL) {
        LOG_ERR("Unable to create client. Out of memory?");
        connection_close(conn);
        return;
    }
    
    // Set connection event callback
    conn->callbacks.on_event = auth_server_handle_event;
    
    // Create start message
    flap_t msg_header;
    msg_header.start_marker = FLAP_START_MARKER;
    msg_header.frame_type = FLAP_FRAME_TYPE_SIGNON;
    msg_header.sequence_number = 0;
    msg_header.payload_length = 0;
    
    ssize_t ret = connection_write(conn, &msg_header, sizeof(msg_header));
    
    if (ret == -1 || ret == 0) {
        LOG_WARN("Failed to send auth start frame.");
    }
}

void auth_server_handle_event(connection_t *conn) {
    if (conn == NULL) {
        return;
    }
    
    // Create frame object
    frame_t frame;
    frame.payload = NULL;
    
    // Read in FLAP and decode
    ssize_t bytes_read = connection_read(conn, &frame.flap, sizeof(flap_t));
    
    // Connection closed if bytes read 0 or less
    if (bytes_read <= 0) {
        return;
    }
    
    if (!flap_decode(&frame.flap, &frame.flap, bytes_read)) {
        // Invalid FLAP. Close connection.
        LOG_ERR("Bad FLAP read.");
        connection_close(conn);
        return;
    }
    
    conn->last_inbound_seq_num = frame.flap.sequence_number;
    
    // Read in rest of data if needed
    if (frame.flap.payload_length > 0) {
        
        // Allocate memory for payload
        frame.payload = malloc(frame.flap.payload_length);
        
        if (frame.payload == NULL) {
            LOG_ERR("Unable to allocate memory for frame. Out of memory?");
            connection_close(conn);
            return;
        }
        
        // Read the rest frame
        bytes_read = connection_read(conn, frame.payload, frame.flap.payload_length);
        
         // Connection closed if bytes read 0 or less
        if (bytes_read <= 0) {
            return;
        }
        
        if (bytes_read != frame.flap.payload_length) {
            LOG_ERR("Unable to read rest of frame.");
            free(frame.payload);
            connection_close(conn);
            return;
        }
    }
    
    // Handle Frame
    prv_auth_server_handle_frame(conn, &frame);
    
    // Free up any allocated memory
    if (frame.payload != NULL) {
        free(frame.payload);
    }
}
