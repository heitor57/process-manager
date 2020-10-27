#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H
#include "CPU.h"
#include "Process.h"
#include "arraylist.h"
typedef struct{
  CPU *cpu;
  Process *executing_process;
  Arraylist ready_processes;
  Arraylist pcb_table;
  FIFO blocked_processes;
  int (*schedulingPolicy)(Arraylist *, Process *);
}ProcessManager;
#endif
