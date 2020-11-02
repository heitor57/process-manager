#include "CPU.h"
#include "utils.h"
#include "ArrayList.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <stdio.h> 

CPU* initCPU(){
  CPU* cpu = malloc(sizeof(CPU));
  cpu->used_time =0;
  cpu->time_slice =0;
  cpu->program=NULL;
  return cpu;
}

void freeCPU(CPU* cpu){
  // deliberately not freeing, because that the program has 2 owners double free can happen and others
  if(cpu!=NULL)
    free(cpu);
}
bool isAllowedInstructionCPU(char instruction){
  switch(instruction){
  case 'S':
  case 'A':
  case 'D':
  case 'B':
  case 'E':
  case 'F':
  case 'R':
    return true;
    break;
  default:
    return false;
  }
}

bool needArgInstructionCPU(char instruction){
  switch(instruction){
  case 'S':
  case 'A':
  case 'D':
  case 'F':
  case 'R':
    return true;
    break;
  default:
    return false;
  }
}

  
