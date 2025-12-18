export default {
  type: 'success_with_warnings',
  exitCode: 0,
  description: 'dc.l at odd address should generate warning',
  asm: `
; Place a byte first to get to odd address
db 0
dc.l $12345678
`,
  warnings: ['longword on an odd address']
};

