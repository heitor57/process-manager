#include "ProcessManager.h"
#include <stdbool.h>
#include <stdlib.h>
#include "ArrayList.h"
ProcessManager* initProcessManager(){
  ProcessManager* pm = malloc(sizeof(ProcessManager));
  if (pm==NULL){
    perror("Could not allocate memory for Process Manager");
  }
  pm->time=0;
  pm->cpu=initCPU();
  pm->executing_process=-1;
  pm->ready_processes=createList(NULL);
  pm->pcb_table=createArrayList(NULL);
  pm->blocked_processes=createList(NULL);
  pm->last_process_id=-1;
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

int newPIDProcessManager(ProcessManager* pm){
  return pm->last_process_id+1;
}

void addProcessProcessManager(ProcessManager* pm, Process* p){
  p->id=newPIDProcessManager(pm);
  pm->last_process_id=p->id;
  insertAtEndList(pm->ready_processes, p);
  addByIndexArrayList(pm->pcb_table, p, p->id);
}

void contextSwitchProcessManager(ProcessManager* pm, Process* p){
  Process* executing_process = (Process*)getArrayList(pm->pcb_table,pm->executing_process);
  if(p->id != executing_process->id){
    *(executing_process->pc)=pm->cpu->pc;
    executing_process->var=pm->cpu->var;
    executing_process->program=pm->cpu->program;

    pm->cpu->pc=*(p->pc);
    pm->cpu->var=p->var;
    pm->cpu->program=p->program;
  }
}

void forkProcessManager(ProcessManager* pm, Process* p){
  Process* newProcess = initProcess();
  *(newProcess->pc) = *(p->pc);
  newProcess->var = p->var;
  newProcess->program = duplicateStringArrayList(p->program);
  newProcess->priority = p->priority;
  newProcess->state = Ready;
  newProcess->init_time = pm->time;
  newProcess->id = newPIDProcessManager(pm);
  newProcess->parent_id = p->id;
  addByIndexArrayList(pm->pcb_table,newProcess,newProcess->id);
  insertAtEndList(pm->ready_processes, newProcess);
}

