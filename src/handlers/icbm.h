/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file icbm.h
 * @author Evan Stoddard
 * @brief ICBM SNAC Handler
 */

#ifndef ICBM_H_
#define ICBM_H_

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
 * @brief Handle ICBM snac frame
 * 
 * @param conn Connection
 * @param frame Frame
 */
void icbm_handle_frame(connection_t *conn, frame_t *frame);

#ifdef __cplusplus
}
#endif
#endif /* ICBM_H_ */