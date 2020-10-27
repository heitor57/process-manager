/*
	arraylist.h
*/

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdlib.h>
#include <stdio.h>


/*
  constants
*/
#undef TRUE
#define TRUE 1

#undef FALSE
#define FALSE 0


/*
  type definitions
*/
#undef Boolean
#define Boolean short unsigned int

#undef Object
#define Object void*

typedef struct Arraylist_Struct *Arraylist;


/*
  function declarations
*/
void arraylistFree(const Arraylist list);
Arraylist arraylistCreate(const Boolean (*equals)(const Object object_1, const Object object_2));
Boolean arraylistAdd(const Arraylist list, Object object);
Boolean arraylistRemove(const Arraylist list, const Object object);
Object arraylistRemoveIndex(const Arraylist list, const int index);
Boolean arraylistContains(const Arraylist list, const Object object);
int arraylistIndexOf(const Arraylist list, const Object object);
Boolean arraylistIsEmpty(const Arraylist list);
int arraylistSize(const Arraylist list);
Object arraylistGet(const Arraylist list, const int index);
void arraylistClear(const Arraylist list);
void arraylistSort(const Arraylist list, int (*compare)(const void * object_1, const void * object_2));


#endif /* __defined_arraylist_h */
