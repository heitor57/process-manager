#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Process.h"

void printProcessList(ArrayList pcb_table,List* process_list) {
    Node *node = getFirstNodeList(process_list);
    Process* process;
    int* pid;
    while(node != NULL){
      pid = ((int*)node->object);
      process = (Process*)getArrayList(pcb_table, *pid);
      /* process = ((Process*)node->object); */
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", process->id, process->parent_id, 
                                        process->priority, process->var, 
                                        process->init_time, process->cpu_usage);
        node = node->next;
    }
}

void reporter(int time, ArrayList pcb_table, Process executing_process, List *ready_processes, List *blocked_processes) {

    printf("****************************************************************\n");
    printf("Estado do sistema:\n");
    printf("****************************************************************\\\\\n\n");

    printf("TEMPO ATUAL: %d\n", time);
    printf("PROCESSO EXECUTANDO:\n");
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", executing_process.id, executing_process.parent_id, 
                                     executing_process.priority, executing_process.var, 
                                     executing_process.init_time, executing_process.cpu_usage);

    printf("BLOQUEADO:\n");
    printf("Fila processos bloqueados:\n");
    printProcessList(pcb_table,blocked_processes);

    printf("PROCESSOS PRONTOS:\n");
    printProcessList(pcb_table,ready_processes);
    
    
}

