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
  Process* (*runSchedulingPolicy)(ProcessManager*);
};

ProcessManager* initProcessManager();
void freeProcessManager(ProcessManager* pm);
void stepTimeProcessManager(ProcessManager* pm);
/* void addProcessProcessManager(ProcessManager* pm, Process* p); */
int newPIDProcessManager(ProcessManager* pm);
void contextSwitchProcessManager(ProcessManager* pm, Process* p);
void forkProcessManager(ProcessManager* pm, Process* p, int pc_diff);
Process* newProcessProcessManager(ProcessManager* pm);
void unblockFirstProcess(ProcessManager* pm);
void finishProcessProcessManager(ProcessManager* pm);
void blockExecuting(ProcessManager* pm);

void searchDecodeRunCPU(CPU *cpu, ProcessManager* pm);

#endif
