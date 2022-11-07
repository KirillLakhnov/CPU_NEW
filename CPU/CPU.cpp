#include "CPU.h"

int CpuCtor (struct CPU* cpu)
{
    assert (cpu);

    cpu->ram = (double*) calloc (RAM_SIZE, sizeof(double));
    if (cpu->ram == nullptr)
    {
        return ERROR_CALLOC;
    }
    
    cpu->registers = (double*) calloc (REGISTERS_SIZE, sizeof(double));
    if (cpu->registers == nullptr)
    {
        return ERROR_CALLOC;
    }

    cpu->cmd_bool = 1;

    struct function_info func_info_command = {.log_file_name = "stack_command_dump.txt", .name_stack = "stack", .number_line_stack_name_main = __LINE__};
    cpu->stack_command.func_info = func_info_command;

    struct function_info func_info_mark = {.log_file_name = "stack_mark_dump.txt", .name_stack = "stack", .number_line_stack_name_main = __LINE__};
    cpu->stack_mark.func_info = func_info_mark;

    cpu->file_info_cpu.file_name = "code_command.bin";

    TextCtor (cpu);

    if (StackCtor (&cpu->stack_command, 5) != GOOD_WORKING)
    {
        return ERROR_STACK_CTOR;
    }
    if (StackCtor (&cpu->stack_mark, 5) != GOOD_WORKING)
    {
        return ERROR_STACK_CTOR;
    }

    for (int i = 0; i < RAM_SIZE; i++)
    {
        cpu->ram[i] = NAN;
    }
    for (int i = 0; i < REGISTERS_SIZE; i++)
    {
        cpu->registers[i] = NAN;
    }

    return GOOD_WORKING;
}

int TextCtor (struct CPU* cpu)
{
    assert (&cpu->text_info_cpu);
    assert (&cpu->file_info_cpu);
    assert (cpu->file_info_cpu.file_name);

    if (BufferDoubleCreater (&cpu->file_info_cpu, &cpu->text_info_cpu))
    {
        return ERROR_BUFFER_CREATER;
    }
    return GOOD_WORKING;
}

double* GetArgument (struct CPU* cpu)
{
    assert (cpu);
    assert (&cpu->text_info_cpu);
    assert (&cpu->text_info_cpu.file_buffer_double);
    assert (cpu->registers);
    assert (cpu->ram);

    double* buffer = cpu->text_info_cpu.file_buffer_double;

    static double argument = 0;
    argument = 0;
    
    unsigned long long cmd = (unsigned long long)buffer[cpu->ip];
    unsigned long long cmd_no_type = cmd & 31;

    if (cmd & BITE_IMMEDIATE_CONST)
    {   
        assert (!(cmd_no_type == POP && ((cmd & BITE_MEMORY) == 0)));

        cpu->ip++;
        argument += buffer[cpu->ip];
    }  
    if (cmd & BITE_REGISTER)
    {
        assert (!(cmd_no_type == POP && ((cmd & BITE_MEMORY) == 0) && cmd & BITE_IMMEDIATE_CONST));

        cpu->ip++;

        if (cmd_no_type == PUSH || (cmd_no_type == POP && cmd & BITE_MEMORY))
        {
            argument += cpu->registers[(unsigned long long)buffer[cpu->ip]];
        }
        else
        {
            return &cpu->registers[(unsigned long long)buffer[cpu->ip]];
        }
    }
    if (cmd & BITE_MEMORY)
    {
        if (cmd_no_type == PUSH)
        {
            argument = cpu->ram[(unsigned long long)(argument)];
        }
        else
        {
            return &cpu->ram[(unsigned long long)(argument)];
        }
    }

    return &argument;
}

int CommandAccomplishment (struct CPU* cpu)
{
    assert (cpu);
    assert (&cpu->text_info_cpu);
    assert (cpu->text_info_cpu.file_buffer_double);
    assert (cpu->registers);
    assert (cpu->ram);

    double* buffer = cpu->text_info_cpu.file_buffer_double;

    if (buffer[SIGNATURE_NUMBER_CELL] != SIGNATURE)
    {
        return ERROR_SIGNATURE;
    }
    if (buffer[VERSION_CPU_NUMBER_CELL] != VERSION_CPU)
    {
        return ERROR_VERSION_CPU;
    }
    
    cpu->ip = 3;
    while (cpu->ip < (buffer[QUANTITY_COMMAND] + 2))
    {
        unsigned long long cmd = (unsigned long long)buffer[cpu->ip] & 31;
        
        switch (cmd)
        {
            #define DEF_COMMAND(name_cmd, code_cmd, there_is_argument, ...)  case code_cmd: __VA_ARGS__                 \
                                                                                            cpu->ip++;                  \
                                                                                            break; 

            #define DEF_REG(name_cmd, code_cmd)

            #include "../command.h"

            #undef DEF_COMMAND
            #undef DEF_REG

            default: return ERROR_SYNTAX_COMMAND;
        }
    }

    return GOOD_WORKING;
}

void CpuDump (struct CPU* cpu)
{
    cpu->cpu_dump = fopen ("cpu_dump.txt", "ab");

    fprintf (cpu->cpu_dump, "ASM COMMAND\n");
    fprintf (cpu->cpu_dump, "ip:  \t");
    for (int i = 0; i < cpu->text_info_cpu.file_buffer_double[QUANTITY_COMMAND] + 3; i++)
    {
        fprintf (cpu->cpu_dump, "%15d", i);
    }
    fprintf (cpu->cpu_dump, "\n");

    fprintf (cpu->cpu_dump, "code:\t");
    for (int i = 0; i < cpu->text_info_cpu.file_buffer_double[QUANTITY_COMMAND] + 3; i++)
    {
        fprintf (cpu->cpu_dump, "%15lf", cpu->text_info_cpu.file_buffer_double[i]);
    }
    fprintf (cpu->cpu_dump, "\n\n");


    fprintf (cpu->cpu_dump, "STACK\n");
    fprintf (cpu->cpu_dump, "{\n\tsize     = %lu\n"
                               "\tcapacity = %lu\n" 
                               "\tcode of error = %d\n"
                               "\tdata[%p]\n\t{\n", cpu->stack_command.size, cpu->stack_command.capacity, cpu->stack_command.code_of_error, cpu->stack_command.data);

    for (int i = 0; i < cpu->stack_command.capacity; i++)
    {
        fprintf (cpu->cpu_dump, "\t\t%c [%d] = " specifier_elem_t "\n", 
                           (cpu->stack_command.data[i] == NULL_SPECIFIER || cpu->stack_command.data[i] != cpu->stack_command.data[i]) ? ' ' : '*', i, cpu->stack_command.data[i]);
    }
    fprintf (cpu->cpu_dump, "\t}\n}\n\n");

    fprintf (cpu->cpu_dump, "REGISTERS\n");
    fprintf (cpu->cpu_dump, "{");
    {
        for (int i = 0; i < REGISTERS_SIZE; i++)
        {
            fprintf (cpu->cpu_dump, "\tregister[%d] = %lf\n", i, cpu->registers[i]);
        }
    }
    fprintf (cpu->cpu_dump, "}");
    fprintf (cpu->cpu_dump, "\n\n");

    fprintf (cpu->cpu_dump, "RAM\n");
    for (int i = 0; i < sqrt(RAM_SIZE); i++)
    {
        for (int j = 0; j < sqrt(RAM_SIZE); j++)
        {
            fprintf (cpu->cpu_dump, "%15lf", cpu->ram[i*(int)sqrt(RAM_SIZE) + j]);
        }
        fprintf (cpu->cpu_dump, "\n");
    }

    fprintf(cpu->cpu_dump, "______________________________________________________________________________________________________________________________\n");
}

void TextDtor (struct CPU* cpu)
{
    assert(cpu->text_info_cpu.file_buffer_double);

    double* buffer = cpu->text_info_cpu.file_buffer_double;
  
    if (buffer)
    {
        free(buffer);
        buffer = nullptr;
    }

    cpu->text_info_cpu.size_buffer = 0;
}

void CpuDtor (struct CPU* cpu)
{
    TextDtor (cpu);
    StackDtor (&cpu->stack_command);
    StackDtor (&cpu->stack_mark);

    cpu->ip = NUMBER_DTOR_VALUE;
    cpu->cmd_bool = NUMBER_DTOR_VALUE;

    if (cpu->ram)
    {
        free (cpu->ram);
        cpu->ram = nullptr;
    }

    for (int i = 0; i < REGISTERS_SIZE; i++)
    {
        cpu->registers[i] = NULL_DOUBLE;
    }

    if (cpu->registers)
    {
        free (cpu->registers);
        cpu->registers = nullptr;
    }
};
