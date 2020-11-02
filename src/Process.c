#include <stdbool.h>
#include <stdlib.h>
#include "utils.h"
#include "Process.h"
#include <errno.h>

Process* initProcess(){
  Process* p = malloc(sizeof(Process));
  p->id=UNDEFINED;
  p->parent_id=UNDEFINED;
  p->var=rand();
  p->cpu_usage=0;
  p->state=Ready;
  p->init_time=0;
  p->priority=0;
  p->pc = malloc(sizeof(int));
  if (p==NULL){
    exit(EPERM);
  }
  return p;
}

void freeProcess(Process* p){
  for(int i =0;i<sizeArrayList(p->program);i++)
    free(getArrayList(p->program, i));
  freeArrayList(p->program);
  if(p->pc!=NULL)
    free(p->pc);
  if(p!=NULL)
    free(p);
}

bool equalsProcess(const Object o1,const Object o2){
  Process* p1 = (Process*)o1;
  Process* p2 = (Process*)o2;
  if(p1->id == p2->id){
    return true;
  }else{
    return false;
  }
}


Process* loadProgramProcess(Process* p, char* file_name) {
  *(p->pc)=0;
  p->program = load_program(file_name);
  return p;
}
