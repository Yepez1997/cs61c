#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

//sign extends a bitfield with given size
/* You may find implementing this ion helpful */
unsigned getBit(int x, int n) {
    return (x >> n) & 1;

}
void setBit(int *x, int n, int v) {
    *x &= ~(1 << n);
    *x |= (v << n);
}
void setBitByte(Byte *x, int n, int v) {
    *x &= ~(1 << n);
    *x |= (v << n);
}

/* Remember that the offsets should return the offset in BYTES */

int get_branch_offset(Instruction instruction) {
    int offset = 0b00000000000000000000000000000000;
    int i;
    for (i = 1; i < 5; i++) {
        setBit(&offset, i - 1, getBit(instruction.sbtype.imm5, i));
    }
    for (i = 0; i < 6; i++) {
        setBit(&offset, i + 4, getBit(instruction.sbtype.imm7, i));
    }
    setBit(&offset, 10, getBit(instruction.sbtype.imm5, 0));
    setBit(&offset, 11, getBit(instruction.sbtype.imm7, 6));
    offset <<= 1;
    for (i = 12; i < 32; i++) {
        setBit(&offset, i, getBit(offset, 12));
    }
    return offset;
}

int get_jump_offset(Instruction instruction) {
    int offset = 0b00000000000000000000000000000000;
    int i;
    for (i = 9; i < 19; i++) {
        setBit(&offset, i - 9, getBit(instruction.ujtype.imm, i));
    }
    setBit(&offset, 10, getBit(instruction.ujtype.imm, 8));
    for (i = 0; i < 8; i++) {
        setBit(&offset, i + 11, getBit(instruction.ujtype.imm, i));
    }
    setBit(&offset, 19, getBit(instruction.ujtype.imm, 19));
    offset <<= 1;
    for (i = 21; i < 32; i++) {
        setBit(&offset, i, getBit(offset,20));
    }
    return offset;
}

int get_store_offset(Instruction instruction) {
    int offset = 0b00000000000000000000000000000000;
    int i;
    for (i = 0; i < 5; i++) {
        setBit(&offset, i, getBit(instruction.stype.imm5, i));
    }
    for (i = 5; i < 12; i++) {
        setBit(&offset, i, getBit(instruction.stype.imm7, i - 5));
    }
    for (i = 12; i < 32; i++) {
        setBit(&offset, i, getBit(offset, 11));
    }
    return offset;
}

void handle_invalid_instruction(Instruction instruction) {
    printf("Invalid Instruction: 0x%08x\n", instruction.bits); 
}

void handle_invalid_read(Address address) {
    printf("Bad Read. Address: 0x%08x\n", address);
    exit(-1);
}

void handle_invalid_write(Address address) {
    printf("Bad Write. Address: 0x%08x\n", address);
    exit(-1);
}

