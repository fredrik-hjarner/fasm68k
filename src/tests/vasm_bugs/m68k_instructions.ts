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

const dataAlterableAddressingModes32 = [
  "dn",       "abs.w",
  /*"an",*/   "abs.l",
  "(an)",     //"imm32",
  "(an)+",
  "-(an)",
  "d(an)",    //"d(pc)",
  "d(an,ix)", //"d(pc,ix)"
] satisfies OperandType[];

export const data: InstructionSet = [
  // OR, AND ///////////////////////////////////////////////////////////////////
  {
    instructions: ["or", "and"],
    variants: [
      // or/and -> ori/andi
      {
        sizes: ["b"],
        sourceOperands: ["imm8"],
        destOperands: ["dn"]
      },
      // or/and -> ori/andi
      {
        sizes: ["w", "l"],
        sourceOperands: ["imm"],
        destOperands: ["dn"]
      },
    ]
  },
  // SUB, ADD //////////////////////////////////////////////////////////////////
  {
    instructions: ["sub", "add"],
    variants: [
      // sub/add -> subi/addi
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["imm"],
        destOperands: ["dn"]
      },
      // sub/add -> suba/adda
      {
        sizes: ["w", "l"],
        sourceOperands: ["imm"],
        destOperands: ["an"]
      },
    ]
  },
  // EOR ////////////////////////////////////////////////////////////////////////
  {
    instructions: ["eor"],
    variants: [
      // eor -> eori
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["imm"],
        destOperands: dataAlterableAddressingModes32,
      },
    ]
  },
  // CMP ///////////////////////////////////////////////////////////////////////
  {
    instructions: ["cmp"],
    variants: [
      // cmp -> cmpi
      {
        sizes: ["b", "w", "l"],
        sourceOperands: ["imm"],
        destOperands: ["dn"]
      },
      // cmp -> cmpa
      {
        sizes: ["w", "l"],
        sourceOperands: ["imm"],
        destOperands: ["an"]
      },
    ]
  },
];