#ifndef ISA_H
#define ISA_H

typedef struct {
    unsigned char opcode;
    const char *mnemonic;
    unsigned int operand_count;
} InstructionDef;

int OpcodeLookup(unsigned char byte, InstructionDef* iptr);
InstructionDef MnemonicLookup(char *instruction);

#endif