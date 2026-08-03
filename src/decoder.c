#include "decoder.h"

int mcause; 

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

int32_t get_imm(uint32_t inst){
    return (int32_t)inst >> 20;
} 

void ill_inst(void){
    printf("illegal instruction\n");
    mcause = 2;
}

void decode(uint32_t inst, struct INST *current_instruction){
    current_instruction->opcode = get_opcode(inst);
    
    if(current_instruction->opcode == 0x33){            /* R-Type */
        current_instruction->rd = get_rd(inst);
        current_instruction->funct3 = get_fun3(inst);
        current_instruction->rs1 = get_rs1(inst);
        current_instruction->rs2 = get_rs2(inst);
        current_instruction->funct7 = get_fun7(inst);
        current_instruction->type = R_Type;
    } else if (current_instruction->opcode == 0x13){     /* I-Type */
        current_instruction->rd = get_rd(inst);
        current_instruction->funct3 = get_fun3(inst);
        current_instruction->rs1 = get_rs1(inst);
        current_instruction->imm = get_imm(inst);
        current_instruction->type = I_Type;
    } else{
        ill_inst();
    }    
}
