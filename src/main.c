#include "emulator.h"
#include "graphics.h"
#include "memory.h"



int main(void)
{
    struct s_emulator emulator;
    int status = -1;
    if(!initialize_emulator(&emulator))
    {
        status = 0;
        emulate(&emulator);
        destroy_emulator(&emulator);
    }
    return status;
}
