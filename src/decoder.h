#ifndef DECODER_H
#define DECODER_H

#include "memory.h"

enum Type{
    R_Type,
    I_Type,
    S_Type,
    B_Type,
    U_Type,
    J_Type
};

struct INST{
    uint32_t opcode;
    uint32_t rd;
    uint32_t funct3;
    uint32_t rs1;
    uint32_t rs2;
    uint32_t funct7;
    int32_t imm;
    enum Type type;
};

void decode(uint32_t inst, struct INST *current_instruction);

#endif
