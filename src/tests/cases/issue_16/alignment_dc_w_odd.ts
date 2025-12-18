export default {
  type: 'success_with_warnings',
  exitCode: 0,
  description: 'dc.w at odd address should generate warning',
  asm: `
; Place a byte first to get to odd address
db 0
dc.w $1234
`,
  warnings: ['word on an odd address']
};

