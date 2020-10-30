#include "Scheduler.h"
ProcessManager* round_robin(ProcessManager* pm){

}

int priorityScheduling(ProcessManager* pm){
  
  insertAtEndList(pm->ready_processes,getArrayList(pm->pcb_table,pm->executing_process);) 
  int higherpriority = 0;
  for(int i=0; i<sizeList(pm->ready_processes);i++){
      if(getByIndexList(pm->ready_processes,i)->priority > higherpriority)
        higherpriority = getByIndexList(pm->ready_processes,i)->priority;
  }
  getByIndexList(pm->ready_processes,higherpriority)->priority -= 1; 
  pm->executing_process = higherpriority;
  return higherpriority;

}