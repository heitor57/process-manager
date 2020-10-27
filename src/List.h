struct process {
    int pid;
};
typedef struct descriptor List;

List* createList();
void freeList(List* li);
int insertAtEnd(List* li, struct process p);
int insertAtSart(List* li, struct process p);
int removeFromStart(List* li);
int removeFromEnd(List* li);
int sizeList(List* li);
int fullList(List* li);
int emptyList(List* li);
int getByPid(List* li, int pid, struct process *p);
int getByIndex(List* li, int pos, struct process *p);
void printList(List* li);
