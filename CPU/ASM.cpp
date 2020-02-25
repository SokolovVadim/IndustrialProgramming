 #include <iostream>
 #include <cassert>
 #include <Windows.h>
 #include <Mmsystem.h>
 #include <conio.h>
 #include <cstdlib>
 #include <cstring>
 #include "ASMHeader.h"
 #pragma comment(lib, "winmm.lib")
 



 #define ASSERT( BUFF , BUFFER )                                 \
	 do {                                                        \
	     if(!BUFF)                                               \
         {                                                       \
              fprintf(Log, "Warning! " #BUFF " is NULL\n");      \
              exit(EXIT_FAILURE);                                \
		 }                                                       \
         if(!BUFFER)                                             \
         {                                                       \
	          fprintf(Log, "Warning! " #BUFFER " is NULL\n");    \
              exit(EXIT_FAILURE);                                \
         }                                                       \
	 } while(0)



//!++++++++++++++++++++++++++++++++++++++++++++++//
//! @brief This macros receives two arguments 
//!        and the param is NOT a log file.
//!        For this situation you should use
//!        assert() without macros
//! @param FILEINPUT
//! @param FILEOUTPUT
//!++++++++++++++++++++++++++++++++++++++++++++++//

#define ASSERTFILE( FILEIN, FILEOUT )                      \
do                                                         \
{                                                          \
	if (FILEIN == nullptr)                                 \
	{                                                      \
		 fprintf(Log, "Warning! " #FILEIN " is NULL\n");   \
	}                                                      \
	if (FILEOUT == nullptr)                                \
	{                                                      \
		 fprintf(Log, "Warning! " #FILEOUT " is NULL\n");  \
	}                                                      \
} while(0)


// ћожно написать фор с 2 итераци€ми прохода
// выдает после 2 прохода отриц числа
// Ќо нужно написать ключ, по которому запускаетс€ 1 и 2 раз

 int main()
 {
	 FopenFiles();

	 /* PlayKotik();*/

	 long size = Size();
	 char *buff = Read(size);
	 int* labels = Init();
	 for(int key(0); key< 2;++key)
		 Asm(buff, size, &labels, key);
	 PrintLabels(&labels);
	 //system("pause");
 }



 void PrintLabels(int **labels)
 {
	 for (int i(0); i < SIZELABELFORPRINT; ++i)
	 {
		 fprintf(Log, "labels: %d\n", **labels);
		 (*labels)++;
	 }
 }

 int * Init()
 {
	 int* labels = (int*)calloc(SIZELABEL, sizeof(int));
	 for (int i(0); i < SIZELABEL; ++i)
	 {
		 labels[i] = -1;
	 }
	 return labels;
 }

 void PlayKotik()
 {
	PlaySoundA    ("Mew.wav", NULL , SND_FILENAME | SND_ASYNC |SND_LOOP);
	PlaySoundA    ("Antihype.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
 }

 void FopenFiles()
 {
 	fopen_s(&Fin,  "INPUT.txt", "rb");
 	fopen_s(&Fout, "OUTPUT.txt", "w");
	fopen_s(&Text, "TEXT.txt", "w");
	fopen_s(&Bin,  "BINOUT.txt", "wb");//     !!!!!!!!!!   wb
	fopen_s(&Log, "LOGS.txt", "w");
	if (Bin == nullptr)
	{
		exit(EXIT_FAILURE);
	}
 }

 char* Read(long size)
 {
	 assert(size != POISON);
	 char* buff;
     char* pointer = (char *) calloc(size, sizeof(char));

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

 	 return buff;
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




 void Asm(char *buff, long size, int **labels, int key)
 {
	 assert(size > 0);

	 int   counter(0), differ(0), newcounter(0), summ(0), num(0);
	 char  buffer[SIZEBUFF];
	 char* binbuff = {};
	 char* pointer = (char*)calloc(size * sizeof(double), sizeof(double));
	 bool  flag_value(true);

	 if (pointer == nullptr)
	 {
		 fprintf(Log, "WARNING! Binbuff was not declared!\n");
	 }
	 else
	 {
		 ASSERT(buff, pointer);
		 binbuff = pointer;
		 while (counter < size)
		 {
			 (sscanf_s(buff, "%s", buffer, SIZEBUFF));// put cmd in buffer
			 //fprintf(Bin, "%s\n", buffer);
			 if (buffer[0] == ':')
			 {
				 //fprintf(Log, "buff[2] - 0 = %d\n", buff[2] - '0');
				 if (isdigit(buff[3]))
				 {
					 labels[0][(buff[2] - '0') * 10 + buff[3] - '0'] = summ;
					 fprintf(Log, "(buff[2] - '0') * 10 + buff[3] - '0' = %d\n", (buff[2] - '0') * 10 + buff[3] - '0');
				 }
				 else
				 {
					 labels[0][buff[2] - '0'] = summ;//labels[0][buff[2] - '0'] = summ;
					 fprintf(Log, "buff[2] - 0 = %d\n", buff[2] - '0');
				 }
				 //labels[0][buff[2] - '0'] = summ;//labels[0][buff[2] - '0'] = summ;
				 //fprintf(Log, "LABEL %d diff = %d\n", buff[3] - '0', binbuff - pointer);
			 }
			 differ = IncreasePtr(buff, buffer);
			 buff += differ;
			 counter += differ;
			 differ = CMP(buffer, buff, counter, binbuff, &newcounter, &flag_value, labels, pointer);
			 if (differ == -1)
			 {
				 break;
			 }
			 buff += differ;
			 if (newcounter)
			 {
				 summ += newcounter;
				 binbuff += newcounter;
				 newcounter = 0;
			 }
			 counter += differ;
		 }
		 binbuff -= summ;
		 fprintf(Log, "\nnewcounter = %d\nsumm = %d\n", newcounter, summ);
		 fprintf(Log, "\nbinbuff = {%s}\n", binbuff);
		 for (int i(0); i < summ; ++i)
			 fprintf(Log, "%c", binbuff[i]);
		 if(key)
			 fwrite(binbuff, sizeof(char), summ, Bin);//////!!!!!!!!!! /2
	 }
 }
 
 inline bool check(char *buff)
 {
	 return (buff == NULL) ? false : true;
 }




 //!++++++++++++++++++++++++++++++++++++++++++++++++//
 //! @brief SWITCH can determine writing commands
 //!        into BINFILE
 //! @param NAME
 //! @param NUM
 //! @param SIZEARG
 //! @param SIZEELEM
 //! @param COMMAND
 //!++++++++++++++++++++++++++++++++++++++++++++++++//

 int CMP(char buffer[SIZEBUFF], char *buff, long counter,
	 char* binbuff, int* newcounter, bool* flag_value, int** labels, char *pointer)
 {
	 ASSERT(buff, buffer);
	 if ((check(buff)) && (check(binbuff)) && (check(buffer)))
	 {
#include "Commands.h"
#include "CMDFORDEF.h" 
		 // им€ регистра в 1 байт
				  // считывать int и double
	//!!!!!!!!! ATTENTION!
#define SWITCH( name , num , sizearg , sizeelem , command)                                           \
    switch(sizearg)                                                                                  \
	{                                                                                                \
        CASE(cmd_pop, nullarg, DO(EMIT1(num, binbuff, newcounter, char);PRINT(Fout, name, \n);       \
        PRINTP(Text, %d\n, num)); return 0;)                                                         \
                                                                                                     \
        CASE(cmd_end, endarg,  DO(EMIT1(num, binbuff, newcounter, char);PRINT(Fout, name, );         \
        PRINTP(Text, %d, num)); return 0;)                                                           \
                                                                                                     \
		CASE(cmd_popr, regarg, DO(EMIT1(num, binbuff, newcounter, char); SCAN(buff, %s, buffer);     \
        EMIT1(REGSUB(buffer), binbuff, newcounter, char) *newcounter += sizeof(char);                \
        PRINTP(Fout, name %s\n, buffer); PRINTF(Text, %d \t%d\n, num, REGSUB(buffer));               \
		IND(buff, buffer)))                                                                          \
                                                                                                     \
		CASE(cmd_resize, onearg, DO(EMIT1(num, binbuff, newcounter, char); SCAN(buff, %s, buffer);   \
        PUTVALUE(buffer) *newcounter+=sizeof(char); PRINTP(Fout, name %s\n, buffer)                  \
		PRINTF(Text, %d \t%s\n, num, buffer); IND(buff, buffer)))                                    \
		                                                                                             \
		CASE(cmd_resize, pusharg, DO(SCAN(buff, %s, buffer); PRINTP(Fout, name %s\n, buffer);        \
		PUTVALUE1(buffer) *newcounter += sizeof(char); IND(buff, buffer)))                           \
                                                                                                     \
        CASE(cmd_begin, twoarg, DO(EMIT1(num, binbuff, newcounter, char); PRINT(Fout, name, \t);     \
		PRINTP(Text, %d\t, num);  SCAN(buff, %s, buffer);                                            \
		EMIT1(SIGNSUB(buffer), binbuff, newcounter, char);                                           \
        PRINTP(Fout, \t%s\t, buffer);  PRINTP(Text, %d\t, SIGNSUB(buffer)); GETSEC(buff, buffer)))   \
                                                                                                     \
       /* CASE(cmd_pushr, pushrarg, DO(  PRINTP(Fout, %s , buffer);                                    \
        GETSEC1(buff, buffer);)) */                                                                    \
                                                                                                     \
        CASE(cmd_jmp, jmparg, DO(SCAN(buff, %s, buffer); PRINTP(Fout, name %s, buffer); /*\n*/ \
        int adr = binbuff - pointer - labels[0][atoi(buffer)];                                       \
        EMIT1(num, binbuff, newcounter, char);                                                       \
        PRINTP(Log, \n\nADR: %d\n\n, adr);   EMIT1(adr, binbuff, newcounter, int);                   \
        *newcounter+=sizeof(char); PRINTF(Text, %d \t%s\n, num, buffer);                             \
        PRINTP(Fout, \tadr: %d, adr); PRINTP(Fout, \tl: %d, labels[0][atoi(buffer)]);                \
        PRINTP(Fout, \ta: %d\n, atoi(buffer));  IND(buff, buffer)))                                  \
                                                                                                     \
                                                                                                     \
        /*CASE(cmd_call, callarg, DO(SCAN(buff, %s, buffer); PRINTP(Fout, name %s, buffer);          \
        EMIT1(num, binbuff, newcounter, char);  \
        EMIT1(binbuff - pointer, binbuff, newcounter, int);\
		 int adr = binbuff - pointer - labels[0][atoi(buffer)];                \
        EMIT1(adr, binbuff, newcounter, int);       \
        *newcounter += (sizeof(char) + sizeof(int));                \
        PRINTF(Text, %d \t%s\n, num, buffer);                             \
        PRINTP(Fout, \tadr: %d, adr); PRINTP(Fout, \tl: %d, labels[0][atoi(buffer)]);                \
        PRINTP(Fout, \tbin - point: %d, binbuff - pointer);\
        PRINTP(Fout, \ta: %d\n, atoi(buffer));  IND(buff, buffer))) */                                 \
                              \
                                                                                                     \
        CASE(cmd_label, labelarg, DO(                                                                \
        /*EMIT1(num, binbuff, newcounter, char);*/SCAN(buff, %s, buffer);                            \
        /*EMIT1(atoi(buffer), binbuff, newcounter, int);*/ /**newcounter += sizeof(char);*/          \
        PRINTP(Fout, name %s\n, buffer); PRINTF(Text, %d \t%s\n, num, buffer); IND(buff, buffer));)  \
                                                                                                     \
        default:                                                                                     \
	    {                                                                                            \
		    return 0;                                                                                \
	    }                                                                                            \
	}
		 //buff[3] - '0', binbuff - pointer


#define CMD_DEF( name , num , sizearg , sizeelem , command)                             \
                 else if (!strcmp(buffer, #name)){                                      \
                         SWITCH( name, num , sizearg , sizeelem , command)              \
                      }
		 if (0)
		 {
			 ;
		 }
		 #include "CMD.h"
		 else
		 {
			 fprintf(Fout, "Unknown command\n");
			 return POISON;
		 }
		 #undef CMD_DEF
	 }
	 else
	 {
		 fprintf(Log, "Warning! CMP has a damaged argument!\n"
			 "Line: %ld", __LINE__);
		 return -1;
	 }
 }

                                



 long IncreasePtr(char *buff, char buffer[SIZEBUFF])
 {
	 int differ = strlen(buffer) + 1;
	 buff += differ;// increase pointer *buff
	 if (*buff == '\n')// avoid '\0'
	 {
		 differ++;
	 }
	 return differ;
 }



 void Print(int num, char name[SIZEBUFF])
 {
	 ASSERTFILE(Fout, Text);
	 assert(Log);
	 if (check(name))
	 {
		 fprintf(Text, "%d\n", num);
		 fprintf(Fout, "%s\n", name);
	 }
	 else
	 {
		 fprintf(Log, "Warning! Print was crashed!\n");
	 }
 }


 void PrintBuff(char buffer[SIZEBUFF], int counter)
 {
	 ASSERTFILE(Fout, Text);
	 assert(Log);
	 fprintf(Fout, "!");
	 for (int i(0); i < counter; ++i)
		 fprintf(Fout, "%c", buffer[i]);
	 fprintf(Fout, "!");
 }


 void  End(char *buff, char* binbuff, char buffer[SIZEBUFF])
 {
	 free(buff);
	 free(binbuff);
	 free(buffer);
	 fclose(Fin);
	 fclose(Fout);
	 fclose(Bin);
	 fclose(Log);
	 fclose(Text);
 }



 #undef ASSERT
 #undef PRINT
 #undef PRINTP
 #undef PRINTF
 #undef SCAN
 #undef IND
 #undef REGSUB
 #undef SIGNSUB
 #undef GETSEC
 #undef DO
