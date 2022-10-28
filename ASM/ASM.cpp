#include "ASM.h"

int MarkFind (struct AsmCodeCreater* code_info)
{
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buffer_char);
    assert (code_info->cmd_array);

    int i = 0;
    int ip = 0;

    char* cmd = (char*) calloc (code_info->max_line_cmd, sizeof(char));
    if (cmd == nullptr)
    {
        return ERROR_CALLOC;
    }

    while (i < code_info->text_info_asm->size_buffer)
    {   
        int length_cmd = 0;

        while (*(code_info->text_info_asm->file_buffer_char + i) == '\0')
        {
            i++;
        }
        
        if (sscanf(code_info->text_info_asm->file_buffer_char + i, "%s%n", cmd, &length_cmd) != 1)
        {
            return ERROR_SSCANF;
        }
        
        i += (length_cmd + 1);

        char* find_colon_in_cmd = strchr (cmd, ':');

        if (find_colon_in_cmd != nullptr)
        {
            if (find_colon_in_cmd - cmd == length_cmd - 1)
            {
                code_info->mark_array[code_info->free_mark].meaning_mark = ip - code_info->free_mark;
                code_info->mark_array[code_info->free_mark].name_mark = strdup (cmd);

                code_info->mark_array[code_info->free_mark].name_mark[strlen(code_info->mark_array[code_info->free_mark].name_mark) - 1] = '\0';
                code_info->free_mark++;
            }
        }

        ip++;
    }

    free (cmd);

    return GOOD_WORKING;
}

int CmdArrayCreater (struct AsmCodeCreater* code_info)
{
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buffer_char);

    code_info->number_cmd = LineToString (code_info);

    code_info->cmd_array = (double*) calloc (code_info->number_cmd + 3, sizeof (double));
    if (code_info->cmd_array == nullptr)
    {
        return ERROR_CALLOC;
    }

    code_info->cmd_array[0] = SIGNATURE; 
    code_info->cmd_array[1] = VERSION_CPU;
    code_info->cmd_array[2] = code_info->number_cmd;

    if (MarkFind (code_info) != GOOD_WORKING)
    {
        return ERROR_MARK_FIND;
    };

    code_info->ip = 3, code_info->counter = 0;

    code_info->cmd = (char*) calloc (code_info->max_line_cmd, sizeof(char));
    if (code_info->cmd == nullptr)
    {
        return ERROR_CALLOC;
    }

    while (code_info->counter < code_info->text_info_asm->size_buffer)
    { 
        while (*(code_info->text_info_asm->file_buffer_char + code_info->counter) == '\0')
        {
            code_info->counter++;
        }

        int length_cmd = 0;

        if (sscanf(code_info->text_info_asm->file_buffer_char + code_info->counter, "%s%n", code_info->cmd, &length_cmd) != 1)
        {
            return ERROR_SSCANF;
        }

        code_info->counter += (length_cmd + 1);

        CommandCmp (code_info);
    }

    free (code_info->cmd);
    return GOOD_WORKING;
}

int RegistrArgument (struct AsmCodeCreater* code_info)
{
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buffer_char);
    assert (code_info->cmd_array);

    int length_cmd = 0;

    if (sscanf(code_info->text_info_asm->file_buffer_char + code_info->counter, "%s%n", code_info->cmd, &length_cmd) != 1)
    {
        return ERROR_SSCANF;
    }

    if (*(code_info->cmd+length_cmd - 1) == ']')
    {
        *(code_info->cmd+length_cmd - 1) = '\0';
    }

    #define DEF_REG(name_cmd, code_cmd)     if (stricmp (code_info->cmd, #name_cmd) == 0)                       \
                                            {                                                                   \
                                                code_info->cmd_array[code_info->ip++] = code_cmd;               \
                                            }                                                                   \
                                            else 

    #define DEF_COMMAND(name_cmd, code_cmd, there_is_argument, ...)

    #include "/Users/kirilllahnov/Documents/CPU/command.h"
    
    #undef DEF_COMMAND
    #undef DEF_REG
    /* else */
    {   
        return INCORRECT_COMMAND;
    }
     
    code_info->counter += (length_cmd + 1);
    return GOOD_WORKING;
}

int GetPushPopArgument (struct AsmCodeCreater* code_info)
{
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buffer_char);
    assert (code_info->cmd_array);

    int length_cmd = 0;
        
    if (*(code_info->text_info_asm->file_buffer_char + code_info->counter) == '[')
    {
        code_info->cmd_array[code_info->ip - 1] += BITE_MEMORY;
        code_info->counter++;
    }

    if (sscanf(code_info->text_info_asm->file_buffer_char + code_info->counter, "%lf%n", &code_info->cmd_array[code_info->ip], &length_cmd) != 0)
    {
        code_info->cmd_array[code_info->ip - 1] += BITE_IMMEDIATE_CONST;
        if (*(code_info->text_info_asm->file_buffer_char + code_info->counter + length_cmd) == '+')
        {
            code_info->counter += (length_cmd + 1);
            code_info->cmd_array[code_info->ip - 1] += BITE_REGISTER;
            code_info->ip++;
    
            return RegistrArgument (code_info);
        }

        code_info->ip++;
    }
    else if (sscanf(code_info->text_info_asm->file_buffer_char + code_info->counter, "%lf%n", &code_info->cmd_array[code_info->ip], &length_cmd) == 0)
    {
        code_info->cmd_array[code_info->ip - 1] += BITE_REGISTER;

        return RegistrArgument (code_info);
    }
        
    code_info->counter += (length_cmd + 1);

    if (*(code_info->text_info_asm->file_buffer_char + code_info->counter - 1) == ']')
    {
        code_info->counter++;
    }

    return GOOD_WORKING;
}

int GetJmpArgument (struct AsmCodeCreater* code_info)
{   
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buffer_char);
    assert (code_info->cmd_array);

    int length_cmd = 0;
    if (sscanf(code_info->text_info_asm->file_buffer_char + code_info->counter, "%lf%n", &code_info->cmd_array[code_info->ip], &length_cmd) != 0)
    {
        code_info->ip++;
    }
    else
    {
        sscanf(code_info->text_info_asm->file_buffer_char + code_info->counter, "%s%n", code_info->cmd, &length_cmd);

        for (int j = 0; j < code_info->free_mark; j++)
        {   
            if (strcmp (code_info->cmd + 1, code_info->mark_array[j].name_mark) == 0)
            {
                code_info->cmd_array[code_info->ip] = code_info->mark_array[j].meaning_mark;
                code_info->ip++;

                break;
            }
        }
    }

    code_info->counter += (length_cmd + 1);
    
    return GOOD_WORKING;
}

int CommandCmp (struct AsmCodeCreater* code_info)
{
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buffer_char);
    assert (code_info->cmd_array);

    #define DEF_COMMAND(name_cmd, code_cmd, there_is_argument, ...)     if (stricmp (code_info->cmd, #name_cmd) == 0)                                              \
                                                                        {                                                                               \
                                                                            code_info->cmd_array[(code_info->ip)++] = code_cmd;                         \
                                                                            if (there_is_argument == 1)                                                 \
                                                                            {                                                                           \
                                                                                GetPushPopArgument (code_info);                                         \
                                                                            }                                                                           \
                                                                            else if (there_is_argument == 2)                                            \
                                                                            {                                                                           \
                                                                                GetJmpArgument (code_info);                                             \
                                                                            }                                                                           \
                                                                        }                                                                               \
                                                                        else 

    #define DEF_REG(name_cmd, code_cmd)

    #include "/Users/kirilllahnov/Documents/CPU/command.h"

    #undef DEF_COMMAND
    #undef DEF_REG

    /* else */
    {
        return INCORRECT_COMMAND;
    }

    return GOOD_WORKING;
}

void FileCodeCmd (struct AsmCodeCreater* code_info)
{
    assert (code_info->text_info_asm);
    assert (code_info->text_info_asm->file_buffer_char);
    assert (code_info->cmd_array);

    FILE* code_cmd_file = fopen ("code_command.bin", "wb");

    fwrite (code_info->cmd_array, sizeof(double), code_info->number_cmd + 3, code_cmd_file);

    fclose (code_cmd_file);
}


