
# 14 Chunks of Bytecode

## Why not walk the Abstract Syntax Tree (AST)?
It is not *memory-efficient*. Each piece of syntax becomes an AST node, which has header parts for book keeping
information. This takes up space as each pointer adds an extra 32 or 64 bits of overhead.

Furthermore, the data is scattered across the heap in a loosely connected web of objects. This is very bad for spatial
locality. We want to utilise spatial locality as Modern CPU's leverage this by retrieving memory addresses around the
location from where it was pulled, and places them in the cache. Therefore, if the program requests some data close
enough to the cache line, the CPU runs more smoothly.

Consequently, if the objects happene to be allocated in sequential memory when the parser first produced them, after a
couple of rounds of garbage collection, this may move the objects around in memory, thus they are not in sequential
memory anymore and can't leverage spatial locatility.

## Why not compile to native code?
We want it to be portable essentially. If we compile to native code, we will have to target the specific CPU
architecture, and there are many architectures around.

## Why Bytecode
Bytecode resembles machine code. It's a dense, linear sequence of binary instructions. This keeps overhead low and
plays nicely with the cache. However, this requires an *emulator* to run, to simulate the bytecode. E.g. a
*Virtual Machine*, but this adds a bit of overhead, however it is still faster than walking the AST.

### The Bytecode format
For the bytecode format, each instruction has a one-byte operation code (universally shorted to **opcode**). The number
controls what kind of instruction we're dealing with. E.g. add, subtract, look up variable, etc.

Each opcode determines how many operand bytes it has and what they mean. Each time we add a new opcode, we specify
what its operands look like - its **instruction format**.

### Constant Values
We'll support only **double-precision, floating-point numbers**. This will expand over time

For small fixed-size values like integers, many instruction sets store the value directly in the code stream right
after the opcode. These are called **immediate instructions** because the bits for the value are immediately after the
opcode. The *immediate instructions* after the **opcode** means that instructions can also have **operands**, as they
are binary data immediately after the opcode stream in the instruction, which let's us parameterize what the instruction
does. This doesn't work well for large or variable-sized constants like strings. In a native compiler to machine
code, those bigger constants get stored in a separate "constant data" region in the binary executable. Then, the
instruction to load a constant has an address or offset pointing to where the value is stored in that section.

- Each chunk will carry with it a list of the values that appear as literals in the program. To keep it simple, we'll
put ***all*** constants in there, even simple integers. In addition, we will need to have an instruction that means
"produce a constant" and those literal values need to get stored in the chunk somewhere. This will be a constant pool
which will be an array of values.

We will also need two kinds of constant instructions - one for immediate values and one for constants in the constant
table - immediates also force us to worry about alignment, padding, and endianness. Some architectures aren't happy if
you try to stuff a 4-byte integer at an odd address.

Constants takes a single byte operand that speciifes which constant to load from the chunk's constant array.

We implement this by adding a constants dynamic array to each chunk.

## Line Information
Taking the simplest approach of keeping a separate array of integers that parallels the bytecode. Each number in the
array is the line number for the corresponding byte in the bytecode. When a runtime error occurs, we look up the line
number at the same index as the current instruction's offset in the code array.

This branded dencoding keeps the line information in a *separate* array instaed of interleaving it in the bytecode
itself. Since line information is only used when a runtime error occurs, we don't want it between the instructions,
taking up precious space in the CPU cache, and causing more cache misses as the interpreter skips past it to get the
opcodes and operands it cares about.

### Bytecode Disassembler
Given a chunk of bytecode, it will print out all of the instructions. Used for print debugging for maintainers.

To disassemble a chunk, we print a little header so we can tell which chunk we're looking at. We then crank through the
bytecode, disassembling each instruction.
- Print the byte offset of the given instruction, this tells us where in the chunk this instruction is.
- Read a single byte from the bytecode at the given offset. This is the **opcode**.
- Switch on the type of **opcode** or instruction, and dispatch a utility function for displaying it.
- Also print any instruction/**opcode** it doesn't understand.

# 15 VM
- Static VM instance? A singleton makes the design much simpler.
- VM works its way through the bytecode, keeping trakc of where it is, the location of the instruction currently being
executed. The name **IP** or **Instruction Pointer**. This always points to the next instruction, not the one currently
beig handled.
