#include "stdafx.h"
#include "linkedList.h"


LinkedList* NewLinkedList()
{
  LinkedList* l = (LinkedList*)malloc(sizeof(LinkedList));
    
  l->deadNodes = NewStack();
  l->head  = nullptr;
  l->last  = nullptr;
  l->nelem = 0;
  
  return l;
}

ListNode* AddToLinkedList(LinkedList* l, void* e)
{

  ListNode* ln;
  
  if (!IsEmpty(l->deadNodes))
    ln = (ListNode*)Pop(l->deadNodes);
  else
    ln = (ListNode*)malloc(sizeof(ListNode));

  ln->data = e;
  ln->next = nullptr;
  ln->prev = l->last;
  
  if (l->head)
    l->last->next = ln;
  else
    l->head = ln;
  l->last = ln;
  
  l->nelem ++;
  return ln;
}


void* GetFromLinkedList(LinkedList* l, int x)
{
  if (! (0 <= x && x < LinkedListSize(l)) )
  {
    fprintf(stderr, "list index out of bounds, linkedList-size: %d, index: %d.\n", LinkedListSize(l), x);
  }
  
  ListNode* thisNode = TopOfLinkedList(l);
  int i;
  for (i=0; i<x; i++)
    thisNode = thisNode->next;
  return thisNode->data;

}

int LinkedListSize(LinkedList* l)
{
  return l->nelem;
}

void* PrevElement(LinkedList* l, ListNode** last)
{
  if (!*last) return nullptr;
  
  void* e = (*last)->data;
  *last = (*last)->prev;
  return e;
}

/******************************************************************************/

void* NextElement(LinkedList* l, ListNode** last)
{
  if (!*last) return nullptr;
  
  void* e = (*last)->data;
  *last = (*last)->next;
  return e;
}

int LinkedListContains(LinkedList* l, void* e)
{
  ListNode* iter = TopOfLinkedList(l);
  void* thisElement;
  
  while((thisElement = (ListNode*)NextElement(l, &iter)))
    if (thisElement==e) return 1;
  
  return 0;
}

ListNode* TopOfLinkedList(LinkedList* l)
{
  return l->head;
}

void RemoveFromLinkedList(LinkedList* l, ListNode* ln)
{
  if (!ln){
    fprintf(stderr, "Error: Tried to remove null element from linkedList.\n");
  }  
 
  if (ln->prev)
    ln->prev->next = ln->next;
  else
    l->head = ln->next;
   
  if (ln->next)
    ln->next->prev = ln->prev;
  else 
    l->last = ln->prev;

  Push(l->deadNodes, ln);
  l->nelem --;
}

void FreeLinkedList(LinkedList* l, void (*destructor)(void* e))
{
  
  ListNode* thisNode = l->head;
  while (thisNode)
  {
    ListNode* tmp = thisNode->next;    
    if (destructor) 
		destructor(thisNode->data);
	free(thisNode);
    thisNode = tmp;
  }
  FreeStack(l->deadNodes, free);
  free(l);
}
