#include "emulator.hpp"

Emulator::Emulator()
{
}

void Emulator::execute()
{
    cpu.execute();
    input.execute();
    screen.execute();
}

void Emulator::operator()()
{
    execute();
}
