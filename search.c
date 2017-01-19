#include <stdio.h>
#include <stdlib.h>

/*
 * Vyhledavaci algoritmy
 * Author: Jakub Kulik
 */


/* 
 * Algoritmus linearniho (sekvencniho) vyhledavani.
 * Complexity: O(n) - musi projit cele pole.
 * Vraci index prvniho vyskytu hledaneho prvku a nebo -1 (pokud prvek neexistuje).
 *
 * Jedina moznost vyhledavani na neserazenem poli, o kterem nic nevime.
 */
int linear_search(int* list, int size, int n) {
	int i;

	for (i = 0; i < size; i++)
		if (list[i] == n) 
			return i;
	return -1;
}

/* 
 * Algoritmus binarniho vyhledavani.
 * Complexity: O(log(n)) - v kazdem kroku zmensi velikost pole na polovinu.
 * Vraci index prvniho vyskytu hledaneho prvku a nebo -1 (pokud prvek neexistuje).
 * 
 * Funguje pouze na serazenem poli!
 * Slozitost algoritmu je log(n) (o dost lepsi nez linearni vyhledavani).
 */
int binary_search(int* list, int size, int n) {
	int sp, ep, middle;

	for (sp = 0, ep = size; sp < ep;) {
		middle = (sp + ep) / 2;
		if (list[middle] == n) return middle;

		if (list[middle] > n)
			ep = middle;
		else
			sp = middle+1;
	}
	return -1;
}

/* 
 * Algoritmus interpolacniho vyhledavani.
 * Complexity: O(log(log(n))) pri rovnomernem rozlozeni.
 * Vraci index prvniho vyskytu hledaneho prvku a nebo -1 (pokud prvek neexistuje).
 * 
 * Funguje pouze na serazenem poli!
 * Algoritmus je velmi dobry na polich, kde mame priblizne rovnomerne rozlozena 
 * cisla, naopak v pripade nerovnomerneho rozlozeni muze byt horsi nez binarni 
 * vyhledavani, v nejhorsim pripade stejny jako linearni prohledavani.
 * 
 * vice zde: https://www.algoritmy.net/article/160/Interpolacni-vyhledavani 
 */
int interpolation_search(int* list, int size, int n) {
	int sp, ep, guess;
	for (sp = 0, ep = size-1; sp <= ep;) {
		guess = (int)(sp + (double)(ep - sp)/(list[ep] - list[sp]) * (n - list[sp]));
		if (list[guess] == n) return guess;

		if (list[guess] > n)
			ep = guess-1;
		else
			sp = guess+1;
 	}
	return -1;
}


/* main function */
int main(int argc, char **argv) {

	int random[] = {71, 34, 66, 33, 80, 60, 8, 55, 51, 98, 37, 45, 16, 96, 35, 78, 44, 5, 57, 6, 18, 54, 85, 95, 62, 81, 59, 63, 31, 82, 39, 77, 19, 
  						12, 23, 41, 25, 90, 42, 9, 75, 30, 61, 29, 43, 74, 22, 04, 69, 24, 13, 93, 53, 92, 27, 38, 50, 58, 79, 47, 28, 86, 10, 21, 20, 56, 
						94, 11, 46, 88, 70, 49, 99, 67, 1, 97, 17, 15, 52, 73, 48, 65, 91, 68, 14, 32, 72, 89, 84, 64, 10, 2, 83, 7, 87, 40, 26, 36, 76, 3};
	int sorted[] = {1, 2, 3, 4, 5, 8, 12, 13, 15, 16, 17, 18, 20, 23, 25, 27, 30, 32, 33, 37, 38, 41, 42, 44, 45, 47, 49, 50, 52, 53, 56, 57, 58, 59, 60, 62, 65, 67, 
						68, 69, 71, 73, 77, 80, 83, 84, 85, 89, 93, 96, 97, 98, 100, 101, 102, 103, 104, 106, 108, 110, 112, 114, 116, 117, 118, 122, 126, 127, 128, 129, 
						136, 137, 138, 141, 145, 147, 148, 149, 150, 154, 155, 159, 163, 165, 169, 171, 172, 173, 176, 177, 180, 181, 185, 186, 189, 192, 193, 197, 199, 200};

	printf("%d\n", linear_search(random, 100, 14));
	printf("%d\n", linear_search(sorted, 100, 12));

	printf("%d\n", binary_search(sorted, 100, 12));
	printf("%d\n", interpolation_search(sorted, 100, 12));

	return EXIT_SUCCESS;
}
