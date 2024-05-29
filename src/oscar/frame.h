/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file frame.h
 * @author Evan Stoddard
 * @brief Holistic frame
 */

#ifndef FRAME_H_
#define FRAME_H_

#include "flap.h"
#include "snac.h"

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
 * @brief Holistic protocol wrapped into frame
 * 
 */
typedef struct frame_t {
    flap_t flap;
    snac_t snac;
    void *payload;
    void *snac_blob;
} frame_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* FRAME_H_ */