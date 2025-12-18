export default {
  type: 'success_with_warnings',
  exitCode: 0,
  description: 'diag_data_word_alignment=1 should warn for dc.w on odd address',
  asm: `
m68k.settings.diag_data_word_alignment = 1

db 0
dc.w 0
`,
  warnings: ['Attempting to place a word on an odd address!']
};


