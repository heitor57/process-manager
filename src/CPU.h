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

#endif