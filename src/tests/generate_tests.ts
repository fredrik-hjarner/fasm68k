#!/usr/bin/env bun
// Generate M68K instruction tests using Bun
// This script generates test cases for 68K assembly instructions

// Load instruction definitions from TypeScript file
import { data, OperandSize, OperandType } from './m68k_instructions.ts';
const instructionsData = data;

declare global {
  interface Array<T> {
    repeat(count: number): T[];
  }
}

Array.prototype.repeat = function<T>(this: T[], count: number): T[] {
  if (typeof count !== 'number' || count < 0 || !Number.isInteger(count)) {
    throw new RangeError('count must be a non-negative integer');
  }
  const result: T[] = [];
  for (let i = 0; i < count; i++) {
    result.push(...this);
  }
  return result;
};

// Allows to run the tests `times` times.
// 6 takes ~~11.0~~ ~~10.8~~ ~~10.2~~ ~~10.1~~ ~~8.8~~ with display disabled
// ~~9.1~~ ~~9.0~~ 7.0
const times = 1;

// Example values for each addressing mode
const examples: Record<OperandType, string[]> = {
  "dn": [
    "d2",
    "d5",
  ].repeat(times),
  "an": [
    "a2",
    "a7",
    "sp"
  ].repeat(times),
  "(an)": [
    "(a2)",
    "(a5)",
  ].repeat(times),
  "(an)+": [
    "(a1)+",
    "(a5)+",
  ].repeat(times),
  "-(an)": [
    "-(a2)",
    "-(a5)",
    "-(sp)"
  ].repeat(times),
  // indirect addressing with displacement
  "d(an)": [
    "$7FFF(a2)",
    "$7FFF(a5)",
    // "($7FFF,a5)", // TODO: Switch this test on!
    "-2(sp)",
    // "(-2)(sp)", // TODO: This causes errors.
    // "(2,a4)", // clownassembler dont support but vasm does.
  ].repeat(times),
  // indirect addressing with displacement and index
  "d(an,ix)": [
    "$7F(a2,d5.w)",
    "$7F(a5,d2.w)",
    "$0F(a5,d2.l)",
    "$1+1(a5,d2.l)",
    "-2(a5,d2.l)",
    // "($1+1)(a5,d2.l)", // TODO: This causes errors.
    '(a0,d1.w)',
    '(a1,d6)',
    // '(5,a5,a7)', Error on clownassembler
  ].repeat(times),
  "abs.w": [
    "($FFFFFFFE).w",
    '$2',
    '-2',
  ].repeat(times),
  "abs.l": [
    "($FFFFFFFE).l",
    'label_start.l',
    '$FFFFFFFE',
    '$FFFFFFFFFFFE',
    '$2',
    '-2'
    // '(label_start)'
  ].repeat(times),
  // pc displacment
  "d(pc)": [
    "@(pc)",
    "@-2(pc)",
  ].repeat(times),
  // pc displacement with index
  "d(pc,ix)": [
    "@(pc,d5.w)",
    "@-2(pc,d5.w)",
    "@-2(pc,d1.l)",
    "@-2(pc,d1)",
  ].repeat(times),
  // TODO: Rename to imm32?
  "imm": [
    "#equ_1",
    '#equ_equ_1',
    '#equ_1_plus_equ_1',
    "#0",
    "#4",
    "#$FF",
    "#$7FFF",
    "#$FFFF",
    "#$FFFFFFFF",
    '#"WXYZ"',
    "#1+1",
    '#(3+4)',
    '#-2',
  ].repeat(times),
  "imm3": ["#1", "#7"].repeat(times),
  "imm4": ["#2"].repeat(times),
  "imm8": [
    "#0",
    "#$FF",
    '#"X"',
    '#-1'
  ].repeat(times),
  // s suffix means signed
  "imm8s": [
    "#0",
    "#$7F",
    '#-1',
  ].repeat(times),
  "imm16": [
    "#0",
    "#4",
    "#$FF",
    '#"XY"',
    "#$2700",
    "#$FFFF",
    "#-1",
  ].repeat(times),
  // TODO: singed numbers
  "imm16s": [
    "#0",
    "#4",
    "#$FF",
    "#$2700",
    "#$FFFF",
    "#-1"
  ].repeat(times),
  "label": [
    "@",
    "@-2",
    // "label",
  ].repeat(times),
  "register_list": [
    "d2", "d5-a7", "d0-d7/a0-a7", "d0-d1/a0-a1", "d0/d1/d2/d3-d4"
  ].repeat(times),
  "ccr": ["ccr"].repeat(times),
  "sr": ["sr"].repeat(times),
  "usp": ["usp"].repeat(times),
  "dc.b": [
    "0, 5, -1, 1",
    "$0A, $FF",
    "'string'",
    "1,1,10,12"
  ].repeat(times),
  "dc.w": ["0", "$FFFF", "1,1,-1"].repeat(times),
  "dc.l": ["0", "$FFFFFFFF", "1,1,-1"].repeat(times)
};

// Helper function to get example values
function getExampleValues(operandType, instr: string, size: OperandSize) {
  // special cases.
  if(size === 'b' && operandType === 'imm') {
    return examples["imm8"];
  } else if(size === 'w' && operandType === 'imm') {
    return examples["imm16"];
  }

  // default case
  return examples[operandType];
}

// Generate valid test cases
function generateValidTests() {
  let output = `
equ_0 equ 0
equ_1 equ 1
; equ_imm_0 equ #0 ; You're not allowed to do this in vasm and clownassembler.
; equ_imm_1 equ #1 ; You're not allowed to do this in vasm and clownassembler.
equ_equ_1 equ equ_1
equ_1_plus_equ_1 equ equ_1+equ_1
; equ_a1 equ a1 ; You're not allowed to do this in vasm and clownassembler.

label_start:

; edge cases etc:
  btst.b	d2,0(pc)
  btst.b	d2,0(pc,d5.w)
; p equ 1
; move.l #$#p#p#p#p#p#p#p#p, 0

`;
  let previousInstrName = ""; // Track the previous instruction name
  
  // Process each group in the data
  for (const group of instructionsData) {
    // Get the variants for this group
    const variants = group.variants;
    
    // Process each instruction in this group
    for (const instrName of group.instructions) {
      // Add a newline between different instructions
      if (previousInstrName && previousInstrName !== instrName) {
        output += "\n";
      }
      
      // Process variants
      for (const variant of variants) {
        // Handle instructions with no operands
        if (variant.op1.length === 0 && variant.op2.length === 0) {
          output += `\t${instrName}\n`;
          continue;
        }

        // const sizes = [...new Set([...variant.sizes, ""])] as OperandSize[];
        const sizes = variant.sizes;
        
        // Process sizes for this variant
        for (const size of sizes) {
          const sizeSuffix = size ? `.${size}` : '';
          
          // Single operand instructions (dest only)
          if (variant.op1.length === 0 && variant.op2.length > 0) {
            for (const destOp of variant.op2.slice().sort()) {
              const destExamples = getExampleValues(destOp, instrName, size);
              
              for (const destExample of destExamples) {
                output += `\t${instrName}${sizeSuffix}\t${destExample}\n`;
              }
            }
          }
          // Source-only instructions (like branch)
          else if (variant.op1.length > 0 && variant.op2.length === 0) {
            for (const srcOp of variant.op1.slice().sort()) {
              const srcExamples = getExampleValues(srcOp, instrName, size);
              
              for (const srcExample of srcExamples) {
                output += `\t${instrName}${sizeSuffix}\t${srcExample}\n`;
              }
            }
          }
          // Two-operand instructions - systematically generate all combinations
          else if (variant.op1.length > 0 && variant.op2.length > 0) {
            // Generate all combinations for all instructions
            for (const srcOp of variant.op1.slice().sort()) {
              const srcExamples = getExampleValues(srcOp, instrName, size);
              
              for (const destOp of variant.op2.slice().sort()) {
                const destExamples = getExampleValues(destOp, instrName, size);
                
                // Generate all combinations of source and dest examples
                for (const srcExample of srcExamples) {
                  for (const destExample of destExamples) {
                    output += `\t${instrName}${sizeSuffix}\t${srcExample},${destExample}\n`;
                  }
                }
              }
            }
          }
        }
      }
      
      previousInstrName = instrName;
    }
  }
  
  // Add label for instructions that need it
  output += `
; edge cases and so on
    add.l #$00060000, d6 ; compat_vasm_add_bug1
    ; cmpi.w #$2000,(($1&$FFFFFF)+$400+$3C).l ; only works with compat_operators
    ; move.w #(5<<8)+5,(0).w
    ; move.w #(5 shl 8)+5,(0).w

; labels
label_end:

; equs and defines
`;
  
  return output;
}

// Main function to generate test files
function generateTestFiles() {
  const validTests = generateValidTests();
  
  // Define output path
  const validTestsPath = './tests/valid_instructions.asm';
  
  // Write file using Bun.write
  Bun.write(validTestsPath, validTests);
  console.log(`Valid tests written to: ${validTestsPath}`);
}

// Run the generator
generateTestFiles(); 