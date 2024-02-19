#include <stdio.h>
int main(void) {
  // We will copy a char from c to d
  char c = 'X';
  char d = 'Z';
  // we will make d value equal to c value
  // using bitwise operations especially the or operation
  int number_of_bits = 8;
  int i = 0;
  while (i < number_of_bits) {
    // if ((c & (1 << i)) != 0) {
    //   d |= (1 << i);
    // } else {
    //   d &= ~(1 << i);
    // }
    // we will use turnary operator to make the code more readable
    d = (c & (1 << i)) ? (d | (1 << i)) : (d & ~(1 << i));
    i++;
  }
  printf("d: %c\n", d);
  return (0);
}
