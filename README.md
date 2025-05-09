# fasm68k - Motorola 68000 instruction set for fasmg (flat assembler g)

**Note**: Consider this to be in alpha stage. Currently supports all 68k
instructions that are validated with about [10,000 tests](https://raw.githubusercontent.com/fredrik-hjarner/fasm68k/refs/heads/master/src/tests/valid_instructions.asm)
but the code might still
contain bugs. If you find bugs then don't hesitate reporting them, since the
hardest part is to find the bugs while it might be way easier to fix them.

## Description

The fasm68k instruction set adds support to assemble assembly code for the
Motorola 68000 cpu with Tomasz Grysztar's fasmg.

[Here](https://github.com/BigEvilCorporation/megadrive_samples/compare/master...fredrik-hjarner:megadrive_samples_fasm68k:master)
you can see what was needed to adapt BigEvilCorporation's megadrive_samples for
fasm68k.

## Usage

<details>

<summary>Linux</summary>
<blockquote>

Get fasm68k and it's dependences (i.e. fasmg and examples) by running:

`git clone --recurse-submodules git@github.com:fredrik-hjarner/fasm68k.git`

Step into the repository directory:

`cd fasm68k`

Script must be executable:

`chmod +x fasm68k`

To assemble the examples run these commands and binary files should be created
which you can run in a Mega Drive/Genesis emulator:

`./fasm68k examples/megadrive_simple_demo/main.asm`

`./fasm68k examples/megadrive_samples_fasm68k/1_hello_world/hello.asm`

`./fasm68k examples/megadrive_samples_fasm68k/2_scroll_planes/scroll.asm`

`./fasm68k examples/megadrive_samples_fasm68k/3_sprites/sprites.asm`

`./fasm68k examples/megadrive_samples_fasm68k/4_gamepad/gamepad.asm`

`./fasm68k examples/megadrive_samples_fasm68k/6_psg_tone/psg_tone.asm`

Add a new line at the bottom of your .bashrc file adding the fasm68k directory
to the PATH so you can run fasm68k from anywhere and not only from the specific
folder you cloned it into:

`export PATH=$HOME/code/fasm68k:$PATH`

</blockquote></details>

<details>

<summary>Windows</summary>
<blockquote>
TODO
</blockquote>
</details>

## Differences from other m68k assemblers

- Macros are completely different and it's the main reason for this project to
exist. fasmg's macro langauge is more powerful than the macro languages of other
assemblers. Check out [fasmg's manual](https://flatassembler.net/docs.php?article=fasmg_manual) for more information.
- fasm68k is less pedantic when it comes to the use of whitespace. You may place
an instruction in the "first column" (without any leading whitespace) for
example.
- fasm68k does not support `*` to get the current address. Either use `@` or `$`
instead.
- Some operators are different. While I have added support for `<<` and `>> `for
bit shifting, the preferred way is to use `shl` and `shr`. Likewise try to use
`or` instead of `|` and `and` instead of `&`.
- Binary numbers are written as `01010101b` (instead of `%01010101`).
- You prefix labels with dot `.label1` to make them local (instead of prefixing
with @ `@label1`).
- Currently no optimizations and might be missing some aliases for some
instructions.

## Acknowledgments and attributions

- [Tomasz Grysztar](https://github.com/tgrysztar) for fasmg.
- [BigEvilCorporation](https://github.com/BigEvilCorporation) for the megadrive_samples which I simply adapted for fasm68k.
- The [vasm](http://sun.hasenbraten.de/vasm/) and [clownassembler](https://github.com/Clownacy/clownassembler) assemblers were very helpful for determining correct behaviour of the encoding of the instructions.
