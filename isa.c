#include <stdio.h>
#include <string.h>
#include "isa.h"


static const InstructionDef instruction_set[] = {
    {0x01, "MOVI",  1},
    {0x02, "ADD",   0},
    {0x03, "SUB",   0},
    {0x04, "PRINT", 0},
    {0xFF, "HALT",  0}
};

int OpcodeLookup(unsigned char byte, InstructionDef* iptr){

    for (size_t i = 0; i < sizeof(instruction_set) / sizeof(instruction_set[0]); i++)
    {
        if (byte == instruction_set[i].opcode)
        {
            *iptr = instruction_set[i];
            return 1;
        }
    }
    return 0;
}
InstructionDef MnemonicLookup(char *instruction);