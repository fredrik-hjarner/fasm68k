# fasm68k Project Structure & Architecture Overview

## TL;DR
**fasm68k** is a Motorola 68000 instruction set implementation for fasmg (flat assembler g). It's a collection of CALM macros that teach fasmg how to assemble 68k code. fasm68k can assemble real games (Sonic 1, RetailClerk89, Speedrun Tower) byte-perfectly, and has ~22,000 instruction tests.

---

## High-Level Architecture

```
fasm68k (the 68k instruction set for fasmg)
├── Core Engine (m68k.inc and friends)
├── Instruction Encoders (CALM macros that turn assembly into binary)
├── Parser (operand parsing, register parsing)
├── Validation (instruction verification)
├── Settings & Compatibility Layers
├── Test Infrastructure
└── Documentation
```

---

## Directory Structure (Deep Dive)

### `src/` - The Main Brain

This is where all the actual assembly logic lives. Most files are `.inc` files (fasmg include files written in CALM/assembly).

#### **Root Level (`src/`)**
- **`m68k.inc`** - **THE ENTRY POINT**. This is what users include to get access to all 68k instructions. It orchestrates all includes and sets up the m68k namespace.
- **`settings/`** - Configuration and behavior flags
- **`directives.inc`** - Custom directives beyond fasmg's standard ones (dc.b, dc.w, dc.l, rs.b, rs.w, rs.l, even, rseven, rsset, __rs)
- **`registers.inc`** - Register name mappings (d0-d7, a0-a7, sp, pc, etc.)

#### **`src/settings/` - Behavioral Tweaks**
- **`diagnostics.inc`** - Error/warning behavior
- **`autofixes.inc`** - Automatic corrections (e.g., optimize_cmp_to_cmpi)
- **`optimization.inc`** - Instruction optimizations (turn `add` into `addi` when appropriate)
- **`settings.inc`** - Central settings namespace where users can flip flags on/off

#### **`src/parsing/` - Input Parsing**
- **`utils.inc`** - Helper utilities (is_one_token?, etc.)
- **`parse_operand.inc`** - **Critical**: Parses operands like `d1`, `($1000)`, `(a2,d3.w)`, `#$FF`, etc. This is a LOT of complex logic.
- **`parse_reg_list.inc`** - Parses register lists for movem: `d0-d7/a0-a5`

#### **`src/validation/` - Instruction Verification**
- **`validate_instruction.inc`** - Checks if an instruction + operands are valid
- **`instruction_validation_structure.inc`** - Auto-generated tree of valid instruction variants (built by TypeScript script during tests)

#### **`src/instructions/` - Instruction Definitions**
This is where the 68k instruction set is implemented. Instructions are organized by operand arity:

- **`dyadic.inc`** - Two-operand instructions (move, add, cmp, etc.)
- **`monadic.inc`** - One-operand instructions (clr, neg, not, etc.)
- **`niladic.inc`** - Zero-operand instructions (nop, rts, etc.)
- **`variadic.inc`** - Variable-operand instructions (movem, etc.)
- **`move.inc`** - Move instruction family (special due to complexity)
- **`ori_andi_subi_addi_eori_cmpi.inc`** - Grouped immediate instructions
- **`emit_ext_words.inc`** - Helper for emitting extension words
- **`aliases.inc`** - Instruction aliases (link → link.w, etc.)
  - **Note**: Current aliases have validation implications; future versions will bake unsized versions into instructions themselves.

#### **`src/debug/`, `src/endianness.inc`, etc.**
- **`debug.inc`** - Logging/debugging utilities
- **`endianness.inc`** - Big-endian/little-endian handling
- **`reverse_bits.inc`** - Bit manipulation utils for instruction encoding
- **`xxcalm.inc`** - Extra CALM utilities and helpers

#### **`src/tests/` - Test Infrastructure**
This is where validation happens. The tests are **TypeScript scripts that generate assembly test files**, then multiple assemblers (fasm68k, clownassembler, vasm) assemble them to compare output.

- **`m68k_instructions.ts`** - Source of truth for instruction specs (opcodes, operand types, etc.)
- **`generate_tests.ts`** - Generates test assembly files from m68k_instructions.ts
- **`generate_validation.ts`** - Generates the instruction validation structure (the tree of valid operand combos)
- **`valid_instructions.asm`** - Generated assembly file with test cases for every instruction variant (~22,000 tests)
- **`fasm68k_wrapper.asm`** - Wrapper that sets fasm68k settings then includes valid_instructions.asm
- **`vasm_bugs/`** - Separate subfolder for testing edge cases/differences between vasm and fasm68k

#### **`src/macro/` - Utility Macros**
- **`inline.inc`** - Inline macro helpers
- **`struct.inc`** - Struct definition support

### `examples/` - Real-World Test Cases

These are actual 68k programs that fasm68k must assemble correctly:

- **`megadrive_simple_demo/`** - Simple Genesis/Mega Drive demo
- **`megadrive_samples_fasm68k/`** - Adapted samples from BigEvilCorporation
- **`RetailClerk89_fasm68k/`** - Classic 1989 Mega Drive game (took 30-40 hours to get byte-perfect)
- **`speedrun-tower_fasm68k/`** - Another game, byte-perfect match target

Each has its own Makefile and test infrastructure to verify byte-for-byte correctness.

### `fasm2/` (Submodule)

fasmg is here for convenience.

### `.github/workflows/tests.yml`

CI/CD that runs on every push:
1. Generates test files from m68k_instructions.ts
2. Assembles valid_instructions.asm
3. Assembles Sonic 1, RetailClerk89, Speedrun Tower
4. Verifies output is byte-identical to reference binaries
5. Fails if ANY bytes differ

---

## How It All Fits Together

### When Someone Writes 68k Assembly Code

```
User writes:  move.l d0, a1
                ↓
m68k.inc loads all the instruction macros
                ↓
Matches "move" → calls the appropriate CALM instruction
                ↓
Parse operands: "l" (size), "d0" (dest reg), "a1" (src reg)
                ↓
Validate: Is move.l dn,an a valid combo? (Check validation structure)
                ↓
Encode: Calculate the 68k opcode bits
                ↓
Emit binary to output file
```

### The TypeScript ↔ CALM Pipeline

```
m68k_instructions.ts (source of truth for instruction specs)
    ↓
TypeScript scripts:
  - generate_tests.ts → valid_instructions.asm (test cases)
  - generate_validation.ts → instruction_validation_structure.inc (valid combos)
    ↓
CALM code uses the generated files to validate & encode instructions
    ↓
Binary output
```

So instructions are defined **once** in TypeScript, and auto-generate both tests and validation structures from it.
