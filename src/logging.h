/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file logging.h
 * @author Evan Stoddard
 * @brief Defines Macros for Logging
 */

#ifndef LOGGING_H_
#define LOGGING_H_

#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

#define LOG_DEBUG(msg, ...) fprintf(stdout, "DEBUG (%s): " msg "\r\n", __PRETTY_FUNCTION__, ## __VA_ARGS__);
#define LOG_INFO(msg, ...) fprintf(stdout, "INFO (%s): " msg "\r\n", __PRETTY_FUNCTION__, ## __VA_ARGS__);
#define LOG_WARN(msg, ...) fprintf(stderr, "WARN (%s): " msg "\r\n", __PRETTY_FUNCTION__, ## __VA_ARGS__);
#define LOG_ERR(msg, ...) fprintf(stderr, "ERR (%s): " msg "\r\n", __PRETTY_FUNCTION__, ## __VA_ARGS__);
#define LOG_FATAL(msg, ...) fprintf(stderr, "FATAL (%s): " msg "\r\n", __PRETTY_FUNCTION__, ## __VA_ARGS__);

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* LOGGING_H_ */