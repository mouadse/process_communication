#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  pid_t pid;
  printf("Enter the pid of the process to send the signal to: ");
  scanf("%d", &pid);
  // check permission
  if (kill(pid, 0) == -1) {
    printf("Process with pid %d does not exist\n", pid);
    return 1;
  }
  // wait so we can send unlimited signals each second
  struct sigaction act;
  act.sa_handler = SIG_IGN;
  sigaction(SIGALRM, &act, NULL);
  alarm(1);
  // send a payload of 0
  union sigval value;
  value.sival_int = 0;
  if (sigqueue(pid, SIGTERM, value) == -1) {
	perror("sigqueue");
	return 1;
  }
  return 0;
}
