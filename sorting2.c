#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define STUDENT_LIST_SIZE 10

/*
 * Counting sort algoritmus.
 * Author: Jakub Kulik
 */

/* Stuktura reprezentujici studenta */
struct Student {
  int grade;
  char name[50];
};

/*
 * Counting sort.
 * Complexity: O(n*m)
 * V pripade, ze radite pole, ve kterem je pouze male mnozstvi moznych hodnot (napriklad znamky),
 * je counting sort jeden z nejlepsich vubec a vyrazne rychlejsi nez treba Merge sort (ktery je fakt rychly).
 *
 * Counting sort neni zalozeny na porovnavani prvku a proto muze jeho slozitost byt lepsi nez O(n*logn).
 *
 * Vysledne pole je serazene a zachovava poradi prvku se stejnou hodnotou.
 *
 * vice na: https://www.algoritmy.net/article/106/Counting-sort
 */
void counting_sort(struct Student studenti[]) {
  int i, min, max, new_position;
  int *counts, *positions;

  /* Nejprve musime najit minimum a maximum v danem poli */
  min = studenti[0].grade;
  max = studenti[0].grade;
  for (i = 1; i < STUDENT_LIST_SIZE; i++) {
    min = (studenti[i].grade > min) ? min : studenti[i].grade;
    max = (studenti[i].grade < max) ? max : studenti[i].grade;
  }

  /* vypocitame pole, ktere pro kazdou znamku pocita pocet vyskytu (kolik studentu ma danou znamku) */
  /* calloc alokuje pole na danou velikost a automaticky ho vynuluje */
  counts = (int*) calloc ((max - min + 1), sizeof(int));
  for (i = 0; i < STUDENT_LIST_SIZE; i++)
    counts[studenti[i].grade - min]++;

  /* vypocitame dalsi pole - tentokrat s indexy prvniho vyskytu studenta s danou znamkou */
  positions = (int*) malloc ((max - min + 1) * sizeof(int));
  positions[0] = 0;
  for (i = 1; i < (max - min + 1); i++)
    positions[i] = positions[i - 1] + counts[i - 1];

  /* puvodni pole si prekopirujeme, protoze do nej bude radit */
  struct Student studenti_copy[STUDENT_LIST_SIZE];
  memcpy(studenti_copy, studenti, STUDENT_LIST_SIZE * sizeof(struct Student));

  /* do puvodniho pole seradime prvni podle pole pozic */
  /* pri kazdem prirazeni zvysime hodnotu v poli pozic o jedna a proto dalsi prvek neprepise ten momentalni */
  for (i = 0; i < STUDENT_LIST_SIZE; i++) {
    new_position = positions[studenti_copy[i].grade - min];
    studenti[new_position] = studenti_copy[i];
    positions[studenti_copy[i].grade - min]++;

    /* stejna vec na jeden radek */
    /*studenti[positions[studenti_copy[i].grade - min]++] = studenti_copy[i];*/
  }
}

/* Jednoducha funkce pro vypsani studentu na obrazovku (terminal). */
void print_students(struct Student studenti[]) {
  int i;
  for (i = 0; i < STUDENT_LIST_SIZE; i++) {
    printf("Name: %s\t Grade: %d\n", studenti[i].name, studenti[i].grade);
  }
}


/* main function */
int main(int argc, char **argv) {
  clock_t start, end;

  /* Student names from: http://fantasynamegenerators.com/ */
  struct Student studenti[] = {{1, "Demosios"},
    {3, "Tyrosmus"},
    {2, "Agamexus"},
    {3, "Thaulix"},
    {1, "Acamedes"},
    {4, "Bryron"},
    {5, "Icopheus"},
    {1, "Tyrorus"},
    {4, "Coryneus"},
    {1, "Lonius"}
  };

  printf("Initial list:\n");
  print_students(studenti);

  start = clock();
  counting_sort(studenti);
  end = clock();

  printf("\nSorted list:\n");
  print_students(studenti);

  printf("\nCounting sort\t time: %fs\n", ((double) (end - start)) / CLOCKS_PER_SEC);

  return EXIT_SUCCESS;
}
