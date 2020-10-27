#ifndef PROCESS_H
#define PROCESS_H
typedef enum State State;
enum State {Blocked, Executing, Ready};
typedef struct{
  int id, parent_id, var, *pc, priority;
  char** program;
  State state;
  float init_time, cpu_usage;
}Process;


/* initProcess */
/* readInput */
/* createProcess */
/* processSwitch */
/* unblockFirstProcess */
/* freeProcess */

#endif
