#include "emulator.hpp"

Emulator *emulator;

int main(int argc, char **argv)
{
    srand(time(NULL));

    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " [rom.ch8]" << std::endl;
        return 0;
    }

    emulator = new Emulator(argv[1]);
    while (!emulator->input.quit)
    {
        emulator->execute();
    }
}
