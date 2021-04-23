#pragma once
#include <stdint.h>

#define MEMORY_SIZE 4096
#define START_ADDRESS 512

struct s_cpu
{
    uint8_t memory[MEMORY_SIZE];
    uint8_t V[16];
    uint16_t I;
    uint16_t jump[16];
    uint8_t jump_nb;
    uint8_t sys_counter;
    uint8_t sound_counter;
    uint16_t pc;
};

void initialize_cpu(struct s_cpu *cpu);

void count(struct s_cpu *cpu);

int load_rom(struct s_cpu *cpu, const char path[]);

