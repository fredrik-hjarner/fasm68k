export default {
  type: 'success_with_warnings',
  exitCode: 0,
  description: 'diag_absolute_too_big=1 should emit a warning and still assemble',
  asm: `
m68k.settings.diag_absolute_too_big = 1

move.l $100000000.l, d0
`,
  warnings: ['abs.l too large to fit in longword.']
};


