all: gen_tests gen_validation build hexdump
.PHONY: all

clown: gen_tests gen_validation clownassembler hexdump
.PHONY: clown

vasm: gen_tests gen_validation build_vasm hexdump
.PHONY: vasm

gen_tests:
	bun tests/generate_tests.ts
.PHONY: gen_tests

# Generate instruction validation structure for fasm68k.
gen_validation:
	bun tests/generate_validation.ts
.PHONY: gen_validation

# clownassembler runs `valid_instructions.asm` directly while fasmg runs a wrapper
# file that includes the m68k instruction set.
# The reason is that * is not supported in fasmg and I don't know if I can
# make it supported, in fasmg $ is used instead. I use @ as a kind of
# "middle-ground" since it is almost the same as * in clownassembler and I can
# easily have `@ equ $` in fasmg.
clownassembler:
#	clownassembler -c -o tests/test.bin -i tests/valid_instructions.asm
# -w silences warnings.
	clownassembler -c -l valid_instructions.lst -w -o tests/test.bin -i tests/valid_instructions.asm
.PHONY: clownassembler

# vasm does not support @ but only * it seems?
build_vasm:
	sed 's/@/\*/g' tests/valid_instructions.asm | vasm -no-opt -Fbin -spaces -wfail -o tests/test.bin
#	vasm -Fbin -spaces -wfail -o tests/test.bin tests/valid_instructions.asm
.PHONY: build_vasm

# TODO: what's best -v1 or -v2? option
build:
	../fasm68k tests/valid_instructions.asm tests/test.bin -e20 -v2
.PHONY: build

# build2 is just for me to have a separate test file to play around with.
build2:
	../fasm68k tests/test2.asm tests/test2.bin -e20 -v0
.PHONY: build2

hexdump:
	xxd -b -c1 tests/test.bin | cut -d' ' -f2,4 > tests/test.hex
#  hexdump -v -e '/1 "%02x\n"' tests/test.bin > tests/test.hex
.PHONY: hexdump

clean:
	rm -f tests/test.bin tests/test.hex
.PHONY: clean

commit_count:
	git rev-list --count HEAD
.PHONY: commit_count

################################################################################
## TESTING VASM BUGS                                                          ##
################################################################################

## GENERATE TESTS ##############################################################

gen_tests_vasm_bugs:
	bun tests/vasm_bugs/generate_tests.ts
.PHONY: gen_tests_vasm_bugs

## TOP LEVEL COMMANDS ##########################################################

fasm_vasm_bugs: gen_tests_vasm_bugs build_fasm_vasm_bugs hexdump_vasm_bugs
.PHONY: fasm_vasm_bugs

clown_vasm_bugs: gen_tests_vasm_bugs build_clown_vasm_bugs hexdump_vasm_bugs
.PHONY: clown_vasm_bugs

vasm_vasm_bugs: gen_tests_vasm_bugs build_vasm_vasm_bugs hexdump_vasm_bugs
.PHONY: vasm_vasm_bugs

## BUILD COMMANDS ##############################################################

build_clown_vasm_bugs:
	clownassembler -c -w -o tests/vasm_bugs/test.bin -i tests/vasm_bugs/valid_instructions.asm
.PHONY: build_clown_vasm_bugs

# vasm does not support @ but only * it seems?
build_vasm_vasm_bugs:
	sed 's/@/\*/g' tests/vasm_bugs/valid_instructions.asm | vasm -no-opt -Fbin -spaces -wfail -o tests/vasm_bugs/test.bin
.PHONY: build_vasm_vasm_bugs

build_fasm_vasm_bugs:
	../fasm68k tests/vasm_bugs/valid_instructions.asm tests/vasm_bugs/test.bin -e20 -v2
.PHONY: build_fasm_vasm_bugs

## HEXDUMP #####################################################################

hexdump_vasm_bugs:
	xxd -b -c1 tests/vasm_bugs/test.bin | cut -d' ' -f2,4 > tests/vasm_bugs/test.hex
#  hexdump -v -e '/1 "%02x\n"' tests/test.bin > tests/test.hex
.PHONY: hexdump_vasm_bugs

## CLEAN #######################################################################

clean_vasm_bugs:
	rm -f tests/vasm_bugs/test.bin tests/vasm_bugs/test.hex tests/vasm_bugs/valid_instructions.asm
.PHONY: clean_vasm_bugs
