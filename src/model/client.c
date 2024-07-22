/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file client.c
 * @author Evan Stoddard
 * @brief AIM Client Model
 */

#include "client.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "logging.h"
#include "backends/backend.h"
#include "utils/random.h"
#include "md5.h"
#include "base32/base32.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

#define CLIENT_AUTH_MD5_MAGIC "AOL Instant Messenger (SM)"

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/*****************************************************************************
 * Variables
 *****************************************************************************/

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Public Functions
 *****************************************************************************/


/*****************************************************************************
 * Public Functions
 *****************************************************************************/

client_t* client_init(void) {
    client_t *client = malloc(sizeof(client_t));
    
    if (client == NULL) {
        return NULL;
    }
    
    memset(client, 0, sizeof(client_t));
    
    return client;
}

bool client_fetch_user_info_with_uin(client_t *client, char *uin) {
    if (client == NULL || uin == NULL) {
        return false;
    }
    
    backend_ret_t ret = backend_fetch_user_info_with_uin(uin, &client->user_info);
    
    if (ret != BACKEND_RET_SUCCESS) {
        return false;
    }
    
    return true;
}

bool client_fetch_user_info_with_email(client_t *client, char *email) {
    if (client == NULL || email == NULL) {
        return false;
    }
    
    backend_ret_t ret = backend_fetch_user_info_with_email(email, &client->user_info);
    
    if (ret != BACKEND_RET_SUCCESS) {
        return false;
    }
    
    return true;
}

void client_deinit(client_t *client) {
    if (client == NULL) {
        return;
    }
    
    if (client->user_info.uin) {
        free(client->user_info.uin);
    }
    
    if (client->user_info.email) {
        free(client->user_info.email);
    }
    
    if (client->client_id_str) {
        free(client->client_id_str);
    }
    
    if (client->challenge) {
        free(client->challenge);
    }
    
    free(client);
}

bool client_generate_cipher(client_t *client) {
    if (client == NULL) {
        return false;
    }
    
    // This case should never exist, but free any previous challenge ciphers...
    if (client->challenge != NULL) {
        free(client->challenge);
        client->challenge == NULL;
    }
    
    // Generate 64 random bytes
    uint8_t random_bytes[64] = {0};
    generate_random_stream(random_bytes, 64);
    
    size_t len = base32_encode_alloc(random_bytes, sizeof(random_bytes), &client->challenge);
    return (len != 0);
}

bool client_validate_challenge(client_t *client, uint8_t *challenge, size_t challenge_size) {
    if (
        client == NULL ||
        challenge == NULL
    ) {
        return false;
    }
    
    if (client->challenge == NULL) {
        return false;
    }
    
    MD5Context md5_ctx;
    md5Init(&md5_ctx);
    
    if (challenge_size != sizeof(md5_ctx.digest)) {
        return false;
    }
    
    // Generate expected challenge response
    md5Update(&md5_ctx, client->challenge, strlen(client->challenge));
    md5Update(&md5_ctx, client->user_info.md5_password, sizeof(client->user_info.md5_password));
    md5Update(&md5_ctx, CLIENT_AUTH_MD5_MAGIC, strlen(CLIENT_AUTH_MD5_MAGIC));
    md5Finalize(&md5_ctx);
    
    int ret = memcmp(challenge, md5_ctx.digest, sizeof(md5_ctx.digest));
    
    return (ret == 0);
}