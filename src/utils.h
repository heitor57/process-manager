#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include "List.h"
#include <string.h>
#include <stdlib.h>

List* load_program(char *file_name);
int unblockProcess(blocked_processes, ready_processes);
#endif
