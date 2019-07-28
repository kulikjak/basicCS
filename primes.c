#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define PRIME_COUNT 168
#define PRIMES {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, \
        137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, \
        281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, \
        449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, \
        619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, \
        811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997}

/*
 * Algoritmy, ktere pracuji s prvocisly a delitelnosti.
 * Author: Jakub Kulik
 */


/*
 * Faktorizace
 * Algoritmus na faktorizaci celeho cisla - tj. nalezeni jeho prvociselneho rozkladu.
 * Nalezeni rozkladu nelze udelat efektivneji, nez bruteforce (nezname lepsi algoritmus).
 * Na tom je postavena pocitacova bezpecnost, napriklad sifrovani pomoci RSA.
 */
void factorization(int a) {
  int i, remainder;

  remainder = a;
  for (i = 2; i < sqrt(a); i++) {
    while (remainder % i == 0) {
      remainder /= i;
      printf("%d ", i);
    }
  }
  if (remainder > 1)
    printf("%d", remainder);
  printf("\n");
}

/*
 * Faktorizace
 * Podobne jako prvni algoritmus, pouze nezkousi deleni vsemi cisly, ale pouze prvocisly.
 * Tech mame ulozenych jen par (do 1000), dal se proto pokracuje stejne jako v prvnim algoritmu.
 */
void factorization2(int a) {
  int i, remainder;
  int primes[] = PRIMES;

  remainder = a;
  for (i = 0; i < PRIME_COUNT; i++) {
    while (remainder % primes[i] == 0) {
      remainder /= primes[i];
      printf("%d ", primes[i]);
    }
  }
  for (i = primes[PRIME_COUNT - 1]; i < sqrt(a); i++) {
    while (remainder % i == 0) {
      remainder /= i;
      printf("%d ", i);
    }
  }
  if (remainder > 1)
    printf("%d", remainder);
  printf("\n");
}

/*
 * Algoritmus faktorizace tak, jak ho zname na stredni skole.
 * Vypisem je klasicky strom se zbytky na leve strane a delitely na prave.
 */
void factorizationX(int a) {
  int i, remainder;

  remainder = a;
  for (i = 2; i < sqrt(a); i++) {
    while (remainder % i == 0) {
      printf("%10d | %d\n", remainder, i);
      remainder /= i;
    }
  }
  if (remainder > 1)
    printf("%10d | %d\n%10d |\n", remainder, remainder, 1);
  else
    printf("%10d |\n", remainder);
}

/*
 * Nejvetsi spolecny delitel
 * Algoritmus na nalezeni nejvetsiho spolecneho delitele.
 */
int gcd(int a, int b) {
  int min, max, temp;
  min = MIN(a, b);
  max = MAX(a, b);

  while (min != 0) {
    temp = min;
    min = max % min;
    max = temp;
  }
  return max;
}

/*
 * Nejvetsi spolecny delitel
 * Algoritmus, ktery nalezne nejvetsiho spolecneho delitele pomoci rekurze.
 */
int gcd2(int a, int b) {
  if (a == 0) return b;
  return gcd2(b % a, a);
}

/*
 * Nejmensi spolecny nasobek
 * Nejlepe se pocita pomoci nejvetsiho spolecneho delitele.
 * Proc to takto funguje se da odvodit na tabuli ;)
 *
 * dalsi implementace: https://www.programiz.com/cpp-programming/examples/lcm
 */
int lcm(int a, int b) {
  return (a * b) / gcd(a , b);
}

/*
 * Eulerova funkce
 * Algoritmus, ktery vraci pocet cisel nesoudelnych s n mezi 1 a n-1.
 * Algoritmus je dulezity pro teorii grup a pro sifrovani.
 *
 * vice na: https://cs.wikipedia.org/wiki/Eulerova_funkce
 */
int euler(int a) {
  int i, euler;

  euler = 0;
  for (i = 1; i < a; i++)
    if (gcd(a, i) == 1)
      euler++;
  return euler;
}

/*
 * Algoritmus zjisti, zda je zadane cislo perfektni.
 * Perfektni cisla jsou ta, kde soucet vsech jejich delitelu (mensich
 * nez zadane cislo) je roven danemu cislu.
 *
 * vice na: https://en.wikipedia.org/wiki/Perfect_number
 */
bool is_perfect_number(int a) {
  int i, sum;

  sum = 0;
  for (i = 1; i < a; i++) {
    if (a % i == 0)
      sum += i;
  }
  if (sum == a)
    return true;
  return false;
}

/*
 * Funkce vypise vsechna perfektni cisla mensi nez zadane maximum.
 * Spoiler: Moc jich neni.
 */
void perfect_numbers(int max) {
  int i;

  for (i = 2; i <= max; i++)
    if (is_perfect_number(i))
      printf("%d ", i);
  printf("\n");
}

/* Bonus: Funkce pro swapovani celych cisel bez pouziti treti promenne */
void swap_numbers() {
  int i;
  int array[] = {1, 2, 3};

  array[0] += array[1];
  array[1] = array[0] - array[1];
  array[0] -= array[1];

  for (i = 0; i < 3; i++)
    printf("%d ", array[i]);
  printf("\n");
}


/* main function */
int main(int argc, char* argv[]) {
  printf("%d\n", gcd(24, 100));
  printf("%d\n", gcd2(24, 100));

  factorization(1023);
  factorization2(1023);

  printf("\n");
  factorizationX(1167483642);
  printf("\n");

  printf("%d\n", euler(1024));
  printf("%d\n", lcm(10, 25));

  perfect_numbers(1000);
  swap_numbers();

  return EXIT_SUCCESS;
}
