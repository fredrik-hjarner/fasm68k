export default {
  type: 'error_expected',
  exitCode: 2,
  description: 'rs.l at odd address should generate warning (currently errors - needs fix)',
  asm: `
rsset $0001  ; Start at odd address
my_var rs.l   ; This should warn
`,
  errorContains: 'illegal instruction'
};

