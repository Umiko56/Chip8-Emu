#include "cpu.hpp"

Cpu::Cpu() : instruction_pointer(0), index_register(0), stack_pointer(0)
{
    for (int x; x < 16; x++)
    {
        general_registers[x] = 0;
    }
    for (int x; x < 4069; x++)
    {
        ram[x] = rand();
    }
}

void Cpu::operator()()
{
    execute();
}

void Cpu::execute()
{
    uint16_t inst = (ram[instruction_pointer] << 8 | ram[instruction_pointer + 1]);
    instruction_pointer++;
    if (instruction_pointer > 4096)
    {
        std::err << "IP overflow";
        return;
    }

    // Unpack the instruction
    uint8_t nibbles[4];
    nibbles[0] = (uint8_t)(inst & 0xf000) >> 12;
    nibbles[1] = (uint8_t)(inst & 0x0f00) >> 8;
    nibbles[2] = (uint8_t)(inst & 0x00f0) >> 4;
    nibbles[3] = (uint8_t)(inst & 0x000f);

    switch (nibbles[0])
    {
    case 0x0:
        break;
    case 0x1:
        instruction_pointer = inst & 0x0fff;
        break;
    case 0x2:
        break;
    case 0x3:
        if (nibbles[1] == (inst & 0xff))
        {
            instruction_pointer++;
        }
        break;
    case 0x4:
        if (nibbles[1] != (inst & 0xff))
        {
            instruction_pointer++;
        }
        break;
    case 0x5:
        switch (nibbles[4])
        {
        case 0x0:
            if (nibbles[1] != nibbles[2])
            {
                instruction_pointer++;
            }
            break;
        default:
            std::cerr << "ERROR: INVALID INSTRUCTION: " << std::hex << instruction_pointer << ":" << inst << std::dec;
            break;
        }
        break;
    default:
        std::cerr << "ERROR: INVALID INSTRUCTION: " << std::hex << instruction_pointer << ":" << inst << std::dec;
    }
}