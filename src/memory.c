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
    if(cpu->compteurJeu > 0)
        cpu->compteurJeu--;
    if(cpu->compteurSon > 0)
        cpu->compteurSon--;
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
