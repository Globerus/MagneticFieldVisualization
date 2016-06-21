#include "stdafx.h"
#include "ArrayList.h"

int AddToArrayList(ArrayList* l, void* element)
{
   if (l->num_elements >= l->num_slots)
   {
   
      l->num_slots *= 2;
      l->arr = (void**)realloc(l->arr, (l->num_slots*sizeof(void*)));
     
      if (l->arr == NULL)
      {
         fprintf(stderr, "Error: Out of Memory.\n");
         return -1;
      }
   }
  
   l->arr[l->num_elements] = element;
   l->num_elements++;
   
   return (l->num_elements -1);
}

ArrayList* NewArrayList()
{
   ArrayList* l;
   l = (ArrayList*)malloc(sizeof(ArrayList));
   l->num_elements = 0;
   l->num_slots = 16;
   l->arr = (void**)malloc(16*sizeof(void*));
   return l;
}

int ArrayListGetIndex(ArrayList* l, void* e)
{
  int i;
  for (i=0; i<ArrayListSize(l); i++)
    if (GetFromArrayList(l, i) == e) 
		return i;
  return -1;
}

void** GetArrayFromArrayList(ArrayList* l)
{
   return l->arr;
}

int ArrayListContains(ArrayList*  l , void*  e)
{
   int i;
   for (i=0; i< l->num_elements; i++)
      if (e == l->arr[i]) 
		  return 1;
   return 0;
}

int ArrayListSize(ArrayList* l)
{
   return l->num_elements;
}

void*  GetFromArrayList (ArrayList* l, int index)
{
   if(index >= 0 && index <  l->num_elements)
      return l->arr[index];
      
   return NULL;
}

void FreeElements(ArrayList* l)
{
  int i;
  
  for (i=0; i<ArrayListSize(l); i++)
    free(GetFromArrayList(l,i));

}

void EmptyArrayList(ArrayList* l)
{
  l->num_elements=0; 
}

void FreeArrayList(ArrayList* l, void (*destructor)(void* e))
{
  int i;
  
  if (destructor)
    for (i=0;i<ArrayListSize(l); i++)
      destructor(GetFromArrayList(l,i));
  
  free(l->arr);
  free(l);
}