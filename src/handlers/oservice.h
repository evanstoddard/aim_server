/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file oservice.h
 * @author Evan Stoddard
 * @brief OSERVICE SNAC Foodgroup Handlers
 */

#ifndef OSERVICE_H_
#define OSERVICE_H_

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
 * @brief handle OSERVICE Frame
 * 
 * @param conn Connection
 * @param frame Frame
 */
void oservice_handle_frame(connection_t *conn, frame_t *frame);

/*****************************************************************************
 * Response Function Prototypes
 *****************************************************************************/

/**
 * @brief Send host online payload
 * 
 * @param conn Connection
 */
void oservice_send_host_online_response(connection_t *conn);

#ifdef __cplusplus
}
#endif
#endif /* OSERVICE_H_ */