#ifndef PROCESS_H
#define PROCESS_H
#include <stdbool.h>
typedef enum State State;
enum State {Blocked, Executing, Ready};
typedef struct{
  int id, parent_id, var, *pc, priority;
  char** program;
  State state;
  float init_time, cpu_usage;
}Process;
bool equalsProcess(const Object o1,const Object o2);
/* initProcess */
/* readInput */
/* createProcess */
/* processSwitch */
/* unblockFirstProcess */
/* freeProcess */
#endif
