#ifndef LIST_H
#define LIST_H
#include <stdbool.h> 


#undef Object
#define Object void*
/* typedef void* Object; */

typedef enum {TypesListProcess=314} TypesList;
struct node {
    Object object;
    struct node *next;
};
typedef struct node Node;

struct descriptor {
  TypesList type;
    struct node *start;
    struct node *end;
    int qty;
  bool (*equals)(const Object object_1, const Object object_2);
};
typedef struct descriptor List;


List* createList(TypesList type,bool (*equals)(const Object object_1, const Object object_2));
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
Node* getFirstNodeList(List* li);
// int getByPid(List* li, int pid, Object object);
// void printList(List* li);
#endif
