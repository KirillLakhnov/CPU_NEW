#ifndef DIS_ASM_H
#define DIS_ASM_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "/Users/kirilllahnov/Documents/CPU_NEW/FileProcessing/FileProcessing.h"
#include "/Users/kirilllahnov/Documents/CPU_NEW/enum.h"

int TextCtor (struct Text* code_bin, struct FileInfo* file_info_dis);

int CommandAccomplishment (size_t* ip, struct Text* code_bin);

void TextDtor (struct Text* code_bin, struct FileInfo* file_info_dis);

#endif // DIS_ASM_H