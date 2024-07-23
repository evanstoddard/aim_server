/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file locate.h
 * @author Evan Stoddard
 * @brief Handler for locate SNACs
 */

#ifndef LOCATE_H_
#define LOCATE_H_

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
 * @brief Handle LOCATE Frame
 * 
 * @param conn Connection
 * @param frame Frame
 */
void locate_handle_frame(connection_t *conn, frame_t *frame);

#ifdef __cplusplus
}
#endif
#endif /* LOCATE_H_ */