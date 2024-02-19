#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void signal_handler(int signum) {
  static int bit_pos = 0;      // Position of the bit to decode
  static int decoded_char = 0; // Decoded character

  if (signum == SIGUSR1) {
    // Bit 0 received
    bit_pos++;
  } else if (signum == SIGUSR2) {
    // Bit 1 received
    decoded_char |= (1 << bit_pos);// we did or here because we want to set the bit at the position bit_pos to 1 cuz if we did and it will be 0 if the bit is 0 and 1 if the bit is 1 so we will lose the previous bits and we will have only the last bit
    bit_pos++;
  }

  if (bit_pos == 8) {
    // Write the decoded character after receiving 8 bits
    write(STDOUT_FILENO, &decoded_char, 1);
    bit_pos = 0;
    decoded_char = 0;
  }
}

void setup_signal_handling() {
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;

  sa.sa_handler = signal_handler;
  sigaction(SIGUSR1, &sa, NULL);
  sigaction(SIGUSR2, &sa, NULL);
}

int main(int argc, char *argv[]) {
  if (argc != 2 || (strcmp(argv[1], "sender") && strcmp(argv[1], "receiver"))) {
    fprintf(stderr, "Usage: %s [sender | receiver]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  setup_signal_handling();

  if (strcmp(argv[1], "receiver") == 0) {
    printf("Receiver PID: %d\n", getpid());
    while (1) {
      pause(); // Wait for signals indefinitely
    }
  } else {
    int target_pid;
    printf("Enter receiver PID: ");
    scanf("%d", &target_pid);

    const char *message = "Hello";
    for (size_t i = 0; message[i] != '\0'; i++) {
      char ch = message[i];
      for (int bit = 0; bit < 8; bit++) {
        int bit_is_set = ch & (1 << bit);
        if (bit_is_set) {
          kill(target_pid, SIGUSR2); // Send bit 1
        } else {
          kill(target_pid, SIGUSR1); // Send bit 0
        }
        usleep(100000); // Wait 100ms between signals
      }
    }
  }
  return 0;
}
