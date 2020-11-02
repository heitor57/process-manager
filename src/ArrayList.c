#include <string.h>
#include "ArrayList.h"

#define ARRAYLIST_INITIAL_CAPACITY 100
#define ARRAYLIST_CAPACITY_DELTA 100

static const size_t objectSize = sizeof(Object);

struct ArrayList_Struct {
  int currentCapacity;
  Object *data;
  int size;
  bool (*equals)(const Object object_1, const Object object_2);
};

void freeArrayList(const ArrayList list){
  free(list->data);
  free(list);
}


ArrayList createArrayList(bool (*equals)(const Object object_1, const Object object_2)){
  ArrayList list;

  list = (ArrayList)malloc(sizeof(struct ArrayList_Struct));
  list->currentCapacity = ARRAYLIST_INITIAL_CAPACITY;
  list->data = (Object *) malloc(objectSize * list->currentCapacity);
  list->size = 0;
  list->equals = equals;

  return list;
}

bool addArrayList(const ArrayList list, Object object){
  int oldSize = sizeArrayList(list);
  int newCapacity;
  Object *newData;

  (list->size)++;
  if (oldSize == list->currentCapacity)
    {
      newCapacity = list->currentCapacity + ARRAYLIST_CAPACITY_DELTA;
      newData = (Object *) malloc(objectSize * newCapacity);
      memcpy(newData, list->data, objectSize * oldSize);
      free(list->data);
      (list->data) = newData;
      list->currentCapacity = newCapacity;
    }
  (list->data)[oldSize] = object;
  return true;
}

bool addByIndexArrayList(const ArrayList list, Object object, const int index){
  int oldSize = sizeArrayList(list);
  int newCapacity;
  Object *newData;

  (list->size)++;
  if (oldSize == list->currentCapacity)
    {
      newCapacity = list->currentCapacity + ARRAYLIST_CAPACITY_DELTA;
      newData = (Object *) malloc(objectSize * newCapacity);
      memcpy(newData, list->data, objectSize * oldSize);
      free(list->data);
      (list->data) = newData;
      list->currentCapacity = newCapacity;
    }
  (list->data)[index] = object;
  for (int i = oldSize; i > index; i--) {
    (list->data)[i] = (list->data)[i-1];
  }
  return true;
}

bool removeArrayList(const ArrayList list, const Object object){
  int length = sizeArrayList(list);
  int lastIndex = length - 1;
  int newSize, newCapacity;
  int index;

  for (index = 0; index < length; index++)
  {
      if ((*list->equals)(getArrayList(list, index), object))
	{
	  (list->size)--;
	  if (index < lastIndex)
	    {
	      memmove(list->data + index, list->data + index + 1, objectSize * (lastIndex - index));
	      newSize = list->size;
	      newCapacity = list->currentCapacity - ARRAYLIST_CAPACITY_DELTA;
	      if (newCapacity > newSize)
		{
		  list->data = (Object *) realloc(list->data, objectSize * newCapacity);
		  list->currentCapacity = newCapacity;
		}
	    }
	  return true;
	}
  }
  return false;
}

bool containsArrayList(const ArrayList list, const Object object){
  return (indexOfArrayList(list, object) > -1);
}

int indexOfArrayList(const ArrayList list, const Object object){
  int length = sizeArrayList(list);
  int index;

  for (index = 0; index < length; index++)
    {
      if ((*list->equals)(getArrayList(list, index), object))
	{
	  return index;
	}
    }
  return -1;
}

bool isEmptyArrayList(const ArrayList list){
  return (0 == sizeArrayList(list));
}

int sizeArrayList(const ArrayList list){
  return list->size;
}

Object getArrayList(const ArrayList list, const int index){
  return list->data[index];
}

void clearArrayList(const ArrayList list){
  list->data = (Object *)realloc(list->data, objectSize * ARRAYLIST_INITIAL_CAPACITY);
  list->currentCapacity = ARRAYLIST_INITIAL_CAPACITY;
  list->size = 0;
}


Object removeIndexArrayList(const ArrayList list, const int index){
  int length = sizeArrayList(list);
  int lastIndex = length - 1;
  int newSize, newCapacity;
  Object o;

  o = list->data[index];

  (list->size)--;
  if (index < lastIndex){
    memmove(list->data + index, list->data + index + 1, objectSize * (lastIndex - index));
    newSize = list->size;
    newCapacity = list->currentCapacity - ARRAYLIST_CAPACITY_DELTA;
    if (newCapacity > newSize){
      list->data = (Object *)realloc(list->data, objectSize * newCapacity);
      list->currentCapacity = newCapacity;
    }
  }

  return o;
}


ArrayList duplicateStringArrayList(const ArrayList list){
  ArrayList new_list;
  new_list = (ArrayList)malloc(sizeof(struct ArrayList_Struct));
  new_list->currentCapacity = list->currentCapacity;
  new_list->data = (Object *) malloc(objectSize * new_list->currentCapacity);
  new_list->size = list->size;
  int string_size;
  for(int i=0; i < list->size;i++){
    string_size = (strlen(list->data[i])+1)*sizeof(char);
    new_list->data[i]= malloc(string_size);
    memcpy(new_list->data[i],list->data[i],string_size);
  }
  return new_list;
}

void cleanIndexArrayList(const ArrayList list, const int index){
  list->data[index] = NULL;
}
