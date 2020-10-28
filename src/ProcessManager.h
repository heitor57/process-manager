#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H
#include "CPU.h"
#include "Process.h"
#include "List.h"
typedef struct ProcessManager ProcessManager;
struct ProcessManager{
  CPU* cpu;
  int time;
  Process *executing_process;
  List* ready_processes;
  List* pcb_table;
  List* blocked_processes;
  int (*runSchedulingPolicy)(ProcessManager*);
};

ProcessManager* initProcessManager();
void freeProcessManager(ProcessManager* pm);
void StepTimeProcessManager(ProcessManager* pm);

#endif
