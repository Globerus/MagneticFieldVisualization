#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdlib.h>

typedef struct
{
   int   num_slots;
   int   num_elements;
   void** arr; 

} ArrayList;

//int         VsetArrayListAt(ArrayList* l, void*  element, int index);
int         AddToArrayList(ArrayList* l, void* element);
void*       GetFromArrayList (ArrayList* l, int index);
void**      GetArrayFromArrayList(ArrayList* l);
int         ArrayListGetIndex(ArrayList* l, void* e);
int         ArrayListSize(ArrayList* l);
ArrayList*  NewArrayList();
void        FreeArrayList(ArrayList* l, void (*destructor)(void* e));
int         ArrayListContains(ArrayList*  l , void*  element);
void        FreeElements(ArrayList* l);
void        EmptyArrayList(ArrayList* l);

#endif