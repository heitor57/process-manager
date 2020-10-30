#ifndef REPORTER_H
#define REPORTER_H
#include "ProcessManager.h"
#include "ArrayList.h"
#include "List.h"
void printState(ProcessManager* pm);

void printProcessList(ArrayList pcb_table,List* process_list);
#endif
