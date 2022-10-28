#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "common.h"
#include "/Users/kirilllahnov/Documents/CPU/enum.h"

int MarkFind (struct AsmCodeCreater* code_info);

int CmdArrayCreater (struct AsmCodeCreater* code_info);

int RegistrArgument (struct AsmCodeCreater* code_info);

int GetPushPopArgument (struct AsmCodeCreater* code_info);

int GetJmpArgument (struct AsmCodeCreater* code_info);

int CommandCmp (struct AsmCodeCreater* code_info);

void FileCodeCmd (struct AsmCodeCreater* code_info);

#endif // ASM_H