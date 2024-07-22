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
#include <stdbool.h>
#include <stddef.h>

#include "model_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

#define CLIENT_MD5_AIM_STRING "AOL Instant Messenger (SM)"

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/**
 * @brief Client Model Definition
 * 
 */
typedef struct client_t {
    user_info_t user_info;
    
    char *client_id_str;
    uint16_t client_id;
    
    uint16_t version_major;
    uint16_t version_minor;
    uint16_t version_lesser;
    uint16_t version_build;
    
    uint8_t ssi;
    
    char lang[3];
    char country[3];
    
    char *challenge;
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
 * @brief Get user info from UIN
 * 
 * @param client Pointer to client
 * @param uin User UIN
 * @return true Able to fetch user info
 * @return false Unable to fetch user info
 */
bool client_fetch_user_info_with_uin(client_t *client, char *uin);

/**
 * @brief Get user info from email address
 * 
 * @param client Pointer to client
 * @param email User email address
 * @return true Able to fetch user info
 * @return false Unable to fetch user info
 */
bool client_fetch_user_info_with_email(client_t *client, char *email);

/**
 * @brief Get client object from UIN
 * 
 * @param uin UIN (Screen name)
 * @return client_t* Fetched client (NULL of client not found)
 */
client_t* client_from_uin(char *uin);

/**
 * @brief Deinitialize client
 * 
 * @param client Pointer to client
 */
void client_deinit(client_t *client);

/**
 * @brief Generate base 32 cipher.
 * 
 * @return char* Pointer to cipher (must be freed after use)
 */

/**
 * @brief Generate base32 challenge cipher
 * 
 * @param client Pointer to client
 * @return true Able to generate cipher
 * @return false Unable to generate cipher
 */
bool client_generate_cipher(client_t *client);

/**
 * @brief Validate challenge response
 * 
 * @param client Pointer to client
 * @param challenge Pointer to challenge response
 * @param challenge_size Size of challenge response
 * @return true Challenge response valid
 * @return false Challenge response invalid
 */
bool client_validate_challenge(client_t *client, uint8_t *challenge, size_t challenge_size);

#ifdef __cplusplus
}
#endif
#endif /* CLIENT_H_ */