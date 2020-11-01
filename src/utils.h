#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include "List.h"
#include <string.h>
#include <stdlib.h>
#include "ArrayList.h"

// Load program in memory in a ArrayList of char* removing new line characters
ArrayList load_program(char *file_name);
/* void unblockFirstProcessManager(List* blocked_processes, List* ready_processes); */
#endif
