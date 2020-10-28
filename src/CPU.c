#include "CPU.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <stdio.h> 

CPU* initCPU(){
  return malloc(sizeof(CPU));
}

void freeCPU(CPU* cpu){
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
    return true;
    break;
  default:
    return false;
  }
}

int execInstructionCPU(CPU* cpu,char instruction_type,ArgumentCPU *arg){
  int buffer_length = 4096;
  char buffer[buffer_length];
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
    break;

  case 'E':
    break;

  case 'F':
    break;
  case 'R':
    load_program(arg->string);
    break;
  }
  return 0;
}
int parseAndExecInstructionCPU(CPU* cpu,char *instruction){
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
      return execInstructionCPU(cpu,instruction_type,&arg);
    }
  }else{
    token = strtok(NULL, " ");
    if(token[0] != ' '){
      printf("Missing space between instruction and argument\n");
      return 1;
    }

    switch(instruction_type){
    case 'S':
    case 'A':
    case 'D':
    case 'F':
      arg.integer = strtol(instruction+1,NULL,10);
      break;
    case 'R':
      arg.string = instruction+2;
      break;
    }
    return execInstructionCPU(cpu, instruction_type, &arg);
  }
}

int searchDecodeRunCPU(CPU *cpu){
  
}
  
