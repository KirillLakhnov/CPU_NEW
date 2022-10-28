#include "common.h"

int LineToString (struct AsmCodeCreater* code_info)
{
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buffer_char);

    size_t number_comand = 0;
    code_info->max_line_cmd = 0;

    size_t line_cmd = 0;
    int i = 0;
    while (i < code_info->text_info_asm->size_buffer)
    {
        line_cmd = 0;
        
        if (code_info->text_info_asm->file_buffer_char[i] == '+')
        {
            number_comand++;
        }
        if (i != 0 && isspace (code_info->text_info_asm->file_buffer_char[i - 1]) == 0 && isspace(code_info->text_info_asm->file_buffer_char[i]) != 0)
        {
            code_info->text_info_asm->file_buffer_char[i] = '\0';
            if (!(isspace (code_info->text_info_asm->file_buffer_char[i]) == 0 && isspace(code_info->text_info_asm->file_buffer_char[i + 1]) != 0))
            {
                number_comand++;
            }

            if (line_cmd > code_info->max_line_cmd)
            {
                code_info->max_line_cmd = line_cmd;
            }
            line_cmd = 0;
        }
        i++;
    }
    return (number_comand + 1);
}

int TextCtor (struct AsmCodeCreater* code_info)
{
    assert (code_info->text_info_asm);
    assert (code_info->file_info_asm);
    assert (code_info->file_info_asm->file_name);

    if (BufferCharCreater (code_info->file_info_asm, code_info->text_info_asm))
    {
        return ERROR_BUFFER_CREATER;
    }

    return GOOD_WORKING;
}

void TextDtor (struct AsmCodeCreater* code_info)
{
    for (int i = 0; i < code_info->text_info_asm->size_buffer; i++)
    {
        *(code_info->text_info_asm->file_buffer_char + i) = NAN;
    }
    free (code_info->text_info_asm->file_buffer_char);
    code_info->text_info_asm->file_buffer_char = nullptr;

    code_info->text_info_asm->size_buffer = NUMBER_DTOR_VALUE;
    code_info->file_info_asm->size_file   = NUMBER_DTOR_VALUE;

    for (int i = 0; i < code_info->number_cmd; i++)
    {
        code_info->cmd_array[i] = NULL_DOUBLE;
    }
    free (code_info->cmd_array);
    code_info->cmd_array = nullptr;

    code_info->number_cmd   = NUMBER_DTOR_VALUE;
    code_info->max_line_cmd = NUMBER_DTOR_VALUE;
}

