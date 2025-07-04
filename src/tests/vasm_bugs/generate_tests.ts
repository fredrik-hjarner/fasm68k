#!/usr/bin/env bun
// Generate M68K instruction tests using Bun
// This script generates test cases for 68K assembly instructions

// Load instruction definitions from TypeScript file
import { data, OperandSize, OperandType } from './m68k_instructions.ts';
const instructionsData = data;

// Example values for each addressing mode
const examples: Record<OperandType, string[]> = {
  "dn": ["d1","d2","d3","d4","d5"],
  "an": ["a1","a2","a3","a4","a5","a6","a7","sp"],
  "(an)": ["(a1)", "(a2)", "(a3)", "(a4)", "(a5)", "(a6)", "(a7)", "(sp)"],
  "(an)+": ["(a1)+", "(a2)+", "(a3)+", "(a4)+", "(a5)+", "(a6)+", "(a7)+", "(sp)+"],
  "-(an)": ["-(a1)", "-(a2)", "-(a3)", "-(a4)", "-(a5)", "-(a6)", "-(a7)", "-(sp)"],
  // indirect addressing with displacement
  "d(an)": [
    "$7FFF(a2)",
    "$7FFF(a5)",
    // "($7FFF,a5)", // TODO: Switch this test on!
    "-2(sp)",
    // "(-2)(sp)", // TODO: This causes errors.
  ],
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
  ],
  "abs.w": [
    "($FFFFFFFF).w",
    '$1',
  ],
  "abs.l": [
    "($FFFFFFFF).l",
    'label_start.l',
    '$FFFFFFFF',
    '$1',
    // '(label_start)'
  ],
  // pc displacment
  "d(pc)": [
    "@(pc)",
    "@-2(pc)",
  ],
  // pc displacement with index
  "d(pc,ix)": [
    "@(pc,d5.w)",
    "@-2(pc,d5.w)",
    "@-2(pc,d1.l)",
  ],
  // TODO: Rename to imm32?
  "imm": [
    // "#equ_1",
    // '#equ_equ_1',
    // '#equ_1_plus_equ_1',
    "#0",
    "#4",
    "#$FF",
    "#$7FFF",
    "#$FFFF",
    "#$FFFFFFFF",
    '#"WXYZ"',
    "#1+1",
    '#(3+4)',
    '#-1',
    '#-2',
    // "#equ_0",
    // "#equ_1",
    // "#label_start",
    // "#label_end",
  ],
  "imm3": ["#1", "#7"],
  "imm4": ["#2"],
  "imm8": [
        "#0",
        "#$FF",
        '#"X"',
        // "#equ_0",
        // "#equ_1"
    ], // TODO: add negative examples too?
  // s suffix means signed
  "imm8s": [
    "#0",
    "#$7F",
    '#-1',
  ],
  "imm16": ["#0", "#4", "#$FF", '#"XY"', "#$2700", "#$7FFF",  "#$FFFF"],
  // TODO: singed numbers
  "imm16s": ["#0", "#4", "#$FF", "#$2700", "#$7FFF",  "#$FFFF"],
  "label": [
    "@",
    "@-2",
    // "label",
  ],
  "register_list": [
    "d2", "d5-a7", "d0-d7/a0-a7", "d0-d1/a0-a1", "d0/d1/d2/d3-d4"
  ],
  "ccr": ["ccr"],
  "sr": ["sr"],
  "usp": ["usp"],
  "dc.b": [
    "0, 5",
    "$0A, $FF",
    "'string'",
    "1,1,10,12"
  ],
  "dc.w": ["0", "$FFFF", "1,1,1"],
  "dc.l": ["0", "$FFFFFFFF", "1,1,1"]
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

`;
//   let previousInstrName = ""; // Track the previous instruction name
  
//   // Helper function to ensure the string has even length
//   function ensureEvenLength(str: string): string {
//     // Split by first whitespace to separate instruction from arguments
//     const parts = str.split(/\s+(.+)/);
    
//     if (parts.length < 2) {
//       // No arguments, just check if we need padding
//       return str.length % 2 === 0 ? str : str + ' ';
//     }
    
//     const [instr, args] = parts;
//     const combined = instr + ' ' + args;
    
//     // If combined length is odd, add an extra space between instruction and args
//     if (combined.length % 2 !== 0) {
//       return instr + '  ' + args; // Two spaces between instruction and args
//     }
    
//     return combined;
//   }
  
//   // Process each group in the data
//   for (const group of instructionsData) {
//     // Get the variants for this group
//     const variants = group.variants;
    
//     // Process each instruction in this group
//     for (const instrName of group.instructions) {
//       // Add a newline between different instructions
//       if (previousInstrName && previousInstrName !== instrName) {
//         output += "\n";
//       }
      
//       // Process variants
//       for (const variant of variants) {
//         // Handle instructions with no operands
//         if (variant.sourceOperands.length === 0 && variant.destOperands.length === 0) {
//           const instruction = `\t${instrName}`;
//           // Create a clean version of the instruction text without tabs
//           const cleanText = instruction.trim();
//           const evenText = ensureEvenLength(cleanText);
//           output += `\tdc.b '${evenText}'\n${instruction}\n`;
//           continue;
//         }

//         // const sizes = [...new Set([...variant.sizes, ""])] as OperandSize[];
//         const sizes = variant.sizes;
        
//         // Process sizes for this variant
//         for (const size of sizes) {
//           const sizeSuffix = size ? `.${size}` : '';
          
//           // Single operand instructions (dest only)
//           if (variant.sourceOperands.length === 0 && variant.destOperands.length > 0) {
//             for (const destOp of variant.destOperands.slice().sort()) {
//               const destExamples = getExampleValues(destOp, instrName, size);
              
//               for (const destExample of destExamples) {
//                 const instruction = `\t${instrName}${sizeSuffix}\t${destExample}`;
//                 const cleanText = instruction.trim();
//                 const evenText = ensureEvenLength(cleanText);
//                 output += `\tdc.b '${evenText}'\n${instruction}\n`;
//               }
//             }
//           }
//           // Source-only instructions (like branch)
//           else if (variant.sourceOperands.length > 0 && variant.destOperands.length === 0) {
//             for (const srcOp of variant.sourceOperands.slice().sort()) {
//               const srcExamples = getExampleValues(srcOp, instrName, size);
              
//               for (const srcExample of srcExamples) {
//                 const instruction = `\t${instrName}${sizeSuffix}\t${srcExample}`;
//                 const cleanText = instruction.trim();
//                 const evenText = ensureEvenLength(cleanText);
//                 output += `\tdc.b '${evenText}'\n${instruction}\n`;
//               }
//             }
//           }
//           // Two-operand instructions - systematically generate all combinations
//           else if (variant.sourceOperands.length > 0 && variant.destOperands.length > 0) {
//             // Generate all combinations for all instructions
//             for (const srcOp of variant.sourceOperands.slice().sort()) {
//               const srcExamples = getExampleValues(srcOp, instrName, size);
              
//               for (const destOp of variant.destOperands.slice().sort()) {
//                 const destExamples = getExampleValues(destOp, instrName, size);
                
//                 // Generate all combinations of source and dest examples
//                 for (const srcExample of srcExamples) {
//                   for (const destExample of destExamples) {
//                     const instruction = `\t${instrName}${sizeSuffix}\t${srcExample},${destExample}`;
//                     const cleanText = instruction.trim();
//                     const evenText = ensureEvenLength(cleanText);
//                     output += `\tdc.b '${evenText}'\n${instruction}\n`;
//                   }
//                 }
//               }
//             }
//           }
//         }
//       }
      
//       previousInstrName = instrName;
//     }
//   }
  
  // Add label for instructions that need it
  output += `
; edge cases and so on

OBJ_SCENE_BASE = $1000

OBJ_SCENE_PLANT_ALT = OBJ_SCENE_BASE + $38

MEM_ACTION_TARGET_OBJID = $FFFF002E

    cmp.w #OBJ_SCENE_PLANT_ALT, (MEM_ACTION_TARGET_OBJID)

    ; or -> ori
    or.w #1, d1
    or.w #1, ($1)

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
  const validTestsPath = './tests/vasm_bugs/valid_instructions.asm';
  
  // Write file using Bun.write
  Bun.write(validTestsPath, validTests);
  console.log(`Valid tests written to: ${validTestsPath}`);
}

// Run the generator
generateTestFiles(); 