#ifndef  FILE_PROCESSING_H
#define FILE_PROCESSING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#include "/Users/kirilllahnov/Documents/CPU/enum.h"


struct Text {
    char* file_buffer_char;
    double* file_buffer_double;
    size_t size_buffer;
};

struct FileInfo {
    const char* file_name;
    size_t size_file;
};

int stricmp (const char* str1, const char* str2);

int SizeFile (FILE* text, struct Text* text_info);

int BufferCharCreater (struct FileInfo* file_info, struct Text* text_info);

int BufferDoubleCreater (struct FileInfo* file_info, struct Text* text_info);

#endif // FILE_PROCESSING_H