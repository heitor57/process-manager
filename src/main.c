#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include "Process.h"
#include "ProcessManager.h"
#include "List.h"
#include "utils.h"

int main(void){
  srand(time(NULL));
  int fd[2];
  int childpid;
  char readbuffer[80];
  Process *init_process;
  // int nbytes;
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
    ProcessManager* pm = initProcessManager();
    /* init_process = startInitProcess(); */
    init_process = initProcess();
    init_process = newProcessProcessManager(pm);
    loadProgramProcess(init_process,"init");
    /* addProcessProcessManager(pm, init_process); */
    
    while(strcmp(readbuffer,"T")){
      // nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
      if(strlen(readbuffer)==1){
        switch(readbuffer[0]){
        case 'Q':
          // Execute one instruction in CPU
          stepTimeProcessManager(pm);
          break;
        case 'U':
          // unblock first process
          unblockFirstProcess(pm); 
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
    freeProcessManager(pm);
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
