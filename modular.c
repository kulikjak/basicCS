#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Algoritmus pro praci s modulem a delenim
 * Author: Jakub Kulik
 */


/* Prepocita sekundy na hodiny, minuty a sekundy */
void seconds_to_time(int total_seconds) {
	int seconds, minutes, hours;

	seconds = total_seconds % 60;
	minutes = total_seconds / 60 % 60;
	hours = total_seconds / 60 / 60;

	printf("%d hours, %d minutes, %d seconds\n", hours, minutes, seconds);
}


/* main function */
int main (int argc, char* argv[]) {

	seconds_to_time(45265);
	return EXIT_SUCCESS;
}