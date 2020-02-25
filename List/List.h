#pragma once

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <Windows.h>
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")

FILE* Fin = nullptr;
FILE* Fout = nullptr;
FILE* Log = nullptr;

typedef double ListType;
typedef bool   boooooool;


struct Node
{
	Node* next;
	Node* prev;
	ListType data;
};


struct List
{
	Node* head;
	Node* root;
	int size;
};


#define ASSERT(BUFF)                                                          \
{                                                                             \
	if (BUFF == nullptr)                                                      \
	{                                                                         \
		fprintf(Log, "WARNING! Function \"%s\" was crashed on line %ld\n)",   \
			__FUNCSIG__, __LINE__);                                           \
	    exit(EXIT_SUCCESS);                                                   \
	}                                                                         \
}



//sort

const int SIZELIST = 100;

void      Openfiles                     ();
void      PrintGraph                    (Node* node, FILE* Dot);
void      PrintDot                      (List* root);
void      PlayKotik                     ();
void      AddEnd                        (List* root, ListType elem);
void      AddBegin                      (List* list, ListType elem);
void      AddMiddleBefore               (List* root, ListType elem, ListType position);
void      AddMiddleAfter                (List* root, ListType elem, ListType position);
Node*     GiveRoot                      (Node* node);
Node*     GiveHead                      (Node* node);
List*     Construct                     (int size);
Node*     GivePrev                      (Node* node, ListType position);
void      DestructNode                  (Node* node);
void      Delete                        (List* root, Node* node, ListType position);
Node*     Search                        (Node* node, ListType position);
Node*     SearchFromRoot                (Node* node, int position, int* number);
Node*     SearchNumber                  (List* root, int position);