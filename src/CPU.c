#include "CPU.h"
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

/* void parseAndExecInstruction(char *instruction){ */
/*   char* token = strtok(instruction, " "); */
/*   char operator=token[0]; */
/*   /\* bool is_allowed_instruction = false; *\/ */
/*   if (strlen(token) != 1 || !isAllowedInstructionCPU(operator)){ */
/*     return 1; */
/*   } */
/*   bool need_arg = needArgInstructionCPU(operator); */
/*   if(!need_arg){ */
/*     if(strlen(instruction)!=1){ */
/*       printf("Instruction in incorrect format\n"); */
/*       return 1; */
/*     }else{ */
/*       // TODO */
/*       return 0; */
/*     } */
/*   } */

/*   if(need_arg){ */
/*     /\* token = strtok(NULL, " "); *\/ */
/*     /\* char *arg = token; *\/ */
/*     // TODO */
/*     switch(operator){ */
/*     case "S": */
/*     case "A": */
/*     case "D": */
/*     case "F": */
/*       int arg = strol(instruction+1,NULL,10); */
/*       break; */
/*     case "R": */
/*       char* arg = instruction+2; */
/*       break; */
/*     } */
/*   } */
  
  
  /* for(int i=0; i<strlen(NEED_ARG_INSTRUCTIONS) ;i++){ */
  /*   if(token[0] == NEED_ARG_INSTRUCTIONS[i]){ */
  /*     return 1; */
  /*   } */
  /* } */
  
  /* token = strtok(NULL, " "); */
  /* switch(operator){ */
    
  /* } */
  /* int i=0; */
  /* while( token != NULL ) { */
  /*   token = strtok(NULL, " "); */
  /*   i++; */
  /* } */
/* } */

/* void execInstructionCPU(CPU* cpu,char instruction,void *arg){ */
/*   switch(instruction){ */
/*   case 'S': */
/*     cpu->var += 1; */
/*     break; */
/*   case 'A': */
/*     break; */

/*   case 'D': */
/*     break; */

/*   case 'B': */
/*     break; */

/*   case 'E': */
/*     break; */

/*   case 'F': */
/*     break; */

/*   case 'R': */
/*     break; */
/*   } */
/* } */
