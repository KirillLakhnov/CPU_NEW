#include "ASM.h"

int main ()
{
    struct Text text_info_asm = {};
    struct FileInfo file_info_asm = {.file_name = "/Users/kirilllahnov/Documents/CPU/ASM_FUNCTION/command.txt"};
    struct AsmCodeCreater code_info = {.free_mark = 0, .text_info_asm = &text_info_asm, .file_info_asm = &file_info_asm};

    TextCtor (&code_info);

    CmdArrayCreater (&code_info);
    FileCodeCmd (&code_info);

    TextDtor (&code_info);
      
    return 0;
}