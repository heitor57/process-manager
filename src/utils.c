#include "utils.h"
#include "List.h"

List* load_program(char *file_name){
  int buffer_length =  4096;
  char buffer[buffer_length];
  FILE* program_file = fopen(file_name,"r");

  /* List* program = createList(TypesListProcess,NULL); */
  char *aux;
  if(program_file==NULL){
    printf("Error opening file\n");
    return 1;
  }

  while(fgets(buffer,buffer_length,program_file) != NULL){
    buffer[strlen(buffer)-1] = '\0';
    /* aux = malloc(sizeof(char)*strlen(buffer)+1); */
    /* strcpy(aux,buffer); */
    /* insertAtStartList(program,aux); */
  }
  fclose(program_file);
  /* return program; */
}
