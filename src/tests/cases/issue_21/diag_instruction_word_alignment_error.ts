export default {
  type: 'error_expected',
  exitCode: 1,
  description: 'diag_instruction_word_alignment=2 should error for odd-placed instruction',
  asm: `
m68k.settings.diag_instruction_word_alignment = 2

db 0
nop
`,
  errorContains: 'Instructions are required to be word-aligned'
};


