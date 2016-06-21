#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "stack.h"

typedef struct _ListNode
{
  void *data;
  struct _ListNode* next;
  struct _ListNode* prev;
 
} ListNode;

typedef struct 
{
  ListNode* head;
  ListNode* last;
  int nelem;
  Stack* deadNodes;

} LinkedList;

LinkedList* NewLinkedList();
ListNode*   AddToLinkedList(LinkedList* l, void* e);
void*       GetFromLinkedList(LinkedList* l, int i);
int         LinkedListSize(LinkedList* l);
void*       NextElement(LinkedList* l, ListNode** last);
ListNode*   TopOfLinkedList(LinkedList* l);
void        RemoveFromLinkedList(LinkedList* l, ListNode* ln);
void        FreeLinkedList(LinkedList* l, void (*destructor)(void* e));
int         LinkedListContains(LinkedList* l, void* e);

#endif