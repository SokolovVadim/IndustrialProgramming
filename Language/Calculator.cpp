#include <iostream>
#include <cassert>


#ifndef ASSERT
#define ASSERT( BUFF )                                           \
	 do {                                                        \
	     if(!BUFF)                                               \
         {                                                       \
              fprintf(Log, "Warning! " #BUFF " is NULL\n");      \
              exit(EXIT_FAILURE);                                \
		 }                                                       \
	 } while(0)
#endif

FILE* Fin = nullptr;
FILE* Fout = nullptr;
FILE* Log = nullptr;


const int POISON = 718;

void OpenFiles();
long Size();
char** Read(long size);
int GetNumber(char** buff);
int GetExept(char** buff);
bool Grammar(char** buff);
int GetMul(char** buff);


bool Calc(char** buff);

int main()
{
	OpenFiles();
	char* buff = *Read(Size());
	//fprintf(Fout, "buff: %s\n", buff);
	Calc(&buff);
	//Free();
}

void OpenFiles()
{
	fopen_s(&Fin, "INPUT.txt", "r");
	fopen_s(&Fout, "OUTPUT.txt", "w");
	fopen_s(&Log, "LOGS.txt", "w");
	if (Log == nullptr)
	{
		exit(EXIT_FAILURE);
	}
}


char** Read(long size)
{
	assert(size != POISON);
	char* buff;
	char* pointer = (char *)calloc(size, sizeof(char));

	if (pointer == nullptr)
	{
		fprintf(Log, "WARNING! Buff was not declared!\n");
		return 0;
	}

	else
	{
		buff = pointer;
		fread(buff, sizeof(char), size, Fin);
	}
	ASSERT(buff);
	return &buff;// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

long Size()
{
	assert(Fin);
	fseek(Fin, NULL, SEEK_END);


	long size(ftell(Fin));
	size++;

	fseek(Fin, NULL, SEEK_SET);
	return size;
}

bool Calc(char** buff)
{
	ASSERT(*buff);
	Grammar(buff);
	//fprintf(Fout, "GetExept = %d\n", GetExept(buff));




	return 0;
}

int GetNumber(char** buff)
{
	ASSERT(*buff);
	int counter(0);
	int value(0);
	while ((**buff <= '9') && (**buff >= '0'))
	{
		value = value * 10 + **buff - '0';
		(*buff)++;
		counter++;
	}
	if(counter)
		(*buff)++;// avoid space
	fprintf(Log, "GetNumber value: %d\n", value);
	return value;
}




int GetMul(char** buff)
{
	int value = GetNumber(buff);
	while ((**buff == '*') || (**buff == '/'))
	{
		char operand = **buff;
		(*buff)++;
		(*buff)++;
		int newvalue = GetNumber(buff);
		if (operand == '*')
			value *= newvalue;
		else
			value /= newvalue;
	}
	fprintf(Log, "GetMul: value = %d\n", value);
	return value;
}


int GetExept(char** buff)
{
	ASSERT(*buff);
	//int value = GetNumber(buff);
	int value = GetMul(buff);
	fprintf(Log, "GetExept value = %d buff[i] = %c\n", value, **buff);
	while ((**buff == '+') || (**buff == '-'))
	{
		char operand = **buff;
		(*buff)++;
		(*buff)++;
		int newvalue = GetMul(buff);
		if (!newvalue)
			newvalue = GetNumber(buff);
		if (operand == '+')
			value += newvalue;
		else
			value -= newvalue;
	}
	fprintf(Log, "GetExept End: value = %d\n", value);
	return value;
}


bool Grammar(char** buff)
{
	ASSERT(*buff);
	int exept(0);
	while (*(*buff - 2) != '\0')// difference between increment after GetNum
	{
		exept = GetExept(buff);
		fprintf(Log, "Simbol = %c\n", **buff);
		(*buff)++;
	}
	fprintf(Fout, "GetExept = %d\n", exept);
	return true;
}


//int GetExept(char** buff)
//{
//	int value = GetNumber(buff);
//	(*buff)++;// avoid space
//	do
//	{
//		char operand = **buff;
//		//fprintf(Log, "value = %d\n", value);
//		//fprintf(Log, "Operand = %c\n", operand);
//		(*buff)++;
//		(*buff)++;
//		int newvalue = GetNumber(buff);
//		//fprintf(Log, "newvalue = %d\n", newvalue);
//		if (operand == '+')
//			value += newvalue;
//		else
//			value -= newvalue;
//		(*buff)++;// avoid space
//	} while ((**buff == '+') || (**buff == '-'));
//	//fprintf(Log, "summ = %d\n", (value));
//	return value;
//}