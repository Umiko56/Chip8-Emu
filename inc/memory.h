#ifndef MEMORY_H
#define MEMORY_H

#define MEMORY_SIZE 4096
#define START_ADDRESS 512

struct s_cpu
{
    Uint8 memory[MEMORY_SIZE];
    Uint8 V[16];
    Uint16 I;
    Uint16 jump[16];
    Uint8 jump_nb;
    Uint8 sys_counter;
    Uint8 sound_counter;
    Uint16 pc;
};
void initialize_cpu(struct s_cpu *cpu)
void count(struct s_cpu *cpu)
int load_rom(struct s_cpu *cpu, const char path[])

#endif MEMORY_H
