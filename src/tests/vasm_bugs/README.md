This folder contains tests to test some bugs I found in vasm.

When vasm auto-fixes some instructions (add -> addi etc.) it encodes them
incorrectly. Well, actually vasm encode them maybe correctly, I misunderstood.
What's going on is that add -> addi is actually a performance optimization
I first thought that it NEEDED to be such a transformation, so actually in
comparison to vasm clownassembler actually doing some more optimizations,
and I happened to think that clownassembler was doing NO optimizations, i.e.
my thinking that vasm encoded them incorrectly was a misunderstanding.

Anyway, so here we have a long file with tests for the involved instructions
by the name `valid_instructions.asm`. fasm68 does not assemble these directly
but here uses a wrapper (that then includes the `valid_instructions.asm` file)
to set some fasm68k settings, i.e. to turn off the optimizations. The goal here
is to perfectly mimic vasm's behavior in the end.