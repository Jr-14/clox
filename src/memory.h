#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize);

/**
 * Macro to calculate new capacity based on a given current capacity.
 *
 * This will be inlined and replaced.
 */
#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

/**
 * Macro to increase the size of the array by reallocating the array and moving the array
 * elements into the new allocated memory location.
 *
 * This will be inlined and replaced.
 */
#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), \
        sizeof(type) * (newCount))

/**
 * Macro to free the Dynamic array.
 */
#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

#endif
