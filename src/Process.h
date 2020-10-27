typedef enum State State;
enum State {Blocked, Executing, Ready};
struct Process{
  int id, parent_id,var, pc, priority;
  State state;
  float init_time, cpu_usage;
};


/* initProcess */
/* readInput */
/* createProcess */
/* processSwitch */
/* unblockFirstProcess */
/* freeProcess */
