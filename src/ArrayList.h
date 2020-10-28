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

typedef struct ArrayList_Struct *ArrayList;


/*
  function declarations
*/
void freeArrayList(const ArrayList list);
ArrayList createArrayList(const Boolean (*equals)(const Object object_1, const Object object_2));
Boolean addArrayList(const ArrayList list, Object object);
Boolean removeArrayList(const ArrayList list, const Object object);
Object removeIndexArrayList(const ArrayList list, const int index);
Boolean containsArrayList(const ArrayList list, const Object object);
int indexOfArrayList(const ArrayList list, const Object object);
Boolean isEmptyArrayList(const ArrayList list);
int sizeArrayList(const ArrayList list);
Object getArrayList(const ArrayList list, const int index);
void clearArrayList(const ArrayList list);
void sortArrayList(const ArrayList list, int (*compare)(const void * object_1, const void * object_2));


#endif /* __defined_arraylist_h */
