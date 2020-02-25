 #include <iostream>
 #include <cstdio>
 #include <cassert>
 #include <ctime>
 #include <cstdlib>
 #include "Windows.h"

 #define ASSERT( BUFF )                                          \
	 do {                                                        \
	     if(!BUFF)                                               \
         {                                                       \
              fprintf(Log, "Warning! " #BUFF					 \
			  " is NULL!\nLine %ld", __LINE__);					 \
              exit(EXIT_FAILURE);                                \
		 }                                                       \
	 } while(0)



 inline bool Checker(const void* buff)
 {

	 if (buff <= nullptr)
		 return false;
	 else
		 return true;
 }

 FILE* Fin       = nullptr;
 FILE* Fout      = nullptr;
 FILE* Log       = nullptr;
 FILE* Dot       = nullptr;
 FILE* TreePrint = nullptr;


 typedef char* NodeType;
 typedef int    stock;

 const size_t SIZEBUFF = 100;


 struct Node
 {
	 NodeType data;
	 Node*    Parent;
	 Node*    Left;
	 Node*    Right;
 };

 struct Tree
 {
	 Node* root;
	 int   counter;
 };



  

 void        FopenFiles      ();
 Tree*       TreeConstr      ();
 inline bool Checker         (const void* buff);
 void        NodeDelete      (Node* root);
 //void        AddNodeLeft   (Node* root, NodeType value);
 //void        AddNodeRight  (Node* root, NodeType value);
 //void        PrintNode     (Node* root);
 //void        TreeSort      (Node* root, NodeType value);
 void        ReadBuff        (Tree* head);
 Node*       RunDown         (Tree* head);
 void        AddNewNode      (Tree* head, Node* node);
 int         CreateTree      (char* buff, int position, Tree* head, Node* node);
 Node*       AddElem         (Tree* head, Node* node, NodeType value);
 void        Akinator        (Tree* head);
 int         SizeofFile      ();
 void        PrintText       (Tree* head);
 void        WriteTree       (Node* node);
 void        PrintDiffer     (Node* head);
 void        SearchForName   (Tree* head);
 bool        Search          (Node* node, char* word);
 void        FindDiff        (Tree* head);
 void        PrintFromDiffer (Node* node, char** buffs, char** buffd);
 bool        SearchDiff      (Node* node, char* word, char** buffs, char** buffd);
 unsigned int      SeparateWords   (char* buff, char** buffer);



 void PrintGraph           (Node* node);
 void PrintDot             (Tree* head);


 int main()
 {
	 FopenFiles   ();
	 Tree* head = TreeConstr();
	 ReadBuff     (head);
	 //Akinator     (head);
	 PrintDot     (head);
	 fclose(Fin);
	 fopen_s(&Fin, "INPUT.txt", "w");
	 PrintText    (head);
	 //PrintDiffer  (head->root);
	 //SearchForName(head);
	 FindDiff(head);
	 system("pause");
	 system       ("start Run.bat");
	 //TerminateProcess(GetCurrentProcess(), 0);
	 
 }


 void SearchForName(Tree* head)
 {
	 char* word = (char*)calloc(SIZEBUFF, sizeof(char));
	 printf("Do you want to find a description of any word?\n"
		 "Print yes or no\n");
	 scanf_s(" %[^\n]100s", word, SIZEBUFF);
	 if (!strcmp(word, "yes"))
	 {
		 printf("Print the word you want to find\n");
		 scanf_s(" %[^\n]100s", word, SIZEBUFF);
		 if (!Search(head->root, word))
			 fprintf(TreePrint, "Word \"%s\""
				 " is not declared in the bank of words!\n", word /*place for word*/);
		 system("pause");
	 }
 }


 void FopenFiles()
 {
	 fopen_s(&Fin, "INPUT.txt", "r");
	 fopen_s(&Fout, "OUTPUT.txt", "w");
	 fopen_s(&Log, "LOGS.txt", "w");
	 fopen_s(&Dot, "DOTOUT.vg", "w");
	 fopen_s(&TreePrint, "TREE.txt", "w");
	 ASSERT(Dot);
	 ASSERT(Fin);
	 ASSERT(Fout);
 }

 void Akinator(Tree* head)
 {
	 Node* NewNode = nullptr;

	 NewNode = RunDown(head);


	 printf("%s\n", NewNode->data);
	 char* answer = (char*)calloc(SIZEBUFF, sizeof(char));//
	 scanf_s(" %[^\n]100s", answer, SIZEBUFF);
	 if (!strcmp(answer, "yes"))
	 {

		 printf("WIN\n");

	 }
	 else
	 {
		 AddNewNode(head, NewNode);
	 }
 }


 void ReadBuff(Tree* head)
 {
	 int size = SizeofFile();
	 char* buff = (char*)calloc(size, sizeof(char));
	 ASSERT(buff);

	 fread(buff, sizeof(char), size, Fin);

	 int position(0);
	 while (buff[position] != '(')// avoid space & /n/r
	 {
		 position++;
	 }

	 CreateTree(buff, position, head, nullptr);
 }




void AddNewNode(Tree* head, Node* node)
 {
	 ASSERT(head);
	 ASSERT(node);
	 char* word = node->data;

	 char* diff = (char*)calloc(SIZEBUFF, sizeof(char));
	 char* rightansw = (char*)calloc(SIZEBUFF, sizeof(char));

	 ASSERT(diff);
	 ASSERT(rightansw);

	 printf("\tWhat was the differense?\n");
	 scanf_s(" %[^\n]100s", diff, SIZEBUFF);// scanf_s("%[^\n]100s", &ans, 100);
	 printf("\tWhat was it?\n");
	 scanf_s(" %[^\n]100s", rightansw, SIZEBUFF);
	 

	 AddElem(head, node, rightansw);
	 AddElem(head, node, node->data);
	 
	 node->data = diff;
 }



 Node* RunDown(Tree* head)
 {
	 ASSERT(head);

	 char * buffer = (char*)calloc(SIZEBUFF, sizeof(char));
	 char * answer = (char*)calloc(SIZEBUFF, sizeof(char));

	 ASSERT(buffer);
	 ASSERT(answer);


	 Node* elem = head->root;
	 while (elem != nullptr)// !!!!!!!!!!!!!!!!!!!!!!!!!!
	 {
		 printf("\t%s\n\t", elem->data);

		 scanf_s(" %[^\n]100s", answer, SIZEBUFF);

		 if (!strcmp(answer, "yes"))
		 {
			 if (elem->Left)
			 {
				 elem = elem->Left;
			 }

			 if (!((elem->Left) || (elem->Right)))
			 {
				 return elem;
			 }
		 }
		 else
		 {
			 if (elem->Right)
			 {
				 elem = elem->Right;
			 }
			 if (!((elem->Left) || (elem->Right)))
			 {
				 return elem;
			 }
		 }
	 }
	 return nullptr;
 }






 void AvoidSpace(char* buff)
 {
	 int counter(0);
	 while (buff)
	 {
		 if (buff[counter] == ' ')
		 {
			 counter++;
		 }
	 }
 }


 int SizeofFile()
 {
	 ASSERT(Fin);

	 fseek(Fin, 0, SEEK_END);

	 int size(ftell(Fin));

	 fseek(Fin, 0, SEEK_SET);

	 assert(size > 0);

	 return size;
 }


 int CreateTree(char* buff, int position, Tree* head, Node* node)
 {

	 Node* NewNode = (Node*)calloc(1, sizeof(Node));

	 char* buffer = (char*)calloc(SIZEBUFF, sizeof(char));

	 if (buff[position] == '(')
	 {
		 position += 2;// avoid '(' & '\"' simbols
		 int counter(0);
		 while (buff[position] != '\"')
		 {
			 buffer[counter] = buff[position];
			 counter++;
			 position++;
		 }

		 buffer[counter] = '\0';
		 NewNode = AddElem(head, node, buffer);

	 }

	 for (; ;)
	 {
		 while ((buff[position] != '(') && (buff[position] != ')'))// Avoid space & \n
		 {
			 position++;
		 }



		 if (buff[position] == ')')
		 {
			 return position + 1;
		 }



		 if (buff[position] == '(')
		 {
			 position = CreateTree(buff, position, head, NewNode);
		 }
	
	 }

 }


 Node* AddElem(Tree* head, Node* node, NodeType value)
 {

	 ASSERT(head);

	 Node* NewNode = (Node*)calloc(1, sizeof(Node));

	 NewNode->data = value;
	 NewNode->Parent = node;
	 head->counter++;

	 if (!(head->root))
	 {
		 head->root = NewNode;
		 return NewNode;
	 }

	 if (!node->Left)
	 {
		 node->Left = NewNode;
	 }
	 else
	 {
		 node->Right = NewNode;
	 }
	 return NewNode;

 }


 Tree* TreeConstr()
 {
	 Tree* CurTree;
	 void *pointer = calloc(1, sizeof(Tree));
	 if (Checker(pointer))
	 {
		 CurTree = (Tree*)pointer;
		 return CurTree;
	 }
	 else
	 {
		 fprintf(Log, "Warning! Tree was not constructed!\n");
		 return nullptr;
	 }
 }
 

 // сначала одинаковые признаки, потом разные
 // проход по дереву и запоминание определения для 1-ого, потом для 2-ого
 // потом проверка общих качеств и разных

 void FindDiff(Tree* head)// сравнение
 {
	 ASSERT(head);

	 char* firstword  = (char*)calloc(SIZEBUFF, sizeof(char));
	 char* secondword = (char*)calloc(SIZEBUFF, sizeof(char));

	 char* BuffForSimilar1 = (char*)calloc(SIZEBUFF, sizeof(char));
	 char* BuffForDiffer1 = (char*)calloc(SIZEBUFF, sizeof(char));
	 Checker(BuffForSimilar1);
	 Checker(BuffForDiffer1);

	 char* BuffForSimilar2 = (char*)calloc(SIZEBUFF, sizeof(char));
	 char* BuffForDiffer2 = (char*)calloc(SIZEBUFF, sizeof(char));
	 Checker(BuffForSimilar2);
	 Checker(BuffForDiffer2);

	 printf( "Add the first word\n");
	 scanf_s(" %[^\n]100s",  firstword, SIZEBUFF);
	 printf("Add the second word\n");
	 scanf_s(" %[^\n]100s", secondword, SIZEBUFF);

	 SearchDiff(head->root,  firstword, &BuffForSimilar1, &BuffForDiffer1);//!Search(head->root, word))
	 SearchDiff(head->root, secondword, &BuffForSimilar2, &BuffForDiffer2);


	 char** buffer = (char**)calloc(SIZEBUFF, sizeof(char*));
	 unsigned int sizesim1 = SeparateWords(BuffForSimilar1, buffer);/// не работает! указатели на всю строку


	 char** buffer3 = (char**)calloc(SIZEBUFF, sizeof(char*));

	 unsigned int sizesim2 = SeparateWords(BuffForSimilar2, buffer3);

	 //printf("sim2\n");
	 //for (unsigned int i(0); i < sizesim2; i++)
	 //{
		// printf("%s\n", buffer3[i]);
	 //}



	 char** Similar = (char**)calloc(SIZEBUFF, sizeof(char*));
	 char** Differ = (char**)calloc(SIZEBUFF, sizeof(char*));

	 int NumberSim(0);
	 int NumberDiff(0);
	 for (int i(0); i < sizesim1 / 2; i++)
	 {
		 std::swap(buffer[i], buffer[sizesim1 - 1 - i]);
	 }

	 for (int i(0); i < sizesim2 / 2; i++)
	 {
		 std::swap(buffer3[i], buffer3[sizesim2 - 1 - i]);
	 }

	 int sizesim = min(sizesim1, sizesim2);


	 printf("SIMILAR\n");

	 for (int i(0); i < sizesim; i++)
	 {
			 if (!(strcmp(buffer[i], buffer3[i])))
			 {
				 printf("%s\n", buffer[i]);// strcat_s(*buffs, SIZEBUFF, node->Parent->data);
				 Similar[NumberSim] = buffer[i];
				 NumberSim++;
			 }
			 else
			 {
				 int point = i;
				 printf("%s: ", firstword);
				 for (i; i < sizesim1 - 1; i++)
				 {
					 printf("%s and ", buffer[i]);
					 Differ[NumberDiff] = buffer[i];
					 NumberDiff++;
				 }
				 printf("%s", buffer[i]);
				 printf("\nBut %s: ", secondword);
				 for (i = point; i < sizesim2 - 1; i++)
				 {
					 printf("%s and ", buffer3[i]);
					 Differ[NumberDiff] = buffer3[i];
					 NumberDiff++;
				 }
				 printf("%s\n", buffer3[i]);
			 }
	 }


 }



 unsigned int SeparateWords(char* buff, char** buffer)
 {
	 unsigned int i(0);
	 //char** buffer = (char**)calloc(SIZEBUFF, sizeof(char*));
	 unsigned int j(0);
	 buffer[j] = &(buff[0]);
	 j++;
	 unsigned int size = strlen(buff);
	 unsigned int counter(0);
	 while (i < size)
	 {
		 if (buff[i] == '|')
		 {
			 buff[i] = '\0';
			 counter++;
			 printf("!!!!!!!\n");
		 }
		 i++;
	 }
	 i = 0;
	 while (i < size)
	 {
		 if (buff[i] == '\0')
		 {
			 buffer[j] = &(buff[i + 1]);
			 j++;
		 }

		 i++;
	 }
	 return counter;
 }



 bool SearchDiff(Node* node, char* word, char** buffs, char** buffd)// сравнение
 {
	 ASSERT(node);
	 if (!strcmp(node->data, word))
	 {
		 PrintFromDiffer(node, buffs, buffd);
		 printf("\nI found it!\n(%s)\n", node->data);
		 return true;
	 }
	 else
	 {
		 if ((node->Right) || (node->Left))
		 {
			 if ((node->Left) && (SearchDiff(node->Left, word, buffs, buffd)))
			 {
				 return true;
			 }
			 if ((node->Right) && (SearchDiff(node->Right, word, buffs, buffd)))
				 return true;
		 }
		 else
		 {
			 return false;
		 }
	 }
	 //return true;
 }


 void PrintFromDiffer(Node* node, char** buffs, char** buffd)// сравнение
 {
	 char* sep = "|";
	 char* negative = "not ";
	 ASSERT(node);
	 if (node->Parent)
	 {
		 if (!strcmp(node->Parent->Left->data, node->data))//this node is left
		 {
			 if (!node->Parent)
			 {
				 strcat_s(*buffs, SIZEBUFF, "bla-bla");
			 }
			 else
			 {
				 assert(node->Parent->data);
				 strcat_s(*buffs, SIZEBUFF, node->Parent->data);
				 strcat_s(*buffs, SIZEBUFF, sep);
				 printf("%s ", node->Parent->data);
			 }
		 }
		 else
		 {
			 strcat_s(*buffs, SIZEBUFF, negative);
			 strcat_s(*buffs, SIZEBUFF, node->Parent->data);
			 strcat_s(*buffs, SIZEBUFF, sep);
			 printf("%s ", node->Parent->data);
		 }
		 PrintFromDiffer(node->Parent, buffs, buffd);
	 }
	 else
	 {
		 ;
	 }
 }







 void NodeDelete(Node* root)
 {
	 ASSERT(root);
	 if (root->Left)
		 NodeDelete(root->Left);
	 if (root->Right)
		 NodeDelete(root->Right);

	 free(root);
 }




 void PrintDot(Tree* head)
 {
	 fprintf(Dot, "digraph Tree{\n");
	 PrintGraph(head->root);
	 fprintf(Dot, "\n}");
	 fclose(Dot);
 }


 void PrintGraph(Node* node)
 {
	 if (node->Left)
	 {
		 fprintf(Dot, "\"%s\"", node->data);
		 fprintf(Dot, "->\"%s\";\n", node->Left->data);
		 PrintGraph(node->Left);
	 }


	 if (node->Right)
	 {
		 fprintf(Dot, "\"%s\"", node->data);
		 fprintf(Dot, "->\"%s\";\n", node->Right->data);
		 PrintGraph(node->Right);
	 }
 }

 void PrintText(Tree* head)
 {
	 WriteTree(head->root);
 }


 void WriteTree(Node* node)
 {
	 fprintf(Fin, "(\"%s\"\n", node->data);
	 if ((node->Left) || (node->Right))
	 {
		 if (node->Left)
		 {
			 WriteTree(node->Left);
			 if (!(node->Right))
				 fprintf(Fin, ")\n");
		 }

		 if (node->Right)
		 {
			 WriteTree(node->Right);
				 fprintf(Fin, ")\n");
		 }
	 }
	 else
	 {
		 if(node->Parent!=nullptr)
			 fprintf(Fin, ")\n");
	 }
 }





 void PrintFrom(Node* node)
 {
	 ASSERT(node);

	 if (node->Parent)
	 {
		 if (!strcmp(node->Parent->Left->data, node->data))//this node is left
		 {
			 printf("and %s ", node->Parent->data);
		 }
		 else
			 printf("not %s ", node->Parent->data);
		 PrintFrom(node->Parent);
	 }
	 else
		/* fprintf(TreePrint, "and %s ", node->data)*/;
 }


 bool Search(Node* node, char* word)
 {
	 ASSERT(node);
	 if (!strcmp(node->data, word))
	 {
		 PrintFrom(node);
		 printf("\nI found it!\n(%s)\n", node->data);
		 return true;
	 }
	 else
	 {
		 if ((node->Right) || (node->Left))
		 {
			 if ((node->Left) && (Search(node->Left, word)))
			 {
				 return true;
			 }
			 if ((node->Right)&&(Search(node->Right, word)))
				 return true;
		 }
		 else
		 {
			 return false;
		 }
	 }
	 //return true;
 }



 void PrintDiffer(Node* node)
 {
	 ASSERT(node);
	 if ((node->Left) || (node->Right))
	 {
		 if (node->Left)
		 {
			 fprintf(TreePrint, "and %s ", node->Left->data);
			 PrintDiffer(node->Left);
		 }


		 if (node->Right)
		 {
			 fprintf(TreePrint, "not %s ", node->Right->data);
			 PrintDiffer(node->Right);
		 } 
	 }
 }
