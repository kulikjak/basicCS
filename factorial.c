#include <stdio.h>
#include <stdlib.h>

/*
 * Algoritmy pro vypocet faktorialu
 * Author: Jakub Kulik
 */

/*
 * Jednoduchy algoritmus na vypocet faktorialu.
 * Vraci -1 pro nedefinovane faktorialy.
 */
int factorial(int number) {
  int i;
  int factorial = 1;

  if (number < 0) return -1;

  for (i = 2; i <= number; i++) {
    factorial *= i;
  }
  return factorial;
}

/*
 * Rekurzivni algoritmus pro vypocet faktorialu.
 * Vraci -1 pro nedefinovane faktorialy.
 */
int rec_factorial(int number) {
  if (number < 0) return -1;
  if (number == 0) return 1;

  return number * rec_factorial(number - 1);
}


/* main function */
int main(int argc, char* argv[]) {
  printf("%d\n", rec_factorial(5));
  printf("%d\n", factorial(4));

  return EXIT_SUCCESS;
}
