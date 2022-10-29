#include "ASM.h"

int main ()
{
    struct Text text_info_asm = {};
    struct FileInfo file_info_asm = {.file_name = "/Users/kirilllahnov/Documents/CPU_NEW/ASM_FUNCTION/command.txt"};
    struct AsmCodeCreater code_info = {.max_line_cmd = 0, .free_mark = 0, .text_info_asm = &text_info_asm, .file_info_asm = &file_info_asm};

    TextCtor (&code_info);

    Compilation (&code_info);

    printf("\n");
    for (int i = 0; i < code_info.free_mark; i++)
    {
        printf("%s\t%f\t%d\n", code_info.mark_array[i].name_mark, code_info.mark_array[i].meaning_mark, i);
    }
    printf("\n");

    for (int i = 0; i < code_info.number_cmd; i++)
    {
        printf ("%lf\t%d\n", code_info.cmd_array[i], i);
    }

    return 0;
}