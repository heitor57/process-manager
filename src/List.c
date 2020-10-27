#include <stdio.h>
#include <stdlib.h>
#include "List.h"

List* createList(bool (*equals)(const Object object_1, const Object object_2)){
    List* li = (List*) malloc(sizeof(List));
    if(li != NULL){
        li->start = NULL;
        li->end = NULL;
        li->qty = 0;
        li->equals = equals;
    }
    return li;
}

void freeList(List* li){
    if(li != NULL){
        Node* node;
        while((li->start) != NULL){
            node = li->start;
            li->start = li->start->next;
            free(node);
        }
        free(li);
    }
}

int sizeList(List* li){
    if(li == NULL)
        return 0;
    return li->qty;
}

int fullList(List* li){
    return 0;
}

int emptyList(List* li){
    if(li == NULL)
        return 1;
    if(li->start == NULL)
        return 1;
    return 0;
}

int insertAtStartList(List* li, Object o){
    if(li == NULL)
        return 0;
    Node* node;
    node = (Node*) malloc(sizeof(Node));
    if(node == NULL)
        return 0;
    node->object = o;
    node->next = li->start;
    if(li->start == NULL)
        li->end = node;
    li->start = node;
    li->qty++;
    return 1;
}

int insertAtEndList(List* li, Object o){
    if(li == NULL)
        return 0;
    Node *node;
    node = (Node*) malloc(sizeof(Node));
    if(node == NULL)
        return 0;
    node->object = o;
    node->next = NULL;
    if(li->start == NULL)//empty list: insert at start
        li->start = node;
    else
        li->end->next = node;

    li->end = node;
    li->qty++;
    return 1;
}


int removeFromStartList(List* li){
    if(li == NULL)
        return 0;
    if(li->start == NULL)//empty list
        return 0;

    Node *node = li->start;
    li->start = node->next;
    free(node);
    if(li->start == NULL)
        li->end = NULL;
    li->qty--;
    return 1;
}

int removeFromEndList(List* li){
    if(li == NULL)
        return 0;
    if(li->start == NULL)//empty list
        return 0;

    Node *ant, *node = li->start;
    while(node->next != NULL){
        ant = node;
        node = node->next;
    }
    if(node == li->start){
        li->start = NULL;
        li->end = NULL;
    }else{
        ant->next = node->next;
        li->end = ant;
    }
    free(node);
    li->qty--;
    return 1;
}

int getByIndexList(List* li, int pos, Object o){
    if(li == NULL || li->start == NULL || pos <= 0)
        return 0;
    Node *node = li->start; //first node
    int i = 1;
    while(node != NULL && i < pos){
        node = node->next;
        i++;
    }
    if(node == NULL)
        return 0;
    else{
        o = node->object;
        return 1;
    }
}

int getObjectList(List* li, Object o){
    if(li == NULL || li->start == NULL)
        return -1;
    Node *node = li->start; //first node
    int i = 0;
    while(node != NULL){
        if(li->equals(o,node->object)){
          return i;
        }
        node = node->next;
        i++;
    }
    return -1;
}




// int getByPid(List* li, int pid, Object *o){
//     if(li == NULL || li->start == NULL)
//         return 0;
//     Node *node = li->start;
//     while(node != NULL && node->object.pid != pid)
//         node = node->next;
//     if(node->object.pid != pid)
//         return 0;
//     else{
//         *p = node->object;
//         return 1;
//     }
// }

// void printList(List* li){
//     if(li == NULL || li->start == NULL)
//         return;
//     Node* node = li->start;
//     while(node != NULL){
//         printf("pid: %d\n",node->object.pid);
//         node = node->next;
//     }
// }
