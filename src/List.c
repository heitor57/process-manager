#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Process.h"

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

int fullList(){
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

Node* getFirstNodeList(List* li){
  if(li == NULL || li->start == NULL)
    return 0;
  return li->start;
}

Object getByIndexList(List* li, int pos){
    if(li == NULL || li->start == NULL || pos < 0)
        return NULL;
    Node *node = li->start; //first node
    int i = 1;
    while(node != NULL && i < pos){
        node = node->next;
        i++;
    }
    if(node == NULL)
        return NULL;
    else{
        return node->object;
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


int removeObjectList(List* li, Object o){
  if(li == NULL || li->start == NULL || o == NULL)
    return -1;
  Node *node = li->start; //first node
  int i = 1;
  Node *previous_node= NULL;
  while(node != NULL && i < li->qty){
    if(li->equals(node->object,o)){
      break;
    }
    previous_node = node;
    node = node->next;
    i++;
  }
  if(previous_node != NULL && node !=NULL){
    previous_node->next = node->next;
  }
  if(i == 1){
    li->start = node->next;
  }
  li->qty--;
  if(node != NULL)
    free(node);
  return -1;
}
