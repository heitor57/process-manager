#include "utils.h"
#include "List.h"
#include "Process.h";

ArrayList load_program(char *file_name){
  int buffer_length =  4096;
  char buffer[buffer_length];
  FILE* program_file = fopen(file_name,"r");
  ArrayList program = createArrayList(NULL);

  char *aux;
  if(program_file==NULL){
    printf("Error opening file\n");
    return 1;
  }
 /*Create array list*/
  /*arraylist = createArrayList();*/

  while(fgets(buffer,buffer_length,program_file) != NULL){
    buffer[strlen(buffer)-1] = '\0';
<<<<<<< HEAD
    /*fread(buffer,buffer_length,1,program_file);*/
    /* aux = malloc(sizeof(char)*strlen(buffer)+1); */
    /* strcpy(aux,buffer); */
    /*addArrayList(const ArrayList arraylist, Object buffer);*/
    /* insertAtStartList(program,aux); */
=======
    aux = malloc(sizeof(char)*strlen(buffer)+1); 
    strcpy(aux, buffer);
    addArrayList(program, aux);
>>>>>>> eee2b5228639f65f69ad2edaa1159188b02c63ad
  }
  fclose(program_file);
  
  return program;
}

int unblockProcess(blocked_processes, ready_processes) {
  Node *node = getFirstNodeList(blocked_processes);
  Process* process = node->object;
  process->state = Ready;
  insertAtEndList(ready_processes, process);
  removeFromStartList(blocked_processes);
}