#pragma once

#define MEMORY_SIZE 4096
#define START_ADDRESS 512

#include <stdint.h>
#include <iostream>
#include <cstdlib>

class Cpu
{
public:
    Cpu(void);
    void operator()();
    void execute();

    uint8_t ram[0xffff];

private:
    uint16_t instruction_pointer;
    uint16_t index_register;
    uint8_t stack_pointer;
    uint8_t general_registers[16];
};
