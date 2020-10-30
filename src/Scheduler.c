#include "Scheduler.h"

Process* round_robin(ProcessManager* pm){

    int executing_process_index = pm->executing_process;
    int end_of_list = sizeArrayList(pm->pcb_table);
    
    if (executing_process_index == end_of_list -1) { // se esta no final da lista, volta pro inicio
        return (Process*)getArrayList(pm->pcb_table, 0);
    return (Process*)getArrayList(pm->pcb_table, pm->executing_process);
 
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