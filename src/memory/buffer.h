/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file buffer.h
 * @author Evan Stoddard
 * @brief Resizable buffer
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <stddef.h>
#include <stdbool.h>

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
 * @brief Buffer typedef
 * 
 */
typedef struct buffer_prv_t* buffer_t;

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief Initialize a buffer with initial size
 * 
 * @return buffer_t* Pointer to initialized buffer (NULL if unable to initialize)
 */
buffer_t buffer_init(void);

/**
 * @brief Deinitialize buffer
 * 
 * @param inst Buffer instance
 */
void buffer_deinit(buffer_t inst);

/**
 * @brief Write to buffer 
 * 
 * @param inst Buffer instance
 * @param src Source of data to write to buffer
 * @param size Size of src
 * @return true Able to write to buffer
 * @return false Unable to write to buffer
 */
bool buffer_write(buffer_t inst, void *src, size_t size);

/**
 * @brief Reserve space (increment size) but don't write value to memory.
 * 
 * @param inst Buffer instance
 * @param size Size to reserve
 * @return true Able to reserve space
 * @return false Unable to reserve space
 */
bool buffer_reserve(buffer_t inst, size_t size);

/**
 * @brief Get pointer to buffer data
 * 
 * @param inst Buffer instance
 * @return void* Pointer to buffer data
 */
void *buffer_ptr(buffer_t inst);

/**
 * @brief Current size of buffer (amount of allocated space used)
 * 
 * @param inst Buffer instance
 * @return size_t Size of buffer used
 */
size_t buffer_size(buffer_t inst);

/**
 * @brief Allocated space buffer is using
 * 
 * @param inst Buffer instance
 * @return size_t Total memory buffer instance has allocated
 */
size_t buffer_allocated_size(buffer_t inst);

#ifdef __cplusplus
}
#endif
#endif /* BUFFER_H_ */