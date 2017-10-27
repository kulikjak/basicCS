#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/*
 * Nekolik algoritmu pro rychle razeni poli.
 * Vsechny radici algoritmy vraceji pole ve vzestupnem poradi.
 * Narocnosti jednotlivych algoritmu jsou vzdy v komentari nad danou funkci.
 * Author: Jakub Kulik
 */

/*
 * Info navic pro zvidave
 * Radici algoritmy se klasifikuji dle nekolika jejich vlastnosti.
 *
 * *Complexity - kolik se musi provest operaci (napr porovnani) pro serazeni pole.
 * Tato vlastnost je asi nejdulezitejsi, protoze primo urcuje rychlost razeni.
 *
 * *Stability - Vlastnost rikajici, jestli serazene pole bude mit prvky se stejnou hodnotou
 * ve stejnem poradi, jako pred serazenim. Prikladem je napriklad razeni studentu nejprve
 * dle jejich jmena a pote znamky. Stabilni algoritmus zachova u lidi se stejnou znamkou
 * poradi dle jmena. Nestabilni je muze prehazet (serazeno tedy bude jen dle znamky)
 *
 * *In-place - In-place algoritmy potrebuji pro serazeni maximalne konstantni dalsi pamet.
 * To znamena, ze velikost pameti pouzite pro razeni je stejna bez ohledu na velikst vstupu.
 *
 * *Data dependency (Prirozenost) - Rika, jestli je dany algoritmus zavisli na vstupnich datech.
 * Data independent algoritmy budou radit pole stejne dlouho bez ohledu na to, jak je prehazene.
 * Seradit jiz serazene pole bude trvat stejne dlouho jako pole serazene opacne (casto nejhorsi
 * mozny pripad).
 *
 * Podrobnejsi popis vlastnosti algoritmu se da najit napriklad zde:
 * https://cs.wikipedia.org/wiki/%C5%98adic%C3%AD_algoritmus
 */

/* Makro, ktere prohodi dve cisla na pozicich x a y. */
#define SWAP(x, y) { int temp = x; x = y; y = temp; }


/* Globalni promenna na pocitani cyklu radicich algoritmu */
int64_t counter;

/* pomocne funkce */
bool is_sorted(int*, int);
void print_list(int*, int);
void shuffle_array(int*, int);

int* generate_random_list(int);
int* generate_ascending_list(int);
int* generate_descending_list(int);


/*
 * Bubble sort
 * Complexity: O(n^2)
 * Stable, In-place, Data independent
 * Velmi jednoduchy radici algoritmus. Realne se nepouziva vubec na nic.
 * Algoritmus projde n krat cele pole a radi prohazovanim dvou poli vedle sebe v pripade,
 * ze je pole vlevo vetsi nez pole vpravo.
 *
 * vice na: https://www.algoritmy.net/article/3/Bubble-sort
 */
void bubble_sort(int *list, int size) {
  int i, j;

  for (i = 0; i < size; i++) {
    for (j = 1; j < size; j++) {
      counter++;
      if (list[j - 1] > list[j])
        SWAP(list[j - 1], list[j]);
    }
  }
}

/*
 * Bubble sort (vylepseny)
 * Complexity: O(n^2)
 * Stable, In-place, Data dependent
 * Algoritmus neprochazi cely list n krat, ale pouze tak dlouho, dokud nejsou vsechny prvky serazene.
 * V nejhorsim pripade je ale stejne efektivni jako naivni Bubble sort.
 * Stejne jako bubble sort se k nicemu nepouziva.
 */
void bubble_sort2(int *list, int size) {
  int i, j;
  bool sorted;

  for (i = 0; i < size; i++) {
    sorted = true;
    for (j = 1; j < size; j++) {
      counter++;
      if (list[j - 1] > list[j]) {
        SWAP(list[j - 1], list[j]);
        sorted = false;
      }
    }
    if (sorted) break;
  }
}

/*
 * Shaker sort
 * Complexity: O(n^2)
 * Stable, In-place, Data dependent
 * Algoritmus funguje podobne jako Bubble sort, neprochazi ale pole pouze vzestupne, ale obema smery
 * Diky tomu se nedostanou pouze vysoke hodnoty rychle na spravne misto, ale i ty nizke.
 * Ackoliv je algoritmus v prumernem pripade o neco rychlejsi, v nejhorsim pripade je stejny jako naivni Bubble sort.
 *
 * vice na: https://www.algoritmy.net/article/93/Shaker-sort
 */
void shaker_sort(int *list, int size) {
  int i, j;
  bool sorted;

  for (i = 0; i < ceil(size / 2); i++) {
    sorted = true;
    for (j = 1; j < size; j++) {
      counter++;
      if (list[j - 1] > list[j]) {
        SWAP(list[j - 1], list[j]);
        sorted = false;
      }
    }
    for (j = (size - 1); j > 0; j--) {
      counter++;
      if (list[j - 1] > list[j]) {
        SWAP(list[j - 1], list[j]);
        sorted = false;
      }
    }
    if (sorted) break;
  }
}

/*
 * Shaker sort 2
 * Complexity: O(n^2)
 * Stable, In-place, Data dependent
 * Vylepseny Shaker sort, ktery zbytecne neprochazi jiz serazene konce pole
 * Algoritmus si pri kazdem pruchodu najde hranice pole, za ktere nemusi
 * chodit (jsou jiz serazene) a v dalsim cyklu do nich uz neprichazi.
 */
void shaker_sort2(int *list, int size) {
  int j;
  int sp, ep;    // start and end pointers
  int fsp, fep;  // future start and end pointers

  // initial positions of the pointers
  sp = 1;
  ep = size;

  while (sp < ep) {
    fep = sp;
    for (j = sp; j < ep; j++) {
      counter++;
      if (list[j - 1] > list[j]) {
        SWAP(list[j - 1], list[j]);
        fep = j;
      }
    }
    ep = fep;
    fsp = ep;
    for (j = (ep - 1); j >= sp; j--) {
      counter++;
      if (list[j - 1] > list[j]) {
        SWAP(list[j - 1], list[j]);
        fsp = j + 1;
      }
    }
    sp = fsp;
  }
}

/*
 * Bogo sort
 * Complexity (expected): O(n * n!)
 * Pravdepodobne nejhorsi mozny radici algoritmus...
 * Je ale nejrychlejsi mozny, pokud je mu podsunuto jiz serazene pole!
 */
void bogo_sort(int *list, int size) {
  srand(time(NULL));

  while (!is_sorted(list, size)) {
    counter++;
    shuffle_array(list, size);
  }
}

/*
 * Selection sort
 * Complexity: O(n^2)
 * Stable, In-place, Data independent
 * Algoritmus v kazdem kroku projde cele neserazene pole a najde dalsi nejmensi
 * prvek, ktery presune na konec jiz serazene casti (Vymeni ho s prvkem na prvni
 * neserazene pozici a posune hranici serazeneho pole o jeden prvek dopredu).
 *
 * vice na: https://www.algoritmy.net/article/4/Selection-sort
 */
void selection_sort(int *list, int size) {
  int i, j, max;

  for (i = 0; i < size - 1; i++) {
    max = i;
    for (j = i + 1; j < size; j++) {
      counter++;
      if (list[j] < list[max])
        max = j;
    }
    SWAP(list[i], list[max]);
  }
}

/*
 * Insertion sort
 * Complexity: O(n^2)
 * Stable, In-place, Data dependent
 * Nejlepsi radici algoritmus pouzivajici porovnavani se slozitosti n^2.
 * U malych poli (max 10 polozek) je dokonce vykonnejsi nez napriklad Quick sort nebo Merge sort.
 *
 * vice na: https://www.algoritmy.net/article/8/Insertion-sort
 */
void insertion_sort(int *list, int size) {
  int i, j, temp;

  for (i = 0; i < size - 1; i++) {
    for (j = i + 1, temp = list[j]; j > 0 && temp < list[j - 1]; j--) {
      counter++;
      list[j] = list[j - 1];
    }
    list[j] = temp;
  }
}




/* pomocne funkce */

/* Funkce pro testovani, zda jestli je pole serazene (vzestupne). */
bool is_sorted(int* list, int size) {
  int i;
  for (i = 1; i < size; i++)
    if (list[i - 1] > list[i])
      return false;
  return true;
}

/* Funkce, ktera nahodne promicha zadane pole. */
void shuffle_array(int *list, int size) {
  int i, pos1, pos2;

  for (i = 0; i < size; i++) {
    pos1 = rand() % size;
    pos2 = rand() % size;
    SWAP(list[pos1], list[pos2]);
  }
}

/* Jednoducha funkce pro vypsani celeho pole na obrazovku (terminal). */
void print_list(int *list, int size) {
  int i;

  for (i = 0; i < size; i++)
    printf("%d ", list[i]);
  printf("\n");
}

/* Funkce pro generovani ruzne serazenych poli (nahodne, vzestupne, sestupne) */
int* generate_ascending_list(int size) {
  int i, *list;

  list = (int*) malloc (size * sizeof(int*));
  for (i = 0; i < size; i++)
    list[i] = i;
  return list;
}
int* generate_descending_list(int size) {
  int i, *list;

  list = (int*) malloc (size * sizeof(int*));
  for (i = 0; i < size; i++)
    list[i] = size - i - 1;
  return list;
}
int* generate_random_list(int size) {
  int i, *list;
  //srand(6841758);  // stejny seed pro vsechny algoritmy
  srand(time(NULL));

  list = (int*) malloc (size * sizeof(int*));
  for (i = 0; i < size; i++)
    list[i] = rand() % 100;
  return list;
}


/* main function */
int main(int argc, char **argv) {
  int size, *array;
  clock_t start;

  size = 1000;

  // This might be a bad idea...
  /*counter = 0;
  array = generate_random_list(size);
  start = clock();
  bogo_sort(array, size);
  printf("Bogo sort\t comparisons: %ld\t time: %fs\n", counter, ((double) (clock() - start)) / CLOCKS_PER_SEC);
  free(array);*/

  counter = 0;
  array = generate_random_list(size);
  start = clock();
  bubble_sort(array, size);
  printf("Bubble sort\t comparisons: %ld\t time: %fs\n", counter, ((double) (clock() - start)) / CLOCKS_PER_SEC);
  free(array);

  counter = 0;
  array = generate_random_list(size);
  start = clock();
  bubble_sort2(array, size);
  printf("Bubble sort 2\t comparisons: %ld\t time: %fs\n", counter, ((double) (clock() - start)) / CLOCKS_PER_SEC);
  free(array);

  counter = 0;
  array = generate_random_list(size);
  start = clock();
  shaker_sort(array, size);
  printf("Shaker sort\t comparisons: %ld\t time: %fs\n", counter, ((double) (clock() - start)) / CLOCKS_PER_SEC);
  free(array);

  counter = 0;
  array = generate_random_list(size);
  start = clock();
  shaker_sort2(array, size);
  printf("Shaker sort 2\t comparisons: %ld\t time: %fs\n", counter, ((double) (clock() - start)) / CLOCKS_PER_SEC);
  free(array);

  counter = 0;
  array = generate_random_list(size);
  start = clock();
  selection_sort(array, size);
  printf("Selection sort\t comparisons: %ld\t time: %fs\n", counter, ((double) (clock() - start)) / CLOCKS_PER_SEC);
  free(array);

  counter = 0;
  array = generate_random_list(size);
  start = clock();
  insertion_sort(array, size);
  printf("Insertion sort\t comparisons: %ld\t time: %fs\n", counter, ((double) (clock() - start)) / CLOCKS_PER_SEC);
  free(array);

  return EXIT_SUCCESS;
}
