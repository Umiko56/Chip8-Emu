#include "cpu.hpp"

Cpu::Cpu() : instruction_pointer(0), index_register(0), stack_pointer(0)
{
    for (int x = 0; x < 16; x++)
    {
        general_registers[x] = 0;
    }
    for (int x = 0; x < 4069; x++)
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
    instruction_pointer += 2;

    // Unpack the instruction
    uint8_t nibbles[4];
    nibbles[0] = (inst & 0xf000) >> 12;
    nibbles[1] = (inst & 0x0f00) >> 8;
    nibbles[2] = (inst & 0x00f0) >> 4;
    nibbles[3] = (inst & 0x000f);

    switch (nibbles[0])
    {
    case 0x0:
        switch (nibbles[2])
        {
        case 0xE:
            switch (nibbles[3])
            {

            // CLS
            case 0x0:
                break;

            // RET
            case 0xE:
                break;

            // Unknown
            default:

                break;
            }

        default:
            // SYS addr
            break;
        }
        break;
    //JP addr
    case 0x1:
        instruction_pointer = inst & 0x0fff;
        break;

    //CALL addr
    case 0x2:
        break;

    //SE Vx, byte
    case 0x3:
        if (nibbles[1] == (inst & 0xff))
        {
            instruction_pointer += 2;
        }
        break;

    //SNE Vx, byte
    case 0x4:
        if (nibbles[1] != (inst & 0xff))
        {
            instruction_pointer += 2;
        }
        break;

    //SE Vx, Vy
    case 0x5:
        switch (nibbles[4])
        {
        case 0x0:
            if (nibbles[1] != nibbles[2])
            {
                instruction_pointer += 2;
            }
            break;
        default:
            break;
        }
        break;

    //LD Vx, byte
    case 0x6:
        switch (nibbles[3])
        {
        //LD Vx, byte
        case 0:
            general_registers[nibbles[1]] = general_registers[nibbles[2]];

        //Unknown
        default:
            break;
        }
        break;
    case 0x7:
        break;
    default:
        break;
    }
}