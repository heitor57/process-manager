#ifndef CPU_H
#define CPU_H
#include "ArrayList.h"
#include <stdbool.h>
typedef struct{
  int var, pc;
  ArrayList program;
  int time_slice, used_time;
}CPU;

typedef union {
  int integer;
  char *string;
}ArgumentCPU;
CPU* initCPU();
void freeCPU(CPU* cpu);

bool isAllowedInstructionCPU(char instruction);
bool needArgInstructionCPU(char instruction);
/* void execInstructionCPU(CPU* cpu,char instruction_type,ArgumentCPU *arg); */
/* void parseInstruction(); */
/* execInstruction(int id) */
/* int updateVar(int new_value) */

/* int sumVar(int a, int b){  */
/* return a + b; */
/* } */

/* int subVar(int a,int b){ */
/* return a - b; */
/* } */
/* requestBlock */
/* requestTermination */
/* requestFork */
/* requestProcessSwitch(){ */
/* } */



/* void sjf(ArrayList process_ready){ */


/* } */
#endif
