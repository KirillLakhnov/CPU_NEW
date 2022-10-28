#include <stdio.h>
#include <stdlib.h>

int main ()
{
    system ("./asm ASM/ASM.cpp ASM/common.cpp ASM/main.cpp FileProcessing/FileProcessing.cpp");
    system ("./cpu CPU/CPU.cpp CPU/main.cpp FileProcessing/FileProcessing.cpp Stack/stack_common.cpp Stack/stack.cpp");
    return 0;
}