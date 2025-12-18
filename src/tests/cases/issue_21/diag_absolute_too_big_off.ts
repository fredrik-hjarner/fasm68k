export default {
  type: 'success_with_warnings',
  exitCode: 0,
  description: 'diag_absolute_too_big=0 should succeed and not emit any warnings',
  asm: `
m68k.settings.diag_absolute_too_big = 0

move.l $100000000.l, d0
`
};


