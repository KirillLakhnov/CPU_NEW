#include "CPU.h"

int main()
{
    struct CPU cpu = {};
    CpuCtor (&cpu);

    CommandAccomplishment (&cpu);

    CpuDtor (&cpu);

    return 0;
}