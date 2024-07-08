/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file model_types.h
 * @author Evan Stoddard
 * @brief Various model types
 */

#ifndef MODEL_TYPES_H_
#define MODEL_TYPES_H_

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
 * @brief User info typedef
 * 
 */
typedef struct user_info_t {
    char *uin;
    char *email;
} user_info_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* MODEL_TYPES_H_ */