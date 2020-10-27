typedef struct CPU CPU;
struct CPU{
  int var, pc;
  ArrayList program;
  float time_slice, used_time;
};
/* initCPU */
/* parseInstruction */
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
/* void freeCPU(CPU cpu){ */

/* } */

/* void sjf(ArrayList process_ready){ */


/* } */
