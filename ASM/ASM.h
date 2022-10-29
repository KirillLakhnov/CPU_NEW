#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "/Users/kirilllahnov/Documents/CPU_NEW/FileProcessing/FileProcessing.h"
#include "/Users/kirilllahnov/Documents/CPU_NEW/enum.h"

const size_t MARK_ARRAY_SIZE = 50;
const size_t VERSION_CPU     = 2;
const size_t SIGNATURE       = 0xFBACF;

struct Mark {
    char* name_mark;
    double meaning_mark;
};

struct AsmCodeCreater {
    double* cmd_array;
    size_t number_cmd;
    size_t max_line_cmd;

    struct Mark mark_array[MARK_ARRAY_SIZE];
    size_t free_mark;

    struct Text* text_info_asm;
    struct FileInfo* file_info_asm;

    size_t ip;
    size_t counter_string;
    size_t counter_symbol;

    char* cmd;   
};

int TextCtor (struct AsmCodeCreater* code_info);

int CompilationFirstPass (struct AsmCodeCreater* code_info);

int LineToString (struct Text* text_info); //_________

int Compilation (struct AsmCodeCreater* code_info);

int CommandCmp (struct AsmCodeCreater* code_info);

int GetPushPopArgument (struct AsmCodeCreater* code_info);

int GetJmpArgument (struct AsmCodeCreater* code_info);

int RegistrArgument (struct AsmCodeCreater* code_info);

void FileCodeCmd (struct AsmCodeCreater* code_info);

#endif // ASM_H