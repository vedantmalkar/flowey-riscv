#include "memory.h"
#include "execute.h"

void run_cpu(struct CPU *cpu){
    cpu->running = 1;

    while(cpu->running){
        uint32_t instruction = read_word(cpu, cpu->pc);
        if(instruction == 0x00){
            cpu->running = 0;
            break;
        }

        execute(cpu, instruction);
        increment_pc(cpu);        
    }

}
