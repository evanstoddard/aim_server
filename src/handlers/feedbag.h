/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file feedbag.h
 * @author Evan Stoddard
 * @brief Feedback SNAC Handler
 */

#ifndef FEEDBAG_H_
#define FEEDBAG_H_

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
 * @brief Handle Feedback frame
 * 
 * @param conn Connection
 * @param frame Frame
 */
void feedback_handle_frame(connection_t *conn, frame_t *frame);

#ifdef __cplusplus
}
#endif
#endif /* FEEDBAG_H_ */