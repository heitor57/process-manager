#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "ProcessManager.h"

// return the process to execute in the CPU
Process* round_robin(ProcessManager* pm);
#endif
