#ifndef clox_value_h
#define clox_value_h

#include "common.h"

// Abstract how Lox values are represented in C. That way, we can change that representation
// without needing to go back and fix existing code that passes around values.
typedef double Value;

/**
 * Constant Pool is a Dynamic Array of values. The instruction to load a constant looks up the value by
 * index in that array.
 */
typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif
