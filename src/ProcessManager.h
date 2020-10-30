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
  int sum_return_time;
  int num_finished;
  Process* (*runSchedulingPolicy)(ProcessManager*);
};

ProcessManager* initProcessManager(Process* (*runSchedulingPolicy)(ProcessManager*));
void freeProcessManager(ProcessManager* pm);
void stepTimeProcessManager(ProcessManager* pm);
/* void addProcessProcessManager(ProcessManager* pm, Process* p); */
int newPIDProcessManager(ProcessManager* pm);
void contextSwitchProcessManager(ProcessManager* pm, Process* p);
void forkProcessManager(ProcessManager* pm, Process* p, int pc_diff);
Process* newProcessProcessManager(ProcessManager* pm);
void unblockFirstProcessManager(ProcessManager* pm);
void blockExecutingProcessManager(ProcessManager* pm);
void finishExecutingProcessManager(ProcessManager* pm);

void searchDecodeRunCPU(CPU *cpu, ProcessManager* pm);

#endif
