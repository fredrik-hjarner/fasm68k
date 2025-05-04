.PHONY: all clown vasm build build2 clownassembler hexdump clean gen_tests

all: gen_tests build hexdump

clown: gen_tests clownassembler hexdump

vasm: gen_tests build_vasm hexdump

gen_tests:
	bun generate_tests.ts

# clownassembler runs `valid_instructions.asm` directly while fasmg runs a wrapper
# file that includes the m68k instruction set.
# The reason is that * is not supported in fasmg and I don't know if I can
# make it supported, in fasmg $ is used instead. I use @ as a kind of
# "middle-ground" since it is almost the same as * in clownassembler and I can
# easily have `@ equ $` in fasmg.
clownassembler:
	clownassembler -c -o tests/test.bin -i tests/valid_instructions.asm

# vasm does not support @ but only * it seems?
build_vasm:
	sed 's/@/\*/g' tests/valid_instructions.asm | vasm -no-opt -Fbin -spaces -wfail -o tests/test.bin
#	vasm -Fbin -spaces -wfail -o tests/test.bin tests/valid_instructions.asm

build:
	fasmg tests/test_fasmg.asm tests/test.bin -e20

# build2 is just for me to have a separate test file to play around with.
build2:
	fasmg tests/test2.asm tests/test2.bin -e20

hexdump:
	xxd -b -c1 tests/test.bin | cut -d' ' -f2,4 > tests/test.hex
#  hexdump -v -e '/1 "%02x\n"' tests/test.bin > tests/test.hex

clean:
	rm -f tests/test.bin tests/test.hex


