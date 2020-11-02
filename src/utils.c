#include "utils.h"
#include "List.h"
#include "Process.h"
#include "ArrayList.h"
#define UTILS_BUFFER_MAX_SIZE 4096


ArrayList load_program(char *file_name){
  int buffer_length = UTILS_BUFFER_MAX_SIZE;
  char buffer[buffer_length];
  FILE* program_file = fopen(file_name,"r");
  ArrayList program = createArrayList(NULL);

  char *aux;
  if(program_file==NULL){
    printf("\"%s\" ",file_name);
    perror("error opening file");
    return NULL;
  }

  while(fgets(buffer,buffer_length,program_file) != NULL){
    buffer[strcspn(buffer,"\n")] = '\0';
    aux = malloc(sizeof(char)*(strlen(buffer)+1)); 
    strcpy(aux, buffer);
    addArrayList(program, aux);
  }
  fclose(program_file);
  
  return program;
}
