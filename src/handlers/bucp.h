/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file bucp.h
 * @author Evan Stoddard
 * @brief BUCP SNAC Handler
 */

#ifndef BUCP_H_
#define BUCP_H_

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
 * @brief Handle BUCP frame
 * 
 * @param conn Connection
 * @param frame Frame
 */
void bucp_handle_frame(connection_t *conn, frame_t *frame);

#ifdef __cplusplus
}
#endif
#endif /* BUCP_H_ */