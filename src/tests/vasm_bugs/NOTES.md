## So let's record what vasm does right and wrong.

Based on observation:

#### or

every single case for or.b <imm> is encoded incorrectly.
every single case for or.w <imm> is encoded incorrectly.
every single case for or.l <imm> is encoded incorrectly.

#### and

every single case for and.b <imm> is encoded incorrectly.
every single case for and.w <imm> is encoded incorrectly.
every single case for and.l <imm> is encoded incorrectly.

#### sub

all sub.[bwl] <imm>, <dn> are encoded incorrectly.
all sub.[wl] <imm>, <an> are encoded incorrectly.
    though with `an` it becomes `suba` so that makes sense.

#### add

all add.[bwl] <imm>, <dn> are encoded incorrectly.
all add.[wl] <imm>, <an> are encoded incorrectly.
    though with `an` it becomes `adda` so that makes sense.

#### eor

vasm encodes `eor` 100% correctly.

#### cmp

all cmp.[bwl] <imm>, <dn> are encoded incorrectly.
all cmp.[wl] <imm>, <an> are encoded incorrectly.
    though with `an` it becomes `cmpa` so that makes sense.