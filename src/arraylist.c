/*
	arraylist.c
*/ 

#include <string.h>
#include "arraylist.h"

/*
  constants
*/
#define ARRAYLIST_INITIAL_CAPACITY 100
#define ARRAYLIST_CAPACITY_DELTA 100

static const size_t objectSize = sizeof(Object);


/*
  structures
*/
struct Arraylist_Struct {
  int currentCapacity;
  Object *data;
  int size;
  const Boolean (*equals)(const Object object_1, const Object object_2);
};


/*
  private function declarations
*/
static void *checkedMalloc(const size_t size);


void arraylistFree(const Arraylist list)
{
  free(list->data);
  free(list);
}

Arraylist arraylistCreate(const Boolean (*equals)(const Object object_1, const Object object_2))
{
  Arraylist list;

  list = (struct Arraylist *)malloc(sizeof(struct Arraylist_Struct));
  list->currentCapacity = ARRAYLIST_INITIAL_CAPACITY;
  list->data = (Object *) malloc(objectSize * list->currentCapacity);
  list->size = 0;
  list->equals = equals;

  return list;
}

Boolean arraylistAdd(const Arraylist list, Object object)
{
  int oldSize = arraylistSize(list);
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
  return TRUE;
}

Boolean arraylistRemove(const Arraylist list, const Object object)
{
  int length = arraylistSize(list);
  int lastIndex = length - 1;
  int newSize, newCapacity;
  int index;

  for (index = 0; index < length; index++)
  {
      if ((*list->equals)(arraylistGet(list, index), object))
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
	  return TRUE;
	}
  }
  return FALSE;
}

Boolean arraylistContains(const Arraylist list, const Object object)
{
  return (arraylistIndexOf(list, object) > -1);
}

int arraylistIndexOf(const Arraylist list, const Object object)
{
  int length = arraylistSize(list);
  int index;

  for (index = 0; index < length; index++)
    {
      if ((*list->equals)(arraylistGet(list, index), object))
	{
	  return index;
	}
    }
  return -1;
}

Boolean arraylistIsEmpty(const Arraylist list)
{
  return (0 == arraylistSize(list));
}

int arraylistSize(const Arraylist list)
{
  return list->size;
}

Object arraylistGet(const Arraylist list, const int index)
{
  return list->data[index];
}

void arraylistClear(const Arraylist list)
{
  list->data = (Object *)realloc(list->data, objectSize * ARRAYLIST_INITIAL_CAPACITY);
  list->currentCapacity = ARRAYLIST_INITIAL_CAPACITY;
  list->size = 0;
}

static void *checkedMalloc(const size_t size)
{
  void *data;

  data = malloc(size);
  if (data == NULL)
    {
      fprintf(stderr, "\nOut of memory.\n");
      fflush(stderr);
      exit(EXIT_FAILURE);
    }

  return data;
}

Object arraylistRemoveIndex(const Arraylist list, const int index)
{
  int length = arraylistSize(list);
  int lastIndex = length - 1;
  int newSize, newCapacity;
  Object o;

  o = list->data[index];

  (list->size)--;
  if (index < lastIndex)
  {
    memmove(list->data + index, list->data + index + 1, objectSize * (lastIndex - index));
	newSize = list->size;
	newCapacity = list->currentCapacity - ARRAYLIST_CAPACITY_DELTA;
	if (newCapacity > newSize)
	{
	  list->data = (Object *)realloc(list->data, objectSize * newCapacity);
	  list->currentCapacity = newCapacity;
	}
  }

  return o;
}

void arraylistSort(const Arraylist list, int (*compare)(const void * object_1, const void * object_2))
{
	qsort(list->data,
		  arraylistSize(list),
		  sizeof(Object),
		  compare);
}
