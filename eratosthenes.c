#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
 * Nekolik implementaci Eratosthenova sita (Sieve of Eratosthenes).
 * Author: Jakub Kulik
 */

/*
 * Eratosthenovo sito.
 * Eratosthenovo sito je jednoduchy a pritom velmi ucinny algoritmus na nalezeni
 * vsech prvocisel do daneho maxima. Presny popis algoritmu je delsi, takze si ho nekde vygooglete...
 *
 * vice zde: https://www.algoritmy.net/article/65/Eratosthenovo-sito
 */
void sieve_of_eratosthenes(int max) {
  int i, j;
  bool* sieve = (bool*) calloc (max, sizeof(bool));

  for (i = 2; i <= sqrt(max); i++) {
    if (sieve[i]) continue;
    printf("%d ", i);
    for (j = 2 * i; j < max; j += i) {
      sieve[j] = true;
    }
  }
  for (i = sqrt(max) + 1; i < max; i++)
    if (!sieve[i])
      printf("%d ", i);

  printf("\n");
  free(sieve);
}

/*
 * Algoritmus muzeme dale optimalizovat hlavne v jeho pametove narocnosti, ktera je to hlavni, co ho brzdi.
 * Typ bool nema presne definovanou velikost a na ruznych platformach muze mit jinou (az 4 byty).
 * To je zjevne dost na true/false hodnoty. V teto uprave je pouzit typ int8_t, ktery je vzdy presne jeden byte.
 */
void sieve_of_eratosthenes2(int max) {
  int i, j;
  int8_t* sieve = (int8_t*) calloc (max, sizeof(int8_t));

  for (i = 2; i <= sqrt(max); i++) {
    if (sieve[i]) continue;
    printf("%d ", i);
    for (j = 2 * i; j < max; j += i) {
      sieve[j] = 1;
    }
  }
  for (i = sqrt(max) + 1; i < max; i++)
    if (!sieve[i])
      printf("%d ", i);

  printf("\n");
  free(sieve);
}

/*
 * Byte na jednu logickou hodnotu je stale zbytecne moc, kdyz nam staci pouze jeden bit. Nasledujici
 * implementace vyuziva bitove pole, ktere je pametove vyrazne efektivnejsi, jeho implementace je ale slozitejsi.
 * Pro spravne pochopeni je potreba pochopit bitove operace a logicke operatory (a trochu se do toho zahledet).
 *
 * vice k bitovym operacim: http://www.mathcs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/bit-array.html
 */
void sieve_of_eratosthenes3(int max) {
  int i, j, size;
  int32_t* sieve;

  size = ceil((double)max / 32);
  sieve = (int32_t*) calloc (size, sizeof(int32_t));

  for (i = 2; i <= sqrt(max); i++) {
    if ((sieve[i / 32] & (1 << (i % 32) ))) continue;

    for (j = 2 * i; j < max; j += i)
      sieve[j / 32] |= 1 << (j % 32);

    printf("%d ", i);
  }
  for (i = sqrt(max) + 1; i < max; i++)
    if (!(sieve[i / 32] & (1 << (i % 32) )))
      printf("%d ", i);

  printf("\n");
  free(sieve);
}

/*
 * Optimalizovat muzeme urcite dale. V predchozim reseni kontrolujeme i suda
 * cisla a sudych prvocisel neni mnoho (presne jedno). Proto muzeme suda cisla vynechat.
 * Tato implementace je uz celkem slozita, ale zabira 16krat mene pameti nez implementace druha.
 */
void sieve_of_eratosthenes4(int max) {
  int i, j, size;
  int32_t* sieve;

  size = ceil((double)max / 64);
  sieve = (int32_t*) calloc (size, sizeof(int32_t));

  printf("2 ");
  for (i = 3; i <= sqrt(max); i += 2) {
    if ((sieve[(i - 1) / 64] & (1 << (((i - 1) / 2) % 32) ))) continue;

    for (j = 3 * i; j < max; j += (2 * i))
      sieve[(j - 1) / 64] |= 1 << (((j - 1) / 2) % 32);

    printf("%d ", i);
  }
  for (; i < max; i += 2)
    if (!(sieve[(i - 1) / 64] & (1 << (((i - 1) / 2) % 32) )))
      printf("%d ", i);

  printf("\n");
  free(sieve);
}

/*
 * Vsechny tyto optimalizace urcite delaji algoritmus rychlejsi a mene pametove narocny, ve skutecnosti
 * se ale nepouziva pro prvocisla vetsi nez 10 milionu a proto tyto optimalizace nejsou tak dulezite.
 * Vypis vsech cisel na obrazovku zabira vyrazne dele casu, nez pocitani jakymkoliv z predchozich algoritmu.
 */


/* main function */
int main(int argc, char* argv[]) {
  sieve_of_eratosthenes(512);
  sieve_of_eratosthenes2(512);
  sieve_of_eratosthenes3(512);
  sieve_of_eratosthenes4(512);

  printf("\n");

  /* Vypis velikosti pomocneho pole u jednotlivych algoritmu */
  printf("(1) Array size: %luB\n", 512 * sizeof(bool));
  printf("(2) Array size: %luB\n", 512 * sizeof(int8_t));
  printf("(3) Array size: %luB\n", (unsigned long)(sizeof(int32_t) * ceil((double)512 / 32)));
  printf("(4) Array size: %luB\n", (unsigned long)(sizeof(int32_t) * ceil((double)512 / 64)));

  return EXIT_SUCCESS;
}
