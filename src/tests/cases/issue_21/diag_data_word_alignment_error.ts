export default {
  type: 'error_expected',
  exitCode: 1,
  description: 'diag_data_word_alignment=2 should error for dc.w on odd address',
  asm: `
m68k.settings.diag_data_word_alignment = 2

db 0
dc.w 0
`,
  errorContains: 'Attempting to place a word on an odd address!'
};


