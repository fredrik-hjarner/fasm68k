// This script generates FASMG validation structure from m68k_instructions.ts

import * as fs from 'fs';
import * as path from 'path';
import { data, OperandType } from './m68k_instructions';

// Blacklist of instructions to exclude from the output
const blacklistedInstructions = [
  "dc" // Excludes dc.b, dc.w, dc.l directives
  // Add more instructions to blacklist as needed
];

// Mapping from TypeScript addressing modes to FASMG-compatible identifiers
const addressingModeMap: Record<OperandType, string> = {
  "dn": "dn",
  "an": "an",
  "(an)": "indir_an",
  "(an)+": "an_post_incr",
  "-(an)": "an_pre_decr",
  "d(an)": "an_displace",
  "d(an,ix)": "an_idx",
  "abs.w": "abs_w",
  "abs.l": "abs_l",
  "d(pc)": "pc_displace",
  "d(pc,ix)": "pc_idx",
  "imm": "imm",
  "imm3": "imm",
  "imm4": "imm",
  "imm8": "imm",
  "imm8s": "imm",
  "imm16": "imm",
  "imm16s": "imm",
  "register_list": "reg_list",
  "ccr": "ccr",
  "sr": "sr",
  "usp": "usp",
  "label": "abs_l",  // Map label to abs_l as per comment in sketch file
  "dc.b": "dc_b",
  "dc.w": "dc_w",
  "dc.l": "dc_l"
};

// Generate FASMG validation structure
function generateFasmgValidation(): string {
  let output = `; AUTOMATICALLY GENERATED FILE - DO NOT EDIT DIRECTLY
; Generated from m68k_instructions.ts by generate_validation.ts

define m68k.valid_instructions
namespace m68k.valid_instructions
`;

  const lines: string[] = [];

  // Process each instruction group
  for (const group of data) {
    for (const instruction of group.instructions) {
      // Skip blacklisted instructions
      if (blacklistedInstructions.includes(instruction)) {
        continue;
      }
      
      lines.push(`\tdefine ${instruction}`);
      
      // Process each variant
      for (const variant of group.variants) {
        // Process each size
        for (const size of variant.sizes) {
          const sizeStr = size === "" ? "_" : size;
          lines.push(`\tdefine ${instruction}.${sizeStr}`);
          
          // Process operands
          if (variant.op1.length === 0) {
            // No operands
            lines.push(`\tdefine ${instruction}.${sizeStr}._`);
            lines.push(`\tdefine ${instruction}.${sizeStr}._._`);
          } else {
            // Process first operand
            for (const op1 of variant.op1) {
              const op1Str = addressingModeMap[op1] || op1;
              lines.push(`\tdefine ${instruction}.${sizeStr}.${op1Str}`);
              
              if (variant.op2.length === 0) {
                // Only one operand
                lines.push(`\tdefine ${instruction}.${sizeStr}.${op1Str}._`);
              } else {
                // Process second operand
                for (const op2 of variant.op2) {
                  const op2Str = addressingModeMap[op2] || op2;
                  lines.push(`\tdefine ${instruction}.${sizeStr}.${op1Str}.${op2Str}`);
                }
              }
            }
          }
        }
      }
    }
  }

  output += [...new Set(lines)].sort().join('\n');
  output += '\nend namespace';
  return output;
}

// Main execution
const outputPath = path.join(__dirname, '../validation/instruction_validation_structure.inc');
const fasmgCode = generateFasmgValidation();
fs.writeFileSync(outputPath, fasmgCode);
console.log(`FASMG validation structure written to ${outputPath}`); 