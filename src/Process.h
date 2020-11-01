#ifndef PROCESS_H
#define PROCESS_H
#include <stdbool.h>
#include "ArrayList.h"
#define UNDEFINED -1
typedef enum State State;
enum State {Blocked, Executing, Ready};
typedef struct{
  int id, parent_id, var, *pc, priority,init_time, cpu_usage;
  ArrayList program;
  State state;
}Process;

bool equalsProcess(const Object o1,const Object o2);
Process* initProcess();
void freeProcess(Process* p);
Process* loadProgramProcess(Process* p, char* file_name);
/* Process* startInitProcess(); */
/* readInput */
/* createProcess */
/* processSwitch */
/* unblockFirstProcessManager */
/* freeProcess */
#endif
