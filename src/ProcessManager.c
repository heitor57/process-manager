#include "ProcessManager.h"
#include <stdbool.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "utils.h"
#include "CPU.h"
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
  pm->executing_process=-1;
  pm->ready_processes=createList(integerEquals);
  pm->pcb_table=createArrayList(NULL);
  pm->blocked_processes=createList(integerEquals);
  pm->last_process_id=-1;
  pm->runSchedulingPolicy=runSchedulingPolicy;
  pm->sum_return_time = 0;
  pm->num_finished = 0;
  return pm;
}

void freeProcessManager(ProcessManager* pm){
  if(pm!=NULL)
    free(pm);
  else
    perror("Error in free Process Manager");
}
/* #include "Scheduler.h" */
void stepTimeProcessManager(ProcessManager* pm){
  if(sizeList(pm->blocked_processes)+sizeList(pm->ready_processes)+
     (pm->executing_process == -1? 0 : 1) > 0){
    Process* p = NULL;
    printf("\tScheduling\n");
    if(pm->cpu->used_time >= pm->cpu->time_slice)
      p=pm->runSchedulingPolicy(pm);
    /* printf("%p %d\n",p,pm->executing_process); */
    if(p!=NULL || pm->executing_process!=-1){
      printf("\tContext switch\n");
      contextSwitchProcessManager(pm,p);
      printf("\tSearch, decode and run\n");
      searchDecodeRunCPU(pm->cpu,pm);
      if(pm->executing_process!=-1){
        Process* pt = (Process*)getArrayList(pm->pcb_table,pm->executing_process);
        pt->cpu_usage++;
      }
    }
  }
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


void updateProcessCPUProcessManager(CPU* cpu, Process* p){
  *(p->pc)=cpu->pc;
  p->var=cpu->var;
  if(p->program != cpu->program){
    /* printf("DIFF E E E%p %p\n",cpu->program,p->program); */
    freeArrayList(p->program);
    p->program=cpu->program;
  }
}
void contextSwitchProcessManager(ProcessManager* pm, Process* p){
  Process* executing_process=NULL;
  if(p!=NULL && p->id != pm->executing_process){
    if(pm->executing_process != -1){
      executing_process = (Process*)getArrayList(pm->pcb_table,pm->executing_process);
      updateProcessCPUProcessManager(pm->cpu,executing_process);
      /* *(executing_process->pc)=pm->cpu->pc; */
      /* executing_process->var=pm->cpu->var; */
      /* executing_process->program=pm->cpu->program; */
      /* } */
      /*     if(pm->executing_process != -1){ */
      executing_process->state = Ready;
      insertAtEndList(pm->ready_processes,&(executing_process->id));
    }
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
  /* printf("Ewwqe%d \n",p->pc); */
  *(newProcess->pc) = *(p->pc)+1;
  newProcess->var = p->var;
  newProcess->program = duplicateStringArrayList(p->program);
  /* printf("EEE\n"); */
  newProcess->priority = p->priority;
  newProcess->state = Ready;
  newProcess->init_time = pm->time;
  newProcess->id = newPIDProcessManager(pm);
  newProcess->parent_id = p->id;
  addByIndexArrayList(pm->pcb_table,newProcess,newProcess->id);
  insertAtEndList(pm->ready_processes, &(newProcess->id));
}

void unblockFirstProcessManager(ProcessManager* pm) {
  Node *node = getFirstNodeList(pm->blocked_processes);
  Process* process = (Process*)node->object;
  process->state = Ready;
  insertAtEndList(pm->ready_processes, process);
  removeFromStartList(pm->blocked_processes);
}

void blockExecutingProcessManager(ProcessManager* pm){
  insertAtEndList(pm->blocked_processes,
                  &(((Process*)getArrayList(pm->pcb_table,pm->executing_process))->id)
                  );
  ((Process*)getArrayList(pm->pcb_table,pm->executing_process))->state = Blocked;
  pm->executing_process = -1;
}
void finishExecutingProcessManager(ProcessManager* pm){
  Process* p = getArrayList(pm->pcb_table, pm->executing_process);
  free(p->pc);
  freeArrayList(p->program);
  removeIndexArrayList(pm->pcb_table, pm->executing_process);
  pm->executing_process = -1;
  pm->sum_return_time += pm->time;
  pm->num_finished += 1;
}



int execInstructionCPU(CPU* cpu,char instruction_type,ArgumentCPU *arg, ProcessManager* pm){
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
    cpu->pc = -1;
    cpu->var = rand();
    /* printf("EEE %s\n",arg->string); */
    cpu->program=load_program(arg->string);
    break;
  }
  return 0;
}
int parseAndExecInstructionCPU(CPU* cpu,char* instruction, ProcessManager* pm){
  char* token = strtok(instruction, " ");
  char instruction_type=token[0];
  ArgumentCPU arg;
  /* bool is_allowed_instruction = false; */
  if (strlen(token) != 1 || !isAllowedInstructionCPU(instruction_type)){
    return 1;
  }
  bool need_arg = needArgInstructionCPU(instruction_type);
  if(!need_arg){
    if(strlen(instruction)!=1){
      printf("Instruction in incorrect format\n");
      return 1;
    }else{
      return execInstructionCPU(cpu,instruction_type,&arg, pm);
    }
  }else{
    token = strtok(NULL, " ");
    /* if(token[0] != ' '){ */
    /*   printf("Missing space between instruction and argument\n"); */
    /*   return 1; */
    /* } */
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
    return execInstructionCPU(cpu, instruction_type, &arg, pm);
  }
}

void searchDecodeRunCPU(CPU *cpu, ProcessManager* pm){
  /* printf("eqweqwe\n"); */
  /* printf("%d %d\n",cpu->pc, 1); */
  /* printf("%d %d\n",1, sizeArrayList(cpu->program)); */
  /* printf("%d %d\n",cpu->pc, sizeArrayList(cpu->program)); */
  char* instruction = (char*)getArrayList(cpu->program,cpu->pc);
  /* printf("\t\t%s\n",instruction); */
  int size = strlen(instruction)+1;
  char* instruction_copy = malloc(size*sizeof(char));
  strcpy(instruction_copy, instruction);
  printf("\t\t%s\n",instruction_copy);
  parseAndExecInstructionCPU(cpu,instruction_copy,pm);
  cpu->pc++;
  cpu->used_time++;
  free(instruction_copy);
}

void updateForkProcessManager(ProcessManager* pm, CPU* cpu, Process* p){
  updateProcessCPUProcessManager(cpu,p);
  forkProcessManager(pm, p);
}
