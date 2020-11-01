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
#include <errno.h>
#define BUFFER_MAX_SIZE 80
int main(void){
  srand(time(NULL));
  int fd[2];
  int childpid,rchildpid;
  char readbuffer[BUFFER_MAX_SIZE];
  Process *init_process;
  /* int  */
  pipe(fd);
  if(pipe(fd) < 0) {
    perror("pipe");
    exit(errno);
  }

  if((childpid = fork()) == -1){
    perror("fork");
    exit(errno);
  }
  if(childpid == 0){
    // ========================= Process Manager ==================================
    close(fd[1]);
    dup2(fd[0],STDIN_FILENO);
    /* printf("Initializating process manager\n"); */
    // Init Process Manager
    ProcessManager* pm = initProcessManager(round_robin);
    int input_string_size;
    // load init
    init_process = newProcessProcessManager(pm);
    loadProgramProcess(init_process,"init");
    // Request input
    while(strcmp(readbuffer,"T")){
      // read from pipe
      read(fd[0], readbuffer, sizeof(readbuffer));
      input_string_size=strlen(readbuffer);
      // Check if is a valid entry
      if((input_string_size==2 && readbuffer[1] == '\n') || input_string_size==1){
        // treat given command
        switch(readbuffer[0]){
        case 'Q':
          // Execute one instruction in CPU
          /* printf("FORK: %d\n",pm->time); */
          stepTimeProcessManager(pm);
          break;
        case 'U':
          // Unblock first process
          unblockFirstProcessManager(pm); 
          break;
        case 'P':
          // Print state
          // ========================= Reporter ==================================
          if((rchildpid = fork()) == -1){
            perror("fork");
            exit(errno);
          }
          if (rchildpid == 0){
            printState(pm);
            exit(0);
          }
          break;
        case 'T':
          // Finish and print turnaround time
          // ========================= Reporter ==================================
          if((rchildpid = fork()) == -1){
            perror("fork");
            exit(errno);
          }
          if(rchildpid ==0){
            printf("The mean turnaround time is %lf\n",(double)(pm->sum_return_time)
                   /(double)(pm->num_finished));
            exit(0);
          }
          break;
        /* default: */
        /*   printf("%s is a invalid instruction\n",readbuffer); */
        }
      }else{
        /* printf("%s is a invalid instruction, pass in the correct format\n",readbuffer); */
      }
    }
    freeProcessManager(pm);
    close(fd[0]);
  }else{
    // ========================= Commander ==================================
    close(fd[0]);
    while(strcmp(readbuffer,"T")){
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
