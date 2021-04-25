#include "emulator.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " [rom.ch8]\n";
        return 0;
    }

    Emulator emulator(argv[1]);
    while (!emulator.input.quit)
    {
        emulator();
    }
}
