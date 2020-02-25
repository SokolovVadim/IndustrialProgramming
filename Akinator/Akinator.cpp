#include "Tree.h"


 int main()
 {
	 FopenFiles   ();
	 Tree* head = TreeConstr();
	 ReadBuff     (head);
	 Menu(head);
	 //TerminateProcess(GetCurrentProcess(), 0);
	 NodeDelete(head->root);
 }


 void Menu(Tree* head)
 {
	 printf("Hello!\n");
	 PrintAdd();
	 int number(0);
	 while (scanf_s("%d", &number))
	 {
		 Tree* head = TreeConstr();
		 ReadBuff(head);
		 switch (number)
		 {
		 case 1:
		 {
			 Akinator(head);
			 PrintDot(head);
			 fopen_s(&Fin, "INPUT.txt", "w");
			 PrintText(head);
			 fclose(Fin);
			 system("start Run.bat");
			 system("pause");
			 system("cls");
			 PrintAdd();
			 break;
		 }
		 case 2:
		 {
			 SearchForName(head);
			 fclose(Srch);
			 system("start balcon.exe -f \"SEARCH.txt\" -w");
			 system("pause");
			 system("cls");
			 PrintAdd();
			 break;
		 }
		 case 3:
		 {
			 FindDiff(head);
			 system("pause");
			 system("cls");
			 PrintAdd();
			 break;
		 }
		 case 4:
		 {
			 exit(EXIT_FAILURE);
			 break;
		 }
		 }
	 }
 }


 void PrintAdd()
 {
	 printf("If you want to find you word print 1\n"
		 "If you want to find a description of any word print 2\n"
		 "If you want to compare two words print 3\n"
		 "If you want to end a programm print 4\n");
 }



 void SearchForName(Tree* head)
 {
	 char* word = (char*)calloc(SIZEBUFF, sizeof(char));
	 printf("Print the word you want to find\n");
	 scanf_s(" %[^\n]100s", word, SIZEBUFF);
	 if (!Search(head->root, word))
		 fprintf(TreePrint, "Word \"%s\""
			 " is not declared in the bank of words!\n", word /*place for word*/);
 }


 void FopenFiles()
 {
	 fopen_s(&Fout, "OUTPUT.txt", "w");
	 fopen_s(&Log, "LOGS.txt", "w");
	 fopen_s(&TreePrint, "TREE.txt", "w");
	 ASSERT(Fout);
	 ASSERT(TreePrint);
 }

 void Akinator(Tree* head)
 {
	 assert(Fin);
	 Node* NewNode = nullptr;

	 NewNode = RunDown(head);


	 printf("%s\n", NewNode->data);
	 char* answer = (char*)calloc(SIZEBUFF, sizeof(char));//

	 Checker(answer);

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
	 fopen_s(&Fin, "INPUT.txt", "r");
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
	 fclose(Fin);
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

	 char * firstbuffer = (char*)calloc(SIZEBUFF, sizeof(char));
	 char * answer = (char*)calloc(SIZEBUFF, sizeof(char));

	 ASSERT(firstbuffer);
	 ASSERT(answer);


	 Node* elem = head->root;
	 while (elem != nullptr)// !!!!!!!!!!!!!!!!!!!!!!!!!!
	 {
		 printf("\t%s\n\t", elem->data);
		 //system("start balcon.exe -f \"INPUT.txt\" -w");
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

	 char* firstbuffer = (char*)calloc(SIZEBUFF, sizeof(char));

	 if (buff[position] == '(')
	 {
		 position += 2;// avoid '(' & '\"' simbols
		 int counter(0);
		 while (buff[position] != '\"')
		 {
			 firstbuffer[counter] = buff[position];
			 counter++;
			 position++;
		 }

		 firstbuffer[counter] = '\0';
		 NewNode = AddElem(head, node, firstbuffer);

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
 

 void FindDiff(Tree* head)
 {
	 ASSERT(head);

	 fopen_s(&Sim, "SIMILAR.txt", "w");
	 fopen_s(&W1, "WORD1.txt", "w");
	 fopen_s(&W2, "WORD2.txt", "w");


	 char* firstword  = (char*)calloc(SIZEBUFF, sizeof(char));
	 char* secondword = (char*)calloc(SIZEBUFF, sizeof(char));

	 Checker(firstword);
	 Checker(secondword);

	 char* BuffForFirst = (char*)calloc(SIZEBUFF, sizeof(char));
	 Checker(BuffForFirst);

	 char* BuffForSecond = (char*)calloc(SIZEBUFF, sizeof(char));
	 Checker(BuffForSecond);

	 printf( "Add the first word\n");
	 scanf_s(" %[^\n]100s",  firstword, SIZEBUFF);
	 printf("Add the second word\n");
	 scanf_s(" %[^\n]100s", secondword, SIZEBUFF);

	 SearchDiff(head->root,  firstword, &BuffForFirst);//!Search(head->root, word))
	 SearchDiff(head->root, secondword, &BuffForSecond);


	 char** firstbuffer = (char**)calloc(SIZEBUFF, sizeof(char*));
	 int sizesim1 = SeparateWords(BuffForFirst, firstbuffer);


	 char** firstsecondbuffer = (char**)calloc(SIZEBUFF, sizeof(char*));
	 int sizesim2 = SeparateWords(BuffForSecond, firstsecondbuffer);


	 char** Similar = (char**)calloc(SIZEBUFF, sizeof(char*));
	 char** Differ = (char**)calloc(SIZEBUFF, sizeof(char*));

	 int NumberSim(0);
	 int NumberDiff(0);

	 for (int i(0); i < sizesim1 / 2; i++)
	 {
		 std::swap(firstbuffer[i], firstbuffer[sizesim1 - 1 - i]);
	 }

	 for (int i(0); i < sizesim2 / 2; i++)
	 {
		 std::swap(firstsecondbuffer[i], firstsecondbuffer[sizesim2 - 1 - i]);
	 }

	 int sizesim = min(sizesim1, sizesim2);

	 printf("SIMILAR\n");

	 for (int i(0); i < sizesim; i++)
	 {
			 if (!(strcmp(firstbuffer[i], firstsecondbuffer[i])))
			 {
				 printf("%s\n", firstbuffer[i]);// strcat_s(*buffs, SIZEBUFF, node->Parent->data);
				 fprintf(Sim, "%s", firstbuffer[i]);
				 Similar[NumberSim] = firstbuffer[i];
				 NumberSim++;
			 }
			 else
			 {
				 int point = i;
				 printf("%s: ", firstword);
				 fprintf(W1, "%s: ", firstword);
				 for (i; i < sizesim1 - 1; i++)
				 {
					 printf("%s and ", firstbuffer[i]);
					 fprintf(W1, "%s and ", firstbuffer[i]);
					 Differ[NumberDiff] = firstbuffer[i];
					 NumberDiff++;
				 }
				 printf("%s", firstbuffer[i]);
				 fprintf(W1, "%s", firstbuffer[i]);
				 printf("\nBut %s: ", secondword);
				 fprintf(W2, "\nBut %s: ", secondword);
				 for (i = point; i < sizesim2 - 1; i++)
				 {
					 printf("%s and ", firstsecondbuffer[i]);
					 fprintf(W2, "%s and ", firstsecondbuffer[i]);
					 Differ[NumberDiff] = firstsecondbuffer[i];
					 NumberDiff++;
				 }
				 printf("%s\n", firstsecondbuffer[i]);
				 fprintf(W2, "%s\n", firstsecondbuffer[i]);
			 }
	 }
	 CloseFindDiff(&firstword, &secondword, firstbuffer, firstsecondbuffer, &BuffForFirst, &BuffForSecond);
 }



 void CloseFindDiff(char**firstword, char** secondword, char** firstbuffer,
	 char** secondbuffer, char** BuffForFirst, char** BuffForSecond)
 {
	 fclose(Sim);
	 fclose(W1);
	 fclose(W2);

	 system("start balcon.exe -f \"SIMILAR.txt\" -w");
	 system("start balcon.exe -f \"WORD1.txt\" -w");
	 system("start balcon.exe -f \"WORD2.txt\" -w");

	 free(*firstword);
	 free(*secondword);
	 free(firstbuffer);//
	 free(secondbuffer);//
	 free(*BuffForFirst);
	 free(*BuffForSecond);
 }



 unsigned int SeparateWords(char* buff, char** firstbuffer)
 {
	 unsigned int i(0);
	 //char** firstbuffer = (char**)calloc(SIZEBUFF, sizeof(char*));
	 unsigned int j(0);
	 firstbuffer[j] = &(buff[0]);
	 j++;
	 unsigned int size = strlen(buff);
	 unsigned int counter(0);
	 while (i < size)
	 {
		 if (buff[i] == '|')
		 {
			 buff[i] = '\0';
			 counter++;
			 //printf("!!!!!!!\n");
		 }
		 i++;
	 }
	 i = 0;
	 while (i < size)
	 {
		 if (buff[i] == '\0')
		 {
			 firstbuffer[j] = &(buff[i + 1]);
			 j++;
		 }

		 i++;
	 }
	 return counter;
 }



 bool SearchDiff(Node* node, char* word, char** buffs)// сравнение
 {
	 ASSERT(node);
	 if (!strcmp(node->data, word))
	 {
		 PrintFromDiffer(node, buffs);
		 //printf("\nI found it!\n(%s)\n", node->data);
		 return true;
	 }
	 else
	 {
		 if ((node->Right) || (node->Left))
		 {
			 if (((node->Left) && (SearchDiff(node->Left, word, buffs))) || (((node->Right) && (SearchDiff(node->Right, word, buffs)))))
			 {
				 return true;
			 }
			 else
				 return false;
		 }
		 else
		 {
			 return false;
		 }
	 }
 }


 void PrintFromDiffer(Node* node, char** buffs)
 {
	 char* sep = "|";
	 char* negative = "not ";
	 ASSERT(node);
	 if (node->Parent)
	 {
		 if (!strcmp(node->Parent->Left->data, node->data))//this node is left
		 {
				 assert(node->Parent->data);
				 strcat_s(*buffs, SIZEBUFF, node->Parent->data);
				 strcat_s(*buffs, SIZEBUFF, sep);
				 //printf("%s ", node->Parent->data);
		 }
		 else
		 {
			 strcat_s(*buffs, SIZEBUFF, negative);
			 strcat_s(*buffs, SIZEBUFF, node->Parent->data);
			 strcat_s(*buffs, SIZEBUFF, sep);
			 //printf("%s ", node->Parent->data);
		 }
		 PrintFromDiffer(node->Parent, buffs);
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
	 fopen_s(&Dot, "DOTOUT.vg", "w");
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
	 //fopen_s(&Fin, "INPUT.txt", "w");
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
			 fprintf(Srch, "and %s ", node->Parent->data);
		 }
		 else
		 {
			 printf("not %s ", node->Parent->data);
			 fprintf(Srch, "not %s ", node->Parent->data);
		 }
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
		 fopen_s(&Srch, "SEARCH.txt", "w");
		 PrintFrom(node);
		 printf("\nI found it!\n(%s)\n", node->data);
		 return true;
	 }
	 else
	 {
		 if ((node->Right) || (node->Left))
		 {
			 if (((node->Left) && (Search(node->Left, word)))||(((node->Right) && (Search(node->Right, word)))))
			 {
				 return true;
			 }
			 else
			 {
				 return false;
			 }
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

#undef ASSERT
