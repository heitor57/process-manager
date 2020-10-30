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
  Process* p = pm->runSchedulingPolicy(pm);
  contextSwitchProcessManager(pm,p);
  searchDecodeRunCPU(pm->cpu);
  p->cpu_usage++;
  pm->time+=1;
}

Process* newProcessProcessManager(ProcessManager* pm){
  Process* p = initProcess();
  p->init_time = pm->time;
  p->id = newPIDProcessManager(pm);
  addByIndexArrayList(pm->pcb_table,p,p->id);
  insertAtEndList(pm->ready_processes,&(p->id));
  return p;
}

int newPIDProcessManager(ProcessManager* pm){
  pm->last_process_id++;
  return pm->last_process_id;
}

/* void addProcessProcessManager(ProcessManager* pm, Process* p){ */
/*   p->id=newPIDProcessManager(pm); */
/*   pm->last_process_id=p->id; */
/*   insertAtEndList(pm->ready_processes, &(p->id)); */
/*   addByIndexArrayList(pm->pcb_table, p, p->id); */
/* } */

void contextSwitchProcessManager(ProcessManager* pm, Process* p){
  if(p->id != pm->executing_process){
    if(pm->executing_process != -1){
      Process* executing_process = (Process*)getArrayList(pm->pcb_table,pm->executing_process);
      *(executing_process->pc)=pm->cpu->pc;
      executing_process->var=pm->cpu->var;
      executing_process->program=pm->cpu->program;
      executing_process->state = Ready;
      insertAtEndList(pm->ready_processes,&(executing_process->id));
    }
    pm->cpu->pc=*(p->pc);
    pm->cpu->var=p->var;
    pm->cpu->program=p->program;
    pm->executing_process=p->id;
    p->state = Executing;
  }
}

void forkProcessManager(ProcessManager* pm, Process* p, int pc_diff){
  Process* newProcess = initProcess();
  *(newProcess->pc) = *(p->pc)+pc_diff;
  newProcess->var = p->var;
  newProcess->program = duplicateStringArrayList(p->program);
  newProcess->priority = p->priority;
  newProcess->state = Ready;
  newProcess->init_time = pm->time;
  newProcess->id = newPIDProcessManager(pm);
  newProcess->parent_id = p->id;
  addByIndexArrayList(pm->pcb_table,newProcess,newProcess->id);
  insertAtEndList(pm->ready_processes, &(newProcess->id));
}

void unblockFirstProcess(ProcessManager* pm) {
  Node *node = getFirstNodeList(pm->blocked_processes);
  Process* process = (Process*)node->object;
  process->state = Ready;
  insertAtEndList(pm->ready_processes, process);
  removeFromStartList(pm->blocked_processes);
}
