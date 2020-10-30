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
#include "Scheduler.h"
#include "reporter.h"

int main(void){
  srand(time(NULL));
  int fd[2];
  int childpid,rchildpid;
  char readbuffer[80];
  Process *init_process;
  /* int  */
  int nbytes;
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
    ProcessManager* pm = initProcessManager(round_robin);
    /* init_process = startInitProcess(); */
    init_process = initProcess();
    init_process = newProcessProcessManager(pm);
    loadProgramProcess(init_process,"init");
    /* addProcessProcessManager(pm, init_process); */
    
    while(strcmp(readbuffer,"T")){
      nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
      /* printf("%d\n",nbytes); */
      if(nbytes == 2/sizeof(char)){
        switch(readbuffer[0]){
        case 'Q':
          // Execute one instruction in CPU
          stepTimeProcessManager(pm);
          break;
        case 'U':
          // unblock first process
          unblockFirstProcessManager(pm); 
          break;
        case 'P':
          // print state
          if((rchildpid = fork()) == -1){
            perror("fork");
            exit(1);
          }
          if (rchildpid == 0){
            printState(pm);
          }

          break;
        case 'T':
          if((rchildpid = fork()) == -1){
            perror("fork");
            exit(1);
          }
          wait(rchildpid);
          printf("The turnaround time is %lf\n",(double)(pm->sum_return_time)
              /(double)(pm->num_finished));

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
