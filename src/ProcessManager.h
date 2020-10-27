typedef struct{
  CPU *cpu;
  Process *executing_process;
  ArrayList ready_processes;
  ArrayList pcb_table;
  FIFO blocked_processes;
  int (*schedulingPolicy)(ArrayList *, Process *);
}ProcessManager;
