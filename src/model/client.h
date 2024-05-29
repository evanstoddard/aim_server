/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file client.h
 * @author Evan Stoddard
 * @brief AIM Client Model
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/**
 * @brief Client Model Definition
 * 
 */
typedef struct client_t {
    char *screen_name;
    
    char *client_id_str;
    uint16_t client_id;
    
    uint16_t version_major;
    uint16_t version_minor;
    uint16_t version_lesser;
    uint16_t version_build;
    
    uint8_t ssi;
    
    char lang[3];
    char country[3];
} client_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief Initialize client object
 * 
 * @return client_t* 
 */
client_t* client_init(void);

/**
 * @brief Deinitialize client
 * 
 * @param client Pointer to client
 */
void client_deinit(client_t *client);

/**
 * @brief Log Client Info
 * 
 * @param client Pointer to Client
 */
void client_log_info(client_t *client);

#ifdef __cplusplus
}
#endif
#endif /* CLIENT_H_ */