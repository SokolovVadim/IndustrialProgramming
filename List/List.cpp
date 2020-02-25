#include "List.h"

// Listtype SerchNumber(number);


int main()
{
	Openfiles();


	List* root = Construct(SIZELIST);
	
	AddEnd(root, 1.32429);
	AddEnd(root, 2.43555);
	AddBegin(root, 3234.535);
	AddBegin(root, 123.456);
	AddEnd(root, 3.45236);
	AddEnd(root, 4.67357);

	AddMiddleBefore(root, 1414.363, 2.43555);
	AddMiddleBefore(root, 5555555.5, 4.67357);
	AddMiddleAfter(root, 111111.11, 123.456);
	AddMiddleBefore(root, 2222.2, 123.456);

	Search(root->head, 1.32429);
	fprintf(Fout, "1.32429 == %lf\n", Search(root->head, 1.32429)->data);

	Delete(root, root->head, 2222.2);


	AddMiddleAfter(root, 3333.3, 4.67357);

	fprintf(Fout, "SEARCHNUMBER: %lf\n", SearchNumber(root, 3)->data);
	SearchNumber(root, 3);

	Delete(root, root->head, 3333.3);

	root->root = GiveRoot(root->head);

	fprintf(Fout, "HEAD\n\n\n%lf\nROOT\n\n\n%lf\nSIZE\n%d",
		GiveHead(root->root)->data, GiveRoot(root->head)->data, root->size);
	
	PrintDot(root);
	
	system("start Run.bat");
	DestructNode(root->head);
}

#define WORDS "Programm was crashed in \"%s\" on line %ld\n"



#define IFEF(PTR, DESCR)                                             \
else                                                                 \
{                                                                    \
	if (PTR)                                                         \
	{                                                                \
		fprintf(Log, "WARNING! "DESCR WORDS, __FUNCSIG__, __LINE__); \
		return false;                                                \
	}                                                                \
}





//inline boooooool ListCheck(List *list)
//{
//	if(0)IFEF(list==nullptr, "Pointer on list == null!\n")
//}

 inline boooooool ListCheck(List *list)
 {
	 if (list == nullptr)
	 {
		 fprintf(Log, "\nWarning! Pointer on list == null!\n"
		              WORDS, __FUNCSIG__, __LINE__);
		 return false;
	 }
	 else
	 {
		 if (list->size <= 1)
		 {
			 fprintf(Log, "Warning! size <= 1!\n"
				          WORDS, __FUNCSIG__, __LINE__);
			 return false;
		 }
		 else
		 {
			 if (list->head == nullptr)
			 {
				 fprintf(Log, "Warning! Head == nullptr!\n"
					 WORDS, __FUNCSIG__, __LINE__);
				 return false;
			 }
			 else
			 {
				 if (list->root == nullptr)
				 {
					 fprintf(Log, "Warning! Root == nullptr!\n"
						 WORDS, __FUNCSIG__, __LINE__);
					 return false;
				 }
				 else
					 return true;
			 }
		 }
	 }
 }

 void PlayKotik()
 {
	 //PlaySoundA("Antihype.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	 PlaySoundA("Mew.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
 }


 void Openfiles()
 {
	fopen_s(&Fin,   "INPUT.txt",   "rb");
	fopen_s(&Fout,  "Output.txt",  "w" );
	fopen_s(&Log,   "Log.txt",     "w" );
	assert(Fin);
	assert(Fout);
 }

 List* Construct(int size)
 {
	List* root = (List*)calloc(1, sizeof(List));
	root->head = NULL;
	root->root = NULL;
	root->size = 0;
	assert(root);
	assert(!(root->size));
	return root;
 }


 void AddEnd(List* root, ListType elem)
 {
	 assert(root);
	 Node* node = (Node*)calloc(1, sizeof(Node));
	 assert(node);
	 node->data = elem;
	 if (root->size == 0)
	 {
	 	 root->root = node;
	 }

	 node->next = NULL;	
	 node->prev = root->head;
	 if (node->prev)
	 {
		 node->prev->next = node;
	 }
	 root->head = node;
	 root->size++;
 }


 void AddBegin(List* root, ListType elem)
 {
	 assert(root);
	 Node* node = (Node*)calloc(1, sizeof(Node));
	 assert(node);
	 node->data = elem;
	 if (root->size == 0)
	 {
		 root->root = node;
	 }
	 if(root->size)
		 root->root = GiveRoot(root->head);
	 fprintf(Log, "root->root: %lf\n", root->root->data);
	 node->next = root->root;
	 if (root->root)
	 {
		 node->next->prev = node;
	 }
	 node->prev = NULL;
	 node->next = root->root;
	 root->root = node;

	 //fprintf(Fout, "\n%lf %lf %lf\n", node->data, node->next->prev->data, node->next->data);

	 root->size++;
 }





 Node* GivePrev(Node* node, ListType position)
 {
	 if (node->data)
	 {
		 if (node->data == position)
		 {
			 return node;
		 }
		 else
		 {
			 if (node->prev)
			 {

				 return GivePrev(node->prev, position);
			 }
			 else
				 return node;
		 }
	 }
	 else
		 return NULL;
 }



 void AddMiddleBefore(List* root, ListType elem, ListType position)
 {
	 if (ListCheck(root))
 	 {
 		 assert(root);
 		 
 		 Node* node = (Node*)calloc(1, sizeof(Node));
 		 Node* CurNode = (Node*)calloc(1, sizeof(Node));
 		 
 		 assert(node);
 		 node->data = elem;

 		 if (root->size == 0)
 		 {
 			 root->root = node;
 		 }
 		 else
 		 {
 			 CurNode = GivePrev(root->head, position);// After this node we put (node -> data == positio
 
 			 ASSERT(CurNode);
 
 			 node->next = CurNode;
 			 node->prev = CurNode->prev;
			 if (CurNode->prev)
				 CurNode->prev->next = node;
			 else
				 root->root = node;
 			 CurNode->prev = node;
			 fprintf(Log, "AMB: CurNode->data = %lf\n"
				          "CurNode->prev->data = %lf\n"
				          "node->data = %lf\n"
				          "node->next->data = %lf\n", CurNode->data, CurNode->prev->data, node->data, node->next->data);
		 }
 		 root->size++;
 	 }
 }


 void AddMiddleAfter(List* root, ListType elem, ListType position)
 {
	 if (ListCheck(root))
	 {
		 assert(root);

		 Node* node = (Node*)calloc(1, sizeof(Node));
		 Node* CurNode = (Node*)calloc(1, sizeof(Node));

		 assert(node);
		 node->data = elem;

		 CurNode = GivePrev(root->head, position);// Before this node we put (node -> data == positio

	 	 ASSERT(CurNode);

		 node->prev = CurNode;
		 node->next = CurNode->next;
		 if (CurNode->next)
			 CurNode->next->prev = node;
		 else
			 root->head = node;
		 CurNode->next = node;
		 
		 /*fprintf(Log, "AMB: CurNode->data = %lf\n"
				    "CurNode->prev->data = %lf\n"
				    "node->data = %lf\n"
				    "node->next->data = %lf\n", CurNode->data, CurNode->prev->data, node->data, node->next->data);*/
		 root->size++;
	 }
 }




 void Delete(List* root, Node* node, ListType position)
 {
	 if (node->data == position)
	 {
		 if (node->prev)
		 {
			 if (node->next)
			 {
				 node->prev->next = node->next;
				 node->next->prev = node->prev;
			 }
			 else
			 {
				 node->prev->next = NULL;
				 root->head = node->prev;
			 }
		 }
		 else
		 {
			 if (node->next)
			 {
				 node->next->prev = NULL;
				 root->root = node->next;
			 }
		 }

		 free(node);
		 root->size--;
	 }
	 else
	 {
		 if (node->prev)
		 {
			 Delete(root, node->prev, position);
		 }
	 }
 }




 Node* Search(Node* node, ListType position)
 {
	 if (node->data == position)
	 {
		 return node;
	 }
	 else
	 {
		 if (node->prev)
		 {
			 return Search(node->prev, position);
		 }
		 else
			 return NULL;
	 }
 }



 Node* SearchNumber(List* root, int position)
 {
	 position++;
	 int* number = (int*)calloc(1, sizeof(int));
	 *(number) = 0;
	 if (root->size < position)
	 {
		 return NULL;
	 }
	 else
	 {
		 return SearchFromRoot(root->root, position, number);
	 }
 }


 Node* SearchFromRoot(Node* node, int position, int* number)
 {
	 (*number)++;
	 if ((*number) == position)
		 return node;
	 else
	 {
		 if (node->next)
		 {
			 SearchFromRoot(node->next, position, number);
		 }
		 else
			 return NULL;
	 }
 }


 void DestructNode(Node* node)
 {
	 if (node->prev)
	 {
		 DestructNode(node->prev);
	 }
	 free(node);
 }



 Node* GiveRoot(Node* node)
 {
	 if (!(node->prev))
	 {
		 return node;
	 }
	 else
	 {
		 fprintf(Log, "node->data: %lf\n", node->data);
		 return GiveRoot(node->prev);
	 }
 }


 Node* GiveHead(Node* node)
 {
	 if (!(node->next))
	 {
		 return node;
	 }
	 else
	 {
		 return GiveHead(node->next);
	 }
 }


 void PrintGraph(Node* node, FILE* Dot)
 {
	 if (node->next)
	 {
		 fprintf(Dot, "\"%lf\nnode: %p\nprev: %p\nnext: %p\"", node->data, node, node->prev, node->next);
		 fprintf(Dot, "->\"%lf\nnode: %p\nprev: %p\nnext: %p\";\n", node->next->data, node->next, node->next->prev, node->next->next);
		 fprintf(Dot, "\"%lf\nnode: %p\nprev: %p\nnext: %p\"[color = \"red\", fontcolor=\"black\""
                      ", shape=\"pentagon\"];\n", node->data, node, node->prev, node->next);
		 fprintf(Dot, "\"%lf\nnode: %p\nprev: %p\nnext: %p\"[color = \"red\", fontcolor=\"black\""
			 ", shape=\"pentagon\"];\n", node->next->data, node->next, node->next->prev, node->next->next);
		 PrintGraph(node->next, Dot);
	 }
 }

 void PrintDot(List* root)
 {
	 FILE* Dot = nullptr;
	 assert(root);
	 fopen_s(&Dot, "DOT.vg", "w");
	 
	 fprintf(Dot, "digraph List{\nrankdir=LR;\n");

	 PrintGraph(root->root, Dot);


	 fprintf(Dot, "\n}");
	 fclose(Dot);
 }
