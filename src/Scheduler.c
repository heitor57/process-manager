#include "Scheduler.h"
#include <stdlib.h>

Process* round_robin(ProcessManager* pm){
  if(sizeList(pm->ready_processes)>0){
    pm->cpu->used_time=0;
    pm->cpu->time_slice=1;
    int* ready_pid = (int*)getByIndexList(pm->ready_processes, 0);
    return ((Process*)getArrayList(pm->pcb_table,*ready_pid));
  }else{
    if(pm->executing_process==UNDEFINED){
      pm->cpu->used_time=0;
      pm->cpu->time_slice=0;
      return NULL;
    }else{
      pm->cpu->used_time=0;
      pm->cpu->time_slice=1;
      return ((Process*)getArrayList(pm->pcb_table,pm->executing_process));
    }
  }
}
