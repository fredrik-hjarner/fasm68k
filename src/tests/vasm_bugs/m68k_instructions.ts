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
        sourceOperands: ["imm8"], // verified
        destOperands: ["dn"] // verified
      },
      {
        sizes: ["w", "l"], // verified
        // `imm` is NOT supported but since `er/and` will be auto-fixed to
        // `ori/andi` it is supported "in practice".
        // TODO: I don't quite understand why the .w one accepts an imm32
        //       in both vasm and clownassembler??
        sourceOperands: ["imm"], // verified
        destOperands: ["dn"] // verified
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
        sourceOperands: ["imm"],
        destOperands: ["dn"] // verified
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
        sourceOperands: ["imm"],
        destOperands: ["an"]
      },
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
        sourceOperands: ["imm"], // verified
        destOperands: dataAlterableAddressingModes32, // verified
      },
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
        sourceOperands: ["imm"],
        destOperands: ["dn"]
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
        sourceOperands: ["imm"],
        destOperands: ["an"]
      },
    ]
  },
];