#pragma once
typedef double StackType;
struct Stack
{
	StackType cnrL;
	StackType *data;

	StackType cnrRbefore;
	StackType cnrLbefore;
	size_t    error; //size_t error;
	int       summBefore;
	int       summAfter;
	int       size;
	int       top;

	StackType cnrR;
};

enum ERRORS
{
	dataexit = 1 << 0,//1
	overflw = 1 << 1,//2
	minestop = 1 << 2,//4
	resizeind = 1 << 3//8
};
