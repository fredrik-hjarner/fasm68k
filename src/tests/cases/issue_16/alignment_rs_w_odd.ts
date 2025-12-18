export default {
  type: 'error_expected',
  exitCode: 2,
  description: 'rs.w at odd address should generate warning (currently errors - needs fix)',
  asm: `
rsset $0001  ; Start at odd address
my_var rs.w   ; This should warn
`,
  errorContains: 'illegal instruction'
};

