#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

/**
 * Bytecode format.
 *
 * Each instruction has a one-byte operation code (opcode). This constrols what kind of instruction
 * we're dealing with, e.g. add, subtract, look up variable, etc. They are defined here
 */
typedef enum {
    OP_CONSTANT, // An instruction to produce a constant
    OP_RETURN, // Means "Return from the current function"
} OpCode;

/**
 * A Dynamic array of Bytecode as Bytecode is a series of instructions.
 */
typedef struct {
    int count;
    int capacity;
    uint8_t* code;
    int* lines;
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);

/**
 * Write a constant into the constant values array.
 *
 * Returns an index to the the array for the constant value.
 */
int addConstant(Chunk* chunk, Value value);

#endif
