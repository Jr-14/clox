#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
/**
 * Disassemble the instruction at the given offset.
 */
int disassembleInstruction(Chunk* chunk, int offset);

#endif
