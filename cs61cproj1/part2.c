#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"
#include "riscv.h"

void execute_rtype(Instruction, Processor *);
void execute_itype_except_load(Instruction, Processor *);
void execute_branch(Instruction, Processor *);
void execute_jal(Instruction, Processor *);
void execute_load(Instruction, Processor *, Byte *);
void execute_store(Instruction, Processor *, Byte *);
void execute_ecall(Processor *, Byte *);
void execute_lui(Instruction, Processor *);
unsigned getBit(int, int);
void setBit(int *, int, int);
void execute_instruction(Instruction instruction,Processor *processor, Byte *memory) {
    /*COMPLETED, JUST FINISH THE OTHER FUNCTIONS*/
    switch(instruction.opcode) { // What do we switch on?
            //r-type
        case(0x33): {
            execute_rtype(instruction, processor);
            processor->PC += 4;
            break;
        }
            //i-type (load)
        case(3): {
            execute_load(instruction, processor, memory);
            processor->PC += 4;
            break;
        }
            //i-type (not load)
        case(0x13): {
            execute_itype_except_load(instruction, processor);
            processor->PC += 4;
            break;
        }
            //ecall
        case (0x73):{
            execute_ecall(processor, memory);
            break;
        }
            //s-type
        case (0x23): {
            execute_store(instruction, processor, memory);
            processor->PC += 4;
            break;
        }
            //sb-type
        case (0x63): {
            execute_branch(instruction, processor);
            break;
        }
            //u-type (lui) lol
        case (0x37): {
            execute_lui(instruction, processor);
            processor->PC += 4;
            break;
        }
            //uj-type (jal)
        case (0x6f): {
            execute_jal(instruction, processor);
            break;
        }
        default: {// undefined opcode
            handle_invalid_instruction(instruction);
            processor->PC += 4;
            exit(-1);
            break;
        }
    }
    processor->R[0] = 0;
}

void execute_rtype(Instruction instruction, Processor *processor) {
    int func7 = instruction.rtype.funct7;

    switch(instruction.rtype.funct3) {
        case(0): {
            if (func7 == 0) {
                processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] + processor->R[instruction.rtype.rs2];
            }
            else if (func7 == 1) {
                Double product = (Double) processor->R[instruction.rtype.rs1] * (Double) processor->R[instruction.rtype.rs2];
                int i;
                for (i = 32; i < 64; i++) {
                    product &= ~(1 << i);
                    product |= (0 << i);
                }
                processor->R[instruction.rtype.rd] = (Register) product;
            }
            else if (func7 == 2) {
                processor->R[instruction.rtype.rd] = (int) processor->R[instruction.rtype.rs1] - (int) processor->R[instruction.rtype.rs2];
            }
            break;
        }
        case(1): {
            if (func7 == 0) {
                processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] << processor->R[instruction.rtype.rs2];
            }
            if (func7 == 1) {
                Double rs1 = (Double) processor->R[instruction.rtype.rs1], rs2 = (Double) processor->R[instruction.rtype.rs2];
                processor->R[instruction.rtype.rd] = (Register) ((rs1 * rs2) >> 32);
            }

            break;
        }
        case(2): {
            if (func7 == 0) {
                processor->R[instruction.rtype.rd] = ((int)processor->R[instruction.rtype.rs1] < (int)processor->R[instruction.rtype.rs2]) ? 1 : 0;
            }
            break;
        }
        case(4): {
            if (func7 == 0) {
                processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] ^ processor->R[instruction.rtype.rs2];
            }
            else if (func7 == 1) {
                processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] / processor->R[instruction.rtype.rs2];
            }
            break;
        }
        case(5): {
            if (func7 == 0) {
                processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] >> processor->R[instruction.rtype.rs2];
            }
            else if (func7 == 0x20) {
                int result = processor->R[instruction.rtype.rs1] >> processor->R[instruction.rtype.rs2], i;
                for (i = 31 - processor->R[instruction.rtype.rs2]; i < 32; i++) {
                    setBit(&result, i, getBit(result, 31 - processor->R[instruction.rtype.rs2]));
                }
                processor->R[instruction.rtype.rd] = (Register) result;
            }
            break;
        }
        case(6): {
            if (func7 == 0) {
                processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] | processor->R[instruction.rtype.rs2];
            }
            else if (func7 == 1) {
                processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] % processor->R[instruction.rtype.rs2];
            }
            break;
        }
        case(7): {
            if (func7 == 0) {
                processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] & processor->R[instruction.rtype.rs2];
            }
            break;
        }
        default:
            handle_invalid_instruction(instruction);
            exit(-1);
            break;
    }
}

void execute_itype_except_load(Instruction instruction, Processor *processor) {
    int imm = instruction.itype.imm, i;
    for (i = 11; i < 32; i++) {
        setBit(&imm, i, getBit(imm, 11));
    }
    switch(instruction.itype.funct3) {
        case(0): {
            processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] + imm;
            break;
        }
        case(1): {
            processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] << imm;
            break;
        }
        case(2): {
            processor->R[instruction.itype.rd] = ((int)processor->R[instruction.itype.rs1] < imm) ? 1 : 0;
            break;
        }
        case(4): {
            processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] ^ imm;
            break;
        }
        case(5): {
            if (getBit(imm, 10) == 0) {
                processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] >> imm;
            }
            else {
                setBit(&imm, 10, 0);
                int result = processor->R[instruction.rtype.rs1] >> imm, i;
                for (i = 31 - imm; i < 32; i++) {
                    setBit(&result, i, getBit(result, 31 - imm));
                }
                processor->R[instruction.itype.rd] = result;
            }
            break;
        }
        case(6): {
            processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] | imm;
            break;
        }
        case(7): {
            processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] & imm;
            break;
        }
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void execute_ecall(Processor *p, Byte *memory) {
    switch(p->R[10]) { // What do we switch on?
        case(1): {
            printf("%d", p->R[11]);
            p->PC += 4;
            //exit(0);
            break;
        }
        case(10): {
            printf("exiting the simulator\n");
            exit(0);
            break;
        }
        default: // undefined ecall
            printf("Illegal ecall number %d\n", -1); // What stores the ecall arg?
            exit(-1);
            break;
    }
}

void execute_branch(Instruction instruction, Processor *processor) {
    /* Remember that the immediate portion of branches
       is counting half-words, so make sure to account for that. */
    switch(instruction.sbtype.funct3) {
        case(0): {
            if (processor->R[instruction.sbtype.rs1] == processor->R[instruction.sbtype.rs2]) {
                processor->PC += get_branch_offset(instruction);
            }
            else  processor->PC += 4;
            break;
        }
        case(1): {
            if (processor->R[instruction.sbtype.rs1] != processor->R[instruction.sbtype.rs2]) {
                processor->PC += get_branch_offset(instruction);
            }
            else  processor->PC += 4;
            break;
        }
        default:
            handle_invalid_instruction(instruction);
            exit(-1);
            break;
    }
}

// grab stuff from the load store
// reg[rs1]
//

void execute_load(Instruction instruction, Processor *processor, Byte *memory) {
    int imm = instruction.itype.imm, i;
    for (i = 12; i < 32; i++) {
        setBit(&imm, i, getBit(imm, 11));
    }
    switch(instruction.itype.funct3) {
        case(0): {
            processor->R[instruction.itype.rd] = load(memory, processor->R[instruction.itype.rs1] + imm, LENGTH_BYTE, 0);
            break;
        }
        case(1): {
            processor->R[instruction.itype.rd] = load(memory, processor->R[instruction.itype.rs1] + imm, LENGTH_HALF_WORD, 0);
            break;
        }
        case(2): {
            processor->R[instruction.itype.rd] = load(memory, processor->R[instruction.itype.rs1] + imm, LENGTH_WORD, 0);
            break;
        }
        default:
            handle_invalid_instruction(instruction);
            exit(-1);
            break;
    }
}

// comments * delete later
// check_align should be 0 however it is a boolean for some case
// no booleans in c so use int 0 or in 1 where int 1 is true 0 is the latter
// *memory takes a huge list of Byte.load , tries to fetch data for some
// addresses, and location of bytes for the address
// KEY -> combining memory and and address will give us a desired result
// reg[rs2]

void execute_store(Instruction instruction, Processor *processor, Byte *memory /*array*/) {
    switch(instruction.stype.funct3) {
        case(0): {
            store(memory, processor->R[instruction.stype.rs1] + get_store_offset(instruction), LENGTH_BYTE, processor->R[instruction.stype.rs2], 0);
            break;
        }
        case(1): {
            store(memory, processor->R[instruction.stype.rs1] + get_store_offset(instruction), LENGTH_HALF_WORD, processor->R[instruction.stype.rs2], 0);
            break;
        }
        case(2): {
            store(memory, processor->R[instruction.stype.rs1] + get_store_offset(instruction), LENGTH_WORD, processor->R[instruction.stype.rs2], 0);
            break;
        }
        default:
            handle_invalid_instruction(instruction);
            exit(-1);
            break;
    }
}

void execute_jal(Instruction instruction, Processor *processor) {
    processor->R[instruction.ujtype.rd] = processor->PC + 4;
    processor->PC += get_jump_offset(instruction);
}

void execute_lui(Instruction instruction, Processor *processor) {
    processor->R[instruction.utype.rd] = instruction.utype.imm << 12;
}

/* Checks that the address is aligned correctly */
int check(Address address,Alignment alignment) {
    if (address > 0 && address < MEMORY_SPACE) {
        if (alignment == LENGTH_BYTE){
            return 1;
        }
        else if (alignment == LENGTH_HALF_WORD) {
            return address % 2 == 0;
        }
        else if (alignment == LENGTH_WORD) {
            return address % 4 == 0;
        }
    }
    return 0;
}

void store(Byte *memory, Address address, Alignment alignment, Word value, int check_align) {
    if ((check_align && !check(address,alignment)) || (address >= MEMORY_SPACE)) {
        handle_invalid_write(address);
    }
    int i,j;
    for (i = 0; i < (int) alignment; i++) {
        for (j = 0; j < 8; j++) {
            setBitByte(memory + address + i, j, getBit(value, j + 8*i));
        }
    }
}


// Recall that alignment is the size of our byte
// Whether it is it a byte a half word or a word
// We want to access a specific byte to load
// maybe in load we want to check the size before loading it
// Address serves as our starter address
// Check_align will always be 0 when passed in
// grab enough bytes to return the load
// should modify to store a load byte load word and load half word
// given that we know
// increase bytes << by x amount to get the next pointer
// alignment is our size load
// mul bytes to get next pointer
// think of memory as an array og bytes
// use address passed into load to index into memory and read a byte
// load program prop
// format instruction in heching ty
// find something that refers to all bytes

Word load(Byte *memory, Address address, Alignment alignment, int check_align) {
    if ((check_align && !check(address,alignment)) || (address >= MEMORY_SPACE)) {
        handle_invalid_read(address);
    }
    int data = 0, i; // initialize our return value to zero
   // set up a loop to go through everything
   //we want to set up a while loop to traverse through everything
   //switch on alignment to deal with half, byte, and full words

   switch(alignment){
       //Byte i.e 8 bits
       case(LENGTH_BYTE): {

           data = (int) memory[address];
            for (i = 7; i < 32; i++) {
                setBit(&data, i, getBit(data, 7));
            }
           return (Word) data;
        }
       // Half Word i.e 16 bits
       case(LENGTH_HALF_WORD): {
           // we want to keep adding to
           for (i = 0; i < 8; i++) {
                setBit(&data, i, getBit((int) memory[address], i));
            }
           for (i = 8; i < 16; i++) {
               setBit(&data, i, getBit((int) memory[address + 1], i - 8));
           }
           for (i = 16; i < 32; i++) {
               setBit(&data, i, getBit((int) data, 15));
           }

           return (Word) data;
            // piece all 2 Bytes

       }
       //Word i.e 32 bits
       case(LENGTH_WORD): {
           for (i = 0; i < 4; i++) {
               int j;
               for (j = 0; j < 8; j++) {
                   setBit(&data, j + 8*i, getBit((int) memory[address + i], j));
                  // printf("* %unsignedg\n", setBit(&data, j + 8*i, getBit((int) memory[address + i], j)));
               }
           }
           return (Word) data;
       }
   }
    return (Word) data;
}


