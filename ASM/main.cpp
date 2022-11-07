#include "ASM.h"

int main ()
{
    struct Text text_info_asm = {};
    struct FileInfo file_info_asm = {.file_name = "/Users/kirilllahnov/Documents/CPU_NEW/ASM_FUNCTION/command.txt"};
    struct AsmCodeCreater code_info = {.max_line_cmd = 0, .free_mark = 0, .text_info_asm = &text_info_asm, .file_info_asm = &file_info_asm};
    
    if (TextCtor (&code_info) != GOOD_WORKING)
    {
        printf ("TextCtor failed, line = %d", __LINE__);
        return 1;
    }

    if (Compilation (&code_info) != GOOD_WORKING)
    {
        printf ("Compilation failed, line = %d", __LINE__);
        return 1;
    }

    if (FileCodeCmd (&code_info) != GOOD_WORKING)
    {
        printf ("FileCodeCmd failed, line = %d", __LINE__);
        return 1;
    }

    TextDtor (&code_info);

    return 0;
}