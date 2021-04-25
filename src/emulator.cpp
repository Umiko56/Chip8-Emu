#include "emulator.hpp"
#include <fstream>

Emulator::Emulator(char *path)
{
    char c;
    uint16_t pos = 0x200;
    std::ifstream rom_file(path, std::ios::in | std::ios::binary);
    while (rom_file.get(c))
    {
        cpu.ram[pos++] = c;
    }
    rom_file.close();
}

void Emulator::execute()
{
    cpu.execute();
    input.execute();
    screen.execute();
    SDL_Delay(5);
}
