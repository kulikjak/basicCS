#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

/*
 * Nekolik algoritmu pro stredoskolskou kombinatoriku.
 * Author: Jakub Kulik
 */

int64_t factorial_range(int, int);
int64_t factorial(int);


/*
 * Algoritmus pro vypocet variace bez opakovani.
 * Vstupem jsou dve cela kladna cisla n (velikost mnoziny) a k (pocet vybiranych prvku).
 *
 * vice zde: http://www.matematika.cz/variace
 */
int variation(int k, int n) {
	int i, result = 1;

	for (i = (n-k+1); i <= n; i++)
		result *= i;
	return result;
}

/*
 * Algoritmus pro vypocet variace bez opakovani s pouziti faktorialu dle klasickeho vzorce.
 * Lehce pomalejsi, ale pravdepodobne nazornejsi.
 */
int variation_with_factorial(int k, int n) {
	return factorial(n) / factorial(n-k);
}


/*
 * Algoritmy pro vypocet kombinacniho cisla.
 * Vstupem jsou dve cela kladna cisla n (velikost mnoziny) a k (velikost kombinaci).
 * Vystupem je pocet k-clenych kombinaci mnoziny.
 *
 * vice zde: http://www.matematika.cz/kombinace#kombinacni-cislo
 */

/*
 * Algoritmus pro vypocet kombinacniho cisla s pouzitim faktorialu (klasicky vzorec).
 */
int binomial_coefficient_with_factorial(int k, int n) {
	return factorial(n) / (factorial(n-k) * factorial(k));
}

/*
 * Algoritmus pro vypocet kombinacniho cisla s pouzitim faktorialu dle upraveneho vzorce.
 * Rychlejsi, nez predchozi implementace.
 */
int binomial_coefficient_better(int k, int n) {
	return factorial_range(n, MAX(n-k, k) + 1) / factorial(MIN(n-k,k));
}

/*
 * Algoritmus pro vypocet kombinacniho cisla s vyuzitim vlastnosti Pascalova trojuhelniku.
 * Pro spravne pochopeni je treba pochopit vyznam Pascalova trojuhelniku pro kombinacni cisla.
 * Velmi rychle bez problemu preteceni faktorialu!
 */
int64_t binomial_coefficient_pascal(int k, int n) {
	int i;
	int64_t value;

	value = 1;
	for (i = 0; i < k; i++)
		value = value * (n-i) / (i+1);
	return value;
}

/* 
 * Variace s opakovanim je n^k - neni moc zajimavy algoritmus.
 * Permutace jsou pouze specialnim pripadem variace bez opakovani kde k je rovno n.
 * Kombinace se pocita pres kombinacni cislo (binomial_coefficient).
 * 
 * Kombinace s opakovanim se pocita stejne jako normalni kombinace, pouze ma jiny vstup.
 * vice na: http://www.matematika.cz/kombinace-opakovani
*/


/* pomocne funkce */
int64_t factorial_range(int j, int min) {
	int i, value;

	value = 1;
	for (i = MAX(min, 1); i <= j; i++)
		value *= i;
	return value;
}
int64_t factorial(int i) {
	return factorial_range(i, 1);
}


/* main function */
int main(int argc, char **argv) {

	printf("%d\n", variation(6, 12));
	printf("%d\n", variation_with_factorial(6, 12));

	/* pozn. vraci maximalne C(n, 20) - vyssi hodnoty pretecou! */
	printf("%d\n", binomial_coefficient_with_factorial(12, 12));

	/* pozn. lehce lepsi, ale stale negarantuje obecne nepreteceni pro hodnoty vetsi nez 20 */
	printf("%d\n", binomial_coefficient_better(0, 12));

	/* funguje pro vsechny kombinacni cisla, jejichz vysledek je mensi nez 64bit */
	printf("%ld\n", binomial_coefficient_pascal(12, 15));
	return EXIT_SUCCESS;
}
