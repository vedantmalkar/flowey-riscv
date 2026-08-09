#include "memory.h"
#include "decoder.h"
#include "execute.h"
#include "cpu.h"

int main(){
    struct CPU *cpu = calloc(1, sizeof(struct CPU));
    cpu_init(cpu);
    write_word(cpu, BASE + 0, 0x00500093);  /* addi x1, x0, 5 (x1 should be 5)*/
    write_word(cpu, BASE + 4, 0x00A00113);  /* addi x2, x0, 10 (x2 should be 10)*/
    write_word(cpu, BASE + 8, 0x002081B3);  /* add  x3, x1, x2 (x3 should be 15)*/
    write_word(cpu, BASE + 12, 0x00000000); /* halt */
    run_cpu(cpu);

    printf("x1=%u x2=%u x3=%u\n", get_reg(cpu, 1), get_reg(cpu, 2), get_reg(cpu, 3));
    free(cpu);
    return 0;
}
