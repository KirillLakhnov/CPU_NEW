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

enum ERROR_CPU {
    GOOD_WORKING           = 0,
    ERROR_MEMMORY          = 1,
    ERROR_READING_FILE     = 2,
    ERROR_FILE_OPEN        = 3,
    ERROR_FILE_CLOSE       = 4,
    ERROR_FSEEK            = 5,
    ERROR_FTELL            = 6,
    ERROR_FPRINTF          = 7,
    ERROR_FPUTS            = 8,
    ERROR_BUFFER_CREATER   = 9,
    INCORRECT_COMMAND      = 10,
    ERROR_SIGNATURE        = 11,
    ERROR_VERSION_CPU      = 12,
    ERROR_SIZE_FILE        = 13,
    ERROR_CALLOC           = 14,
    ERROR_REALLOC          = 15,
    ERROR_MARK_FIND        = 16,
    ERROR_SSCANF           = 17,
    ERROR_COMMAND_CMP      = 18,
    ERROR_STACK_CTOR       = 19,
};

enum NUMBER_REGISTERS {
    RAX = 1,
    RBX = 2,
    RCX = 3,
    RDX = 4,
    REX = 5,
    RFX = 6,
};

enum NUMBER_COMMAND {
    HTL        = 0,
    PUSH       = 1,
    ADD        = 2,
    SUB        = 3,
    MUL        = 4,
    DIV        = 5,
    OUT        = 6,
    POP        = 7,
    JMP        = 8,
    JB         = 9,
    JBE        = 10,
    JA         = 11,
    JAE        = 12,
    JE         = 13,
    JNE        = 14,
    DUMP       = 15,
    IN         = 16,
    SQRT       = 17,
    OUTCHR     = 18,
    CALL       = 19,
    RET        = 20,
    EMPTY      = 21,
    OUT_SCREEN = 22,
    INT        = 23,
    REMAIN     = 24,
    SQR        = 25,
};

#endif // ENUM_H
