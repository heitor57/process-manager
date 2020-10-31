#include "Scheduler.h"

Process* round_robin(ProcessManager* pm){
  pm->cpu->used_time=0;
  pm->cpu->time_slice=1;
  /* if(sizeList(pm->ready_processes)==0){ */
  /*   if(pm->executing_process!=-1) */
  /*     return ((Process*)getArrayList(pm->pcb_table,pm->executing_process)); */
  /*   else */
  /*     return NULL; */
  /* } */
  if(sizeList(pm->ready_processes)>0){
    int* ready_pid = (int*)getByIndexList(pm->ready_processes, 0);
    return ((Process*)getArrayList(pm->pcb_table,*ready_pid));
  }else{
    if(pm->executing_process==-1){
      return NULL;
    }else{
      return ((Process*)getArrayList(pm->pcb_table,pm->executing_process));
    }
  }
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
