#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H
#include "CPU.h"
#include "Process.h"
#include "List.h"
#include "ArrayList.h"
typedef struct ProcessManager ProcessManager;
struct ProcessManager{
  CPU* cpu;
  int time;
  int executing_process;
  List* ready_processes;
  ArrayList pcb_table;
  List* blocked_processes;
  int last_process_id;
  int (*runSchedulingPolicy)(ProcessManager*);
};

ProcessManager* initProcessManager();
void freeProcessManager(ProcessManager* pm);
void StepTimeProcessManager(ProcessManager* pm);
void addProcessProcessManager(ProcessManager* pm, Process* p);
int newPIDProcessManager(ProcessManager* pm);
void contextSwitchProcessManager(ProcessManager* pm, Process* p);
#endif
