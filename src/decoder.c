#include "decoder.h"

uint32_t get_opcode(uint32_t inst){
    return inst & 0x7F;
}

uint32_t get_rd(uint32_t inst){
    return (inst >> 7) & 0x1F;
}

uint32_t get_fun3(uint32_t inst){
    return (inst >> 12) & 0x7;
}

uint32_t get_rs1(uint32_t inst){
    return (inst >> 15) & 0x1F;
}

uint32_t get_rs2(uint32_t inst){
    return (inst >> 20) & 0x1F;
}

uint32_t get_fun7(uint32_t inst){
    return (inst >> 25) & 0x7F;
}

void decoder(uint32_t inst, struct INST *current_instruction){
    current_instruction->opcode = get_opcode(inst);
    current_instruction->rd = get_rd(inst);
    current_instruction->funct3 = get_fun3(inst);
    current_instruction->rs1 = get_rs1(inst);
    current_instruction->rs2 = get_rs2(inst);
    current_instruction->funct7 = get_fun7(inst);

    switch (current_instruction->opcode){
    case 0x13:
        /* TODO - 
            immidiate(imm) values are supposed
            to be unsigned, hence masking wont
            work here, need to find a way
            to filter to correct instruction */
        break;

    default:
        break;
    }
}
