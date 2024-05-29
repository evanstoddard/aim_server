/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file client.c
 * @author Evan Stoddard
 * @brief AIM Client Model
 */

#include "client.h"

#include "logging.h"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

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

client_t* client_init(void) {
    client_t *client = malloc(sizeof(client_t));
    
    if (client == NULL) {
        return NULL;
    }
    
    memset(client, 0, sizeof(client_t));
    
    return client;
}

void client_deinit(client_t *client) {
    if (client == NULL) {
        return;
    }
    
    if (client->screen_name) {
        free(client->screen_name);
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
    
    printf("\tScreen Name: %s\r\n", (client->screen_name ? client->screen_name : "N/A"));
    printf("\tID String: %s\r\n", (client->client_id_str ? client->client_id_str : "N/A"));
    printf("\tVersion: %u.%u.%u\r\n", client->version_major, client->version_minor, client->version_build);
    printf("\tClient Language: %s\r\n", client->lang);
    printf("\tClient Country: %s\r\n", client->country);
    
}