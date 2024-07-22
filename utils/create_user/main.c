/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file main.c
 * @author Evan Stoddard
 * @brief Tool to create users
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#include "backends/backend.h"
#include "backends/sqlite3/sqlite3_backend.h"

#include "model/model_types.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

#define INPUT_BUFFER_SIZE_BYTES 64

/*****************************************************************************
 * Variables
 *****************************************************************************/

static sqlite3_backend_t data_backend;

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/**
 * @brief Get user input
 * 
 * @param dest Destination buffer
 * @param size Size of destination buffer
 * @return int Size of input (Doesn't include line break)
 */
static int get_input(char *dest, size_t size);

/**
 * @brief Check if user exists with given UIN
 * 
 * @param uin UIN to check for 
 * @return true User exists with UIN
 * @return false User does not exist with UIN
 */
static bool uin_exists(char *uin);

/**
 * @brief Check if user exists with given email
 * 
 * @param email Email to check for
 * @return true User exists with Email
 * @return false User does not exist with Email
 */
static bool email_exists(char *email);

/*****************************************************************************
 * Functions
 *****************************************************************************/

static int get_input(char *dest, size_t size) {
    char *ret = fgets(dest, size, stdin);
    
    if (ret == NULL) {
        return 0;
    }
    
    unsigned int len = strlen(dest);
    if (len == 0) {
        return 0;
    }
    
    dest[len - 1] = '\0';
    
    return len - 1;
}

int main(int argc, char **argv) {
    // Create backend
    if (argc < 2) {
        printf("Please provide path to SQLite3 database.\r\n");
        return 1;
    }
    
    if (!sqlite3_backend_init(&data_backend, argv[1])) {
        printf("Unable to initialize data backend.\r\n");
        return 1;
    }
    
    backend_set_backend((backend_t *)&data_backend);
    
    // Create user model
    char uin[INPUT_BUFFER_SIZE_BYTES] = {0};
    char email[INPUT_BUFFER_SIZE_BYTES] = {0};
    char password[INPUT_BUFFER_SIZE_BYTES] = {0};
    
    user_info_t user;
    user.email = email;
    user.uin = uin;
    
    while (true) {
        puts("");
        
        // Prompt for username
        printf("UIN: ");
        if (!get_input(user.uin, INPUT_BUFFER_SIZE_BYTES)) {
            printf("Error: Please enter valid UIN.\r\n");
            continue;
        }
        
        printf("Email: ");
        if (!get_input(user.email, INPUT_BUFFER_SIZE_BYTES)) {
            printf("Error: Please enter valid email.\r\n");
            continue;
        }
        
        printf("Password: ");
        if (!get_input(password, INPUT_BUFFER_SIZE_BYTES)) {
            printf("Error: Please enter valid password.\r\n");
            continue;
        }
        
        backend_ret_t ret = backend_create_user(user.uin, user.email, password);
        
        if (ret == BACKEND_RET_USER_ALREADY_EXISTS) {
            printf("Error: User already exists!\r\n");
            continue;
        }
        
        if (ret == BACKEND_RET_EMAIL_ALREADY_EXISTS) {
            printf("Error: Email already exists!\r\n");
            continue;
        }
        
        puts("");
        printf("Creating user with the following information:\r\n");
        printf("\tUIN: %s\r\n", user.uin);
        printf("\tEmail: %s\r\n", user.email);
        puts("");
    }

    return 0;
}
