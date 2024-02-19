#include <signal.h>
#include <stdio.h>
#include <sys/_types/_pid_t.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int signo, siginfo_t *info, void *extra);

int main(void) {
  pid_t pid;
  pid = getpid();
  printf("pid: %d\n", pid);
  struct sigaction act;
  act.sa_sigaction = &handler;
  act.sa_flags = SA_SIGINFO;
  sigaction(SIGTERM, &act, NULL);
  while (1) {
    sleep(1);
  }
  return (0);
}

// siginfo is a structure that is used to pass information to a signal handler

void handler(int signo, siginfo_t *info, void *extra) {
  printf("Signal %d was caught\n", signo);
  printf("Signal originates from process %lu\n", (unsigned long)info->si_pid);
}
