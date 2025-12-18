export default {
  type: 'success_binary',
  exitCode: 0,
  description: 'Properly aligned data should not generate warnings',
  asm: `
; All these should assemble without warnings
dc.w $1234
dc.l $12345678
rsset $0000
my_var_w rs.w
my_var_l rs.l
move.w ($0000).w, d0
move.l ($0000).l, d0
`,
  binaryHex: '12341234567830380000203900000000'
};

