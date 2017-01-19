#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Algoritmy pro vyhledavani v textech.
 * Author: Jakub Kulik
 */


/*
 * Algoritmus naivniho porovnavani dvou retezcu s pouziti standardni funkce strcmp.
 * Funkce vypise na vystup pozice ve stringu, kde zacina matchovany pattern.
 * Complexity: O(n*m).
 */
void naive_matching(char* string, char* pattern) {
	int i, size, psize;

	size = strlen(string);
	psize = strlen(pattern);

	for (i = 0; i <= size - psize; i++)
		if (! strncmp(string + i, pattern, psize))
			printf("%d ", i);
	printf("\n");
}

/*
 * Algoritmus naivniho porovnavani dvou retezcu bez pouziti standardni funkce strcmp.
 * Funkce vypise na vystup pozice ve stringu, kde zacina matchovany pattern.
 * Complexity: O(n*m).
 */
void naive_matching2(char* string, char* pattern) {
	int i, j, size, psize;

	size = strlen(string);
	psize = strlen(pattern);

	for (i = 0; i <= size - psize; i++) {
		for (j = 0; string[i+j] == pattern[j]; j++) {
			if (j == psize-1)
				printf("%d ", i);
		}
	}
	printf("\n");
}

/*
 * Algoritmu pro string matching je velike mnozstvi, ale jsou celkem slozite
 * a protoze zde uvadim jen tento jeden - nejjednodussi 
 */


/* main function */
int main(int argc, char **argv) {
	if (argc < 3) 
		return EXIT_FAILURE;

	naive_matching(argv[1], argv[2]);
	naive_matching2(argv[1], argv[2]);

	return EXIT_SUCCESS;
}
