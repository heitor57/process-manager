#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "ProcessManager.h"
/* struct roundRobin{ */

/* }; */
Process* round_robin(ProcessManager* pm);
int priorityScheduling(ProcessManager* pm);
#endif
