#pragma once

 const int SIZEBUFF = 20;
 const int POISON   = 718;
 const int SIZELABEL = 1000;
 const int SIZELABELFORPRINT = 20;


 FILE* Fin =  NULL;
 FILE* Fout = NULL;
 FILE* Text = NULL;
 FILE* Bin =  NULL;
 FILE* Log =  NULL;

 void  FopenFiles   ();
 void  PlayKotik    ();
 void  Asm          (char *buff, long size, int **labels, int key);
 void  PrintBuff    (char buffer[SIZEBUFF], int counter);
 
 char* Read         (long size);

 long  Size         ();
 long  IncreasePtr  (char *buff, char buffer[SIZEBUFF]);

 int   CMP          (char buffer[SIZEBUFF], char *buff, long counter,
	                 char* binbuff, int* newcounter,
	                 bool* flag_value, int** labels, char *pointer);


 void  Print        (int num, char name[SIZEBUFF]);

 void  End          (char *buff, char* binbuff, char buffer[SIZEBUFF]);

 int   *Init        ();
 void  PrintLabels  (int **labels);
