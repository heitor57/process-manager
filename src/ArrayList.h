/*
	arraylist.h
*/

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


/*
  constants
*/


/*
  type definitions
*/

#undef Object
#define Object void*

typedef struct ArrayList_Struct *ArrayList;


/*
  function declarations
*/
void freeArrayList(const ArrayList list);
ArrayList createArrayList(bool (*equals)(const Object object_1, const Object object_2));
bool addArrayList(const ArrayList list, Object object);
bool addByIndexArrayList(const ArrayList list, Object object, const int index);
bool removeArrayList(const ArrayList list, const Object object);
Object removeIndexArrayList(const ArrayList list, const int index);
bool containsArrayList(const ArrayList list, const Object object);
int indexOfArrayList(const ArrayList list, const Object object);
bool isEmptyArrayList(const ArrayList list);
int sizeArrayList(const ArrayList list);
Object getArrayList(const ArrayList list, const int index);
void clearArrayList(const ArrayList list);
ArrayList duplicateStringArrayList(const ArrayList list);
void cleanIndexArrayList(const ArrayList list, const int index);
#endif /* __defined_arraylist_h */
