#include <stdio.h>
#include <stdlib.h>

/*
 * Algoritmy pro vypocet fibonacciho cisel.
 * Author: Jakub Kulik
 */


/* 
 * Fibonacciho cisla.
 * Algoritmus nalezne n-te fibonacciho cislo.
 */
int fib(int a) {
	int i, first, second, temp;

	first = 0;
	second = 1;

	for (i = 1; i < a; i++) {
		temp = first + second;
		first = second;
		second = temp;
	}
	return second;
}

/* Vylepseny algoritmus, ktery potrebuje pro svuj beh mene pameti (nejlepsi mozne). */
int fib2(int a) {
	int array[] = {0,1};

	while (a >= 2) {
		array[0] += array[1];
		array[1] += array[0];
		a -= 2;
	}
	return array[a];
}

/* 
 * Algoritmus pro nalezeni Fibonacciho cisla pomoci rekurze.
 *
 * Pozn: Tato verze je ukazkou toho, ze rekurze neni idealni na vsechno.
 * Je extremne pomala, protoze pocita nektere casti (temer vsechny )vickrat.
 */
int rec_fib(int a) {
	if (a < 2) return a;
	return rec_fib(a-1) + rec_fib(a-2);
}


/* main function */
int main(int argc, char **argv) {

	printf("%d\n", fib(64));
	printf("%d\n", fib2(64));

	printf("%d\n", rec_fib(30));

	return EXIT_SUCCESS;
}
