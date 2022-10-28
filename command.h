#define JMP_REALIZATION(ip) ip++; ip = cpu->text_info_cpu.file_buffer_double[ip] + 2;                                                                  

#define STACK_COMMAND &cpu->stack_command
#define STACK_MARK    &cpu->stack_mark

DEF_COMMAND (HTL,        0,  0, {cpu->cmd_bool = 0;})
DEF_COMMAND (PUSH,       1,  1, {double* argument = GetArgument(cpu); StackPush (STACK_COMMAND, *argument);})
DEF_COMMAND (ADD,        2,  0, {StackPush (STACK_COMMAND,     StackPop(STACK_COMMAND)  + StackPop(STACK_COMMAND));})
DEF_COMMAND (SUB,        3,  0, {StackPush (STACK_COMMAND,    -StackPop(STACK_COMMAND)  + StackPop(STACK_COMMAND));})
DEF_COMMAND (MUL,        4,  0, {StackPush (STACK_COMMAND,     StackPop(STACK_COMMAND)  * StackPop(STACK_COMMAND));})
DEF_COMMAND (DIV,        5,  0, {StackPush (STACK_COMMAND, (1./StackPop(STACK_COMMAND)) * StackPop(STACK_COMMAND));})
DEF_COMMAND (OUT,        6,  0, {printf    ("%lf\n", StackPop(STACK_COMMAND));})
DEF_COMMAND (POP,        7,  1, {double* argument = GetArgument(cpu); *argument = StackPop(STACK_COMMAND);})
DEF_COMMAND (JMP,        8,  2, {JMP_REALIZATION(cpu->ip);})
DEF_COMMAND (JB,         9,  2, {if (StackPop(STACK_COMMAND) >  StackPop (STACK_COMMAND)) {JMP_REALIZATION(cpu->ip);} else {cpu->ip++;}})
DEF_COMMAND (JBE,        10, 2, {if (StackPop(STACK_COMMAND) >= StackPop (STACK_COMMAND)) {JMP_REALIZATION(cpu->ip);} else {cpu->ip++;}})
DEF_COMMAND (JA,         11, 2, {if (StackPop(STACK_COMMAND) <  StackPop (STACK_COMMAND)) {JMP_REALIZATION(cpu->ip);} else {cpu->ip++;}})
DEF_COMMAND (JAE,        12, 2, {if (StackPop(STACK_COMMAND) <= StackPop (STACK_COMMAND)) {JMP_REALIZATION(cpu->ip);} else {cpu->ip++;}})
DEF_COMMAND (JE,         13, 2, {if (StackPop(STACK_COMMAND) == StackPop (STACK_COMMAND)) {JMP_REALIZATION(cpu->ip);} else {cpu->ip++;}})
DEF_COMMAND (JNE,        14, 2, {if (StackPop(STACK_COMMAND) != StackPop (STACK_COMMAND)) {JMP_REALIZATION(cpu->ip);} else {cpu->ip++;}})
DEF_COMMAND (DUMP,       15, 0, {CpuDump (cpu);})
DEF_COMMAND (IN,         16, 0, {double argument = 0; scanf ("%lf", &argument); StackPush (STACK_COMMAND, argument);})
DEF_COMMAND (SQRT,       17, 0, {StackPush (STACK_COMMAND, sqrt(StackPop(STACK_COMMAND)));})
DEF_COMMAND (OUTCHR,     18, 0, {printf("%c", (int)StackPop(STACK_COMMAND));})
DEF_COMMAND (CALL,       19, 2, {StackPush (STACK_MARK, cpu->ip+2); JMP_REALIZATION(cpu->ip);})
DEF_COMMAND (RET,        20, 0, {cpu->ip = StackPop(STACK_MARK) - 1;})
DEF_COMMAND (EMPTY,      21, 0, {for (int i = 0; i < RAM_SIZE; i++){cpu->ram[i] = 32;}})
DEF_COMMAND (OUT_SCREEN, 22, 0, {for (int i = 0; i < sqrt(RAM_SIZE); i++)                               \
                                    {                                                                   \
                                        for (int j = 0; j < sqrt(RAM_SIZE); j++)                        \
                                        {                                                               \
                                            printf ("%c", (int)cpu->ram[i*(int)sqrt(RAM_SIZE) + j]);    \
                                        }                                                               \
                                        printf ("\n");                                                  \
                                    }})
DEF_COMMAND (INT,    23, 0, {int argument = (int)StackPop (STACK_COMMAND); StackPush (STACK_COMMAND, argument);})
DEF_COMMAND (REMAIN, 24, 0, {   double divider = StackPop (STACK_COMMAND);          \
                                double divisible = StackPop (STACK_COMMAND);        \
                                double rezult = remainder (divisible, divider);     \
                                if (rezult != rezult)                               \
                                {                                                   \
                                    StackPush (STACK_COMMAND, 0);                   \
                                }                                                   \
                                else                                                \
                                {                                                   \
                                    if (rezult < 0)                                 \
                                    {                                               \
                                        rezult = fabs (rezult - 4);                 \
                                    }                                               \
                                    StackPush (STACK_COMMAND, rezult);              \
                                }                                                   \
                            })
DEF_COMMAND (SQR,    25, 0, {double argument = StackPop (STACK_COMMAND); StackPush (STACK_COMMAND, pow (argument, 2));})

DEF_REG (RAX, 1)
DEF_REG (RBX, 2)
DEF_REG (RCX, 3)
DEF_REG (RDX, 4)
DEF_REG (RFX, 5)
DEF_REG (REX, 6)