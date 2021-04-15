#include <SDL2/SDL.h>
#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

void initialize_cpu(struct s_cpu *cpu)
{
    memset(cpu, 0, sizeof(*cpu));
    cpu->pc = START_ADDRESS;
}

void count(struct s_cpu *cpu)
{
    if(cpu->sys_counter > 0)
        cpu->sys_counter--;
    if(cpu->sound_counter > 0)
        cpu->sound_counter--;
}

int load_rom(struct s_cpu *cpu, const char path[])
{
    FILE *rom = fopen(path, "rb");
    if(!rom)
    {
        perror("Error fopen:");
        return EXIT_FAILURE;
    }
    fread(&cpu->memory[START_ADDRESS], sizeof(Uint8) * (MEMORY_SIZE - START_ADDRESS), 1, rom);
    fclose(rom);
    return EXIT_SUCCESS;
}
