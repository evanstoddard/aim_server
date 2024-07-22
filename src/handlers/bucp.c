/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file bucp.c
 * @author Evan Stoddard
 * @brief BUCP SNAC Handler
 */

#include "bucp.h"

#include "oscar/flap.h"
#include "oscar/tlv.h"

#include "oscar/flap_decoder.h"
#include "oscar/snac_decoder.h"
#include "oscar/tlv_decoder.h"
#include "oscar/tlv_encoder.h"

#include "oscar/flap_encoder.h"
#include "oscar/snac_encoder.h"

#include "model/client.h"

#include "memory/buffer.h"

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
 * @brief Handle login request
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_bucp_handle_login_request(connection_t *conn, frame_t *frame);

/**
 * @brief Handle challenge request
 * 
 * @param conn Connection
 * @param frame Frame
 */
static void prv_bucp_handle_challenge_request(connection_t *conn, frame_t *frame);

/**
 * @brief Send challenge response
 * 
 * @param conn Connection
 */
static void prv_bucp_send_challenge_response(connection_t *conn);

/**
 * @brief Send successful loging response
 * 
 * @param conn Connection
 * @param client Client
 */
static void prv_bucp_send_login_response_success(connection_t *conn);

/**
 * @brief Send signoff flap
 * 
 * @param conn Connection
 */
static void prv_bucp_send_signoff_flap(connection_t *conn);

/*****************************************************************************
 * Private Functions
 *****************************************************************************/

/*****************************************************************************
 * Handlers
 *****************************************************************************/

static void prv_bucp_handle_login_request(connection_t *conn, frame_t *frame) {
    uint8_t *blob = frame->snac_blob;
    ssize_t blob_size = frame->flap.payload_length - sizeof(snac_t);
    ssize_t idx = 0;
    
    // Iterate through TLVs
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
            conn->client->version_major = version->version_major;
            break;
        }
        case TLV_TAG_VERSION_MINOR: {
            tlv_client_version_minor_f_t *version = (tlv_client_version_minor_f_t*)tlv.payload;
            conn->client->version_minor = version->version_minor;
            break;
        }
        case TLV_TAG_VERSION_LESSER: {
            tlv_client_version_lesser_f_t *version = (tlv_client_version_lesser_f_t*)tlv.payload;
            conn->client->version_lesser = version->version_lesser;
            break;
        }
        case TLV_TAG_BUILD_NUM: {
            tlv_client_build_number_f_t *build = (tlv_client_build_number_f_t*)tlv.payload;
            conn->client->version_build = build->build_number;
            break;
        }
        case TLV_TAG_CLIENT_ID: {
            tlv_client_id_f_t *client_id = (tlv_client_id_f_t*)tlv.payload;
            conn->client->client_id = client_id->client_id;
            break;
        }
        case TLV_TAG_CLIENT_LANG: {
            tlv_client_language_f_t *lang = (tlv_client_language_f_t*)tlv.payload;
            memcpy(conn->client->lang, lang->language, 2);
            break;
        }
        case TLV_TAG_CLIENT_COUNTRY: {
            tlv_client_country_f_t *country = (tlv_client_country_f_t*)tlv.payload;
            memcpy(conn->client->country, country->country, 2);
            break;
        }
        case TLV_TAG_SSI_FLAG: {
            tlv_client_ssi_flag_f_t *payload = (tlv_client_ssi_flag_f_t*)tlv.payload;
            conn->client->ssi = payload->ssi_flag;
            break;
        }
        case TLV_TAG_SCREEN_NAME: {
            char *uin = calloc(sizeof(char), tlv.header.length + 1);
            
            if (uin == NULL) {
                LOG_ERR("Unable to malloc space for screen name. Out of memory?");
                connection_close(conn);
                return;
            }

            memcpy(uin, tlv.payload, tlv.header.length);
            
            // Attempt to fetch user info
            bool ret = client_fetch_user_info_with_uin(conn->client, uin);
            free(uin);
            
            // TODO: Implement login failed response instead of silently dumping connection
            if (!ret) {
                LOG_ERR("Failed to find user.");
                connection_close(conn);
                return;
            }
            
            break;
        }
        case TLV_TAG_CLIENT_NAME: {
            conn->client->client_id_str = malloc(tlv.header.length + 1);
            memcpy(conn->client->client_id_str, tlv.payload, tlv.header.length);
            break;
        }
        case TLV_TAG_MD5_HASHED_PASSWORD: {
            bool valid_challenge = client_validate_challenge(conn->client, tlv.payload, tlv.header.length);
            
            if (valid_challenge == false) {
                // TODO: Implement login failed response instead of silently dumping connection.
                LOG_INFO("User challenge response incorrect.");
                connection_close(conn);
                return;
            }
            break;
        }
        default:
            break;
        }
        
        idx += sizeof(tlv_header_t) + tlv.header.length;
    }
    
    prv_bucp_send_login_response_success(conn);
}

static void prv_bucp_handle_challenge_request(connection_t *conn, frame_t *frame) {
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

    prv_bucp_send_challenge_response(conn);
    
}

/*****************************************************************************
 * Responses
 *****************************************************************************/

static void prv_bucp_send_challenge_response(connection_t *conn) {
    uint16_t payload_length = sizeof(snac_t);
    size_t buffer_size = sizeof(flap_t);
    
    // Encode SNAC
    snac_t snac = snac_encode(SNAC_FOODGROUP_ID_BUCP, BUCP_CHALLENGE_RESPONSE, 0, 0);
    
    // Generate challenge to pass to client
    if (client_generate_cipher(conn->client) == false) {
        LOG_ERR("Unable to generate challenge for client.");
        connection_close(conn);
        return;
    }
    
    uint16_t challenge_size = strlen(conn->client->challenge);
    uint16_t challenge_size_swapped = htons(challenge_size);
    
    payload_length += sizeof(challenge_size);
    payload_length += challenge_size;
    
    // Encode FLAP
    uint16_t sequence_number = conn->last_outbound_seq_num + 1;
    conn->last_outbound_seq_num = sequence_number;
    flap_t flap = flap_encode(FLAP_FRAME_TYPE_DATA, sequence_number, payload_length);
    
    buffer_size += payload_length;
    
    // Create outbound buffer
    buffer_t buffer = buffer_init();

    if (buffer == NULL) {
        LOG_ERR("Unable to allocate buffer.  Out of memory?");
        connection_close(conn);
        return;
    }
    
    buffer_write(buffer, &flap, sizeof(flap_t));
    buffer_write(buffer, &snac, sizeof(snac_t));
    buffer_write(buffer, &challenge_size_swapped, sizeof(uint16_t));
    buffer_write(buffer, conn->client->challenge, challenge_size);
    
    if (connection_write(conn, buffer_ptr(buffer), buffer_size) != buffer_size) {
        LOG_ERR("Failed to write to connection.");
    }
    
    buffer_deinit(buffer);
}

static void prv_bucp_send_login_response_success(connection_t *conn) {
    uint16_t payload_length = sizeof(snac_t);
    ssize_t buffer_size = sizeof(flap_t);
    
    // Encode SNAC
    snac_t snac = snac_encode(SNAC_FOODGROUP_ID_BUCP, BUCP_LOGIN_RESPONSE, 0, 0);
    
    // Create TLVs
    tlv_t uid_tlv;
    ssize_t uid_tlv_size = tlv_encode_screen_name(&uid_tlv, conn->client->user_info.uin);
    ssize_t uid_payload_size = uid_tlv_size - sizeof(tlv_header_t);
    payload_length += uid_tlv_size;
    
    tlv_t bos_address_tlv;
    ssize_t bos_address_tlv_size = tlv_encode_bos_address(&bos_address_tlv, "192.168.86.50:5191");
    ssize_t bos_address_payload_size = bos_address_tlv_size - sizeof(tlv_header_t);
    payload_length += bos_address_tlv_size;
    
    // TODO: Create real cookie and base64 encode.
    tlv_t login_cookie_tlv;
    ssize_t login_cookie_tlv_size = tlv_encode_login_cookie(&login_cookie_tlv, conn->client->user_info.uin);
    ssize_t login_cookie_payload_size = login_cookie_tlv_size - sizeof(tlv_header_t);
    payload_length += login_cookie_tlv_size;

    tlv_t email_address_tlv;
    ssize_t email_address_tlv_size = tlv_encode_email_address(&email_address_tlv, conn->client->user_info.email);
    ssize_t email_address_payload_size = email_address_tlv_size - sizeof(tlv_header_t);
    payload_length += email_address_tlv_size;

    // Encode FLAP
    uint16_t sequence_number = conn->last_outbound_seq_num + 1;
    conn->last_outbound_seq_num = sequence_number;
    flap_t flap = flap_encode(FLAP_FRAME_TYPE_DATA, sequence_number, payload_length);
    
    buffer_size += payload_length;
    
    // Create outbound buffer
    buffer_t buffer = buffer_init();
    
    if (buffer == NULL) {
        LOG_ERR("Unable to allocate buffer.  Out of memory?");
        connection_close(conn);
    }
    
    buffer_write(buffer, &flap, sizeof(flap));
    buffer_write(buffer, &snac, sizeof(snac_t));
    buffer_write(buffer, &uid_tlv.header, sizeof(tlv_header_t));
    buffer_write(buffer, uid_tlv.payload, uid_payload_size);
    buffer_write(buffer, &bos_address_tlv.header, sizeof(tlv_header_t));
    buffer_write(buffer, bos_address_tlv.payload, bos_address_payload_size);
    buffer_write(buffer, &login_cookie_tlv.header, sizeof(tlv_header_t));
    buffer_write(buffer, login_cookie_tlv.payload, login_cookie_payload_size);
    buffer_write(buffer, &email_address_tlv.header, sizeof(tlv_header_t));
    buffer_write(buffer, email_address_tlv.payload, email_address_payload_size);
    
    if (connection_write(conn, buffer_ptr(buffer), buffer_size) != buffer_size) {
        LOG_ERR("Failed to write to connection.");
    }
    
    buffer_deinit(buffer);
    
    LOG_INFO("Writing signoff flap.");
    prv_bucp_send_signoff_flap(conn);
    
    connection_close(conn);
}

static void prv_bucp_send_signoff_flap(connection_t *conn) {
    // Encode FLAP
    uint16_t sequence_number = conn->last_outbound_seq_num + 1;
    conn->last_outbound_seq_num = sequence_number;
    flap_t flap = flap_encode(FLAP_FRAME_TYPE_DATA, sequence_number, 0);
    
    // Send signoff FLAP
    connection_write(conn, &flap, sizeof(flap_t));
}

/*****************************************************************************
 * Public Functions
 *****************************************************************************/

void bucp_handle_frame(connection_t *conn, frame_t *frame) {
    // Call appropriate subgroup handler
    switch(frame->snac.subgroup_id) {
    case BUCP_ERR:
        // TODO: Implement BUCP_ERR Handler
        LOG_WARN("BUCP_ERR handler not implemented.");
        break;
    case BUCP_LOGIN_REQUEST:
        prv_bucp_handle_login_request(conn, frame);
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
        prv_bucp_handle_challenge_request(conn, frame);
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