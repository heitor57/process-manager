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
void freeArrayList(const Arraylist list);
Arraylist createArrayList(const Boolean (*equals)(const Object object_1, const Object object_2));
Boolean addArrayList(const Arraylist list, Object object);
Boolean removeArrayList(const Arraylist list, const Object object);
Object removeIndexArrayList(const Arraylist list, const int index);
Boolean containsArrayList(const Arraylist list, const Object object);
int indexOfArrayList(const Arraylist list, const Object object);
Boolean isEmptyArrayList(const Arraylist list);
int sizeArrayList(const Arraylist list);
Object getArrayList(const Arraylist list, const int index);
void clearArrayList(const Arraylist list);
void sortArrayList(const Arraylist list, int (*compare)(const void * object_1, const void * object_2));


#endif /* __defined_arraylist_h */
