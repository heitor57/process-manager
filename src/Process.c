#include "Process.h"
#include <stdbool.h>
#include <stdlib.h>
Process* initProcess(){
  Process* p = malloc(sizeof(Process));
  p->cpu_usage=0;
  p->state=Ready;
  p->cpu_usage=0;
  time(&p->init_time);
  if (p==NULL){
    exit(1);
  }
  return p;
}

void freeProcess(Process* p){
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
