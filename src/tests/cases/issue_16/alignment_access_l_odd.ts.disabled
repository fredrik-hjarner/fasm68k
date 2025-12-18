export default {
  type: 'success_with_warnings',
  exitCode: 0,
  description: 'Accessing long with (xxx).L at odd address should generate warning (feature not implemented yet)',
  asm: `
move.l ($0001).l, d0  ; Accessing long at odd address should warn
`,
  warnings: [
    'longword',
    'odd address'
  ]
};

