#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include "Process.h"
#include "ProcessManager.h"
#include "List.h"
#include "utils.h"

int main(void){
  int fd[2];
  int childpid;
  char readbuffer[80];
  FILE* init_file;
  int nbytes;
  ProcessManager pm;
  pipe(fd);
  if(pipe(fd) < 0) {
    perror("pipe");
    exit(1);
  }

  if((childpid = fork()) == -1){
    perror("fork");
    exit(1);
  }
  if(childpid == 0){
    // process manager
    close(fd[1]);
    dup2(fd[0],STDIN_FILENO);
    printf("Initializating process manager\n");
    
    /* init_file=fopen("init","r"); */
    /* if(init_file == NULL){ */
    /*   printf("Failed to start init file, it could be missing, check it out!\n"); */
    /* } */
    /* = load_program("init"); */
    while(strcmp(readbuffer,"q")){
      nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
      /* printf("%s",readbuffer); */
      /* printf("|| %s ||",readbuffer); */
      /* printf("%d",strlen(readbuffer)); */
      /* printf("LOL1\n"); */
      if(strlen(readbuffer)==1){
        /* printf("%s is a invalid instruction\n",readbuffer); */
        switch(readbuffer[0]){
        case 'Q':
          // Execute one instruction in CPU
          break;
        case 'U':
          // unblock first process
          unblockFirstProcess(pm.blocked_processes, pm.ready_processes); 
          break;
        case 'P':
          // print state
          break;
        case 'T':
          // print mean return time
          break;
        default:
          printf("%s is a invalid instruction\n",readbuffer);
        }
      }else{
        printf("%s is a invalid instruction, pass in the correct format\n",readbuffer);
      }
    }
    fclose(init_file);
    close(fd[0]);
  }else{
    close(fd[0]);
    while(1){
      // commander
      fgets(readbuffer,sizeof(readbuffer),stdin);
      readbuffer[strlen(readbuffer)-1] = 0;
      /* printf("\nENVIANDO: %s\n",readbuffer); */
      write(fd[1], readbuffer, strlen(readbuffer)+1);
      sleep(1.0);
    }
  }
  wait(0);
  return 0;
}
