/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file buffer.c
 * @author Evan Stoddard
 * @brief Resizable buffer
 */

#include "buffer.h"

#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/**
 * @brief Definition of buffer type
 * 
 */
struct buffer_prv_t {
    void *ptr;
    size_t size;
    size_t allocated_size;
};

/*****************************************************************************
 * Variables
 *****************************************************************************/

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Functions
 *****************************************************************************/

buffer_t buffer_init(void) {
    buffer_t inst = malloc(sizeof(struct buffer_prv_t));
    
    if (inst == NULL) {
        return NULL;
    }
    
    memset(inst, 0, sizeof(struct buffer_prv_t));
    
    return inst;
}

void buffer_deinit(buffer_t inst) {
    if (inst == NULL) {
        return;
    }
    
    if (inst->ptr != NULL) {
        free(inst->ptr);
        inst->ptr = NULL;
    }
    
    free(inst);
}

bool buffer_write(buffer_t inst, void *src, size_t size) {
    if (inst == NULL) {
        return false;
    }
    
    // Check if we need to allocate more space
    size_t required_space = inst->allocated_size + size;
    if (required_space > inst->allocated_size) {
        size_t new_size = required_space * 2;
        
        inst->ptr = realloc(inst->ptr, new_size);
        
        if (inst->ptr == NULL) {
            return false;
        }
        
        inst->allocated_size = new_size;
    }
    
    memcpy(inst->ptr + inst->size, src, size);
    inst->size += size;
    
    return true;
}

bool buffer_reserve(buffer_t inst, size_t size) {
    if (inst == NULL) {
        return false;
    }
    
    // Check if we need to allocate more space
    size_t required_space = inst->size + size;
    if (required_space > inst->allocated_size) {
        size_t new_size = inst->allocated_size * 2;
        
        if (new_size == 0) {
            new_size = size;
        }
        
        inst->ptr = realloc(inst->ptr, new_size);
        
        if (inst->ptr == NULL) {
            return false;
        }
        
        inst->allocated_size = new_size;
    }
    
    inst->size += size;
    
    return true;
}

void *buffer_ptr(buffer_t inst) {
    if (inst == NULL) {
        return false;
    }
    
    return inst->ptr;
}

size_t buffer_size(buffer_t inst) {
    if (inst == NULL) {
        return 0;
    }
    
    return inst->size;
}

size_t buffer_allocated_size(buffer_t inst) {
    if (inst == NULL) {
        return 0;
    }
    
    return inst->allocated_size;
}