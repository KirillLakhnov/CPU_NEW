#define DIS_ASM_PUSH_POP                        if (cmd_with_type & BITE_IMMEDIATE_CONST)                               \
                                                {                                                                       \
                                                    fprintf (text_output, "%lf", code_bin->file_buffer_double[*ip]);    \
                                                    if (cmd_with_type & BITE_REGISTER)                                  \
                                                    {                                                                   \
                                                        (*ip)++;                                                        \
                                                        fprintf (text_output, "+");                                     \
                                                        switch ((int)code_bin->file_buffer_double[*ip])                 \
                                                        {                                                               \
                                                            case RAX: fprintf (text_output, "RAX"); break;              \
                                                            case RBX: fprintf (text_output, "RAB"); break;              \
                                                            case RCX: fprintf (text_output, "RCX"); break;              \
                                                            case RDX: fprintf (text_output, "RDX"); break;              \
                                                            case REX: fprintf (text_output, "REX"); break;              \
                                                            case RFX: fprintf (text_output, "RFX"); break;              \
                                                            default:  fprintf (text_output, "REGISTERS_ERROR");         \
                                                        }                                                               \
                                                    }                                                                   \
                                                }                                                                       \
                                                else if (cmd_with_type & BITE_REGISTER)                                 \
                                                {                                                                       \
                                                    switch ((int)code_bin->file_buffer_double[*ip])                     \
                                                    {                                                                   \
                                                        case RAX: fprintf (text_output, "RAX"); break;                  \
                                                        case RBX: fprintf (text_output, "RBX"); break;                  \
                                                        case RCX: fprintf (text_output, "RCX"); break;                  \
                                                        case RDX: fprintf (text_output, "RDX"); break;                  \
                                                        case REX: fprintf (text_output, "REX"); break;                  \
                                                        case RFX: fprintf (text_output, "RFX"); break;                  \
                                                        default:  fprintf (text_output, "REGISTERS_ERROR");             \
                                                    }                                                                   \
                                                }     

DEF_COMMAND_DIS_ASM (HLT,        0,  0)
DEF_COMMAND_DIS_ASM (ADD,        2,  0)
DEF_COMMAND_DIS_ASM (SUB,        3,  0)
DEF_COMMAND_DIS_ASM (MUL,        4,  0)
DEF_COMMAND_DIS_ASM (DIV,        5,  0)
DEF_COMMAND_DIS_ASM (OUT,        6,  0)
DEF_COMMAND_DIS_ASM (DUMP,       15, 0)
DEF_COMMAND_DIS_ASM (IN,         16, 0)
DEF_COMMAND_DIS_ASM (SQRT,       17, 0)
DEF_COMMAND_DIS_ASM (OUTCHR,     18, 0)
DEF_COMMAND_DIS_ASM (RET,        20, 0)
DEF_COMMAND_DIS_ASM (EMPTY,      21, 0)
DEF_COMMAND_DIS_ASM (OUT_SCREEN, 22, 0)
DEF_COMMAND_DIS_ASM (INT,        23, 0)
DEF_COMMAND_DIS_ASM (REMAIN,     24, 0)
DEF_COMMAND_DIS_ASM (SQR,        25, 0)

DEF_COMMAND_DIS_ASM (JMP,        8,  2, {(*ip)++; fprintf(text_output, "%lf", code_bin->file_buffer_double[*ip]);})
DEF_COMMAND_DIS_ASM (JB,         9,  2, {(*ip)++; fprintf(text_output, "%lf", code_bin->file_buffer_double[*ip]);})
DEF_COMMAND_DIS_ASM (JBE,        10, 2, {(*ip)++; fprintf(text_output, "%lf", code_bin->file_buffer_double[*ip]);})
DEF_COMMAND_DIS_ASM (JA,         11, 2, {(*ip)++; fprintf(text_output, "%lf", code_bin->file_buffer_double[*ip]);})
DEF_COMMAND_DIS_ASM (JAE,        12, 2, {(*ip)++; fprintf(text_output, "%lf", code_bin->file_buffer_double[*ip]);})
DEF_COMMAND_DIS_ASM (JE,         13, 2, {(*ip)++; fprintf(text_output, "%lf", code_bin->file_buffer_double[*ip]);})
DEF_COMMAND_DIS_ASM (JNE,        14, 2, {(*ip)++; fprintf(text_output, "%lf", code_bin->file_buffer_double[*ip]);})
DEF_COMMAND_DIS_ASM (CALL,       19, 2, {(*ip)++; fprintf(text_output, "%lf", code_bin->file_buffer_double[*ip]);})

DEF_COMMAND_DIS_ASM (PUSH,       1,  1, {                                               \
                                            (*ip)++;                                    \
                                            if (cmd_with_type & BITE_MEMORY)            \
                                            {                                           \
                                                fprintf (text_output, "[");             \
                                                DIS_ASM_PUSH_POP;                       \
                                                fprintf (text_output, "]");             \
                                            }                                           \
                                            else                                        \
                                            {                                           \
                                                DIS_ASM_PUSH_POP;                       \
                                            }                                           \
                                        })

DEF_COMMAND_DIS_ASM (POP,        7,  1, {                                               \
                                            (*ip)++;                                    \
                                            if (cmd_with_type & BITE_MEMORY)            \
                                            {                                           \
                                                fprintf (text_output, "[");             \
                                                DIS_ASM_PUSH_POP;                       \
                                                fprintf (text_output, "]");             \
                                            }                                           \
                                            else                                        \
                                            {                                           \
                                                DIS_ASM_PUSH_POP;                       \
                                            }                                           \
                                        })