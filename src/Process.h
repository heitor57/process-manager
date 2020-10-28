#ifndef PROCESS_H
#define PROCESS_H
#include <stdbool.h>
#include "List.h"
#include <time.h>

typedef enum State State;
enum State {Blocked, Executing, Ready};
typedef struct{
  int id, parent_id, var, *pc, priority;
  char** program;
  State state;
  time_t init_time;
  double cpu_usage;
  
}Process;

bool equalsProcess(const Object o1,const Object o2);
Process* initProcess();
void freeProcess(Process* p);
/* readInput */
/* createProcess */
/* processSwitch */
/* unblockFirstProcess */
/* freeProcess */
#endif
