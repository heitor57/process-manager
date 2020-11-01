#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H
#include "CPU.h"
#include "Process.h"
#include "List.h"
#include "ArrayList.h"
typedef struct ProcessManager ProcessManager;
struct ProcessManager{
  CPU* cpu;
  int time, executing_process,last_process_id,sum_return_time,num_finished;
  ArrayList pcb_table;
  List* ready_processes,*blocked_processes;
  Process* (*runSchedulingPolicy)(ProcessManager*);
};

ProcessManager* initProcessManager(Process* (*runSchedulingPolicy)(ProcessManager*));
void freeProcessManager(ProcessManager* pm);
void stepTimeProcessManager(ProcessManager* pm);
/* void addProcessProcessManager(ProcessManager* pm, Process* p); */
int newPIDProcessManager(ProcessManager* pm);
void contextSwitchProcessManager(ProcessManager* pm, Process* p);
void forkProcessManager(ProcessManager* pm, Process* p);
Process* newProcessProcessManager(ProcessManager* pm);
void unblockFirstProcessManager(ProcessManager* pm);
void blockExecutingProcessManager(ProcessManager* pm);
void finishExecutingProcessManager(ProcessManager* pm);

void searchDecodeRunCPU(CPU *cpu, ProcessManager* pm);

void updateForkProcessManager(ProcessManager* pm, CPU* cpu, Process* p);
#endif
