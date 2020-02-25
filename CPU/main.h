#pragma once

 struct words
 {
	 char* buffer;
	 char* asmbuffer;
	 int*  digits;
 };

 const int SIZEBUFF = 20;
 FILE* Fin =  NULL;// init.
 FILE* Fout = NULL;
 FILE* Text = NULL;

 void  FopenFiles   ();
 void  PlaySnd      ();
 void  Asm          (char *buff, short countstr, long size);
 void  PushValue    (bool alphapush, long digitcount, char digitbuff[SIZEBUFF]);
 void  PrintBuff    (char buffer[SIZEBUFF], int counter);
 
 char* Read         (long size);
 short Sizestr      (char *buff, long size);
 long  Size         ();
 long  AvoidEnd     (char *buff, long counter);
 long  AvoidSpace   (char *buff, long counter);
 int   DiffAlpha         (char *buff, char alphabuff[SIZEBUFF], long counter);
 int   DiffDigit    (char *buff, char digitbuff[SIZEBUFF], long counter);

 bool  Alphacmp     (int alphacount, char alphabuff[SIZEBUFF]);



 int main()
 {

	 words StrTool = {};
	 FopenFiles();

	/* PlaySnd();*/

	 long size = Size          ();
	 char *buff = Read         (size);
	 short countstr = Sizestr  (buff, size);

	 Asm(buff, countstr, size);

	 /*system("pause");*/
 }
