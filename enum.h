#ifndef ENUM_H
#define ENUM_H

const double NULL_DOUBLE = NAN;
const size_t NUMBER_DTOR_VALUE = 0xBABADEDA;

enum BIN_FILE_NUMBER_CELLS {
    SIGNATURE_NUMBER_CELL   = 0,
    VERSION_CPU_NUMBER_CELL = 1,
    QUANTITY_COMMAND        = 2,
};

enum BITE_VARIATIONS {
    BITE_IMMEDIATE_CONST = 1 << 5,
    BITE_REGISTER        = 1 << 6,
    BITE_MEMORY          = 1 << 7,
};

enum ERRORS {
    GOOD_WORKING                    = 0,
    ERROR_MEMMORY                   = 1,
    ERROR_READING_FILE              = 2,
    ERROR_FILE_OPEN                 = 3,
    ERROR_FILE_CLOSE                = 4,
    ERROR_FSEEK                     = 5,
    ERROR_FTELL                     = 6,
    ERROR_FPRINTF                   = 7,
    ERROR_FPUTS                     = 8,
    ERROR_BUFFER_CREATER            = 9,
    INCORRECT_COMMAND               = 10,
    ERROR_SIGNATURE                 = 11,
    ERROR_VERSION_CPU               = 12,
    ERROR_SIZE_FILE                 = 13,
    ERROR_CALLOC                    = 14,
    ERROR_REALLOC                   = 15,
    ERROR_MARK_FIND                 = 16,
    ERROR_SSCANF                    = 17,
    ERROR_COMMAND_CMP               = 18,
    ERROR_STACK_CTOR                = 19,
    ERROR_FWRITE                    = 20,
    ERROR_COMPILATION_FIRST_PASS    = 21,
    ERROR_SYNTAX_COMMAND            = 22,
};

enum NUMBER_REGISTERS {
    #define DEF_COMMAND(name_cmd, code_cmd, there_is_argument, ...)  
    #define DEF_REG(name_cmd, code_cmd) name_cmd = code_cmd,

    #include "command.h"

    #undef DEF_COMMAND
    #undef DEF_REG
};

enum NUMBER_COMMAND {

    #define DEF_COMMAND(name_cmd, code_cmd, there_is_argument, ...) name_cmd = code_cmd,  
    #define DEF_REG(name_cmd, code_cmd)

    #include "command.h"

    #undef DEF_COMMAND
    #undef DEF_REG
};

#endif // ENUMS_H
