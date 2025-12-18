export default {
  type: 'success_with_warnings',
  exitCode: 0,
  description: 'autofix_eor_to_eori=1 should warn (and autofix)',
  asm: `
m68k.settings.autofix_eor_to_eori = 1

eor.b #1, d0
`,
  warnings: ['Auto-fixing to `eori`.']
};


