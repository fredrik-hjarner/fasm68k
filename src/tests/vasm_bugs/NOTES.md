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
I realize the reason for it being 100 "correct" is because eor NEEDS to be eori, i.e. it's not a performance optimization but a requirement.

#### cmp

all cmp.[bwl] <imm>, <dn> are encoded incorrectly.
all cmp.[wl] <imm>, <an> are encoded incorrectly.
    though with `an` it becomes `cmpa` so that makes sense.

## OBSERVE! There are actually more differences with these specific instructions but I have a problem pinpointing what the exact problem is and with which exact situations.

## OBSERVE! I think I misunderstood the situation. `add -> addi` seems to only be a performance optimization??


------------------------

Finally I found something interesting:

OBJ_SCENE_BASE = $1000

OBJ_SCENE_PLANT_ALT = OBJ_SCENE_BASE + $38

MEM_ACTION_TARGET_OBJID = $FFFF002E

5EE6:   cmp.w #OBJ_SCENE_PLANT_ALT, (MEM_ACTION_TARGET_OBJID)

so whats happening here...
vasm does cmp -> cmpi because 2nd operand is a
NOT Dn (cmp only supports a Dn dest)!!!