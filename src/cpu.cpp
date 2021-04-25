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

void Cpu::execute()
{
    int x;

    std::cout << "IP: 0x" << std::hex << instruction_pointer << std::dec << "\n";
    for (x = 0; x < 8; x++)
    {
        std::cout << "V" << x << ": 0x" << std::hex << general_registers[x] << std::dec << "\n";
    }
    std::cout << "\n";

    uint16_t inst = (ram[instruction_pointer] << 8 | ram[instruction_pointer + 1]);
    bool value;
    int j;
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
                return;

            // RET
            case 0xE:
                return;

            // Unknown
            default:

                return;
            }

        default:
            // SYS addr
            return;
        }
        return;
    //JP addr
    case 0x1:
        instruction_pointer = inst & 0x0fff;
        return;

    //CALL addr
    case 0x2:
        return;

    //SE Vx, byte
    case 0x3:
        if (nibbles[1] == (inst & 0xff))
        {
            instruction_pointer += 2;
        }
        return;

    //SNE Vx, byte
    case 0x4:
        if (nibbles[1] != (inst & 0xff))
        {
            instruction_pointer += 2;
        }
        return;

    //SE Vx, Vy
    case 0x5:
        switch (nibbles[3])
        {
        case 0x0:
            if (nibbles[1] != nibbles[2])
            {
                instruction_pointer += 2;
            }
            return;
        default:
            return;
        }
        return;

    //LD Vx, byte
    case 0x6:
        switch (nibbles[3])
        {
        //LD Vx, byte
        case 0:
            general_registers[nibbles[1]] = inst & 0xff;

        //Unknown
        default:
            return;
        }
        return;

    //ADD Vx, byte
    case 0x7:
        general_registers[nibbles[1]] += inst & 0xff;
        return;

    case 0x8:
        switch (nibbles[3])
        {

        // LD Vx, Vy
        case 0x0:

            return;

        //OR Vx, Vy
        case 0x1:

            return;

        //AND Vx, Vy
        case 0x2:
            return;

        //XOR Vx, Vy
        case 0x3:
            return;

        //ADD Vx, Vy
        case 0x4:

            return;

        //SUB Vx, Vy
        case 0x5:
            return;

        //SHR Vx {, Vy}
        case 0x6:
            return;

        //SUBN Vx, Vy
        case 0x7:
            return;

        //SHL Vx {, Vy}
        case 0xE:
            return;

        //Unknown
        default:
            return;
        }

        return;
    case 0x9:
        switch (nibbles[3])
        {

        //SNE Vx, Vy
        case 0x0:
            return;

        //Unknown
        default:
            return;
        }
        return;

    //LD I, addr
    case 0xa:
        index_register = inst & 0x0fff;
        return;

    //JP V0, addr
    case 0xb:
        instruction_pointer += general_registers[1] + (inst & 0xfff);
        return;

    //RND Vx, byte
    case 0xc:

        general_registers[nibbles[1]] = (rand() & 0xff) & (inst & 0xff);
        return;

    //DRW Vx, Vy, nibble
    case 0xd:
        x = nibbles[1];
        y = nibbles[2];
        for (j = 0; j < nibbles[3]; j++)
        {
            value = emulator->screen.readpx(x++, y);
            emulator->screen.drawpx(general_registers[nibbles[1]], general_registers[nibbles[2]], !value);
            if (x <= 8)
            {
                x = 0;
                y++;
            }
        }
        return;

    case 0xe:
        switch (nibbles[2])
        {
        case 0x9:
            switch (nibbles[3])
            {
            case 0xe:
                return;
            default:
                return;
            }
            return;
        default:
            return;
        }
        return;
    case 0xf:
        switch (nibbles[2])
        {
        case 0x0:
            return;
        case 0x1:
            switch (nibbles[3])
            {
            case 0x5:
                delay_timer = general_registers[nibbles[1]];
                return;

            //LD ST, Vx
            case 0x8:
                sound_timer = general_registers[nibbles[1]];
                return;

            //ADD I, Vx
            case 0xE:
                index_register += general_registers[nibbles[1]];
                return;
            default:
                return;
            }
            return;
        case 0x2:
            return;
        case 0x3:
            return;
        case 0x5:
            switch (nibbles[3])
            {

            //LD[I], Vx
            case 0x5:
                for (x = 0; x < nibbles[1]; x++)
                {
                    ram[index_register + x] = general_registers[x];
                }
                return;
            default:
                return;
            }
            return;
        case 0x6:
            switch (nibbles[3])
            {

            //LD Vx, [I]
            case 0x5:
                for (x = 0; x < nibbles[1]; x++)
                {
                    general_registers[x] = ram[index_register + x];
                }
                return;
            default:
                return;
            }
            return;
        default:
            return;
        }
        return;
    default:
        return;
    }
}