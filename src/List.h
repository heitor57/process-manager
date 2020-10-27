typedef struct descriptor List;

#undef Object
#define Object void*

List* createList();
void freeList(List* li);
int insertAtEnd(List* li, Object o);
int insertAtSart(List* li, Object o);
int removeFromStart(List* li);
int removeFromEnd(List* li);
int sizeList(List* li);
int fullList(List* li);
int emptyList(List* li);
int getByIndex(List* li, int pos, Object o);
// int getByPid(List* li, int pid, Object object);
// void printList(List* li);
