#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
int main(void) {
  int fd[2];
  int bytes_read;
  char string[] = "Hate from Morocco!!!\n";
  char read_buffer[100];
  pid_t childpid;

  pipe(fd);
  if ((childpid = fork()) == -1) {
    perror("Fork");
    exit(1);
  }
  if (childpid == 0) {
    /* this is the child process. Closing up the input side of pipe*/
    printf("The value of input pipe is {%d}\n", fd[0]);
    close(fd[0]);
    /*Lets send something through the output stream*/
    write(fd[1], string, (strlen(string) + 1));
    exit(0);
  } else {
    /*This is the parent process going to close the output side of the pipe*/
    printf("The value of output pipe is {%d}\n", fd[1]);
    close(fd[1]);
    bytes_read = read(fd[0], read_buffer, sizeof(read_buffer));
    printf("The string we received is %s", read_buffer);
  }
  return (0);
}
