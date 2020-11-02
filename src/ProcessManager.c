#include "ProcessManager.h"
#include <stdbool.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "utils.h"
#include "CPU.h"
#include <errno.h>


bool integerEquals(const Object o1,const Object o2){
  int* v1= (int*)o1;
  int* v2= (int*)o2;
  if(*v1 == *v2)
    return true;
  else
    return false;
}

ProcessManager* initProcessManager(Process* (*runSchedulingPolicy)(ProcessManager*)){
  ProcessManager* pm = malloc(sizeof(ProcessManager));
  if (pm==NULL){
    perror("Could not allocate memory for Process Manager");
  }
  pm->time=0;
  pm->cpu=initCPU();
  pm->executing_process=UNDEFINED;
  pm->ready_processes=createList(integerEquals);
  pm->pcb_table=createArrayList(NULL);
  pm->blocked_processes=createList(integerEquals);
  pm->last_process_id=UNDEFINED;
  pm->runSchedulingPolicy=runSchedulingPolicy;
  pm->sum_return_time = 0;
  pm->num_finished = 0;
  return pm;
}

void freeProcessManager(ProcessManager* pm){
  if(pm!=NULL){
    Node *node = getFirstNodeList(pm->ready_processes);
    Process* process;
    int* pid;
    while(node != NULL){
      pid = ((int*)node->object);
      process = (Process*)getArrayList(pm->pcb_table, *pid);
      freeProcess(process);
      node = node->next;
    }
    node=getFirstNodeList(pm->blocked_processes);
    while(node != NULL){
      pid = ((int*)node->object);
      process = (Process*)getArrayList(pm->pcb_table, *pid);
      freeProcess(process);
      node = node->next;
    }
    if(pm->executing_process!=UNDEFINED)
      freeProcess(getArrayList(pm->pcb_table, pm->executing_process));
    freeList(pm->ready_processes);
    freeList(pm->blocked_processes);
    freeArrayList(pm->pcb_table);
    freeCPU(pm->cpu);
    free(pm);
  }else
    perror("Error in free Process Manager");
}

void stepTimeProcessManager(ProcessManager* pm){
  // simulate one time unit step in the process manager
  // Check if the system is empty of processes
  if(sizeList(pm->blocked_processes)+sizeList(pm->ready_processes)+
     (pm->executing_process == UNDEFINED? 0 : 1) > 0){
    Process* p = NULL;
    /* printf("\tScheduling %d %d\n",pm->cpu->used_time, pm->cpu->time_slice); */
    // check if the time slice exceeded
    if(pm->cpu->used_time >= pm->cpu->time_slice){
      // Next process to be executed
      p=pm->runSchedulingPolicy(pm);
    }
    if(p!=NULL || pm->executing_process!=UNDEFINED){
      /* printf("\tContext switch\n"); */
      contextSwitchProcessManager(pm,p);
      /* printf("\tSearch, decode and run\n"); */
      searchDecodeRunCPU(pm->cpu,pm);
      if(pm->executing_process!=UNDEFINED){
        Process* pt = (Process*)getArrayList(pm->pcb_table,pm->executing_process);
        pt->cpu_usage++;
      }
    }
  }
  pm->time+=1;
}
// new process and put it in all structures of ProcessManager
Process* newProcessProcessManager(ProcessManager* pm){
  Process* p = initProcess();
  p->init_time = pm->time;
  p->id = newPIDProcessManager(pm);
  addByIndexArrayList(pm->pcb_table,p,p->id);
  insertAtEndList(pm->ready_processes,&(p->id));
  return p;
}
// request new PID
int newPIDProcessManager(ProcessManager* pm){
  pm->last_process_id++;
  return pm->last_process_id;
}

// upate process data in PCB table after some execution at CPU
void updateProcessCPUProcessManager(CPU* cpu, Process* p){
  *(p->pc)=cpu->pc;
  p->var=cpu->var;
  if(p->program != cpu->program){

    for(int i =0;i<sizeArrayList(p->program);i++)
      free(getArrayList(p->program, i));
    freeArrayList(p->program);
    p->program=cpu->program;
    cpu->used_time=0;
    cpu->time_slice=0;
  }
}
void contextSwitchProcessManager(ProcessManager* pm, Process* p){
  Process* executing_process=NULL;
  if(p!=NULL && p->id != pm->executing_process){
    if(pm->executing_process != UNDEFINED){
      // get process
      executing_process = (Process*)getArrayList(pm->pcb_table,pm->executing_process);
      // update it data
      updateProcessCPUProcessManager(pm->cpu,executing_process);
      // change state
      executing_process->state = Ready;
      insertAtEndList(pm->ready_processes,&(executing_process->id));
    }
    // load other process in CPU
    pm->cpu->pc=*(p->pc);
    pm->cpu->var=p->var;
    pm->cpu->program=p->program;
    pm->executing_process=p->id;
    p->state = Executing;
    removeObjectList(pm->ready_processes, &(p->id));
  }
}
void forkProcessManager(ProcessManager* pm, Process* p){
  Process* newProcess = initProcess();
  *(newProcess->pc) = *(p->pc)+1;
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

void unblockFirstProcessManager(ProcessManager* pm) {
  if(sizeList(pm->blocked_processes)>0){
    Node *node = getFirstNodeList(pm->blocked_processes);
    Process* process = (Process*)node->object;
    process->state = Ready;
    insertAtEndList(pm->ready_processes, process);
    removeFromStartList(pm->blocked_processes);
  }
}

void blockExecutingProcessManager(ProcessManager* pm){
  insertAtEndList(pm->blocked_processes,
                  &(((Process*)getArrayList(pm->pcb_table,pm->executing_process))->id)
                  );
  pm->cpu->time_slice=0;
  pm->cpu->used_time=0;
  Process* p = ((Process*)getArrayList(pm->pcb_table,pm->executing_process));
  updateProcessCPUProcessManager(pm->cpu, p);
  p->state = Blocked;
  *(p->pc)+=1;
  p->cpu_usage+=1;
  pm->executing_process = UNDEFINED;
}
void finishExecutingProcessManager(ProcessManager* pm){
  Process* p = getArrayList(pm->pcb_table, pm->executing_process);
  freeProcess(p);
  cleanIndexArrayList(pm->pcb_table,pm->executing_process);
  pm->executing_process = UNDEFINED;
  pm->cpu->time_slice=0;
  pm->cpu->used_time=0;
  pm->sum_return_time += pm->time-p->init_time;
  pm->num_finished += 1;
}



void execInstructionCPU(CPU* cpu,char instruction_type,ArgumentCPU *arg, ProcessManager* pm){
  switch(instruction_type){
  case 'S':
    cpu->var = arg->integer;
    break;
  case 'A':
    cpu->var += arg->integer;
    break;
  case 'D':
    cpu->var -= arg->integer;
    break;
  case 'B':
    blockExecutingProcessManager(pm);
    break;
  case 'E':
    finishExecutingProcessManager(pm);
    break;
  case 'F':
    updateForkProcessManager(pm, cpu, (Process*)getArrayList(pm->pcb_table, pm->executing_process));
    cpu->pc += arg->integer;
    break;
  case 'R':
    cpu->pc = UNDEFINED;
    cpu->var = rand();
    cpu->program=load_program(arg->string);
    break;
  }
}
void parseAndExecInstructionCPU(CPU* cpu,char* instruction, ProcessManager* pm){
  char* token = strtok(instruction, " "), *token_aux;
  char instruction_type=token[0];
  ArgumentCPU arg;
  // check if is a allowed instruction
  if (strlen(token) != 1 || !isAllowedInstructionCPU(instruction_type)){
    fprintf(stderr,"Not allowed instruction \"%s\"\n",token);
    exit(EPERM);
  }
  bool need_arg = needArgInstructionCPU(instruction_type);
  if(!need_arg){
    if(strlen(instruction)!=1){
      fprintf(stderr,"Instruction in incorrect format \"%s\"\n",token);
      exit(EPERM);
    }else{
      execInstructionCPU(cpu,instruction_type,&arg, pm);
    }
  }else{
    token = strtok(NULL, " ");
    token_aux = strtok(NULL, " ");
    if(token_aux != NULL){
      fprintf(stderr,"More arguments than expected \"%s\"\n",token_aux);
      exit(EPERM);
    }
    switch(instruction_type){
    case 'S':
    case 'A':
    case 'D':
    case 'F':
      arg.integer = strtol(token,NULL,10);
      break;
    case 'R':
      arg.string = token;
      break;
    }
    execInstructionCPU(cpu, instruction_type, &arg, pm);
  }
}

void searchDecodeRunCPU(CPU *cpu, ProcessManager* pm){
  char* instruction = (char*)getArrayList(cpu->program,cpu->pc);
  int size = strlen(instruction)+1;
  // copy instruction in memory
  char* instruction_copy = malloc(size*sizeof(char));
  strcpy(instruction_copy, instruction);
  /* printf("\t\t%s\n",instruction_copy); */
  parseAndExecInstructionCPU(cpu,instruction_copy,pm);
  cpu->pc++;
  cpu->used_time++;
  free(instruction_copy);
}

void updateForkProcessManager(ProcessManager* pm, CPU* cpu, Process* p){
  updateProcessCPUProcessManager(cpu,p);
  forkProcessManager(pm, p);
}
