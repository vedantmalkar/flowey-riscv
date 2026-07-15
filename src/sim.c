#include <stdlib.h>
#include "memory.h"

int main(){
    struct CPU *cpu = malloc(sizeof(struct CPU));
    cpu_init(cpu);

    /* TODO */
    
    free(cpu);
    return 0;
}
