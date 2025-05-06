# fasm68k - Motorola 68000 instruction set for fasmg (flat assembler g)

**Note**: Consider this to be in alpha stage. Currently supports all 68k
instructions that are validated with about [10,000 tests](https://raw.githubusercontent.com/fredrik-hjarner/fasm68k/refs/heads/master/src/tests/valid_instructions.asm)
but the code might still
contain bugs. If you find bugs then don't hesitate reporting them, since the
hardest part is to find the bugs while it might be way easier to fix them.

## Description

The fasm68k instruction set adds support to assemble assembly code for the
Motorola 68000 cpu with Tomasz Grysztar's fasmg.

## Usage

### Linux

Get fasm68k and it's dependences (i.e. fasmg and examples) by running:

`git clone --recurse-submodules git@github.com:fredrik-hjarner/fasm68k.git`

Step into the repository directory:

`cd fasm68k`

Script must be executable:

`chmod +x fasm68k`

To assemble an example now run this command and a binary should be created which you can run in a Mega Drive/Genesis emulator:

`./fasm68k megadrive_samples_fasm68k/1_hello_world/hello.asm`

### Windows

TODO

## Differences from other m68k assemblers

- Macros are completely different and it's the main reason for this project to
exist. fasmg's macro langauge is more powerful than the macro languages of other
assemblers. Check out [fasmg's manual](https://flatassembler.net/docs.php?article=fasmg_manual) for more information.
- fasm68k does not support `*` to get the current address. Either use `@` or `$`
instead.
- Some operators are different. While I have added support for `<<` and `>> `for
bit shifting, the preferred way is to use `shl` and `shr`. Likewise try to use
`or` instead of `|` and `and` instead of `&`.
- Currently no optimizations and might be missing some aliases for some
instructions.



