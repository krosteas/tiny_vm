#include <stdio.h>
#include "isa.h"

int disass(FILE* fptr,unsigned char byte, unsigned int *offset,InstructionDef *currentInstruction);

int main(int argc, char* argv[]){

    if(argc != 2){
        printf("Must provide a single filename\n");
        return 1;
    }

    unsigned char byte;
    FILE* fptr;
    unsigned int offset = 0;
    size_t ret;
    int result = 0;
    InstructionDef currentinstruction;

    fptr = fopen(argv[1],"rb");

    if(!fptr){
        perror("Unable to open file\n");
        return 1;
    }

    printf("OFFSET\tBYTES\tINSTRUCTION\n");

    while (1)
    {
        ret = fread(&byte,1,1,fptr);

        if(ret == 0){
            break;
        }
        result = disass(fptr,byte,&offset,&currentinstruction);
        if(result == 0){
                if (fclose(fptr) != 0)
                    {
                        perror("unable to close the file\n");
                    }
                return 1;
        }else if (result == 2)
        {
            break;
        }
        offset++;
    }

    if (result != 2)
    {
        printf("HALT not encountered\n");
        if (fclose(fptr) != 0)
        {
            perror("unable to close the file\n");
            return 1;
        }
        return 1;
    }
    

    if (fclose(fptr) != 0)
    {
        perror("unable to close the file\n");
        return 1;
    }
    
    return 0;
}

int disass(FILE* fptr,unsigned char byte, unsigned int* offset,InstructionDef *currentInstruction){
    unsigned char operand;
    int ret;

    ret = OpcodeLookup(byte,currentInstruction);
    if (ret == 0)
    {
        printf("Invalid Opcode\n");
        return 0;
    }
    
    if (currentInstruction->operand_count == 0)
    {
        if (currentInstruction->opcode == 0xFF)
        {
            printf("%08X %02X   \tHALT\n",*offset,(unsigned int)byte);
            if(fread(&operand,1,1,fptr) == 1){
                    printf("Trailing Data Found After HALT!\n");
                    return 0;
            }
            return 2;
        }
        printf("%08X %02X   \t%s\n",*offset,(unsigned int)currentInstruction->opcode,currentInstruction->mnemonic);
        return 1;
    }else if (currentInstruction->operand_count == 1)
    {
        if(fread(&operand,1,1,fptr) != 1){
            printf("%08X %02X   \t%s MISSING OPERAND\n",*offset,(unsigned int)currentInstruction->opcode,currentInstruction->mnemonic);
            return 0;
        }
        printf("%08X %02X %02X\t%s %d\n",*offset,(unsigned int)currentInstruction->opcode,(unsigned int)operand,currentInstruction->mnemonic,(unsigned int)operand);
        (*offset)++;
        return 1;
    }else
    {
        printf("Invalid amount of operands!\n");
        return 0;
    }
    
    /*
    switch (byte)
    {
    case 0x01:
        if(fread(&operand,1,1,fptr) != 1){
                printf("%08X %02X   \tMOVI MISSING OPERAND\n",*offset,(unsigned int)byte);
                return 0;
        }
        printf("%08X %02X %02X\tMOVI %d\n",*offset,(unsigned int)byte,(unsigned int)operand,(unsigned int)operand);
        (*offset)++;
        return 1;

    case 0x02:
        printf("%08X %02X   \tADD\n",*offset,(unsigned int)byte);
        return 1;

    case 0x03:
        printf("%08X %02X   \tSUB\n",*offset,(unsigned int)byte);
        return 1;

    case 0x04:
        printf("%08X %02X   \tPRINT\n",*offset,(unsigned int)byte);
        return 1;

    case 0xFF:
        printf("%08X %02X   \tHALT\n",*offset,(unsigned int)byte);
        if(fread(&operand,1,1,fptr) == 1){
                printf("Trailing Data Found After HALT!\n");
                return 0;
        }
        return 2;

    default:
        printf("%08X %02X   \tUnknown Opcode\n",*offset,(unsigned int)byte);
        return 0;
    }
    */
}