#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "Commands.h"

const int SIZEBUFF(20);

FILE* Ferr = nullptr;
FILE* Fin = nullptr;
FILE* Fout = nullptr;
FILE* Disout = nullptr;
FILE* Bin = nullptr;
FILE* Log = nullptr;

const int POISON = 718;

void      Disasm(int size, char** buff);
long      Size();
char*     Read(long size);
double    GetDouble(char** buff);
int       GetInt(char** buff);
int       Ctoi(char** buff);
void      FopenFiles();

#ifndef ASSERT
#define ASSERT( BUFF )                                 \
	 do {                                                        \
	     if(!BUFF)                                               \
         {                                                       \
              fprintf(Ferr, "Warning! " #BUFF " is NULL\n");      \
              exit(EXIT_FAILURE);                                \
		 }                                                       \
	 } while(0)
#endif


int main()
{


	FopenFiles();

	long sizebuff = Size();
	char *buff = Read(sizebuff);




	Disasm(sizebuff, &buff);
}


void FopenFiles()
{
	fopen_s(&Fin, "INPUT.txt", "rb");
	fopen_s(&Fout, "OUTPUT.txt", "w");
	fopen_s(&Log, "LOG.txt", "w");
	fopen_s(&Disout, "DISASMOUT.txt", "w");
	fopen_s(&Bin, "BINOUT.txt", "rb");
}


char* Read(long size)
{
	assert(size != POISON);
	char* buff = (char *)calloc(size, sizeof(char));

	fread(buff, sizeof(char), size, Bin);

	return buff;
}

long Size()
{
	assert(Bin);
	fseek(Bin, NULL, SEEK_END);


	long size(ftell(Bin));
	size++;

	fseek(Bin, NULL, SEEK_SET);
	fprintf(Fout, "SIZEBUFF: %d\n", size);
	return size;
}


void Disasm(int size, char** buff)
{
	ASSERT(*buff);
	int counter(0);

#define CASE(NUM, COMMAND)                 \
       case NUM:                           \
       {                                   \
		    COMMAND;                       \
            break;                         \
	   }

	char *pointer = (*buff);

	while (counter < size)
	{
		fprintf(Log, "elem[%d] = %d\n", counter, Ctoi(buff));
		switch (**buff)
		{
			CASE(cmd_begin, fprintf(Disout, "begin "); (*buff)++; counter++;
			if ((**buff) != cmd_VS)
			{
				fprintf(Ferr, "You are not Vadim! Please, go away!\n counter = %d", counter);
				assert(0);///!!!!!!!!!!!!!!!!!!!
				break;
			}
			else
			{
				(*buff)++;
				fprintf(Disout, "VS %d\n", int(**buff));
				counter += 2;
			})
		    case cmd_call:
			{
				counter += sizeof(int);

				int jump = GetInt(buff);


				fprintf(Disout, "call %d counter %d diff %d\n", jump, counter, (*buff) - pointer);
				
				break;
			}


			CASE(cmd_ret, fprintf(Disout, "ret\n");)

			//(*buff)--;

		    //CASE(cmd_label, counter += sizeof(int); fprintf(Disout, ": %d\n", GetInt(buff));)
		    CASE(cmd_pushi, fprintf(Disout, "push %d\n",  GetInt(buff));  counter += sizeof(int);)
			CASE(cmd_pushd, fprintf(Disout, "push %lf\n", GetDouble(buff));  counter += sizeof(double);)
			CASE(cmd_pushr, (*buff)++; counter++;  fprintf(Disout, "push %cx\n", char('a' + Ctoi(buff)));)
			CASE(cmd_jmp, int jump = GetInt(buff); fprintf(Disout, "jmp %d\n", jump);
			counter += sizeof(int);)

			CASE(cmd_fsqrt,  fprintf(Disout, "fsqrt\n");)
		    CASE(cmd_pop,    fprintf(Disout, "pop\n");)
			CASE(cmd_add,    fprintf(Disout, "add\n");)
			CASE(cmd_sub,    fprintf(Disout, "sub\n");)
			CASE(cmd_div,    fprintf(Disout, "div\n");)
			CASE(cmd_mul,    fprintf(Disout, "mul\n");)
			CASE(cmd_back,   fprintf(Disout, "back\n");)
			CASE(cmd_size,   fprintf(Disout, "size\n");)
			CASE(cmd_clear,  fprintf(Disout, "clear\n");)
			CASE(cmd_end, fprintf(Disout, "end\n"); )
			CASE(cmd_popr, (*buff)++; counter++;  fprintf(Disout, "pop %cx\n", char('a' + Ctoi(buff)));)
		CASE(cmd_resize, int ressize = GetInt(buff); fprintf(Disout, "resize %d\n", ressize);
		counter += sizeof(int);)
		CASE(cmd_jxx, int jump = GetInt(buff); fprintf(Disout, "jxx %d\n", jump);
		counter += sizeof(int);)
		};

		counter++;
		(*buff)++;
	}
	fprintf(Fout, "SizeWhile: %d\n", counter);
}

double GetDouble(char** buff)
{
	ASSERT(*buff);

	double digit = 0.0;
	fprintf(Log, "Ctoi = %d\n", Ctoi(buff));
	(*buff)++;
	memcpy_s(&digit, sizeof(double), *buff, sizeof(double));// byte atod
	(*buff) += sizeof(double) - 1;
	fprintf(Log, "Ctoi = %d\n", Ctoi(buff));

	return digit;
}

int GetInt(char** buff)
{
	ASSERT(*buff);
	int digit = 0;
	(*buff)++;
	memcpy_s(&digit, sizeof(int), *buff, sizeof(int));
	(*buff) += 3;///!!!!!!

	return digit;
}



int Ctoi(char** buff)
{
	ASSERT(*buff);
	return ((**buff) / 16) * 16 + (**buff - (**buff) / 16);
}


