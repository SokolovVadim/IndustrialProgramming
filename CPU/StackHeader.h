#pragma once
#include <iostream>
#include <cstdio>
#include <math.h>
#include <cassert>
#include <cstdlib>


typedef double StackType;
struct Stack
{
	StackType CANARYL;

	StackType *data;
	StackType CANARYRbefore;
	StackType CANARYLbefore;
	size_t    error; 
	int       summStackBefore;
	int       summStackAfter;
	int       summBefore;
	int       summAfter;
	int       size;
	int       top;
	StackType *regs;
	StackType CANARYR;
};


struct Labels
{
	int label;
	char* descr;
};

typedef double StackTypeForRets;

struct StackForRets
{
	StackType CANARYL;
	StackTypeForRets *data;
	StackType CANARYRbefore;
	StackType CANARYLbefore;
	size_t    error;
	int       summStackBefore;
	int       summStackAfter;
	int       summBefore;
	int       summAfter;
	int       size;
	int       top;
	StackType CANARYR;
};

enum SIZES
{
	RAMSIZE = 100,
	REGSSIZE = 8
};

struct RAM
{
	int addr[100];
};


enum ERRORS
{
	dataexit   = 1 << 0,
	overflw    = 1 << 1,
	minestop   = 1 << 2,
	resizeind  = 1 << 3,
	hasherr    = 1 << 4
};

static int POISON = 1534029;
static int ERRORSIZE = 5;
static int HASHDIV = 131;
static int CNRDIFF = 2;
static StackType CANARYLDIGIT = 43.9;
static StackType CANARYRDIGIT = 2017.9;

FILE* Ferr = nullptr;
FILE* Fin =  nullptr;
FILE* Fout = nullptr;
FILE* Cpuout = nullptr;
FILE* Bin =  nullptr;
FILE* Log = nullptr;

void ConstructStack(Stack* stack);
void DestructStack(Stack* stack);
void FopenError(Stack* stack);
void dump(Stack* stack);
void PrintErr(Stack* stack);
void Resize(Stack* stack, int size);
void PrintOk(Stack* stack);
void PrintHash(Stack* stack);

void FileOpen();

StackType Push (Stack *stack, StackType digit);
StackType Pop  (Stack *stack);
StackType Back (Stack *stack);
StackType Add  (Stack *stack);
int Hash(Stack *stack);
int ForHash(Stack *stack, int size);
int Size(Stack *stack);

bool Clear(Stack *stack);
bool ExitData(Stack *stack);
bool StackOk(Stack *stack);
