#include "CPU.h"

int main()
{
    struct CPU cpu = {};
    CpuCtor (&cpu);

    if (CommandAccomplishment (&cpu) != GOOD_WORKING)
    {
        printf ("ERROR SYNTAX, line = %d", __LINE__);
        return 1;
    }

    CpuDtor (&cpu);

    return 0;
}