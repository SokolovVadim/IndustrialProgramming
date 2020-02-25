 #pragma once
 #include <iostream>
 #include <cstdlib>
 #include <cstdio>
 #include <assert.h>

 FILE* Fin  = nullptr;
 FILE* Fout = nullptr;
 FILE* Log  = nullptr;
 FILE* Dot  = nullptr;

 typedef char* NodeType;


 enum NUMBERS
 {
 	 SIZEBUFF = 1000
 };

 enum TYPES
 {
	 integer,
	 real,
	 variable,
	 operation
 };



 struct Node
 {
	 NodeType data;
	 Node*    Parent;
	 Node*    Left;
	 Node*    Right;
	 int      type;

 };

 struct Tree
 {
	 Node* root;
	 int   counter;
 };


 void        FopenFiles                  ();
 char*       Read                        (size_t size);
 size_t      SizeofFile                  ();
 inline bool CheckValue                  (int value);
 Tree*       ConstrTree                  ();
 void        AvoidSpace                  (char** buff);
 Node*       AddElem                     (Tree* head, Node* node, NodeType value);
 int CreateTree(char* buff, int position, Tree* head, Node* node);
 void PrintDot(Tree* head);
 void PrintGraph(Node* node);
 void PrintText(Tree* head);
 void WriteTree(Node* node);


 inline bool Error(const void* argument)
 {
	 fprintf(Log, "%s", (char*)argument);
 }


 inline bool Checker(const void* buff)
 {
	 if (buff <= nullptr)
		 return false;
	 else
		 return true;
 }



 #define ASSERT( BUFF )                                          \
	 do {                                                        \
	     if(!BUFF)                                               \
         {                                                       \
              fprintf(Log, "Warning! " #BUFF					 \
			  " is NULL!\nLine %ld", __LINE__);					 \
              exit(EXIT_FAILURE);                                \
		 }                                                       \
	 } while(0)

 #define BOOLCHECK( NAME )                                       \
      do{                                                        \
	     if (NAME)                                               \
		      fprintf(Log, #NAME " has no errors!\n");           \
	     else                                                    \
		      fprintf(Log, "WARNONG! " #NAME                     \
			  " has an error in line %ld\n", __LINE__);          \
      }while(0);
