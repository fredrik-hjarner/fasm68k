export default {
  type: 'success_with_warnings',
  exitCode: 0,
  description: 'autofix_cmp_to_cmpa=1 should warn (and autofix)',
  asm: `
m68k.settings.autofix_cmp_to_cmpa = 1

cmp.w d0, a0
`,
  warnings: ['Auto-fixing to `cmpa`.']
};


