#include "DIS_ASM.h"

int main ()
{
    struct FileInfo file_info_dis = {.file_name = "/Users/kirilllahnov/Documents/CPU/code_command.bin"};
    struct Text code_bin = {};

    size_t ip = 3;

    TextCtor (&code_bin, &file_info_dis);

    CommandAccomplishment (&ip,&code_bin);

    TextDtor (&code_bin, &file_info_dis);

    return 0;
}