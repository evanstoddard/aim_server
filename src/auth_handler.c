/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file auth_handler.c
 * @author Evan Stoddard
 * @brief Handlers for auth requests
 */

#include "auth_handler.h"

#include "oscar/flap.h"
#include "oscar/frame.h"
#include "oscar/tlv.h"

#include "oscar/flap_decoder.h"
#include "oscar/snac_decoder.h"
#include "oscar/tlv_decoder.h"

#include "oscar/flap_encoder.h"
#include "oscar/snac_encoder.h"

#include "model/client.h"

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
 * @brief Handle received frame
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_auth_handler_handle_frame(connection_t *conn, frame_t *frame);

/**
 * @brief Handle signon frame
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_auth_handler_handle_signon_frame(connection_t *conn, frame_t *frame);

/**
 * @brief Handle normal data frame
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_auth_handler_handle_data_frame(connection_t *conn, frame_t *frame);

/**
 * @brief Handle BUCP foodgroup message
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_auth_handler_handle_bucp_foodgroup(connection_t *conn, frame_t *frame);

/**
 * @brief Handle BUCP login request
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_auth_handler_handle_bucp_login_request(connection_t *conn, frame_t *frame);

/**
 * @brief Handle BUCP challenge request
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_auth_handler_handle_bucp_challenge_request(connection_t *conn, frame_t *frame);

/**
 * @brief Send BUCP challence response
 * 
 * @param conn Connection
 */
static void prv_auth_handler_send_bucp_challenge_response(connection_t *conn);


/*****************************************************************************
 * Public Functions
 *****************************************************************************/

void auth_handler_handle_new_connection(connection_t *conn) {
    if (conn == NULL) {
        return;
    }
    
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

void auth_handler_connection_receive(connection_t *conn) {
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
    prv_auth_handler_handle_frame(conn, &frame);
    
    // Free up any allocated memory
    if (frame.payload != NULL) {
        free(frame.payload);
    }
}

/*****************************************************************************
 * Private Functions
 *****************************************************************************/

static void prv_auth_handler_handle_frame(connection_t *conn, frame_t *frame) {
    // Parse FLAP type
    switch(frame->flap.frame_type) {
    case FLAP_FRAME_TYPE_SIGNON:
        prv_auth_handler_handle_signon_frame(conn, frame);
        break;
    case FLAP_FRAME_TYPE_DATA:
        prv_auth_handler_handle_data_frame(conn, frame);
        break;
    default:
        break;
    }
}

static void prv_auth_handler_handle_signon_frame(connection_t *conn, frame_t *frame) {
    // TODO: Implement Handle Signon Frame
}

static void prv_auth_handler_handle_data_frame(connection_t *conn, frame_t *frame) {
    // Parse snac
    bool ret = snac_decode(&frame->snac, frame->payload, frame->flap.payload_length);
    
    if (!ret) {
        LOG_ERR("Unable to parse SNAC. Malformed frame.");
        connection_close(conn);
        return;
    }
    
    frame->snac_blob = frame->payload + sizeof(snac_t);
    
    switch(frame->snac.foodgroup_id) {
    case SNAC_FOOTGROUP_ID_LOCATE:
        // TODO: Implement SNAC_FOOTGROUP_ID_LOCATE handler
        LOG_WARN("SNAC_FOOTGROUP_ID_LOCATE handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_OSERVICE:
        // TODO: Implement SNAC_FOOTGROUP_ID_OSERVICE handler
        LOG_WARN("SNAC_FOOTGROUP_ID_OSERVICE handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_BUDDY:
        // TODO: Implement SNAC_FOOTGROUP_ID_BUDDY handler
        LOG_WARN("SNAC_FOOTGROUP_ID_BUDDY handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_ICBM:
        // TODO: Implement SNAC_FOOTGROUP_ID_ICBM handler
        LOG_WARN("SNAC_FOOTGROUP_ID_ICBM handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_ADVERT:
        // TODO: Implement SNAC_FOOTGROUP_ID_ADVERT handler
        LOG_WARN("SNAC_FOOTGROUP_ID_ADVERT handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_INVITE:
        // TODO: Implement SNAC_FOOTGROUP_ID_INVITE handler
        LOG_WARN("SNAC_FOOTGROUP_ID_INVITE handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_ADMIN:
        // TODO: Implement SNAC_FOOTGROUP_ID_ADMIN handler
        LOG_WARN("SNAC_FOOTGROUP_ID_ADMIN handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_POPUP:
        // TODO: Implement SNAC_FOOTGROUP_ID_POPUP handler
        LOG_WARN("SNAC_FOOTGROUP_ID_POPUP handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_PD:
        // TODO: Implement SNAC_FOOTGROUP_ID_PD handler
        LOG_WARN("SNAC_FOOTGROUP_ID_PD handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_USER_LOOKUP:
        // TODO: Implement SNAC_FOOTGROUP_ID_USER_LOOKUP handler
        LOG_WARN("SNAC_FOOTGROUP_ID_USER_LOOKUP handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_STATS:
        // TODO: Implement SNAC_FOOTGROUP_ID_STATS handler
        LOG_WARN("SNAC_FOOTGROUP_ID_STATS handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_TRANSLATE:
        // TODO: Implement SNAC_FOOTGROUP_ID_TRANSLATE handler
        LOG_WARN("SNAC_FOOTGROUP_ID_TRANSLATE handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_CHAT:
        // TODO: Implement SNAC_FOOTGROUP_ID_CHAT handler
        LOG_WARN("SNAC_FOOTGROUP_ID_CHAT handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_ODIR:
        // TODO: Implement SNAC_FOOTGROUP_ID_ODIR handler
        LOG_WARN("SNAC_FOOTGROUP_ID_ODIR handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_BART:
        // TODO: Implement SNAC_FOOTGROUP_ID_BART handler
        LOG_WARN("SNAC_FOOTGROUP_ID_BART handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_FEEDBAG:
        // TODO: Implement SNAC_FOOTGROUP_ID_FEEDBAG handler
        LOG_WARN("SNAC_FOOTGROUP_ID_FEEDBAG handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_ICQ:
        // TODO: Implement SNAC_FOOTGROUP_ID_ICQ handler
        LOG_WARN("SNAC_FOOTGROUP_ID_ICQ handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_BUCP:
        prv_auth_handler_handle_bucp_foodgroup(conn, frame);
        break;
    case SNAC_FOOTGROUP_ID_ALERT:
        // TODO: Implement SNAC_FOOTGROUP_ID_ALERT handler
        LOG_WARN("SNAC_FOOTGROUP_ID_ALERT handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_PLUGIN:
        // TODO: Implement SNAC_FOOTGROUP_ID_PLUGIN handler
        LOG_WARN("SNAC_FOOTGROUP_ID_PLUGIN handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_MDIR:
        // TODO: Implement SNAC_FOOTGROUP_ID_MDIR handler
        LOG_WARN("SNAC_FOOTGROUP_ID_MDIR handler not implemented.");
        break;
    case SNAC_FOOTGROUP_ID_ARS:
        // TODO: Implement SNAC_FOOTGROUP_ID_ARS handler
        LOG_WARN("SNAC_FOOTGROUP_ID_ARS handler not implemented.");
        break;
    default:
        LOG_WARN("Unknown SNAC ID.");
        break;
    }
}

/*****************************************************************************
 * BUCP Handlers
 *****************************************************************************/

static void prv_auth_handler_handle_bucp_foodgroup(connection_t *conn, frame_t *frame) {
    // Call appropriate subgroup handler
    switch(frame->snac.subgroup_id) {
    case BUCP_ERR:
        // TODO: Implement BUCP_ERR Handler
        LOG_WARN("BUCP_ERR handler not implemented.");
        break;
    case BUCP_LOGIN_REQUEST:
        prv_auth_handler_handle_bucp_login_request(conn, frame);
        break;
    case BUCP_REGISTER_REQUEST:
        // TODO: Implement BUCP_REGISTER_REQUEST Handler
        LOG_WARN("BUCP_REGISTER_REQUEST handler not implemented.");
        break;
    case BUCP_REGISTER_RESPONSE:
        // TODO: Implement BUCP_REGISTER_RESPONSE Handler
        LOG_WARN("BUCP_REGISTER_RESPONSE handler not implemented.");
        break;
    case BUCP_CHALLENGE_REQUEST:
        prv_auth_handler_handle_bucp_challenge_request(conn, frame);
        break;
    case BUCP_CHALLENGE_RESPONSE:
        // TODO: Implement BUCP_CHALLENGE_RESPONSE Handler
        LOG_WARN("BUCP_CHALLENGE_RESPONSE handler not implemented.");
        break;
    case BUCP_ASASN_REQUEST:
        // TODO: Implement BUCP_ASASN_REQUEST Handler
        LOG_WARN("BUCP_ASASN_REQUEST handler not implemented.");
        break;
    case BUCP_ASASN_RESPONSE:
        // TODO: Implement BUCP_ASASN_RESPONSE Handler
        LOG_WARN("BUCP_ASASN_RESPONSE handler not implemented.");
        break;
    case BUCP_SECURID_REQUEST:
        // TODO: Implement BUCP_SECURID_REQUEST Handler
        LOG_WARN("BUCP_SECURID_REQUEST handler not implemented.");
        break;
    case BUCP_SECURID_RESPONSE:
        // TODO: Implement BUCP_SECURID_RESPONSE Handler
        LOG_WARN("BUCP_SECURID_RESPONSE handler not implemented.");
        break;
    case BUCP_REGISTRATION_IMAGE:
        // TODO: Implement BUCP_REGISTRATION_IMAGE Handler
        LOG_WARN("BUCP_REGISTRATION_IMAGE handler not implemented.");
        break;
    case BUCP_REGISTRATION_RESPONSE:
        // TODO: Implement BUCP_REGISTRATION_RESPONSE Handler
        LOG_WARN("BUCP_REGISTRATION_RESPONSE handler not implemented.");
        break;
    default:
        break;
    }
}

static void prv_auth_handler_handle_bucp_login_request(connection_t *conn, frame_t *frame) {
    uint8_t *blob = frame->snac_blob;
    ssize_t blob_size = frame->flap.payload_length - sizeof(snac_t);
    ssize_t idx = 0;
    
    client_t *client = client_init();
    
    if (client == NULL) {
        LOG_ERR("Unable to create client. Out of memory?");
        connection_close(conn);
        return;
    }
    
    // Iterate throut TLVs
    while (idx < blob_size) {
        ssize_t remaining_bytes = blob_size - idx;
        
        uint8_t *ptr = &blob[idx];
        tlv_t tlv;
        
        bool ret = tlv_decode(&tlv, ptr, remaining_bytes);

        if (!ret) {
            LOG_ERR("Failed to parse TLV.");
            connection_close(conn);
            return;
        }
        
        switch (tlv.header.tag) {
        case TLV_TAG_VERSION_MAJOR: {
            tlv_client_version_major_f_t *version = (tlv_client_version_major_f_t*)tlv.payload;
            client->version_major = version->version_major;
            break;
        }
        case TLV_TAG_VERSION_MINOR: {
            tlv_client_version_minor_f_t *version = (tlv_client_version_minor_f_t*)tlv.payload;
            client->version_minor = version->version_minor;
            break;
        }
        case TLV_TAG_VERSION_LESSER: {
            tlv_client_version_lesser_f_t *version = (tlv_client_version_lesser_f_t*)tlv.payload;
            client->version_lesser = version->version_lesser;
            break;
        }
        case TLV_TAG_BUILD_NUM: {
            tlv_client_build_number_f_t *build = (tlv_client_build_number_f_t*)tlv.payload;
            client->version_build = build->build_number;
            break;
        }
        case TLV_TAG_CLIENT_ID: {
            tlv_client_id_f_t *client_id = (tlv_client_id_f_t*)tlv.payload;
            client->client_id = client_id->client_id;
            break;
        }
        case TLV_TAG_CLIENT_LANG: {
            tlv_client_language_f_t *lang = (tlv_client_language_f_t*)tlv.payload;
            memcpy(client->lang, lang->language, 2);
            break;
        }
        case TLV_TAG_CLIENT_COUNTRY: {
            tlv_client_country_f_t *country = (tlv_client_country_f_t*)tlv.payload;
            memcpy(client->country, country->country, 2);
            break;
        }
        case TLV_TAG_SSI_FLAG: {
            tlv_client_ssi_flag_f_t *payload = (tlv_client_ssi_flag_f_t*)tlv.payload;
            client->ssi = payload->ssi_flag;
            break;
        }
        case TLV_TAG_SCREEN_NAME: {
            client->screen_name = malloc(tlv.header.length + 1);
            memcpy(client->screen_name, tlv.payload, tlv.header.length);
            break;
        }
        case TLV_TAG_CLIENT_NAME: {
            client->client_id_str = malloc(tlv.header.length + 1);
            memcpy(client->client_id_str, tlv.payload, tlv.header.length);
            break;
        }
        default:
            break;
        }
        
        idx += sizeof(tlv_header_t) + tlv.header.length;
    }
    
    client_log_info(client);
}

static void prv_auth_handler_handle_bucp_challenge_request(connection_t *conn, frame_t *frame) {
    uint8_t *blob = frame->snac_blob;
    ssize_t blob_size = frame->flap.payload_length - sizeof(snac_t);
    ssize_t idx = 0;
    
    // Note, will not be null terminated
    char *screenname = NULL;
    uint16_t screenname_size = 0;
    
    // Iterate throut TLVs
    while (idx < blob_size) {
        ssize_t remaining_bytes = blob_size - idx;
        
        uint8_t *ptr = &blob[idx];
        tlv_t tlv;
        
        bool ret = tlv_decode(&tlv, ptr, remaining_bytes);

        if (!ret) {
            LOG_ERR("Failed to parse TLV.");
            connection_close(conn);
            return;
        }
        
        idx += sizeof(tlv_header_t) + tlv.header.length;
        
        switch(tlv.header.tag) {
        case TLV_TAG_SCREEN_NAME:
            screenname = tlv.payload;
            screenname_size = tlv.header.length;
            break;
        default:
            break;
        }
    }
    
    if (screenname == NULL) {
        LOG_ERR("Screenname not part of request.");
        connection_close(conn);
        return;
    }
    
    // Copy screenname to connection
    memcpy(conn->screenname, screenname, screenname_size);

    prv_auth_handler_send_bucp_challenge_response(conn);
    
}

static void prv_auth_handler_send_bucp_challenge_response(connection_t *conn) {
    uint16_t payload_length = sizeof(snac_t);
    ssize_t buffer_size = sizeof(flap_t);
    
    // Encode SNAC
    snac_t snac = snac_encode(SNAC_FOOTGROUP_ID_BUCP, BUCP_CHALLENGE_RESPONSE, 0, 0);
    
    // TODO: Fetch actual salt and encode in frame.
    char challenge[] = "b04ec0ade3d49b4a079f0e207d5e2821";
    uint16_t challenge_size = sizeof(challenge) - 1;
    uint16_t challenge_size_swapped = htons(challenge_size);
    
    payload_length += sizeof(challenge_size);
    payload_length += challenge_size;
    
    // Encode FLAP
    uint16_t sequence_number = conn->last_outbound_seq_num + 1;
    conn->last_outbound_seq_num = sequence_number;
    flap_t flap = flap_encode(FLAP_FRAME_TYPE_DATA, sequence_number, payload_length);
    
    buffer_size += payload_length;
    
    // Create outbound buffer
    ssize_t offset = 0;
    uint8_t *buffer = malloc(buffer_size);
    
    if (buffer == NULL) {
        LOG_ERR("Unable to allocate buffer.  Out of memory?");
        connection_close(conn);
    }
    
    memcpy(&buffer[offset], &flap, sizeof(flap_t));
    offset += sizeof(flap_t);
    
    memcpy(&buffer[offset], &snac, sizeof(snac_t));
    offset += sizeof(snac_t);
    
    memcpy(&buffer[offset], &challenge_size_swapped, sizeof(uint16_t));
    offset += sizeof(uint16_t);
    
    memcpy(&buffer[offset], challenge, challenge_size);
    
    if (connection_write(conn, buffer, buffer_size) != buffer_size) {
        LOG_ERR("Failed to write to connection.");
    }
    
    free(buffer);
}