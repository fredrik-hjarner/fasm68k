export default {
  type: 'success_with_warnings',
  exitCode: 0,
  description: 'diag_instruction_word_alignment=1 should warn for odd-placed instruction',
  asm: `
m68k.settings.diag_instruction_word_alignment = 1

db 0
nop
`,
  binaryHex: '004e71',
  warnings: ['Instructions are required to be word-aligned']
};


