typedef struct{
  int *var, *pc;
  char** program;
  float time_slice, used_time;
}CPU;
CPU* initCPU();
void freeCPU(CPU* cpu);
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
