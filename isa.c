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

    if (((size_t)byte) < sizeof(instruction_set) && ((unsigned int)byte) > 0)
    {
        for (size_t i = 0; i < sizeof(instruction_set); i++)
        {
            if (byte == instruction_set[i].opcode)
            {
                iptr = &instruction_set[i];
                return 1;
            }
        }
    }else
    {
        return 0;
    }
    return 2;
}
InstructionDef MnemonicLookup(char *instruction);