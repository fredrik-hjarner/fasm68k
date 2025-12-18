export default {
    type: 'success_with_warnings',
    exitCode: 0,
    description: 'optimize_cmp_to_cmpi=1 should warn when cmp #imm,dn is optimized to cmpi',
    asm: `
  m68k.settings.optimize_cmp_to_cmpi = 1
  
  cmp.w #1, d0
  `,
    warnings: [
      "Using `cmp` when the first operand is an immediate is less efficient than using `cmpi`. Optimizing to `cmpi`!"
    ]
  };