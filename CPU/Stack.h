#pragma once
#include "StackHeader.h"

void ConstructStack(Stack* stack)///
{
	assert(stack != nullptr);
	stack->size = POISON;
	fscanf_s(Fin, "%d", &stack->size);

	if (stack->size == POISON)
	{
		fprintf(Fout, "WARNING! size was not declared\n"
			"Please, scanf size again!");
		fscanf_s(Fin, "%d", &stack->size);
	}

	stack->size += CNRDIFF;// for canaries

	stack->CANARYL = CANARYLDIGIT;
	stack->top = CNRDIFF - 1;
	StackType*pdata = (StackType*)calloc(stack->size, sizeof(StackType));
	if (pdata)
	{
		stack->data = pdata;
	}
	else
	{
		fprintf(Fout, "WARNING! data memory was not allocated\n"
			"Resize was called\n");
	}
	assert(stack->data);


	//for (int counter(0); counter < 4; counter++)
	//{
	//	stack->regs[counter] = StackType(0.0);
	//}



	stack->data[0] = CANARYLDIGIT;
	stack->data[stack->size - 1] = CANARYRDIGIT;
	stack->CANARYLbefore = CANARYLDIGIT;
	stack->CANARYRbefore = CANARYRDIGIT;// 

	stack->CANARYR = CANARYRDIGIT;
	stack->CANARYL = CANARYLDIGIT;

	stack->summAfter = 0;
	stack->summBefore = 0;
	stack->summStackBefore = 0;
	stack->summStackAfter = 0;
}



void FileOpen()
{
	if ((Fin == nullptr) && (Fout == nullptr))
	{
		fopen_s(&Fin, "INPUT.txt", "rb");
		fopen_s(&Fout, "OUTPUT.txt", "w");

	}
	else
	{
		return;
	}
	assert((Fin) && (Fout));
}

#pragma warning (push)
#pragma warning (disable: 6011)

void FopenError(Stack* stack)
{
	if (stack == nullptr)
	{
		return;
	}
	stack->summBefore = 0;

	fopen_s(&Ferr, "ERRORLIST.txt", "w");
	assert(Ferr);
}


StackType Push(Stack *stack, StackType digit)
{

	if (stack == nullptr)
	{
		return -1;
	}
	if (stack->top < CNRDIFF - 1)//
	{
		fprintf(Fout, "WARNING! top index is less than 0\n");
		return -1;
	}
	else
	{
		if (stack->top > stack->size - 1)//
		{
			fprintf(Fout, "WARNING! top index is large than size\n");
			dump(stack);
			return -1;
		}
		else
		{
			stack->data[stack->top++] = digit;
			fprintf(Fout, "\nPush was called!\n"
				"New value: %lg\n", stack->data[stack->top - 1]);
			return stack->data[stack->top - 1];
		}
	}
}



StackType Pop(Stack *stack)
{
	if (stack == nullptr)
	{
		return -1;
	}
	if (stack->top > stack->size - 1)//
	{
		fprintf(Fout, "WARNING! top index is large than size\n"
			"Line: %ld\n", __LINE__);
		dump(stack);
		PrintErr(stack);
	}
	if (stack->top < 1)//
	{
		fprintf(Fout, "WARNING! top index is less than 0\n");
		dump(stack);
		PrintErr(stack);
	}
	stack->top--;
	return stack->data[(stack->top)];
}


//++++++++++++++++++++++++++++++++++++++++++++++//
//! @brief This function returns latest element 
//!        and does not change top element      
//++++++++++++++++++++++++++++++++++++++++++++++//


StackType Back(Stack *stack)
{
	if (stack == nullptr)
	{
		return -1;
	}
	dump(stack);
	if (stack->top < 1)//
	{
		fprintf(Fout, "Stack is empty\n"
			"Line: %ld\n", __LINE__);
		return -1;
	}
	else
	{
		return stack->data[(stack->top) -1];
	}
}



int Size(Stack *stack)
{
	if (stack == nullptr)
	{
		return -1;
	}
	StackOk(stack);
	assert(stack->size > CNRDIFF);
	fprintf(Fout, "Stack size is: %d\n", stack->size - 2);// without canaries
	return stack->size;
}


bool Clear(Stack *stack)
{
	if (stack == nullptr)
	{
		return false;
	}
	dump(stack);
	free(stack->data);
	stack->size = 0;

	if (stack->data == nullptr)
	{
		fprintf(Fout, "Stack was cleared\n");
		dump(stack);
		return true;
	}
	else
		return false;
}



void Resize(Stack* stack, int size)
{
	assert(stack);
	stack->top = CNRDIFF - 1;
	stack -> size = size;
	//fscanf_s(Fin, "%d", &stack->size);
	if (stack->size < CNRDIFF - 1)
	{
		fprintf(Fout, "Warning! Function: %s Line: %ld"
			"\n Resize is incorrect", __FUNCSIG__, __LINE__);
		//fscanf_s(Fin, "%d", &stack->size);
	}
	stack->size += CNRDIFF;// for two canaries
	void* pointer = realloc(stack->data, stack->size * sizeof(StackType));
	if (pointer)
	{
		stack->data = (StackType*)pointer;
	}
	else
	{
		fprintf(Fout, "Warning!"
			"Function: %s \nLine: %ld\nResize works incorrect!\n"
			"Data pointer was not realloced", __FUNCSIG__, __LINE__);
	}
	if (stack->data <= 0)
	{
		fprintf(Fout, "Warning! Resize killed your stack!\n"
			"Line: %ld", __LINE__);
		dump(stack);
		PrintErr(stack);
	}

	stack->error = stack->error | resizeind;
	stack->CANARYLbefore = CANARYLDIGIT;
	stack->CANARYRbefore = CANARYRDIGIT;
	stack->data[0] = CANARYLDIGIT;
	stack->data[stack->size - 1] = CANARYRDIGIT;
	StackOk(stack);
}


StackType Add(Stack *stack)
{

	if (stack == nullptr)
	{
		return -1;
	}
	if (stack->top > stack->size - 1)//
	{
		fprintf(Fout, "WARNING! top index is large than size\n"
			"Line: %ld\n", __LINE__);
		dump(stack);
		PrintErr(stack);
	}
	if (stack->top < 1)//
	{
		fprintf(Fout, "WARNING! top index is less than 0\n");
		dump(stack);
		PrintErr(stack);
	}
	Push(stack, Pop(stack) + Pop(stack));
	return Back(stack);
}


//++++++++++++++++++++++++++++++++++++++++++++//
//! @brief This function makes "canary test"  
//!        If right side of data was changed, 
//!        canary has been killed      
//! @param CANARYR
//! @param CANARYL
//++++++++++++++++++++++++++++++++++++++++++++//

bool ExitData(Stack *stack)
{
	if (stack == nullptr)
	{
		return false;
	}
	if (stack->CANARYR != CANARYRDIGIT)
	{
		fprintf(Fout, "Warning! Right canary was killed!\n");
		fprintf(Ferr, "Error code: canary\n");
		return false;
	}
	if (stack->CANARYL != CANARYLDIGIT)
	{
		fprintf(Fout, "Warning! Right canary was killed!\n");
		fprintf(Ferr, "Error code: canary\n");
		return false;
	}

	stack->CANARYL = CANARYLDIGIT;
	stack->CANARYR = CANARYRDIGIT;

	return true;
}

//PlayKotik


//++++++++++++++++++++++++++++++++++++++++++++//
//! @brief This function makes "hash test"    
//!        and prints error code after dump 
//! @param summBefore
//! @param summAfter
//++++++++++++++++++++++++++++++++++++++++++++//



int Hash(Stack *stack)
{
	if (stack == nullptr)
	{
		return -1;
	}
	if ((stack->top > 0) && (stack->top < stack->size))
	{
		ForHash(stack, sizeof(StackType));
	}
	else
	{
		stack->error = stack->error | hasherr;
		return -1;
	}
	stack->summAfter %= HASHDIV;
	return int(stack->summAfter);
}


int ForHash(Stack *stack, int size)
{
	/*stack->summStackBefore = 0;*/
	for (int counter(0); counter < (stack->top - 1) * size; counter++)
	{
		stack->summAfter += ((char *)(stack->data))[counter];//
	}
	/*int diff = &(stack->CANARYR) - &(stack->CANARYL);*/
	/*fprintf(Ferr, "%d\n", diff);*/
	return 1;
}


void PrintHash(Stack *stack)
{
	if (stack == nullptr)
	{
		return;
	}
	fprintf(Fout, "Hash was called!\n");
	int hashsumm = Hash(stack);
	if ((hashsumm != stack->summBefore) || (stack->error & hasherr))
	{
		fprintf(Fout, "Stack status: Error!\n");
		dump(stack);
		PrintErr(stack);
	}
	stack->summBefore = hashsumm;
}

//#pragma warning (push)
//#pragma warning (disable: 6011)

void dump(Stack *stack)
{
	fprintf(Fout, "DUMP:\n");
	if (stack == nullptr)
	{
		fprintf(Fout, "Stack status: NULL\n");
	}
	else
	{
		if (stack->data == nullptr)
		{
			fprintf(Fout, "Array data status: NULL\n");
			stack->error = stack->error | dataexit;//
		}
		else
		{
			for (short counter(0); counter < stack->top; ++counter)
			{
				fprintf(Fout, "\tdata[%d]=%lg\n", counter, stack->data[counter]);
			}
			fprintf(Fout, "Array data status: OK\n");
			if (stack->top < stack->size)
			{
				fprintf(Fout, "Stack is not overflowing\n");
			}
			else
			{
				stack->error = stack->error | overflw;
				fprintf(Fout, "Warning! Stack is overflowing!\n");
			}
			if (stack->top > 0)
			{
				fprintf(Fout, "Stack is not empty!\n");
			}
			else
			{
				stack->error = stack->error | minestop;
				fprintf(Fout, "Warning! Stack is empty!\n");
			}
		}
	}
}
//#pragma warning (pop)

//++++++++++++++++++++++++++++++++++++++++++++++++//
//! @brief This function print numbers of errors
//!        into Errorfile from array with error
//!        parameter flag save true if there were
//!        no mistakes
//! @param flag
//++++++++++++++++++++++++++++++++++++++++++++++++//

void PrintErr(Stack* stack)
{
	if (stack == nullptr)
	{
		fprintf(Fout, "Stack status: NULL\n");
		return;
	}
	bool flag(true);
	for (short counter(0); counter < ERRORSIZE; counter++)
	{
		if ((stack->error)&(1 << counter))
		{
			fprintf(Ferr, "Error code: %d\n", counter);
			flag = false;
		}
	}
	if (flag)
		fprintf(Ferr, "Status: OK\n");
}




//++++++++++++++++++++++++++++++++++++++++++++++++//
//! @brief This function calls dump if there were
//!        mistakes
//++++++++++++++++++++++++++++++++++++++++++++++++//


bool StackOk(Stack* stack)
{
	if (stack == nullptr)
	{
		fprintf(Fout, "Stack == nullptr!\n");
		return false;
	}
	else
	{
		if (stack->data == nullptr)
		{
			dump(stack);
			return false;
		}
		else
		{
			if (stack->top >= stack->size)
			{
				dump(stack);
				return false;
			}
			else
			{
				if (stack->top < 0)
				{
					dump(stack);
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}
}


void PrintOk(Stack* stack)
{
	if (stack == nullptr)
	{
		fprintf(Fout, "Stack status: NULL\n");
		return;
	}
	if (StackOk(stack))
	{
		fprintf(Fout, "Stack status: ok");
		dump(stack);
	}
	else
		fprintf(Fout, "Stack status: error!");
}


void DestructStack(Stack* stack)
{
	if (stack == nullptr)
	{
		fprintf(Fout, "Stack status: NULL\n");
		return;
	}
	if (stack->error & resizeind)
	{
		fprintf(Fout, "Resize was used before destruct was called!\n");
	}
	else
	{
		if (stack->data <= nullptr)
		{
			fprintf(Fout, "A destructor was called\nStatus: free(data)\n");
		}
		else
		{
			free(stack->data);
		}
	}
	fprintf(Fout, "A destructor was called\nStatus: free(data)\n");
	fclose(Fin);
	fclose(Fout);
	fclose(Ferr);
}
