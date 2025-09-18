
# 14 Chunks of Bytecode

## Why not walk the Abstract Syntax Tree (AST)?
It is not *memory-efficient*. Each piece of syntax becomes an AST node, which has header parts
for book keeping information. This takes up space as each pointer adds an extra 32 or 64 bits
of overhead.

Furthermore, the data is scattered across the heap in a loosely connected web of objects. This
is very bad for spatial locality. We want to utilise spatial locality as Modern CPU's leverage
this by retrieving memory addresses around the location from where it was pulled, and places
them in the cache. Therefore, if the program requests some data close enough to the cache
line, the CPU runs more smoothly.

Consequently, if the objects happene to be allocated in sequential memory when the parser
first produced them, after a couple of rounds of garbage collection, this may move the objects
around in memory, thus they are not in sequential memory anymore and can't leverage spatial
locatility.

## Why not compile to native code?
We want it to be portable essentially. If we compile to native code, we will have to target
the specific CPU architecture, and there are many architectures around.

## Why Bytecode
Bytecode resembles machide code. It's a dense, linear sequence of binary instructions. This
keeps overhead low and plays nicely with the cache. However, this requires an *emulator* to
run, to simulate the bytecode. E.g. a *Virtual Machine*, but this adds a bit of overhead,
however it is still faster than walking the AST.

## The Bytecode format
For the bytecode format, each instruction has a one-byte operation code (universally shorted
to **opcode**). The number controls what kind of instruction we're dealing with. E.g. add,
subtract, look up variable, etc.
