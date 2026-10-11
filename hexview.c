#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void printline(unsigned long int offset, unsigned char *readbytes, size_t len);

int main(int argc, char* argv[]){
		
	if(argc != 2){
		printf("Enter a file name to be opened\n");
		return 1;	
	}
	
	if(strlen(argv[1]) <= 0 ){
		printf("Filename must be longer\n");
		return 1;	
	}
	
	unsigned char readbytes[16];
	size_t ret = 0;

	unsigned long int offset = 0;
		
	FILE *fptr = fopen(argv[1], "rb");
	if(fptr == NULL){
		printf("Unable to open file!\n");
		return 1;
	}
	
	printf("OFFSET  \tHEX BYTES \t\t\t\t\tASCII\n");
	
	while(1){
		ret = fread(readbytes,sizeof(unsigned char),(size_t)16,fptr);
		if (ret == 0)
		{
			break;
		}
		if(ret < 16){
			printline(offset,readbytes,ret);
			break;
		}
		printline(offset,readbytes,ret);
		offset = offset + ret;
	}
	if (ferror(fptr)) {
    	perror("Error reading file");
    	fclose(fptr);
    	return 1;
	}
	
	if (fclose(fptr) != 0)
	{
		perror("Error Closing File");
		return 1;
	}
	return 0;
}



void printline(unsigned long int offset, unsigned char *readbytes, size_t len){
	printf("%08lX\t",offset);

	if (len < 16)
	{
		for(size_t i = 0; i < len; i++){
			printf("%02X ",(unsigned int)readbytes[i]);	
		}
		for (size_t i = len; i < 16; i++)
		{
			printf("   ");
		}
		printf("\t");
		for (size_t i = 0; i < len; i++)
		{
			if (isprint(readbytes[i]))
			{
				printf("%c",readbytes[i]);
			}else
			{
				printf(".");
			}
		}
		

	}
	else
	{
		for(size_t i = 0; i < len; i++){
			printf("%02X ",(unsigned int)readbytes[i]);	
		}
		printf("\t");
		for (size_t i = 0; i < len; i++)
		{
			if (isprint(readbytes[i]))
			{
				printf("%c",readbytes[i]);
			}else
			{
				printf(".");
			}
		}
	}
	printf("\n");
}
