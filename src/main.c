#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
int main(void){
  int fd[2];
  int childpid;
  char readbuffer[80];
  int nbytes;
  /* pipe(fd); */
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
    while(strcmp(readbuffer,"q")){
      nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
      printf("%s",readbuffer);
    }
    close(fd[0]);
  }else{
    close(fd[0]);
    while(1){
      // commander
      fgets(readbuffer,sizeof(readbuffer),stdin);
      write(fd[1], readbuffer, strlen(readbuffer)+1);
      sleep(1.0);
    }
  }
  wait(0);
  return 0;
}
