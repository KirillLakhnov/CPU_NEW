#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "/Users/kirilllahnov/Documents/CPU/FileProcessing/FileProcessing.h"
#include "/Users/kirilllahnov/Documents/CPU/enum.h"

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
    size_t counter;

    char* cmd;   
};

int LineToString (struct AsmCodeCreater* code_info);

int TextCtor (struct AsmCodeCreater* code_info);

void TextDtor (struct AsmCodeCreater* code_info);

#endif // COMMON_H