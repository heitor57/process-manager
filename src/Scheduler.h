#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "ProcessManager.h"
/* struct roundRobin{ */

/* }; */
int round_robin(ProcessManager* pm);
int priorityScheduling(ProcessManager* pm);
#endif
