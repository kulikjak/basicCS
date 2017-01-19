#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
 * Algoritmy pro praci s Mersonnovo prvocisly.
 * About Mersenne primes: https://www.youtube.com/watch?v=PLL0mo5rHhk
 * Author: Jakub Kulik
 */

bool is_prime(int);


/*
 * Mersennovo prvocislo je prvocislo, ktere se da zapsat jako 2^k-1 pro prirozene k.
 * Vzhledem k tomu, jak rychle se cisla zvetsuji, nebylo jich zatim objeveno moc.
 */

/* Vypise Mersennova prvocisla do zadaneho horniho limitu (nefunguje pro max > 31). */
void list_mersenne_primes(int max) {
	int i, candidate;

	for (i = 1; i < max; i++) {
		candidate = (2<<i) - 1;
		if (is_prime(candidate))
			printf("2^%d-1 = %d\n", i+1, candidate);
	}
}

/* Funkce, ktera pouze vrati, jestli je zadane cislo Mersennovo prvocislo a nebo ne. */
bool is_mersenne_prime(int prime) {
	double power;
	
	power = log2(prime+1);
	if (power == floor(power))
		return true;
	return false;
}


/* pomocne funkce */
bool is_prime(int a) {
	int i;
	for (i = 2; i <= sqrt(a); i++)
		if (a % i == 0) return false;
	return true;
}

/* main function */
int main(int argc, char* argv[]) {

	list_mersenne_primes(31);

	printf("%d\n", (int)is_mersenne_prime(7));
	printf("%d\n", (int)is_mersenne_prime(8));
	printf("%d\n", (int)is_mersenne_prime(30));
	printf("%d\n", (int)is_mersenne_prime(127));

	return EXIT_SUCCESS;
}
