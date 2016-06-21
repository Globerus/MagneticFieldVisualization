#ifndef Stack_H
#define Stack_H
#include <stdlib.h>

typedef struct 
{
  int top;
  int slots;
  void** arr;

} Stack;

Stack*	NewStack();
void	Push(Stack* s, void*e);
void*	Pop(Stack* s);
int		StackSize(Stack* s);
void    FreeStack(Stack* s, void (*destructor)(void* e));
int     IsEmpty(Stack* s);
void    EmptyStack(Stack* s);

#endif