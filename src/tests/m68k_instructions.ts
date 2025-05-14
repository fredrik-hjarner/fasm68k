////////////////////////////////////////////////////////////////////////////////
// THIS FILE CONTAINS ALL THE VALID INSTRUCTIONS AND THEIR VARIANTS.          //
////////////////////////////////////////////////////////////////////////////////

// Types for M68k instructions data
export type OperandType = 
    | "dn" | "an" | "(an)" | "(an)+" | "-(an)" | "d(an)" | "d(an,ix)" 
    | "abs.w" | "abs.l" | "d(pc)" | "d(pc,ix)" | "imm" | "imm3" | "imm4" 
    | "imm8" | "imm8s" | "imm16" | "imm16s" | "label" | "register_list" | "ccr"
    | "sr" | "usp" | "dc.b" | "dc.w" | "dc.l";

// "" means without size suffix.
export type OperandSize = "b" | "w" | "l" | "s" | "";

export type InstructionVariant = {
    sizes: OperandSize[];
    op1: OperandType[];
    op2: OperandType[];
};

export type Group = {
    instructions: string[];
    variants: InstructionVariant[];
}

export type InstructionSet = Group[];

// TODO: Remove all of these all32, dataAddressingModes8 etc. and have them
// inline instead. That makes it easier to verify that all's correct.
// All <ea> addressing modes 32-bits
const all32 = [
  "dn",       "abs.w",
  "an",       "abs.l",
  "(an)",     "imm",
  "(an)+",
  "-(an)",
  "d(an)",    "d(pc)",
  "d(an,ix)", "d(pc,ix)"
] satisfies OperandType[];

////////////////////////////////////////////////////////////////////////////////
// dataAddressingModes8                                                       //
////////////////////////////////////////////////////////////////////////////////

const dataAddressingModes8 = [
  "dn",       "abs.w",
  /*"an",*/   "abs.l",
  "(an)",     "imm8",
  "(an)+",
  "-(an)",
  "d(an)",    "d(pc)",
  "d(an,ix)", "d(pc,ix)"
] satisfies OperandType[];
const dataAddressingModes16 = [
  "dn",       "abs.w",
  /*"an",*/   "abs.l",
  "(an)",     "imm16",
  "(an)+",
  "-(an)",
  "d(an)",    "d(pc)",
  "d(an,ix)", "d(pc,ix)"
] satisfies OperandType[];
const dataAddressingModes32 = [
  "dn",       "abs.w",
  /*"an",*/   "abs.l",
  "(an)",     "imm", // TODO: Rename to imm32!
  "(an)+",
  "-(an)",
  "d(an)",    "d(pc)",
  "d(an,ix)", "d(pc,ix)"
] satisfies OperandType[];

const alterableAddressingModes32 = [
  "dn",       "abs.w",
  "an",       "abs.l",
  "(an)",     //"imm32",
  "(an)+",
  "-(an)",
  "d(an)",    //"d(pc)",
  "d(an,ix)", //"d(pc,ix)"
] satisfies OperandType[];

const dataAlterableAddressingModes32 = [
  "dn",       "abs.w",
  /*"an",*/   "abs.l",
  "(an)",     //"imm32",
  "(an)+",
  "-(an)",
  "d(an)",    //"d(pc)",
  "d(an,ix)", //"d(pc,ix)"
] satisfies OperandType[];

const controlAddressingModes = [
  /*"dn",*/   "abs.w",
  /*"an",*/   "abs.l",
  "(an)",     //"imm32",
  //"(an)+",
  //"-(an)",
  "d(an)",    "d(pc)",
  "d(an,ix)", "d(pc,ix)"
] satisfies OperandType[];

// Extention to allow to remove values from an array with shorter syntax.
Array.prototype.except = function(value) {
  return this.filter(item => item !== value);
};

export const data: InstructionSet = [
  // Data declaration instructions
  // I mean `dc` is more of a `directive` so have in mind it's different.
  //     For example `dc` is completely variadic which no real instruction is. 
  {
    instructions: ["dc"],
    variants: [
      { sizes: ["b"], op1: ["dc.b"], op2: [] },
      { sizes: ["w"], op1: ["dc.w"], op2: [] },
      { sizes: ["l"], op1: ["dc.l"], op2: [] },
    ]
  },
  {
    // All verified. I am very confident that this is correct.
    instructions: ["ori", "andi", "eori"],
    variants: [
      // CCR variant
      {
        sizes: ["b", ""],           // ori=verified, andi=veri, eori=veri
        op1: ["imm8"],   // ori=verified, andi=veri, eori=veri
        op2: ["ccr"]       // ori=verified, andi=veri, eori=veri
      },
      // SR variant
      {
        sizes: ["w", ""],           // ori=verified, andi=veri, eori=veri
        op1: ["imm16"],  // ori=verified, andi=veri, eori=veri
        op2: ["sr"]        // ori=verified, andi=veri, eori=veri
      },
      // Standard variant
      {
        sizes: ["b", "w", "l"],     // ori=verified, andi=veri, eori=veri
        op1: ["imm"],    // ori=verified, andi=veri, eori=veri
        op2:
          dataAlterableAddressingModes32, // ori=verified, andi=veri, eori=veri
      },
    ]
  },
  {
    // All verified. I am very confident that this is correct.
    instructions: ["subi", "addi", "cmpi"],
    variants: [
      {
        sizes: ["b", "w", "l"],   // subi=verified, addi=veri, cmpi=veri
        op1: ["imm"],  // subi=verified, addi=veri, cmpi=veri
        op2:
          // Note: Reference says "dataAddressingModes" for cmpi, but adds that:
          //       "PC relative addressing modes do not apply to MC68000"
          dataAlterableAddressingModes32, // subi=verified, addi=veri, cmpi=veri
      }
    ]
  },
  {
    // Verified. Should be correct.
    //
    // Assembler syntax:
    //     BTST Dn,      <ea>
    //     BTST #<data>, <ea>
    instructions: ["btst"],
    variants: [
      {
        sizes: ["l", ""],               // verified
        op1: ["dn", "imm8"], // verified
        op2: ["dn"]            // verified
      },
      {
        sizes: ["b", ""],       // verified
        op1: ["dn"], // verified
        op2: [         // verified
          /*"dn",*/   "abs.w",
          /*"an",*/   "abs.l",
          "(an)",     "imm8",
          "(an)+",
          "-(an)",
          "d(an)",    "d(pc)",
          "d(an,ix)", "d(pc,ix)"
        ],
      },
      {
        sizes: ["b", ""],         // verified
        op1: ["imm8"], // verified
        op2: [           // verified
          /*"dn",*/   "abs.w",
          /*"an",*/   "abs.l",
          "(an)",     //"imm",
          "(an)+",
          "-(an)",
          "d(an)",    "d(pc)",
          "d(an,ix)", "d(pc,ix)"
        ],
      }
    ]
  },
  // Bit manipulation instructions - BCHG, BCLR, BSET (no PC-relative addressing)
  {
    instructions: ["bchg", "bclr", "bset"],
    variants: [
      {
        sizes: ["l", ""],
        op1: ["dn"],
        op2: ["dn"]
      },
      {
        sizes: ["b", ""],
        op1: ["dn"],
        op2: ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      {
        sizes: ["l", ""],
        op1: ["imm8"],
        op2: ["dn"]
      },
      {
        sizes: ["b", ""],
        op1: ["imm8"],
        op2: ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // Set according to condition (Scc) instructions
  {
    // TODO: Make sure these also contain all the aliases for conditions.
    instructions: ["st", "sf", "shi", "sls", "scc", "scs", "sne", "seq", "svc", "svs", "spl", "smi", "sge", "slt", "sgt", "sle", "shs", "slo"],
    variants: [
      {
        sizes: ["b", ""],
        op1: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"],
        op2: []
      }
    ]
  },
  // Branch instructions
  {
    // TODO: Make sure these also contain all the aliases for conditions.
    instructions: ["bra", "bsr", "bhi", "bls", "bcc", "bcs", "bne", "beq", "bvc", "bvs", "bpl", "bmi", "bge", "blt", "bgt", "ble", "bhs", "blo"],
    variants: [
      {
        sizes: ["s", "w", ""],
        op1: ["label"],
        op2: []
      }
    ]
  },
  // DBcc instructions
  {
    // TODO: Make sure these also contain all the aliases for conditions.
    instructions: ["dbt", "dbf", "dbhi", "dbls", "dbcc", "dbcs", "dbne", "dbeq", "dbvc", "dbvs", "dbpl", "dbmi", "dbge", "dblt", "dbgt", "dble", "dbhs", "dblo"],
    variants: [
      {
        sizes: ["w", ""],
        op1: ["dn"],
        op2: ["label"]
      }
    ]
  },
  // MOVEP
  {
    // Verified. Should be correct.
    instructions: ["movep"],
    variants: [
      {
        sizes: ["w", "l"],          // verified
        op1: ["d(an)"],  // verified
        op2: ["dn"]        // verified
      },
      {
        sizes: ["w", "l"],          // verified
        op1: ["dn"],     // verified
        op2: ["d(an)"]     // verified
      }
    ]
  },
  // MOVEA
  {
    // Verified. I am very confident that this is correct.
    instructions: ["movea"],
    variants: [
      {
        sizes: ["w", "l"],    // verified
        op1: [     // verified
          "dn",       "abs.w",
          "an",       "abs.l",
          "(an)",     "imm",
          "(an)+",
          "-(an)",
          "d(an)",    "d(pc)",
          "d(an,ix)", "d(pc,ix)"
        ],
        op2: ["an"]  // verified
      }
    ]
  },
  // MOVE
  {
    // Quote from reference manual:
    //     NOTE
    //     Most assemblers use MOVEA when the destination is an
    //     address register.
    //     MOVEQ can be used to move an immediate 8-bit value to a data
    //     register.
    instructions: ["move"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        op1: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "imm", "d(pc)", "d(pc,ix)"],
        op2: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      // `an` is NOT supported but since `move` will be auto-fixed to `movea`
      // it is supported "in practice".
      {
        sizes: ["w", "l"],
        op1: all32,
        op2: ["an"]
      },
      // // TODO: This includes "an"???
      // https://github.com/prb28/m68k-instructions-documentation/blob/master/instructions/move.md
      {
        sizes: ["w", "l"],
        op1: ["an"],
        op2: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      {
        sizes: ["w"],
        op1: ["sr"],
        op2: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      {
        sizes: ["w"],
        op1: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        op2: ["ccr"]
      },
      {
        sizes: ["w"],
        op1: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        op2: ["sr"]
      },
      // MOVE USP
      {
        sizes: ["l", ""],
        op1: ["usp"],
        op2: ["an"]
      },
      {
        sizes: ["l", ""],
        op1: ["an"],
        op2: ["usp"]
      }
    ]
  },
  // Simple memory/register operations (negx, clr, neg, not)
  {
    instructions: ["negx", "clr", "neg", "not"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        op1: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"],
        op2: []
      }
    ]
  },
  // TAS instruction (byte only)
  {
    // Verified. I am very confident that this is correct.
    instructions: ["tas"],
    variants: [
      {
        sizes: ["b", ""],   // verified
        op1: [     // verified
          "dn",       "abs.w",
          /*"an",*/   "abs.l",
          "(an)",     //"imm",
          "(an)+",
          "-(an)",
          "d(an)",    //"d(pc)",
          "d(an,ix)", //"d(pc,ix)"
        ],
        op2: [], // verified
      }
    ]
  },
  {
    // Verified. I am very confident that this is correct.
    instructions: ["ext"],
    variants: [
      {
        sizes: ["w", "l"],    // verified
        op1: ["dn"],   // verified
        op2: []  // verified
      }
    ]
  },
  // SWAP instruction (no size suffix)
  {
    instructions: ["swap"],
    variants: [
      {
        sizes: ["w", ""],
        op1: ["dn"],
        op2: []
      }
    ]
  },
  // NBCD
  {
    instructions: ["nbcd"],
    variants: [
      {
        sizes: ["b", ""],
        op1: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"],
        op2: []
      }
    ]
  },
  // PEA
  {
    instructions: ["pea"],
    variants: [
      {
        sizes: ["l", ""],
        op1: ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
        op2: []
      }
    ]
  },
  // No operand instructions
  {
    // Verified. I am very confident that this is correct.
    instructions: ["illegal", "reset", "nop", "rte", "rts", "trapv", "rtr"],
    variants: [
      { sizes: [""], op1: [], op2: [] } // verified
    ]
  },
  // TST
  {
    // Verified. I am very confident that this is correct.
    instructions: ["tst"],
    variants: [
      {
        sizes: ["b", "w", "l"], // verified
        op1: [       // verified
          "dn",       "abs.w",
          /*"an",*/   "abs.l",
          "(an)",     //"imm",
          "(an)+",
          "-(an)",
          "d(an)",    //"d(pc)",
          "d(an,ix)", //"d(pc,ix)"
        ],
        op2: [],       // verified
      }
    ]
  },
  // TRAP
  {
    instructions: ["trap"],
    variants: [
      {
        sizes: [""],
        op1: ["imm4"],
        op2: []
      }
    ]
  },
  // LINK
  {
    instructions: ["link"],
    variants: [
      {
        sizes: ["w", ""],
        op1: ["an"],
        op2: ["imm16s"]
      }
    ]
  },
  // UNLK
  {
    instructions: ["unlk"],
    variants: [
      {
        sizes: [""],
        op1: ["an"],
        op2: []
      }
    ]
  },
  // STOP
  {
    instructions: ["stop"],
    variants: [
      {
        sizes: [""],
        op1: ["imm16"],
        op2: []
      }
    ]
  },
  // Jump instructions
  {
    instructions: ["jsr", "jmp"],
    variants: [
      {
        sizes: [""],
        op1: ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
        op2: []
      }
    ]
  },
  // MOVEM
  {
    instructions: ["movem"],
    variants: [
      {
        sizes: ["w", "l"],
        op1: ["register_list"],
        op2: ["(an)", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      {
        sizes: ["w", "l"],
        op1: ["(an)", "(an)+", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
        op2: ["register_list"]
      }
    ]
  },
  // LEA
  {
    instructions: ["lea"],
    variants: [
      {
        sizes: ["l", ""], // verified
        op1: controlAddressingModes, // verified
        op2: ["an"] // verified
      }
    ]
  },
  // CHK
  {
    instructions: ["chk"],
    variants: [
      {
        sizes: ["w", ""], // verified
        op1: dataAddressingModes16, // verified
        op2: ["dn"] // verified
      }
    ]
  },
  // Quick operations
  {
    instructions: ["addq", "subq"],
    variants: [
      {
        sizes: ["b", "w", "l"], // verified
        op1: ["imm3"], // verified
        op2: [ // verified
          "dn",       "abs.w",
          /*"an",*/   "abs.l",
          "(an)",     //"imm",
          "(an)+",
          "-(an)",
          "d(an)",    //"d(pc)",
          "d(an,ix)", //"d(pc,ix)"
        ]
      },
      {
        sizes: ["w", "l"],
        op1: ["imm3"],
        op2: ["an"]
      },
    ]
  },
  // MOVEQ
  {
    instructions: ["moveq"],
    variants: [
      {
        sizes: ["l", ""], // verified
        op1: ["imm8s"], // verified
        op2: ["dn"] // verified
      }
    ]
  },
  // Division operations
  {
    instructions: ["divu", "divs"],
    variants: [
      {
        sizes: ["w", ""], // verified
        op1: dataAddressingModes16, // verified
        op2: ["dn"] // verified
      }
    ]
  },
  // Binary-coded decimal operations
  {
    instructions: ["sbcd", "abcd"],
    variants: [
      {
        sizes: ["b", ""], // verified
        op1: ["dn"], // verified
        op2: ["dn"] // verified
      },
      {
        sizes: ["b", ""], // verified
        op1: ["-(an)"], // verified
        op2: ["-(an)"] // verified
      },
    ]
  },
  // Logical operations
  {
    /*
      Quote from reference manual:
        NOTE
        If the destination is a data register, it must be specified using the
        destination Dn mode, not the destination < ea > mode.
        Most assemblers use ORI when the source is immediate data
    */
    instructions: ["or", "and"],
    variants: [
      {
        sizes: ["b"], // verified
        // `imm` is NOT supported but since `or/and` will be auto-fixed to
        // `ori/andi` is supported "in practice".
        op1: dataAddressingModes8, // verified
        op2: ["dn"] // verified
      },
      {
        sizes: ["w", "l"], // verified
        // `imm` is NOT supported but since `er/and` will be auto-fixed to
        // `ori/andi` it is supported "in practice".
        // TODO: I don't quite understand why the .w one accepts an imm32
        //       in both vasm and clownassembler??
        op1: dataAddressingModes32, // verified
        op2: ["dn"] // verified
      },
      {
        sizes: ["b", "w", "l"], // verified
        op1: ["dn"], // verified
        op2: [ // verified
          /*"dn",*/   "abs.w",
          /*"an",*/   "abs.l",
          "(an)",     //"imm",
          "(an)+",
          "-(an)",
          "d(an)",    //"d(pc)",
          "d(an,ix)", //"d(pc,ix)"
        ]
      },
    ]
  },
  {
    instructions: ["sub", "add"],
    /*
      Quote from reference manual:
        NOTE
        The Dn mode is used when the destination is a data register; the
        destination < ea > mode is invalid for a data register.

        ADDA is used when the destination is an address register. ADDI
        and ADDQ are used when the source is immediate data. Most
        assemblers automatically make this distinction.
     */
    variants: [
      {
        sizes: ["b", "w", "l"], // verified
        op1: [ // verified
          "dn",       "abs.w",
          /*"an",*/   "abs.l",
          // `imm` is NOT supported but since `add/sub` will be auto-fixed to
          // `addi/subi` it is supported "in practice".
          "(an)",     "imm",
          "(an)+",
          "-(an)",
          "d(an)",    "d(pc)",
          "d(an,ix)", "d(pc,ix)"
        ],
        op2: ["dn"] // verified
      },
      {
        sizes: ["w", "l"], // verified
        op1: ["an"], // verified
        op2: ["dn"] // verified
      },
      // `an` is NOT supported but since `move` will be auto-fixed to `movea`
      // it is supported "in practice".
      // TODO: I mean... what I could do in cases of auto-fixing is that
      //       I could add the entire `movea` here, though that would probably
      //       end up in duplicated tests maybe not sure.
      //       Anyway that would be nicer than adding each thingie manually
      //       hard-coded.
      {
        sizes: ["w", "l"],
        op1: all32,
        op2: ["an"]
      },
      {
        sizes: ["b", "w", "l"], // verified
        op1: ["dn"], // verified
        op2: [ // verified
          /*"dn",*/   "abs.w",
          /*"an",*/   "abs.l",
          "(an)",     //"imm",
          "(an)+",
          "-(an)",
          "d(an)",    //"d(pc)",
          "d(an,ix)", //"d(pc,ix)"
        ]
      }
    ]
  },
  {
    instructions: ["subx", "addx"],
    variants: [
      {
        sizes: ["b", "w", "l"], // verified
        op1: ["dn"], // verified
        op2: ["dn"] // verified
      },
      {
        sizes: ["b", "w", "l"], // verified
        op1: ["-(an)"], // verified
        op2: ["-(an)"] // verified
      }
    ]
  },
  // SUBA
  {
    instructions: ["suba"],
    variants: [
      {
        sizes: ["w", "l"], // verified
        op1: all32, // verified
        op2: ["an"] // verified
      }
    ]
  },
  // EOR
  {
    instructions: ["eor"],
    variants: [
      {
        sizes: ["b", "w", "l"], // verified
        // `imm` is NOT supported but since `eor` will be auto-fixed to `eori`
        // it is supported "in practice".
        // TODO: Add imm and make sure I am not missing anything.
        op1: ["dn", "imm"], // verified
        op2: dataAlterableAddressingModes32, // verified
      },
      // TODO: vasm auto-fixes (I think) eor -> eori when 2nd operand is ccr/sr
      //       but clownassembler does not, so it makes it hard to test since
      //       I have no other assembler that does EVERYTHING so to speak, so
      //       I settle for compatability with clownassembler for now (since
      //       vI found bugs in vasm encodings for example).
      // // CCR variant
      // {
      //   sizes: ["b", ""],
      //   op1: ["imm8"],
      //   op2: ["ccr"]
      // },
      // // SR variant
      // {
      //   sizes: ["w", ""],
      //   op1: ["imm16"],
      //   op2: ["sr"]
      // },
    ]
  },
  // CMPM
  {
    instructions: ["cmpm"],
    variants: [
      {
        sizes: ["b", "w", "l"], // verified
        op1: ["(an)+"], // verified
        op2: ["(an)+"] // verified
      }
    ]
  },
  // CMP
  {
    instructions: ["cmp"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        /*
          Quote from reference manual:
            NOTE
            CMPA is used when the destination is an address register. CMPI
            is used when the source is immediate data. CMPM is used for
            memory-to-memory compares. Most assemblers automatically
            make the distinction.
        */
        // Does that mean cmp does not support memory-to-memory compares
        // or just that cmpm is more effecient for memory-to-memory compares?
        op1: [ // TODO: Double-check this.
          "dn",       "abs.w",
          /*"an",*/   "abs.l",
          // `imm` is NOT supported but since `cmp` will be auto-fixed to
          // `cmpi` it is supported "in practice".
          "(an)",     "imm",
          "(an)+",
          "-(an)",
          "d(an)",    "d(pc)",
          "d(an,ix)", "d(pc,ix)"
        ],
        op2: ["dn"]
      },
      {
        sizes: ["w", "l"],
        op1: [ "an"],
        op2: ["dn"]
      },
      // `an` is NOT supported but since `cmp` will be auto-fixed to `cmpa`
      // it is supported "in practice".
      // TODO: I mean... what I could do in cases of auto-fixing is that
      //       I could add the entire `movea` here, though that would probably
      //       end up in duplicated tests maybe not sure.
      //       Anyway that would be nicer than adding each thingie manually
      //       hard-coded.
      {
        sizes: ["w", "l"],
        op1: all32,
        op2: ["an"]
      },
    ]
  },
  // CMPA
  {
    instructions: ["cmpa"],
    variants: [
      {
        sizes: ["w", "l"], // verified
        op1: all32, // verified
        op2: ["an"] // verified
      }
    ]
  },
  // Multiplication operations
  {
    instructions: ["mulu", "muls"],
    variants: [
      {
        sizes: ["w", ""], // verified
        op1: dataAddressingModes16, // verified,
        op2: ["dn"] // verified
      }
    ]
  },
  // EXG
  {
    instructions: ["exg"],
    variants: [
      {
        sizes: ["l", ""], // verified
        op1: ["dn", "an"], // verified
        op2: ["dn", "an"] // verified
      }
    ]
  },
  // ADDA
  {
    instructions: ["adda"],
    variants: [
      {
        sizes: ["w", "l"], // verified
        op1: all32, // verified,
        op2: ["an"] // verified
      }
    ]
  },
  // Shift/Rotate operations
  {
    instructions: ["asl", "asr", "lsl", "lsr", "roxl", "roxr", "rol", "ror"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        op1: ["dn", "imm3"],
        op2: ["dn"]
      },
      {
        sizes: ["w", ""],
        op1: ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"],
        op2: []
      }
    ]
  }
];