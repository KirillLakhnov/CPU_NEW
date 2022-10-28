#include "FileProcessing.h"

int stricmp (const char* str1, const char* str2)
{
    assert (str1);
    assert (str2);
    
    int i = 0;
    while (tolower (str1[i]) == tolower (str2[i]) && (str1[i] != '\0' && str2[i++] != '\0'));
    
    return tolower (str1[i]) - tolower (str2[i]);
}

int SizeFile (FILE* text, struct Text* text_info)
{
    assert(text);

    if (fseek (text, 0, SEEK_END) != 0)
    {
        return ERROR_FSEEK;
    }

    text_info->size_buffer = ftell (text);
    if (!(text_info->size_buffer))
    {
        return ERROR_FTELL;
    }

    if (fseek (text, 0, SEEK_SET) != 0)
    {
        return ERROR_FSEEK;
    }
    return GOOD_WORKING;
}

int BufferCharCreater (struct FileInfo* file_info, struct Text* text_info)
{
    assert(file_info->file_name);

    FILE* text = fopen (file_info->file_name, "rb");
    if (!text)
    {
        return ERROR_FILE_OPEN;
    }

    if (SizeFile (text, text_info) != GOOD_WORKING)
    {
        return ERROR_SIZE_FILE;
    }; 

    text_info->file_buffer_char = (char*) calloc (text_info->size_buffer + 1, sizeof (char));
    if (!(text_info->file_buffer_char))
    {
        fclose (text);
        return ERROR_MEMMORY;
    }

    size_t count_simbols = fread (text_info->file_buffer_char, sizeof (char), text_info->size_buffer, text);
    if (count_simbols != text_info->size_buffer)
    {
        free (text_info->file_buffer_char);
        text_info->file_buffer_char = nullptr;

        fclose (text);
        return ERROR_READING_FILE;
    }

    if (fclose (text) != 0)
    {
        free (text_info->file_buffer_char);
        text_info->file_buffer_char = nullptr;
        
        return ERROR_FILE_CLOSE;
    }

    return GOOD_WORKING;
}

int BufferDoubleCreater (struct FileInfo* file_info, struct Text* text_info)
{
    assert(file_info->file_name);

    FILE* text = fopen (file_info->file_name, "rb");
    if (!text)
    {
        return ERROR_FILE_OPEN;
    }

    if (SizeFile (text, text_info) != GOOD_WORKING)
    {
        return ERROR_SIZE_FILE;
    }; 

    text_info->file_buffer_double = (double*) calloc (text_info->size_buffer + 1, sizeof (double));
    if (!(text_info->file_buffer_double))
    {
        fclose (text);
        return ERROR_MEMMORY;
    }

    size_t count_simbols = fread (text_info->file_buffer_double, sizeof (char), text_info->size_buffer, text);
    if (count_simbols != text_info->size_buffer)
    {
        free (text_info->file_buffer_double);
        text_info->file_buffer_double = nullptr;

        fclose (text);
        return ERROR_READING_FILE;
    }

    if (fclose (text) != 0)
    {
        free (text_info->file_buffer_double);
        text_info->file_buffer_double = nullptr;
        
        return ERROR_FILE_CLOSE;
    }

    return GOOD_WORKING;
}