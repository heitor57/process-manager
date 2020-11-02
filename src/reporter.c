#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Process.h"
#include "ProcessManager.h"

void printProcessList(ArrayList pcb_table,List* process_list) {
    Node *node = getFirstNodeList(process_list);
    Process* process=NULL;
    int* pid=NULL;
    printf("PID\tPPID\tPrioridade\tValor\tTempo início\tCPU usada até o momento\n");
    while(node != NULL){
      pid = ((int*)node->object);
      process = (Process*)getArrayList(pcb_table, *pid);
      /* process = ((Process*)node->object); */
      printf("%d\t%d\t%d\t\t%d\t%d\t\t%d\n", process->id, process->parent_id, 
             process->priority, process->var, 
             process->init_time, process->cpu_usage);
      node = node->next;
    }
}

void printState(ProcessManager* pm) {
  Process* executing_process=NULL;
  printf("****************************************************************\n");
  printf("Estado do sistema:\n");
  printf("****************************************************************\\\\\n\n");

  printf("TEMPO ATUAL: %d\n", pm->time);
  if(pm->executing_process!=UNDEFINED){
    printf("PROCESSO EXECUTANDO:\n");
    printf("PID\tPPID\tPrioridade\tValor\tTempo início\tCPU usada até o momento\n");
    executing_process = (Process*)getArrayList(pm->pcb_table, pm->executing_process);
    printf("%d\t%d\t%d\t\t%d\t%d\t\t%d\n", executing_process->id, executing_process->parent_id, 
           executing_process->priority, executing_process->var, 
           executing_process->init_time, executing_process->cpu_usage);
  }
//   printf("BLOQUEADO:\n");
//   printf("Fila processos bloqueados:\n");
  if(sizeList(pm->blocked_processes)){
    printf("PROCESSOS BLOQUEADOS:\n");
    printProcessList(pm->pcb_table,pm->blocked_processes);
  }

  if(sizeList(pm->ready_processes)){
    printf("PROCESSOS PRONTOS:\n");
    printProcessList(pm->pcb_table,pm->ready_processes);
  }
  printf("****************************************************************\n");
}

