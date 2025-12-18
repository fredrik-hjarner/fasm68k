export default {
  type: 'success_binary',
  exitCode: 0,
  description: 'addq without size suffix should work',
  asm: `
addq #1, d0
addq #1, d1
`,
  binaryHex: '52405241'
};

