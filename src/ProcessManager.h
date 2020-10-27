#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H
#include "CPU.h"
#include "Process.h"
#include "List.h"

typedef struct{
  CPU *cpu;
  Process *executing_process;
  List ready_processes;
  List pcb_table;
  List blocked_processes;
  int (*schedulingPolicy)(List *, Process *);
}ProcessManager;
#endif
