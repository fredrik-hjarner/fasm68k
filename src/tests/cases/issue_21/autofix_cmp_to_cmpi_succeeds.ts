export default {
    type: 'success_binary',
    exitCode: 0,
    description: 'cmp #imm,<ea-not-dn> should be auto-fixed to cmpi',
    asm: `
m68k.settings.optimize_cmp_to_cmpi = 1

; invalid for cmp, should be rewritten to cmpi
cmp.w #1, (a0)
`,
    binaryHex: '0c500001',
    warnings: [
      "Using `cmp` when the first operand is an immediate is less efficient than using `cmpi`. Optimizing to `cmpi`!"
    ]
};


