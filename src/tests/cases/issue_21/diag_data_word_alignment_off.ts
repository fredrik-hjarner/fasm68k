export default {
  type: 'success_binary',
  exitCode: 0,
  description: 'diag_data_word_alignment=0 should not warn or error for dc.w on odd address',
  asm: `
m68k.settings.diag_data_word_alignment = 0

db 0
dc.w 0
`,
  binaryHex: '000000'
};


