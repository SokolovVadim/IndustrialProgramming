 #include "Stack.h"
 #include "Commands.h"

 const int  SIZEBUFF(20);
 // 666 means 0 solutions
 // 718 means inf

 void       CPU             (int size, char** buff, Stack* stack,
	                        Labels* labels, Stack* stackrets);
 long       Sizebuff        ();
 char*      Read            (long size);
 double     GetDouble       (char** buff);
 int        GetInt          (char** buff);
 int        Ctoi            (char** buff);
 void       FopenFiles      ();
 void       PrintRegs       (Stack* stack);
 StackType  Add             (Stack *stack);
 void       Free            (char* buff, Labels* label);
 Labels*    ConstructLabels (Labels *labeltool);
 StackType* ConstructRegs   (Stack * stackrets);

 #ifndef ASSERT
 #define ASSERT( BUFF )                                          \
	 do {                                                        \
	     if(!BUFF)                                               \
         {                                                       \
              fprintf(Ferr, "Warning! " #BUFF " is NULL\n");     \
              exit(EXIT_FAILURE);                                \
		 }                                                       \
	 } while(0)
 #endif



 const int SIZELABEL = 1000;


 int main()
 {
	 Stack           StackTool = {};
	 FopenFiles      ();
	 FopenError      (&StackTool);
	 ConstructStack  (&StackTool);
	 //Push            (&StackTool, 12.133);
	 //Push            (&StackTool, 12.134);
	 //Push            (&StackTool, 12.135);
	 //Push            (&StackTool, 12.136);


	 long            sizebuff = Sizebuff();
	 char            *buff = Read(sizebuff);

	 Labels *        LabelsTool = {};
	 LabelsTool =    ConstructLabels(LabelsTool);
	 Stack           StackRetsTool = {};
	 ConstructStack  (&StackRetsTool);
	 ConstructRegs   (&StackTool);
	 CPU(sizebuff, &buff, &StackTool, LabelsTool, &StackRetsTool);

	 dump            (&StackTool);

	 fprintf(Fout, "StackRets:\n");

	 dump(&StackRetsTool);
	 PrintRegs(&StackTool);
	 //system("pause");
	 //Free(buff, &LabelTool);
	 DestructStack(&StackTool);
 }



 Labels* ConstructLabels(Labels *labeltool)
 {
	 Labels* labels = (Labels*)calloc(SIZELABEL, sizeof(*labels));
	 labels[0].label = 0;
	 fprintf(Log, "%d", labels[0].label);
	 labeltool = labels;
	 return labeltool;
 }



 StackType* ConstructRegs(Stack * stack)
 {
	 StackType *regs = (StackType *)calloc(REGSSIZE, sizeof(StackType));
	 ASSERT(regs);
	 stack->regs = regs;
	 return regs;
 }


 void FopenFiles()
 {
	 fopen_s(&Fin,   "INPUT.txt",  "rb");
	 fopen_s(&Fout,  "OUTPUT.txt",  "w");
	 fopen_s(&Log, "LOG.txt", "w");
	 fopen_s(&Cpuout, "CPUOUT.txt", "w");
	 //fopen_s(&Ferr, "ERRORLIST.txt", "w");
	 fopen_s(&Bin,   "BINOUT.txt", "rb");
	 //asssert
 }



 char* Read(long size)
 {
	 assert(size != POISON);
	 char* buff = (char *)calloc(size, sizeof(char));

	 fread(buff, sizeof(char), size, Bin);

	 return buff;
 }

 long Sizebuff()
 {
	 assert(Bin);
	 fseek(Bin, NULL, SEEK_END);
	 

	 long size(ftell(Bin));
	 size++;

	 fseek(Bin, NULL, SEEK_SET);
	 fprintf(Fout, "SIZEBUFF: %d\n", size);
	 return size;
 }

 
 void CPU(int size, char** buff, Stack* stack,
	 Labels* labels, Stack* stackrets)
 {
	 ASSERT(*buff);
	 //char buffer[SIZEBUFF];
	 int counter(0);
	 //int diff(0);
	// fprintf(Disout, "buff: %s\n", *buff);

#define CASE(NUM, COMMAND)                 \
       case NUM:                           \
       {                                   \
		    COMMAND;                       \
            break;                         \
	   }
	 //int* labels = (int*)calloc(SIZELABEL, sizeof(int));
	 //
	 //for (int i(0); i < SIZELABEL; ++i)
	 //{
		// labels[i] = -1;
	 //}
	 char *pointer = (*buff);
	 while (counter < size)/////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 {
		 //fprintf(Log, "elem[%d] = %d\n", counter, Ctoi(buff));
		 switch (**buff)
		 {
			 CASE(cmd_begin, fprintf(Cpuout, "begin "); (*buff)++; counter++;
			 if ((**buff) != cmd_VS)
			 {
				 fprintf(Ferr, "You are not Vadim! Please, go away!\n counter = %d", counter);
				 assert(0);///!!!!!!!!!!!!!!!!!!!
				 break;
			 }
			 else
			 {
				 (*buff)++;
				 fprintf(Cpuout, "VS %d\n", int(**buff));
				 counter += 2;
			 })

			 CASE(cmd_pushi, int value = GetInt(buff); Push(stack, StackType(value));
			 fprintf(Cpuout, "push %d\n", value); counter += sizeof(int);)

			 CASE(cmd_pushd, double value = GetDouble(buff); Push(stack, StackType(value));
			 fprintf(Cpuout, "push %lf\n", value); counter += sizeof(double);)
			 
		     CASE(cmd_pushr, (*buff)++; counter++;  fprintf(Cpuout, "push %cx\n", char('a' + Ctoi(buff)));
			 Push(stack, stack->regs[Ctoi(buff)]);)
		
			 case cmd_call:
			 {
				 counter += sizeof(int);

				 int jump = GetInt(buff);
				 
				 Push(stackrets, (*buff) - pointer);// Push after GetInt? - Y

				 fprintf(Cpuout, "call %d counter %d diff %d\n", jump, counter, (*buff) - pointer);
				 (*buff) -= (jump + sizeof(int) + 1);
				 counter -= (jump + sizeof(int) + 2);
				 break;
			 }


			CASE(cmd_pop,   Pop(stack);    fprintf(Cpuout, "pop\n");)
			CASE(cmd_add,   Push(stack, StackType(Pop(stack) + Pop(stack)));  fprintf(Cpuout, "add\n");)
			CASE(cmd_fsqrt, Push(stack, StackType(sqrt(Pop(stack))));         fprintf(Cpuout, "fsqrt\n");)
			CASE(cmd_sub,   Push(stack, StackType(Pop(stack) - Pop(stack)));  fprintf(Cpuout, "sub\n");)
			CASE(cmd_div,   Push(stack, StackType(Pop(stack) / Pop(stack)));  fprintf(Cpuout, "div\n");)
			CASE(cmd_mul,   Push(stack, StackType(Pop(stack) * Pop(stack)));  fprintf(Cpuout, "mul\n");)
			CASE(cmd_back,  Back(stack);   fprintf(Cpuout, "back\n");)

			CASE(cmd_ret,   int digitpop = (int)Pop(stackrets);
			(*buff) = pointer + digitpop - 1; counter = (digitpop - 1);
			fprintf(Cpuout, "ret %d, counter: %d\n", digitpop, counter);)

			CASE(cmd_size,  Size(stack);   fprintf(Cpuout, "size\n");)
			CASE(cmd_clear, Clear(stack);  fprintf(Cpuout, "clear\n");)
			CASE(cmd_end,   counter = size;  fprintf(Cpuout, "end");)

			CASE(cmd_popr, (*buff)++; counter++;  fprintf(Cpuout, "pop %cx\n", char('a' + Ctoi(buff)));
			stack->regs[Ctoi(buff)] = Pop(stack);)

			CASE(cmd_resize, int ressize = GetInt(buff); fprintf(Cpuout, "resize %d\n", ressize);
			counter += sizeof(int); Resize(stack, ressize);)

			CASE(cmd_jxx, int jump = GetInt(buff); fprintf(Cpuout, "jxx %d\n", jump);
			counter += sizeof(int); StackType first = Pop(stack); StackType second = Pop(stack);
			if (first >= second) { (*buff) -= jump; (*buff) -= (sizeof(int) + 1); counter -= (jump + sizeof(int) + 1); })

			CASE(cmd_jmp, int jump = GetInt(buff); fprintf(Cpuout, "jmp %d\n", jump);
			counter += sizeof(int); (*buff) -= jump;)
		 };

		 counter++;
		 (*buff)++;
	 }
	 fprintf(Fout, "SizeWhile: %d\n", counter);
 }

 double GetDouble(char** buff)
 {
	 ASSERT(*buff);
	 //(*buff)++;
	 
	 double digit = 0.0;
	 fprintf(Log, "Ctoi = %d\n", Ctoi(buff));
	 (*buff)++;
	 memcpy_s(&digit, sizeof(double), *buff, sizeof(double));// byte atod
	 (*buff) += sizeof(double) - 1;
	 fprintf(Log, "Ctoi = %d\n", Ctoi(buff));

	 //push(stack, digit);
	 return digit;
 }

 int GetInt(char** buff)/// Pleeeeeease look into Log file
 {
	 ASSERT(*buff);
	 int digit = 0;
	 (*buff)++;
	 fprintf(Log, "Ctoi before = %d\n", Ctoi(buff));
	 memcpy_s(&digit, sizeof(int), *buff, sizeof(int));
	 (*buff) += 3 ;///!!!!!!
	 fprintf(Log, "Ctoi after = %d\n", Ctoi(buff));
	 //fprintf(Cpuout, "Ctoi = %d\n", Ctoi(buff));

	 //push(stack, digit);
	 return digit;
 }


 void PrintRegs(Stack* stack)
 {
	 fprintf(Fout, "REGGS:\n");
	 for (int counter(0); counter < REGSSIZE; counter++)
	 {
		 fprintf(Fout, "reg[%d] = %lf\n", counter, stack->regs[counter]);
	 }
 }


 int Ctoi(char** buff)
 {
	 ASSERT(*buff);
	 //return ((**buff) / 16) * 16 + (**buff - (**buff) / 16);
	 return (int) **buff;
 }

 void Free(char* buff, Labels* label)
 {
	 free(buff);
	 free(label);
 }


#undef ASSERT
#undef CASE
