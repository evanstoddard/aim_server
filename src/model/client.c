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

/*****************************************************************************
 * Definitions
 *****************************************************************************/


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
    
    free(client);
}

void client_log_info(client_t *client) {
    if (client == NULL) {
        return;
    }
    
    LOG_INFO("Client Info:");
    
    printf("\tScreen Name: %s\r\n", (client->user_info.uin ? client->user_info.uin : "N/A"));
    printf("\tEmail: %s\r\n", (client->user_info.email ? client->user_info.email : "N/A"));
    printf("\tID String: %s\r\n", (client->client_id_str ? client->client_id_str : "N/A"));
    printf("\tVersion: %u.%u.%u\r\n", client->version_major, client->version_minor, client->version_build);
    printf("\tClient Language: %s\r\n", client->lang);
    printf("\tClient Country: %s\r\n", client->country);
    
}