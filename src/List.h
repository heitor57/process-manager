#ifndef LIST_H
#define LIST_H
#include <stdbool.h> 
typedef struct descriptor List;

#undef Object
#define Object void*
/* typedef void* Object; */

List* createList();
void freeList(List* li);
int insertAtEndList(List* li, Object o);
int insertAtStartList(List* li, Object o);
int removeFromStartList(List* li);
int removeFromEndList(List* li);
int sizeList(List* li);
int fullList(List* li);
int emptyList(List* li);
int getByIndexList(List* li, int pos, Object o);
int getObjectList(List* li, Object o);
// int getByPid(List* li, int pid, Object object);
// void printList(List* li);
#endif
