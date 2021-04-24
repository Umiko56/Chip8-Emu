#include "emulator.hpp"

int main(int argc, char **argv)
{
    Emulator emulator;
    while (!emulator.input.quit)
    {
        emulator();
    }
}
