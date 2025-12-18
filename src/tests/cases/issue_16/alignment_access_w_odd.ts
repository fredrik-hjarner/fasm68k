export default {
  type: 'success_with_warnings',
  exitCode: 0,
  description: 'Accessing word with (xxx).W at odd address should generate warning (feature not implemented yet)',
  asm: `
move.w ($0001).w, d0  ; Accessing word at odd address should warn
`,
  warnings: [
    'word',
    'odd address'
  ]
};

