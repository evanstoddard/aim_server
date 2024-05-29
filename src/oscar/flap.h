/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file flap.h
 * @author Evan Stoddard
 * @brief Definition of FLAP
 */

#ifndef FLAP_H_
#define FLAP_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

#define FLAP_START_MARKER '*'

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/**
 * @brief Enum outline frame type
 * 
 */
typedef enum {
    FLAP_FRAME_TYPE_SIGNON = 0x1,
    FLAP_FRAME_TYPE_DATA = 0x2,
    FLAP_FRAME_TYPE_ERROR = 0x3,
    FLAP_FRAME_TYPE_SIGNOFF = 0x4,
    FLAP_FRAME_TYPE_KEEPALIVE = 0x5,
} __attribute__((packed)) flap_frame_type_t;

/**
 * @brief Definition of FLAP type
 * 
 */
typedef struct flap_t {
    uint8_t start_marker;
    uint8_t frame_type;
    uint16_t sequence_number;
    uint16_t payload_length;
} __attribute__((packed)) flap_t;

typedef struct flap_signon_frame_t {
    flap_t header;
    uint32_t flap_version;
} __attribute__((packed)) flap_signon_frame_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* FLAP_H_ */