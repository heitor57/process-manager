#ifndef LIST_H
#define LIST_H
#include <stdbool.h> 


#undef Object
#define Object void*
/* typedef void* Object; */

struct node {
    Object object;
    struct node *next;
};
typedef struct node Node;

struct descriptor {
    struct node *start;
    struct node *end;
    int qty;
  bool (*equals)(const Object object_1, const Object object_2);
};
typedef struct descriptor List;


List* createList(bool (*equals)(const Object object_1, const Object object_2));
void freeList(List* li);
int insertAtEndList(List* li, Object o);
int insertAtStartList(List* li, Object o);
int removeFromStartList(List* li);
int removeFromEndList(List* li);
int sizeList(List* li);
int fullList();
int emptyList(List* li);
Object getByIndexList(List* li, int pos);
int getObjectList(List* li, Object o);
Node* getFirstNodeList(List* li);
int removeObjectList(List* li, Object o);
#endif
