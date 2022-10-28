#include "DIS_ASM.h"

int TextCtor (struct Text* code_bin, struct FileInfo* file_info_dis)
{
    assert (code_bin);
    assert (file_info_dis);
    assert (file_info_dis->file_name);

    if (BufferDoubleCreater (file_info_dis, code_bin))
    {
        return ERROR_BUFFER_CREATER;
    }
    return GOOD_WORKING;
}

int CommandAccomplishment (size_t* ip, struct Text* code_bin)
{
    assert (code_bin);
    assert (code_bin->file_buffer_double);
    
    FILE* text_output = fopen ("disasembler.txt", "wb");
    if (text_output == nullptr)
    {
        return ERROR_FILE_OPEN;
    }

    while (*ip < (code_bin->file_buffer_double[QUANTITY_COMMAND] + 2))
    {
        unsigned long long cmd = (unsigned long long)code_bin->file_buffer_double[*ip] & 31;
        unsigned long long cmd_with_type = (unsigned long long)code_bin->file_buffer_double[*ip];

        switch (cmd)
        {
            #define DEF_COMMAND_DIS_ASM(name_cmd, code_cmd, there_is_argument, ... ) case code_cmd: fprintf (text_output, #name_cmd" ");    \
                                                                                                    __VA_ARGS__                             \
                                                                                                    fprintf (text_output, "\n");            \
                                                                                                    (*ip)++;                                \
                                                                                                    break;

            #include "/Users/kirilllahnov/Documents/CPU/command_disassembler.h"

            #undef DEF_COMMAND_DIS_ASM

            default: assert (0 && "ERROR SYNTAX COMMAND\n");
        }
    }

    if (fclose (text_output) != 0)
    {
        return ERROR_FILE_CLOSE;
    }

    return GOOD_WORKING;
}

void TextDtor (struct Text* code_bin, struct FileInfo* file_info_dis)
{
    for (int i = 0; i < code_bin->size_buffer; i++)
    {
        code_bin->file_buffer_double[i] = NULL_DOUBLE;
    }
    free (code_bin->file_buffer_double);

    code_bin->size_buffer = NUMBER_DTOR_VALUE;
}

