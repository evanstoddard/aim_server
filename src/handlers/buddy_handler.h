/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file buddy_handler.h
 * @author Evan Stoddard
 * @brief BUDDY SNAC Handler
 */

#ifndef BUDDY_HANDLER_H_
#define BUDDY_HANDLER_H_

#include "connection.h"
#include "oscar/frame.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief Handle BUDDY SNAC Frame
 * 
 * @param conn Connection
 * @param frame Frame
 */
void buddy_handler_handle_frame(connection_t *conn, frame_t *frame);

#ifdef __cplusplus
}
#endif
#endif /* BUDDY_HANDLER_H_ */