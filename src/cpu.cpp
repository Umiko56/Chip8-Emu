#include "cpu.hpp"
#include "emulator.hpp"

Cpu::Cpu() : instruction_pointer(0x200), index_register(0), stack_pointer(0)
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
    bool value;
    int j;
    int x;
    int y;
    uint8_t nibbles[4];
    instruction_pointer += 2;

    // Unpack the instruction
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
            general_registers[nibbles[1]] = inst & 0xff;

        //Unknown
        default:
            break;
        }
        break;

    //ADD Vx, byte
    case 0x7:
        general_registers[nibbles[1]] += inst & 0xff;
        break;

    case 0x8:
        switch (nibbles[3])
        {

        // LD Vx, Vy
        case 0x0:

            break;

        //OR Vx, Vy
        case 0x1:

            break;

        //AND Vx, Vy
        case 0x2:
            break;

        //XOR Vx, Vy
        case 0x3:
            break;

        //ADD Vx, Vy
        case 0x4:

            break;

        //SUB Vx, Vy
        case 0x5:
            break;

        //SHR Vx {, Vy}
        case 0x6:
            break;

        //SUBN Vx, Vy
        case 0x7:
            break;

        //SHL Vx {, Vy}
        case 0xE:
            break;

        //Unknown
        default:
            break;
        }

        break;
    case 0x9:
        switch (nibbles[3])
        {

        //SNE Vx, Vy
        case 0x0:
            break;

        //Unknown
        default:
            break;
        }
        break;

    //LD I, addr
    case 0xa:
        index_register = inst & 0x0fff;
        break;

    //JP V0, addr
    case 0xb:
        instruction_pointer += general_registers[1] + (inst & 0xfff);
        break;

    //RND Vx, byte
    case 0xc:

        general_registers[nibbles[1]] = (rand() & 0xff) & (inst & 0xff);
        break;

    //DRW Vx, Vy, nibble
    case 0xd:
        x = nibbles[1];
        y = nibbles[2];
        for (j = 0; j < nibbles[3]; j++)
        {
            value = emulator->screen.readpx(x++, y);
            emulator->screen.drawpx(general_registers[nibbles[1]], general_registers[nibbles[2]], !value);
        }
        break;

    case 0xe:
        switch (nibbles[2])
        {
        case 0x9:
            switch (nibbles[3])
            {
            case 0xe:
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        break;
    case 0xf:
        switch (nibbles[2])
        {
        case 0x0:
            break;
        case 0x1:
            switch (nibbles[3])
            {
            case 0x5:
                delay_timer = general_registers[nibbles[1]];
                break;

            //LD ST, Vx
            case 0x8:
                sound_timer = general_registers[nibbles[1]];
                break;

            //ADD I, Vx
            case 0xE:
                index_register += general_registers[nibbles[1]];
                break;
            default:
                break;
            }
            break;
        case 0x2:
            break;
        case 0x3:
            break;
        case 0x5:
            break;
        case 0x6:
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    //std::cout << "IP: 0x" << std::hex << instruction_pointer << std::dec << "\n";
}