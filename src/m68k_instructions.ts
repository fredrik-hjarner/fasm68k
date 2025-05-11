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
    sourceOperands: OperandType[];
    destOperands: OperandType[];
};

export type Group = {
    instructions: string[];
    variants: InstructionVariant[];
}

export type InstructionSet = Group[];

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

const dataAddressingModes16 = [
  "dn",       "abs.w",
  /*"an",*/   "abs.l",
  "(an)",     "imm16",
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
  {
    instructions: ["dc"],
    variants: [
      {
        sizes: ["b"],
        sourceOperands: [],
        destOperands: ["dc.b"]
      },
      {
        sizes: ["w"],
        sourceOperands: [],
        destOperands: ["dc.w"]
      },
      {
        sizes: ["l"],
        sourceOperands: [],
        destOperands: ["dc.l"]
      }
    ]
  },
  // Immediate to CCR/SR instructions group
  {
    instructions: ["ori", "andi", "eori"],
    variants: [
      // CCR variant
      {
        sizes: ["b", ""],
        sourceOperands: ["imm8"],
        destOperands: ["ccr"]
      },
      // SR variant
      {
        sizes: ["w", ""],
        sourceOperands: ["imm16"],
        destOperands: ["sr"]
      },
      // Standard variant
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["imm"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // Immediate to memory/register instructions
  {
    instructions: ["subi", "addi", "cmpi"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["imm"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // Bit manipulation instructions - BTST (supports PC-relative addressing)
  {
    instructions: ["btst"],
    variants: [
      {
        sizes: ["l", ""],
        sourceOperands: ["dn"],
        destOperands: ["dn"]
      },
      {
        sizes: ["b", ""],
        sourceOperands: ["dn"],
        destOperands: ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"]
      },
      {
        sizes: ["l", ""],
        sourceOperands: ["imm8"],
        destOperands: ["dn"]
      },
      {
        sizes: ["b", ""],
        sourceOperands: ["imm8"],
        destOperands: ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"]
      }
    ]
  },
  // Bit manipulation instructions - BCHG, BCLR, BSET (no PC-relative addressing)
  {
    instructions: ["bchg", "bclr", "bset"],
    variants: [
      {
        sizes: ["l", ""],
        sourceOperands: ["dn"],
        destOperands: ["dn"]
      },
      {
        sizes: ["b", ""],
        sourceOperands: ["dn"],
        destOperands: ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      {
        sizes: ["l", ""],
        sourceOperands: ["imm8"],
        destOperands: ["dn"]
      },
      {
        sizes: ["b", ""],
        sourceOperands: ["imm8"],
        destOperands: ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // Set according to condition (Scc) instructions
  {
    instructions: ["st", "sf", "shi", "sls", "scc", "scs", "sne", "seq", "svc", "svs", "spl", "smi", "sge", "slt", "sgt", "sle", "shs", "slo"],
    variants: [
      {
        sizes: ["b", ""],
        sourceOperands: [],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // Branch instructions
  {
    instructions: ["bra", "bsr", "bhi", "bls", "bcc", "bcs", "bne", "beq", "bvc", "bvs", "bpl", "bmi", "bge", "blt", "bgt", "ble", "bhs", "blo"],
    variants: [
      {
        sizes: ["s", "w", ""],
        sourceOperands: ["label"],
        destOperands: []
      }
    ]
  },
  // DBcc instructions
  {
    instructions: ["dbt", "dbf", "dbhi", "dbls", "dbcc", "dbcs", "dbne", "dbeq", "dbvc", "dbvs", "dbpl", "dbmi", "dbge", "dblt", "dbgt", "dble", "dbhs", "dblo"],
    variants: [
      {
        sizes: ["w", ""],
        sourceOperands: ["dn"],
        destOperands: ["label"]
      }
    ]
  },
  // MOVEP
  {
    instructions: ["movep"],
    variants: [
      {
        sizes: ["w", "l"],
        sourceOperands: ["d(an)"],
        destOperands: ["dn"]
      },
      {
        sizes: ["w", "l"],
        sourceOperands: ["dn"],
        destOperands: ["d(an)"]
      }
    ]
  },
  // MOVEA
  {
    instructions: ["movea"],
    variants: [
      {
        sizes: ["w", "l"],
        sourceOperands: ["dn", "an", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["an"]
      }
    ]
  },
  // MOVE
  {
    instructions: ["move"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "imm", "d(pc)", "d(pc,ix)"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      // // TODO: This includes "an"???
      // https://github.com/prb28/m68k-instructions-documentation/blob/master/instructions/move.md
      {
        sizes: ["w", "l"],
        sourceOperands: ["an"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      {
        sizes: ["w"],
        sourceOperands: ["sr"],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      {
        sizes: ["w"],
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["ccr"]
      },
      {
        sizes: ["w"],
        sourceOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)", "imm"],
        destOperands: ["sr"]
      },
      // MOVE USP
      {
        sizes: ["l", ""],
        sourceOperands: ["usp"],
        destOperands: ["an"]
      },
      {
        sizes: ["l", ""],
        sourceOperands: ["an"],
        destOperands: ["usp"]
      }
    ]
  },
  // Simple memory/register operations (negx, clr, neg, not)
  {
    instructions: ["negx", "clr", "neg", "not"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: [],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // TAS instruction (byte only)
  {
    instructions: ["tas"],
    variants: [
      {
        sizes: ["b", ""],
        sourceOperands: [],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // Register-only operations
  {
    instructions: ["ext"],
    variants: [
      {
        sizes: ["w", "l"],
        sourceOperands: [],
        destOperands: ["dn"]
      }
    ]
  },
  // SWAP instruction (no size suffix)
  {
    instructions: ["swap"],
    variants: [
      {
        sizes: ["w", ""],
        sourceOperands: [],
        destOperands: ["dn"]
      }
    ]
  },
  // NBCD
  {
    instructions: ["nbcd"],
    variants: [
      {
        sizes: ["b", ""],
        sourceOperands: [],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // PEA
  {
    instructions: ["pea"],
    variants: [
      {
        sizes: ["l", ""],
        sourceOperands: ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
        destOperands: []
      }
    ]
  },
  // No operand instructions
  {
    instructions: ["illegal", "reset", "nop", "rte", "rts", "trapv", "rtr"],
    variants: [
      {
        sizes: [""],
        sourceOperands: [],
        destOperands: []
      }
    ]
  },
  // TST
  {
    instructions: ["tst"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: [],
        destOperands: ["dn", "(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  },
  // TRAP
  {
    instructions: ["trap"],
    variants: [
      {
        sizes: [""],
        sourceOperands: ["imm4"],
        destOperands: []
      }
    ]
  },
  // LINK
  {
    instructions: ["link"],
    variants: [
      {
        sizes: ["w", ""],
        sourceOperands: ["an"],
        destOperands: ["imm16s"]
      }
    ]
  },
  // UNLK
  {
    instructions: ["unlk"],
    variants: [
      {
        sizes: [""],
        sourceOperands: [],
        destOperands: ["an"]
      }
    ]
  },
  // STOP
  {
    instructions: ["stop"],
    variants: [
      {
        sizes: [""],
        sourceOperands: ["imm16"],
        destOperands: []
      }
    ]
  },
  // Jump instructions
  {
    instructions: ["jsr", "jmp"],
    variants: [
      {
        sizes: [""],
        sourceOperands: ["(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
        destOperands: []
      }
    ]
  },
  // MOVEM
  {
    instructions: ["movem"],
    variants: [
      {
        sizes: ["w", "l"],
        sourceOperands: ["register_list"],
        destOperands: ["(an)", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      },
      {
        sizes: ["w", "l"],
        sourceOperands: ["(an)", "(an)+", "d(an)", "d(an,ix)", "abs.w", "abs.l", "d(pc)", "d(pc,ix)"],
        destOperands: ["register_list"]
      }
    ]
  },
  // LEA
  {
    instructions: ["lea"],
    variants: [
      {
        sizes: ["l", ""], // verified
        sourceOperands: controlAddressingModes, // verified
        destOperands: ["an"] // verified
      }
    ]
  },
  // CHK
  {
    instructions: ["chk"],
    variants: [
      {
        sizes: ["w", ""], // verified
        sourceOperands: dataAddressingModes16, // verified
        destOperands: ["dn"] // verified
      }
    ]
  },
  // Quick operations
  {
    instructions: ["addq", "subq"],
    variants: [
      {
        sizes: ["b", "w", "l"], // verified
        sourceOperands: ["imm3"], // verified
        destOperands: [ // verified
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
        sourceOperands: ["imm3"],
        destOperands: ["an"]
      },
    ]
  },
  // MOVEQ
  {
    instructions: ["moveq"],
    variants: [
      {
        sizes: ["l", ""], // verified
        sourceOperands: ["imm8s"], // verified
        destOperands: ["dn"] // verified
      }
    ]
  },
  // Division operations
  {
    instructions: ["divu", "divs"],
    variants: [
      {
        sizes: ["w", ""], // verified
        sourceOperands: dataAddressingModes16, // verified
        destOperands: ["dn"] // verified
      }
    ]
  },
  // Binary-coded decimal operations
  {
    instructions: ["sbcd", "abcd"],
    variants: [
      {
        sizes: ["b", ""], // verified
        sourceOperands: ["dn"], // verified
        destOperands: ["dn"] // verified
      },
      {
        sizes: ["b", ""], // verified
        sourceOperands: ["-(an)"], // verified
        destOperands: ["-(an)"] // verified
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
        sizes: ["b", "w", "l"], // verified
        sourceOperands: dataAddressingModes16.except("imm16"), // verified
        destOperands: ["dn"] // verified
      },
      {
        sizes: ["b", "w", "l"], // verified
        sourceOperands: ["dn"], // verified
        destOperands: [ // verified
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
        sourceOperands: [ // verified
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
        destOperands: ["dn"] // verified
      },
      {
        sizes: ["w", "l"], // verified
        sourceOperands: ["an"], // verified
        destOperands: ["dn"] // verified
      },
      {
        sizes: ["b", "w", "l"], // verified
        sourceOperands: ["dn"], // verified
        destOperands: [ // verified
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
        sourceOperands: ["dn"], // verified
        destOperands: ["dn"] // verified
      },
      {
        sizes: ["b", "w", "l"], // verified
        sourceOperands: ["-(an)"], // verified
        destOperands: ["-(an)"] // verified
      }
    ]
  },
  // SUBA
  {
    instructions: ["suba"],
    variants: [
      {
        sizes: ["w", "l"], // verified
        sourceOperands: all32, // verified
        destOperands: ["an"] // verified
      }
    ]
  },
  // EOR
  {
    instructions: ["eor"],
    variants: [
      {
        sizes: ["b", "w", "l"], // verified
        sourceOperands: ["dn"], // verified
        // `imm` is NOT supported but since `eor` will be auto-fixed to `eori`
        // it is supported "in practice".
        // TODO: Add imm and make sure I am not missing anything.
        destOperands: dataAlterableAddressingModes32, // verified
      }
    ]
  },
  // CMPM
  {
    instructions: ["cmpm"],
    variants: [
      {
        sizes: ["b", "w", "l"], // verified
        sourceOperands: ["(an)+"], // verified
        destOperands: ["(an)+"] // verified
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
        sourceOperands: [ // TODO: Double-check this.
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
        destOperands: ["dn"]
      },
      {
        sizes: ["w", "l"],
        sourceOperands: [ "an"],
        destOperands: ["dn"]
      }
    ]
  },
  // CMPA
  {
    instructions: ["cmpa"],
    variants: [
      {
        sizes: ["w", "l"], // verified
        sourceOperands: all32, // verified
        destOperands: ["an"] // verified
      }
    ]
  },
  // Multiplication operations
  {
    instructions: ["mulu", "muls"],
    variants: [
      {
        sizes: ["w", ""], // verified
        sourceOperands: dataAddressingModes16, // verified,
        destOperands: ["dn"] // verified
      }
    ]
  },
  // EXG
  {
    instructions: ["exg"],
    variants: [
      {
        sizes: ["l", ""], // verified
        sourceOperands: ["dn", "an"], // verified
        destOperands: ["dn", "an"] // verified
      }
    ]
  },
  // ADDA
  {
    instructions: ["adda"],
    variants: [
      {
        sizes: ["w", "l"], // verified
        sourceOperands: all32, // verified,
        destOperands: ["an"] // verified
      }
    ]
  },
  // Shift/Rotate operations
  {
    instructions: ["asl", "asr", "lsl", "lsr", "roxl", "roxr", "rol", "ror"],
    variants: [
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["dn", "imm3"],
        destOperands: ["dn"]
      },
      {
        sizes: ["w", ""],
        sourceOperands: [],
        destOperands: ["(an)", "(an)+", "-(an)", "d(an)", "d(an,ix)", "abs.w", "abs.l"]
      }
    ]
  }
];