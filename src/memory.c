#include "memory.h"

uint32_t get_current_address(struct CPU *cpu){
    return cpu->pc;
}

void increment_pc(struct CPU *cpu){
    cpu->pc+= 4;    /* next instruction */
}

uint32_t get_reg(struct CPU *cpu, uint32_t num){
    return cpu->regs[num];
}

void cpu_init(struct CPU *cpu){
    cpu->pc = BASE;

    for(int i = 0; i < 32; i++){
        cpu->regs[i] = 0;
    }
}

uint8_t read_byte(struct CPU *cpu, uint32_t addr){
    uint32_t index = addr - BASE;

    if(index >= 0 && index < MEM_SIZE){
        return cpu->mem[index];
    }
    
    printf("\n HALTING - unable to fetch address, outside capacity");
    return 0;
}

uint32_t read_word(struct CPU *cpu, uint32_t addr){
    uint32_t byte_0 = read_byte(cpu, addr);
    uint32_t byte_1 = read_byte(cpu, addr + 1);
    uint32_t byte_2 = read_byte(cpu, addr + 2);
    uint32_t byte_3 = read_byte(cpu, addr + 3);
    
    return (byte_0) | (byte_1 << 8) | (byte_2 << 16) | (byte_3 << 24);  /* RV32I instructions are 32-bit wide & in a little-endian configuration*/
}

void write_byte(struct CPU *cpu, uint32_t addr, uint8_t data){
    uint32_t index = addr - BASE;

    if(index >= 0 && index < MEM_SIZE){
        cpu->mem[index] = data;
    }
    
    printf("\n HALTING - unable to write to address, outside capacity");
}

void write_word(struct CPU *cpu, uint32_t addr, uint32_t inst){
    uint8_t byte_0 = (inst & 0xFF);
    uint8_t byte_1 = (inst >> 8) & 0xFF;
    uint8_t byte_2 = (inst >> 16) & 0xFF; 
    uint8_t byte_3 = (inst >> 24) & 0xFF;

    uint32_t index = addr - BASE;
    cpu->mem[index] = byte_0;
    cpu->mem[index + 1] = byte_1;
    cpu->mem[index + 2] = byte_2;
    cpu->mem[index + 3] = byte_3;
}

void write_reg(struct CPU *cpu, uint32_t val, uint32_t reg){
    if(reg != 0){
        cpu->regs[reg] = val;
    }
}
