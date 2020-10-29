#include "ProcessManager.h"
#include <stdbool.h>
#include <stdlib.h>
ProcessManager* initProcessManager(){
  ProcessManager* pm = malloc(sizeof(ProcessManager));
  if (pm==NULL){
    perror("Could not allocate memory for Process Manager");
  }
  pm->time=0;
  pm->cpu=initCPU();
  pm->executing_process=NULL;
  pm->ready_processes=createList(TypesListProcess,NULL);
  pm->pcb_table=createList(TypesListProcess,NULL);
  pm->blocked_processes=createList(TypesListProcess,NULL);
  return pm;
}

void freeProcessManager(ProcessManager* pm){
  if(pm!=NULL)
    free(pm);
  else
    perror("Error in free Process Manager");
}

void stepTimeProcessManager(ProcessManager* pm){
  pm->runSchedulingPolicy(pm);
  searchDecodeRunCPU(pm->cpu);
  pm->time+=1;
}
