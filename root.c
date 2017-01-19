#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
 * Aproximace druhe odmocniny cisla
 * Author: Jakub Kulik
 */

/* Presnost nalezene odmocniny */
#define PRECISION 0.000001


/* 
 * Funkce pro porovnani dvou cisel s plovouci desetinnou carkou.
 *
 * Pozn: Cisla s plovouci desetinou carkou nelze porovnavat stejne jako cela cisla,
 * protoze jsou presna pouze na nekolik mist!
 */
int compare(double a, double b) {
	if (fabs(a - b) < PRECISION) return 0;
	if ((a - b) < 0) return -1;
	return 1;
}

/*
 * Funkce, ktera aproximuje druhou odmocninu cisla s volitelnout presnosti.
 * Maximalni presnost je presnost typu double.
 * Toto je jedna z mnoha moznosti, jak se da odmocnina aproximovat.
 */
void get_root(double square) {
	int cmp, steps;
	double guess, jump;
	bool direction;

	jump = square;
	guess = steps = 0;
	direction = true;
	do {
		printf("%4d %.20f\n", steps, guess);

		cmp = compare(guess*guess, square);
		if (cmp == -1) {
			if (!direction) {
				jump *= 0.5;
				direction = true;
			}
			guess += jump;
		}
		else if (cmp == 1) {
			if (direction) {
				jump *= 0.5;
				direction = false;
			}
			guess -= jump;
		}
		steps ++;
	} while (cmp);

	printf("real %.20f\n", sqrt(square));
}


/* main function */
int main (int argc, char **argv) {
	
	get_root(126);
	
	return EXIT_SUCCESS;
}