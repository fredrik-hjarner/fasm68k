export default {
  type: 'error_expected',
  exitCode: 1,
  description: 'diag_absolute_too_big=2 should turn the diagnostic into a hard error',
  asm: `
m68k.settings.diag_absolute_too_big = 2

; Use explicit .l so this parses as abs.l in current parser.
move.l $100000000.l, d0
`,
  errorContains: 'abs.l too large to fit in longword.'
};


