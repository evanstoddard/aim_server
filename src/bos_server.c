/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file bos_server.c
 * @author Evan Stoddard
 * @brief BOSS server implementation
 */

#include "bos_server.h"

#include "oscar/flap.h"
#include "oscar/frame.h"

#include "oscar/flap_decoder.h"
#include "oscar/snac_decoder.h"

#include "oscar/flap_encoder.h"
#include "oscar/snac_encoder.h"

#include "model/client.h"

#include "handlers/oservice.h"
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
 * @brief Handle signon frame
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_bos_server_handle_signon_frame(connection_t *conn, frame_t *frame);

/**
 * @brief Handle normal data frame
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_bos_server_handle_data_frame(connection_t *conn, frame_t *frame);

/**
 * @brief Handle signoff frame;
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_bos_server_handle_signoff_frame(connection_t *conn, frame_t *frame);

/**
 * @brief Handle keepalive frame;
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_bos_server_handle_keepalive_frame(connection_t *conn, frame_t *frame);

/*****************************************************************************
 * Private Functions
 *****************************************************************************/

static void prv_bos_server_handle_frame(connection_t *conn, frame_t *frame) {
    // Parse FLAP type
    switch(frame->flap.frame_type) {
    case FLAP_FRAME_TYPE_SIGNON:
        prv_bos_server_handle_signon_frame(conn, frame);
        break;
    case FLAP_FRAME_TYPE_DATA:
        prv_bos_server_handle_data_frame(conn, frame);
        break;
    case FLAP_FRAME_TYPE_SIGNOFF:
        prv_bos_server_handle_signoff_frame(conn, frame);
        break;
    case FLAP_FRAME_TYPE_KEEPALIVE:
        prv_bos_server_handle_keepalive_frame(conn, frame);
        break;
    default:
        LOG_INFO("Unhandled Frame Type: 0x%02X", frame->flap.frame_type);
        break;
    }
}

static void prv_bos_server_handle_signon_frame(connection_t *conn, frame_t *frame) {
    // TODO: Find client info and authenticate
   
    oservice_send_host_online_response(conn);
}

static void prv_bos_server_handle_signoff_frame(connection_t *conn, frame_t *frame) {
    LOG_INFO("Received signoff frame from client.");
    connection_close(conn);
}

static void prv_bos_server_handle_keepalive_frame(connection_t *conn, frame_t *frame) {
    LOG_INFO("Keep-alive frame received from client.");
}

static void prv_bos_server_handle_data_frame(connection_t *conn, frame_t *frame) {
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
        oservice_handle_frame(conn, frame);
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
        // TODO: Implement SNAC_FOODGROUP_ID_BUCP handler
        LOG_WARN("SNAC_FOODGROUP_ID_BUCP handler not implemented.");
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

void bos_server_handle_new_connection(connection_t *conn) {
    if (conn == NULL) {
        return;
    }
    LOG_INFO("Handling new boss connection.");
    
    // Set connection event callback
    conn->callbacks.on_event = bos_server_handle_event;
    
    // Create start message
    struct {
        flap_t header;
        uint32_t version;
    } __attribute__((packed)) signon_frame;
    
    signon_frame.header = flap_encode(FLAP_FRAME_TYPE_SIGNON, 0, sizeof(uint32_t));
    signon_frame.version = htonl(1);
    
    ssize_t ret = connection_write(conn, &signon_frame, sizeof(signon_frame));
    
    if (ret == -1 || ret == 0) {
        LOG_WARN("Failed to send auth start frame.");
    }
}

void bos_server_handle_event(connection_t *conn) {
    if (conn == NULL) {
        return;
    }
    
    LOG_INFO("Handling BOS Event.");
    
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
    prv_bos_server_handle_frame(conn, &frame);
    
    // Free up any allocated memory
    if (frame.payload != NULL) {
        free(frame.payload);
    }
}
