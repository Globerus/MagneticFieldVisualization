#include "stdafx.h"
#include "stack.h"

Stack* NewStack()
{
  Stack* s = (Stack*)malloc(sizeof(Stack));
  
  s->top   = 0;
  s->slots = 2;
  s->arr = (void**)malloc(2*sizeof(void*));
  
  return s;
}


int StackSize(Stack *s)
{
  return s->top;
}

int IsEmpty(Stack *s)
{
  return (s->top == 0);
}

void EmptyStack(Stack *s)
{
  s->top = 0;
}

void  Push(Stack* s, void* e)
{
  if (s->top >= s->slots)
   {
      s->slots *= 2;
      s->arr = (void**)realloc(s->arr, (s->slots*sizeof(void*)));
      
	  if (s->arr == NULL)
      {
         fprintf(stderr, "Error: Out of Memory.\n");
         exit(1);
      }
   }
 
   s->arr[s->top] = e;
   s->top ++;
}

void* Pop(Stack* s)
{
  if (s->top == 0) 
	  return NULL;  
  s->top--;
  return s->arr[s->top];
}

void FreeStack(Stack* s, void (*destructor)(void* e))
{
  void* e;
  if (destructor)
    while ((e = Pop(s)))
      destructor(e); 
      
  free(s->arr);
  free(s);
}
