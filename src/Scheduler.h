#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "ProcessManager.h"
/* struct roundRobin{ */

/* }; */
/* typedef struct{ */
/*   void* scheduler_data; */
/*   Process* (*schedule)(ProcessManager*); */
/* }Scheduler; */
/* Scheduler* initScheduler(); */
/* void freeScheduler(); */
Process* round_robin(ProcessManager* pm);
/* Process* priorityScheduling(ProcessManager* pm); */
Process* shortest_remaining_time(ProcessManager* pm);
/* Process* priority_remaining_time(ProcessManager* pm); */
#endif
