#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BASE 0x80000000
#define MEM_SIZE (4 * 1024 * 1024)  /* 4MB of memory */

struct CPU { 
    uint32_t regs[32];
    uint32_t pc;
    uint8_t mem[MEM_SIZE];
};

uint32_t get_current_address(struct CPU *cpu);
void increment_pc(struct CPU *cpu);
uint32_t get_reg(struct CPU *cpu, uint32_t num);
void cpu_init(struct CPU *cpu);
uint8_t read_byte(struct CPU *cpu, uint32_t addr);
uint32_t read_word(struct CPU *cpu, uint32_t addr);
void write_reg(struct CPU *cpu, uint32_t val, uint32_t reg);

#endif
