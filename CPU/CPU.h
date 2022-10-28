#ifndef CPU_H
#define CPU_H

#include "/Users/kirilllahnov/Documents/CPU/Stack/stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "/Users/kirilllahnov/Documents/CPU/FileProcessing/FileProcessing.h"
#include "/Users/kirilllahnov/Documents/CPU/enum.h"

const size_t VERSION_CPU = 2;
const size_t SIGNATURE   = 0xFBACF;

const size_t RAM_SIZE       = 10000;
const size_t REGISTERS_SIZE = 7;

struct CPU {
    FILE* cpu_dump;

    double* ram;
    double* registers;

    size_t ip;

    struct Text text_info_cpu;
    struct FileInfo file_info_cpu;

    struct Stack stack_command;
    struct Stack stack_mark;

    int cmd_bool;
};

int CpuCtor (struct CPU* cpu);

int TextCtor (struct CPU* cpu);

double* GetArgument (struct CPU* cpu);

int CommandAccomplishment (struct CPU* cpu);

void CpuDump (struct CPU* cpu);

void TextDtor (struct CPU* cpu);

void CpuDtor (struct CPU* cpu);

#endif // CPU_H