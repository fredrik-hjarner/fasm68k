export default {
  type: 'error_expected',
  exitCode: 1,
  description: 'autofix_cmp_to_cmpa=0 should error instead of auto-fixing',
  asm: `
m68k.settings.autofix_cmp_to_cmpa = 0

cmp.w d0, a0
`,
  errorContains: 'Use `cmpa` instead'
};


