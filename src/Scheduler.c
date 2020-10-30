#include "Scheduler.h"
ProcessManager* round_robin(ProcessManager* pm){

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