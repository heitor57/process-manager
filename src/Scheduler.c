#include "Scheduler.h"

Process* round_robin(ProcessManager* pm){
    int* ready_pid = (int*)getByIndexList(pm->ready_processes, 0);
    /* insertAtEndList(pm->ready_processes, */
    /*                 &(((Process*)getArrayList(pm->pcb_table,pm->executing_process))->id) */
    /*                 ); */
    return ((Process*)getArrayList(pm->pcb_table,*ready_pid));
}

Process* priorityScheduling(ProcessManager* pm){
  insertAtEndList(pm->ready_processes,
                  &(((Process*)getArrayList(pm->pcb_table,pm->executing_process))->id)
                  );
  int higherpriority = 0;
  for(int i=0; i<sizeList(pm->ready_processes);i++){
    if(((Process*)getByIndexList(pm->ready_processes,i))->priority > higherpriority)
      higherpriority = ((Process*)getByIndexList(pm->ready_processes,i))->priority;
  }
  ((Process*)getByIndexList(pm->ready_processes,higherpriority))->priority -= 1; 
  pm->executing_process = higherpriority;
  return higherpriority;

}
