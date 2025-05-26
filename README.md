# fasm68k - Motorola 68000 instruction set for fasmg (flat assembler g)

> [!NOTE]
> Consider this to be in beta stage. It's perfectly usable with all 68k
instructions validated with about [22,000 tests](https://raw.githubusercontent.com/fredrik-hjarner/fasm68k/refs/heads/master/src/tests/valid_instructions.asm)
and Sonic 1 and Retail Clerk '89 are assembled after every push, but I don't
feel ready to call this version 1.0.0 yet.

## What is fasm68k?

fasm68k is a set of fasmg macros that adds the Motorola 68000 instruction set to
[fasmg](https://flatassembler.net/docs.php?article=fasmg) to allow it
to assemble 68k assembly code. fasm68k also has it's own set of directives and
adds settings to allow for _some_ compatability (such as aliases or support for
colonless labels), with other m68k assemblers in order to make it easier to
convert codebases to fasm68k.

### Why?

Well, fasmg's macro language is cool, other macro languages feel a bit pale in
comparison, but there was no one who had made a 68000 instruction set for it yet
so here it is.

If you have no idea what `fasmg` is then
I'll quite from it's _Introduction and Overview_:

> This is a bare engine that by itself has no ability to recognize and encode instructions of any processor, however it has the ability to become an assembler for any CPU architecture.

And that's what fasm68k is, it's a set of fasmg macros to allow fasmg to
assemble 68k assembly code.

## Scope

- The instruction set for the original 68000 _not_ including any later models such as the 68020 etc. though if demand exists I might consider adding such instructions.
- Compatibility with other assemblers to aid in reproducing exactly the same binaries as other assemblers.

Performance and optimization of the produced binary is not prioritized
at this point.

## Example

fasm68k aims to have _some_ compatability with other 68k assemblers, but will
probably never become 100% compatible.
[Here](https://github.com/BigEvilCorporation/megadrive_samples/compare/master...fredrik-hjarner:megadrive_samples_fasm68k:master) is one example of what was
needed to to adapt code originally for the asm68k assembler to fasm68k.

The compatability aspect of fasm68k is still under development. I hope that it
will be even easier to adapt projects to fasm68k in the future.

## Installation

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

```
./fasm68k examples/megadrive_simple_demo/main.asm
./fasm68k examples/megadrive_samples_fasm68k/1_hello_world/hello.asm
./fasm68k examples/megadrive_samples_fasm68k/2_scroll_planes/scroll.asm
./fasm68k examples/megadrive_samples_fasm68k/3_sprites/sprites.asm
./fasm68k examples/megadrive_samples_fasm68k/4_gamepad/gamepad.asm
./fasm68k examples/megadrive_samples_fasm68k/6_psg_tone/psg_tone.asm
./fasm68k examples/RetailClerk89_fasm68k/src/RetailClerk89.X68
./fasm68k examples/speedrun-tower_fasm68k/src/SpeedrunTower.X68
```

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

<details>
<summary>Mac</summary>
<blockquote>
Unfortunately you're out of luck. fasmg only runs on x86 processors (since
it is written in assembly), so you would need to run a virtual machine with
either Windows or Linux then follow the Linux or Windows instructions.
</blockquote>
</details>

## Directives and keywords

Beyond the standard fasmg directives and keywords, fasm68k adds the following
ones:

| Directive/<br>keyword  | Description                                   | Also present in<br>these assemblers |
|------------------------|-----------------------------------------------|----------------------|
| `__rs`                 | Current value of RS counter                   | asm68k               |
| `rsset`                | Set `__rs` address.                           | asm68k               |
| `even`                 | Word-align the current address.               | asm68k, vasm         |
| `rseven`               | Word-align the `__rs` address.                |                      |
| `rs.b`                 | Reserve a byte of space.                      | asm68k               |
| `rs.w`                 | Reserve a word of space.                      | asm68k               |
| `rs.l`                 | Reserve a longword of space.                  | asm68k               |
| `dc.b`                 | Define a byte.                                | asm68k, vasm         |
| `dc.w`                 | Define a word.                                | asm68k, vasm         |
| `dc.l`                 | Define a longword.                            | asm68k, vasm         |
| `incbin`               | Include a binary file.                        | asm68k, vasm         |

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

<details>
<summary>In comparison to vasm (vasmm68k_mot)</summary>
<blockquote>
### ORG

`ORG` works very differently in vasm and fasmg. In fasmg the addresses in after
`ORG` are based on the value specified in the argument. In vasm the `ORG`
command actually adds empty bytes up to the specified address.

- [x] I will add a compatibility setting to support the vasm behaviour. It is recommended to have that setting disabled unless you need it.
</blockquote>
</details>

## History

- 2025-03-28:
  - Humble beginnings: Initial implementation of `nop`, `rte` and `rts`.
- 2025-05-05:
  - Alpha "release".
  - Rudimentary implementation of all 680000 instructions and all addressing modes.
  - First commit to the `fasm68k` repository.
- 2025-05-06:
  - fasm68k can correctly assemble all BigEvilCorporation's `megadrive_samples`.
- 2025-05-12:
  - fasm68k can correctly assemble Hugues Johnson's RetailClerk89. It took about 30-40 hours to get it to produce identical binary.
- 2025-05-13:
  - fasm68k can correctly assemble Hugues Johnson's Speedrun Tower. It took 45 minutes to get it to run in an emulator and about 1 hour to produce identical binary.
- 2025-05-20:
  - fasm68k can correctly assemble Sonic Retro's Sonic 1 dissasembly producing identical binary, though it required many changes to the code to make itcompatible.

## Acknowledgments and attributions

- [Tomasz Grysztar](https://github.com/tgrysztar) for fasmg.
- [BigEvilCorporation](https://github.com/BigEvilCorporation) for the megadrive_samples which I simply adapted for fasm68k.
- The [vasm](http://sun.hasenbraten.de/vasm/) and [clownassembler](https://github.com/Clownacy/clownassembler) assemblers were very helpful for determining correct behaviour of the encoding of the instructions.
- [Hugues Johnson's](https://github.com/HuguesJohnson) [RetailClerk89](https://github.com/HuguesJohnson/RetailClerk89) and [Speedrun Tower](https://github.com/HuguesJohnson/speedrun-tower) were great games to test fasm68k with.
- Exodus and Kega Fusion emulators were used to test the output of fasm68k.
- [This m68k encoding pdf](http://goldencrystal.free.fr/M68kOpcodes-v2.3.pdf) by GoldenCrystal was extremely helpful.
