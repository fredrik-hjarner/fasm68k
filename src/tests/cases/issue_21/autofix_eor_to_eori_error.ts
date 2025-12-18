export default {
  type: 'error_expected',
  exitCode: 1,
  description: 'autofix_eor_to_eori=0 should error instead of auto-fixing',
  asm: `
m68k.settings.autofix_eor_to_eori = 0

eor.b #1, d0
`,
  errorContains: 'Use `eori` instead'
};


