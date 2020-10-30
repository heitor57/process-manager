#include "Scheduler.h"

int round_robin(ProcessManager* pm){
    int* ready_pid = (int*)getByIndexList(pm->ready_processes, 0);
    insertAtEndList(pm->ready_processes,
                    &(((Process*)getArrayList(pm->pcb_table,pm->executing_process))->id)
                    );
    pm->executing_process = *ready_pid;
    return 0;
}

int priorityScheduling(ProcessManager* pm){
  
  int higherpriority = 0;
  for(int i=0; i<sizeList(pm->ready_processes);i++){
      if(getByIndexList(pm->ready_processes,i)->priority > higherpriority)
        higherpriority = getByIndexList(pm->ready_processes,i)->priority;
  }
  getByIndexList(pm->ready_processes,higherpriority)->priority -= 1; 
  return higherpriority;
  
}
