#include <stdio.h>
#include <stdlib.h>
#include "List.h";
#include "Process.h";

void reporter(int time, Process executing_process, List *ready_processes, List *blocked_processes) {

    printf("****************************************************************\n");
    printf("Estado do sistema:\n");
    printf("****************************************************************\\\\\n\n");

    printf("TEMPO ATUAL: %d\n", time);
    printf("PROCESSO EXECUTANDO:\n");
    printf("%d\t%d\t%d\t%d\t%f\t%f\n", executing_process.id, executing_process.parent_id, 
                                     executing_process.priority, executing_process.var, 
                                     executing_process.init_time, executing_process.cpu_usage);

    printf("BLOQUEADO:\n");
    printf("Fila processos bloqueados:\n");
    printProcessList(blocked_processes);

    printf("PROCESSOS PRONTOS:\n");
    printProcessList(ready_processes);
    
    
}

void printProcessList(List* process_list) {
    Node *node = getFirstNodeList(process_list);
    Process process;
    while(node != NULL){
        process = node->object;
        printf("%d\t%d\t%d\t%d\t%f\t%f\n", process.id, process.parent_id, 
                                        process.priority, process.var, 
                                        process.init_time, process.cpu_usage);
    }
    node = node->next;
}
