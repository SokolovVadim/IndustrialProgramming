#include "Differ.h"

 int main()
 {
	FopenFiles();

	size_t size = SizeofFile();

	Tree *head = ConstrTree();

	//TreeEntry(head, Read(size), size);

	CreateTree(Read(size), 0, head, nullptr);

	PrintDot(head);
	PrintText(head);

	fclose(Fin);
	system("start Run.bat");
	system("pause");

 }

 void FopenFiles()
 {
	fopen_s(&Fin,  "INPUT.txt",  "r");
	fopen_s(&Fout, "OUTPUT.txt", "w");
	fopen_s(&Log,  "LOGOUT.txt", "w");
	assert(Fin);
	assert(Fout);
	assert(Log);


 }

 Tree* ConstrTree()
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


 void Traversal(Node* node)
 {
	if (node->Left)
	{
		Traversal(node->Left);
	}
	else
	{
		if (node->Right)
			Traversal(node->Right);
		else
		{
			fprintf(Fout, "%s\n", node->data);
		}
	}
 }

 size_t SizeofFile()
 {
	ASSERT(Fin);

	fseek(Fin, 0, SEEK_END);

	int size(ftell(Fin));

	fseek(Fin, 0, SEEK_SET);


	assert(size > 0);

	return size;
 } 

 char* Read(size_t size)
 {

	char* buffer = (char*)calloc(SIZEBUFF, sizeof(double));

	ASSERT(buffer);

	int CheckDigit = fread(buffer, sizeof(char), size, Fin);

	buffer[size] = '\0';

	fprintf(Fout, "BUFFER: %s\n", buffer);

	BOOLCHECK(CheckValue(CheckDigit));

	return buffer;

 }

 int CreateTree(char* buff, int position, Tree* head, Node* node)
 {

	 Node* NewNode = (Node*)calloc(1, sizeof(Node));

	 char* firstbuffer = (char*)calloc(SIZEBUFF, sizeof(char));

	 if (buff[position] == '(')
	 {
		 position += 1;// avoid '(' & '\"' simbols
		 int counter(0);
		 while ((buff[position] != '(') && (buff[position] != ')'))
		 {
			 if ((buff[position] != '\n') && (buff[position] != '\r')
				 && (buff[position] != '\t') && (buff[position] != ' '))
			 {
				 firstbuffer[counter] = buff[position];
				 counter++;
			 }
			 position++;
		 }
		 firstbuffer[counter] = '\0';
		 fprintf(Log, "buff = %s\n", firstbuffer);
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


 void AvoidSpace(char** buff)
 {
	 ASSERT(*buff);
	 (*buff)++;
	 while ((**buff) != '\0')
	 {
		 if (((**buff) == ' ') || ((**buff) == '\n'))
			 (*buff)++;
		 else
			 break;
	 }
 }


 Node* AddElem(Tree* head, Node* node, NodeType value)
 {
	 ASSERT(head);
	 Node* NewNode = (Node*)calloc(1, sizeof(Node));

	 NewNode->data = value;
	 NewNode->Parent = node;
	 head->counter++;

	 if (head->root == nullptr)
	 {
		 head->root = NewNode;
		 return NewNode;
	 }

	 if (!node->Left)
		 node->Left = NewNode;
	 else
		 if (!node->Right)
			node->Right = NewNode;

	 return NewNode;
 }


 //int CreateTree(int position, char *buff, Node* node, Tree* head)
 //{
	// Node* NewNode = (Node*)calloc(1, sizeof(Node));

	// 




 //}

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
		 if (node->Parent != nullptr)
			 fprintf(Fin, ")\n");
	 }
 }






 inline bool CheckValue(int value)
 {
	 if (value <= 0)
		 return false;
	 else
		 return true;
	 return true;
 }

 #undef ASSERT
 #undef BOOLCHECK
