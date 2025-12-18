export default {
  type: 'success_binary',
  exitCode: 0,
  description: 'diag_instruction_word_alignment=0 should not warn or error for odd-placed instruction',
  asm: `
m68k.settings.diag_instruction_word_alignment = 0

db 0      ; move to odd address
nop       ; instruction on odd address (normally should warn/error)
`,
  binaryHex: '004e71'
};


