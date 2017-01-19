#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/*
 * Nekolik algoritmu pro rychle razeni poli.
 * Vsechny radici algoritmy vraceji pole ve vzestupnem poradi.
 * Narocnosti jednotlivych algoritmu jsou vzdy v komentari nad danou funkci.
 * Author: Jakub Kulik
 */

/* Makro, ktere prohodi dve cisla na pozicich x a y. */
#define SWAP(x, y) { int temp = x; x = y; y = temp; }

/* pomocne funkce */
bool is_sorted(int*, int);
void print_list(int*, int);

int* generate_random_list(int);
int* generate_ascending_list(int);
int* generate_descending_list(int);


/*
 * Quicksort
 * Complexity: O(n*logn) best, O(n^2) worst
 * non Stable, Not-in-place, Data independent
 * Velmi rychly radici algoritmus, ktery nevyzaduje zadnou pamet navic.
 * Nevyhodou je, ze v nejhorsim pripade muze razeni trvat az kvadraticky cas.
 *
 * Velmi dulezite je spravne nalezeni pivota, ktere je 1. rychle a 2. idelane v pulce hodnot.
 * Toto reseni bere jako pivota vzdy prvni prvek pole a i proto je velmi pomale v porovnani
 * s napriklad Merge sortem.
 *
 * vice na: https://www.algoritmy.net/article/10/Quicksort
 */
void quicksort(int array[], int left, int right){
	int pivot, i, boundary;

	if (left >= right) return;

	pivot = left;
    boundary = left;
    for (i = pivot + 1; i < right; i++) {
        if (array[i] < array[pivot]) {
        	boundary++;
            SWAP(array[i], array[boundary]);
        }
    }
    SWAP(array[left], array[boundary]);
    quicksort(array, left, boundary);
    quicksort(array, boundary + 1, right);
}

/*
 * Merge sort
 * Complexity: O(n*logn)
 * Stable, Not-in-place, Data independent
 * Jeden z nejrychlejsich radicich algoritmu zalozenych na porovnavani vubec. 
 * (Je dokazano, ze radit pomoci porovnavani neni mozne rychleji nez n*logn)
 * Nevyhodou je, ze algoritmus potrebuje velike mnozstvi pameti navic (dvojnasobek).
 *
 * vice na: https://www.algoritmy.net/article/13/Merge-sort
 */
void merge_sort(int *list, int *aux, int left, int right) {
	int leftIndex, rightIndex, insertIndex;
    int middle, i;

	if (left == right) return;

    middle = (left + right)/2;

    /* zavolame merge sort pro kazdou cast naseho pole */
    merge_sort(list, aux, left, middle);
    merge_sort(list, aux, middle + 1, right);

    /* nyni slijeme obe dve pulky dohromady tak, aby byli serazene */
	leftIndex = left;
    rightIndex = middle + 1;
    insertIndex = left;

    /* nejprve postupne mergujeme obe dve casti dohromady */
    while (leftIndex <= middle && rightIndex <= right) {
        if (list[leftIndex] <= list[rightIndex])
            aux[insertIndex] = list[leftIndex++];
        else
            aux[insertIndex] = list[rightIndex++];
        insertIndex++;
    }

    /* pote uz jen prekopirujeme tu cast, ktera zbyla */
    while (leftIndex <= middle) {
        aux[insertIndex] = list[leftIndex++];
        insertIndex++;
    }
    while (rightIndex <= right) {
        aux[insertIndex] = list[rightIndex++];
        insertIndex++;
    }
  
  	/* nakopiruje cele pomocne pole pres pole puvodni */
  	for (i = left; i <= right; i++)
		list[i] = aux[i];
}

/*
 * Merge sort 2
 * Complexity: O(n*logn)
 * Stable, Not-in-place, Data independent
 * Stejny algoritmus, pouze optimalizovanejsi a bez komentaru. 
 * Memcpy je rychlejsi operace, nez kopirovani pomoci for cyklu (nekdy i nekolika nasobne)
 */
void merge_sort2(int *list, int *aux, int left, int right) {
	int leftIndex, rightIndex, insertIndex;
    int middle;

	if (left == right) return;

    middle = (left + right)/2;
    merge_sort(list, aux, left, middle);
    merge_sort(list, aux, middle + 1, right);

	leftIndex = left;
    rightIndex = middle + 1;
    insertIndex = left;

    while (leftIndex <= middle && rightIndex <= right) {
        if (list[leftIndex] <= list[rightIndex])
            aux[insertIndex++] = list[leftIndex++];
        else
            aux[insertIndex++] = list[rightIndex++];
    }

    if (leftIndex <= middle)
    	memcpy (&aux[insertIndex], &list[leftIndex], (middle-leftIndex+1) * sizeof(int));
    else if (rightIndex <= right)
    	memcpy (&aux[insertIndex], &list[rightIndex], (middle-leftIndex+1) * sizeof(int));

  	memcpy (&list[left], &aux[left], (right-left+1) * sizeof(int));
}

/*
 * Existuje i in-place Merge sort, ktery pro mergovani nepouziva druhe pomocne pole a je tak pametove nenarocny.
 * Algoritmus opet rekurzivne rozdeli pole do polovin, ale pote pro slevani pouziva slozitejsi algoritmus rotaci a presunu.
 *
 * Pozn: Na netu se toho o nem moc neda najit tak dobre, jako o ostatnich.
 */



/* pomocne funkce */

/* Funkce pro testovani, zda jestli je pole serazene (vzestupne). */
bool is_sorted(int* list, int size) {
	int i;
	for (i = 1; i < size; i++)
		if (list[i-1] > list[i])
			return false;
	return true;
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
		list[i] = size-i-1;
	return list;	
}
int* generate_random_list(int size) {
	int i, *list;
	//srand(6841758);	// stejny seed pro vsechny algoritmy
	srand(time(NULL));

	list = (int*) malloc (size * sizeof(int*));
	for (i = 0; i < size; i++)
		list[i] = rand() % 100;
	return list;
}


/* Porovnavaci funcke pro quicksort definovany ve standardni knihovne */
int compare (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

/* main function */
int main(int argc, char **argv) {
	int size, *array, *aux;
	clock_t start;

	size = 10000000;

	array = generate_random_list(size);
	aux = (int*) malloc (size * sizeof(int*));
	start = clock();
	merge_sort(array, aux, 0, size-1);
	printf("Merge sort\t time: %fs\n", ((double) (clock() - start)) / CLOCKS_PER_SEC);
	free(array);
	free(aux);

	array = generate_random_list(size);
	aux = (int*) malloc (size * sizeof(int*));
	start = clock();
	merge_sort2(array, aux, 0, size-1);
	printf("Merge sort2\t time: %fs\n", ((double) (clock() - start)) / CLOCKS_PER_SEC);
	free(array);
	free(aux);

	array = generate_random_list(size);
	start = clock();
	quicksort(array, 0, size);
	printf("Quick sort\t time: %fs\n", ((double) (clock() - start)) / CLOCKS_PER_SEC);
	free(array);

	/* pro ukazku porovnani s rychlosti qsortu, ktery je vyuzit ve standardni knihovne C++ */
	array = generate_random_list(size);
	start = clock();
	qsort (array, size, sizeof(int), compare);
	printf("Quick sort X\t time: %fs\n", ((double) (clock() - start)) / CLOCKS_PER_SEC);
	free(array);

	return EXIT_SUCCESS;
}
