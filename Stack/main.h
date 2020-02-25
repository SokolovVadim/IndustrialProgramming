#pragma once
void ConstructStack (Stack* stack);
void DestructStack  (Stack* stack);
void FopenError     (Stack* stack);
void dump           (Stack* stack);
void PrintErr       (Stack* stack);
void Resize         (Stack* stack);
void PrintOk        (Stack* stack);
void PrintHash      (Stack* stack);

void FileOpen();

StackType push      (Stack *stack, StackType digit);
StackType pop       (Stack *stack);
StackType back      (Stack *stack);
int Hash            (Stack *stack);
int size            (Stack *stack);

bool clear          (Stack *stack);
bool ExitData       (Stack *stack);
bool StackOk        (Stack *stack);

int main()
{
	Stack             StackTool = {};
	FileOpen();
	FopenError        (&StackTool);
	ConstructStack    (&StackTool);
	push              (&StackTool, 1.197);
	pop               (&StackTool);
	push              (&StackTool, 1.337);
	push              (&StackTool, 4.9876);
	push              (&StackTool, 98.337);
	push              (&StackTool, 9876.87);
	dump              (&StackTool);
	ExitData          (&StackTool);
	Hash              (&StackTool);
	pop               (&StackTool);
	ExitData          (&StackTool);
	Hash              (&StackTool);
	push              (&StackTool, 9.1029);
	push              (&StackTool, 10.1239);
	dump              (&StackTool);
	Resize            (&StackTool);
	size              (&StackTool);
	push              (&StackTool, 11.987);
	push              (&StackTool, 11.987);
	push              (&StackTool, 19.987);
	push              (&StackTool, 152.25);
	push              (&StackTool, 25.7);
	dump              (&StackTool);
	back              (&StackTool);
	back              (&StackTool);
	back              (&StackTool);
	pop               (&StackTool);
	pop               (&StackTool);
	pop               (&StackTool);
	dump              (&StackTool);
	PrintErr          (&StackTool);
	DestructStack     (&StackTool);
}