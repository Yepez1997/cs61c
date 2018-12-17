#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"

void print_rtype(char *, Instruction);
void print_itype_except_load(char *, Instruction, int);
void print_load(char *, Instruction);
void print_store(char *, Instruction);
void print_branch(char *, Instruction);
void write_rtype(Instruction);
void write_itype_except_load(Instruction); 
void write_load(Instruction);
void write_store(Instruction);
void write_branch(Instruction);
void write_lui(Instruction);
void write_jal(Instruction);
void write_ecall(Instruction);
unsigned getBit(int, int);
void setBit(int *, int, int);
void setBitByte(Byte *, int, int);

/** decode_instruction switches between the type of instructions i.e itype,
*rtype, stype, etc through opcodes.
*@params instruction - refer to types.h for the structure of a Instruction
**/
void decode_instruction(Instruction instruction) {
    //switch on opcode
    //find a way to get opcode
    switch(instruction.opcode) {
        //r-type
        case (0x33): {
            write_rtype(instruction);
            break;
        }
        //i-type (load)
        case (3): {
            write_load(instruction);
            break;
        }
        //i-type (not load)
        case (0x13): {
            write_itype_except_load(instruction);
            break;
        }
         //ecall
        case (0x73):{
            write_ecall(instruction);
            break;
        }
        //s-type
        case (0x23): {
            write_store(instruction);
            break;
        }
        //sb-type
        case (0x63): {
            write_branch(instruction);
            break;
        }
        //u-type (lui)
        case (0x37): {
            write_lui(instruction);
            break;
        }
        //uj-type (jal)
        case (0x6f): {
            write_jal(instruction);
            break;
        }
        //undefined opcode
    	default: {
            handle_invalid_instruction(instruction);
            break;
        }
    }
}

/** write_rtype switches between the func in an r_type to get a more specific instruction
*@params - refer to types.h for the structure of a Instruction
**/
void write_rtype(Instruction instruction) {
    unsigned int func3 = instruction.rtype.funct3, func7 = instruction.rtype.funct7;
    char* name = "";
    if (func3 == 0) {
        if (func7 == 0) name = "add";
        else if (func7 == 1) name = "mul";
        else if (func7 == 0x20) name = "sub";
        else {
            handle_invalid_instruction(instruction);
            return;
        }
    }
    else if (func3 == 1) {
        if (func7 == 0) name = "sll";
        else if (func7 == 1) name = "mulh";
        else {
            handle_invalid_instruction(instruction);
            return;
        }
    }
    else if (func3 == 2) {
        if (func7 == 0) name = "slt";
        else {
            handle_invalid_instruction(instruction);
            return;
        }
    }
    else if (func3 == 4) {
        if (func7 == 0) name = "xor";
        else if (func7 == 1) name = "div";
        else {
            handle_invalid_instruction(instruction);
            return;
        }
    }
    else if (func3 == 5) {
        if (func7 == 0) name = "srl";
        else if (func7 == 0x20) name = "sra";
        else {
            handle_invalid_instruction(instruction);
            return;
        }
    }
    else if (func3 == 6) {
        if (func7 == 0) name = "or";
        else if (func7 == 1) name = "rem";
        else {
            handle_invalid_instruction(instruction);
            return;
        }
    }
    else if (func3 == 7) {
        if (func7 == 0) name = "and";
        else {
            handle_invalid_instruction(instruction);
            return;
        }
    }
    else {
        handle_invalid_instruction(instruction);
        return;
    }
    print_rtype(name, instruction);
}

/** write_itype switches between the func in an i_type to get a more specific instruction
*@params - refer to types.h for the structure of a Instruction
**/
void write_itype_except_load(Instruction instruction) {
    unsigned int func3 = instruction.itype.funct3;
    int imm = instruction.itype.imm;
    char* name = "";
    if (func3 == 0) name = "addi";
    else if (func3 == 1) name = "slli";
    else if (func3 == 2) name = "slti";
    else if (func3 == 4) name = "xori";
    else if (func3 == 5) {
        name = (getBit(imm, 10) == 1) ? "srai" : "srli";
        setBit(&imm, 10, 0);
        setBit(&imm, 9, 0);
    }
    else if (func3 == 6) name = "ori";
    else if (func3 == 7) name = "andi";
    else {
        handle_invalid_instruction(instruction);
        return;
    }
    int i;
    for (i = 12; i < 32; i++) {
        setBit(&imm, i, getBit(imm, 11));
    }
    print_itype_except_load(name, instruction, imm);
}

/** write_load switches between the func in an load(itype) to get a more specific instruction
*@params - refer to types.h for the structure of a Instruction
**/
void write_load(Instruction instruction) {
   char* name = "";
   unsigned int func3 = instruction.itype.funct3;
   if (func3 == 0b000) name = "lb";
   else if (func3 == 0b001) name = "lh";
   else if (func3 == 0b010) name = "lw";
   else {
       handle_invalid_instruction(instruction);
       return;
   }
   print_load(name, instruction);
}

/** write_store switches between the func in an store (stype) to get a more specific instruction
*@params - refer to types.h for the structure of a Instruction
**/
void write_store(Instruction instruction) {
    char *name = "";
    unsigned int func3 = instruction.stype.funct3;
    if (func3 == 0) name = "sb";
    else if (func3 == 1) name = "sh";
    else if (func3 == 2) name = "sw";
    else {
        handle_invalid_instruction(instruction);
        return;
    }
    print_store(name, instruction);
}

/** write_branch switches between the func in an sb_type to get a more specific instruction
*@params - refer to types.h for the structure of a Instruction
**/
void write_branch(Instruction instruction) {
    char *name = "";
    unsigned int func3 = instruction.sbtype.funct3;
    if (func3 == 0) name = "beq";
    else if (func3 == 1) name = "bne";
    else {
        handle_invalid_instruction(instruction);
        return;
    }
    print_branch(name, instruction);
}


/** write_lui switches between the func in an u_type to get a more specific instruction
*@params - refer to types.h for the structure of a Instruction
**/
void write_lui(Instruction instruction) {
  printf("lui\tx%d, %d\n",instruction.utype.rd, instruction.utype.imm);
}

/** write_rtype switches between the func in an r_type to get a more specific instruction
*@params - refer to types.h for the structure of a Instruction
**/
void write_jal(Instruction instruction) {
    printf("jal\tx%d, %d\n", instruction.ujtype.rd, get_jump_offset(instruction));
}

void write_ecall(Instruction instruction) {
     printf("ecall\n");
}

/**
*Prints rtype format for rtype, itype, load, store, branch and jal
*i.e we have the format as name, rs1 ,rs2 ... look at utils.h for
*respective types and format.
**/
void print_rtype(char *name, Instruction instruction) {
    printf("%s\tx%d, x%d, x%d\n", name, instruction.rtype.rd, instruction.rtype.rs1, instruction.rtype.rs2);
}

void print_itype_except_load(char *name, Instruction instruction, int imm) {
    printf("%s\tx%d, x%d, %d\n", name, instruction.itype.rd, instruction.itype.rs1, (signed int) imm);
}

void print_load(char *name, Instruction instruction) {
    int imm = instruction.itype.imm;
    int i;
    for (i = 12; i < 32; i++) {
        setBit(&imm, i, getBit(imm, 11));
    }
    printf("%s\tx%d, %d(x%d)\n", name, instruction.itype.rd, imm, instruction.itype.rs1);
}

void print_store(char *name, Instruction instruction) {
    printf("%s\tx%d, %d(x%d)\n", name, instruction.stype.rs2, get_store_offset(instruction), instruction.stype.rs1);
}

void print_branch(char *name, Instruction instruction) {
    printf("%s\tx%d, x%d, %d\n", name, instruction.sbtype.rs1, instruction.sbtype.rs2, get_branch_offset(instruction));
}


