#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/*
 * Implementace jednoduche hadaci hry.
 * Author: Jakub Kulik
 */

/* Definovane konstanty pro nabarveni textu terminalu. */
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

/* 
 * Hadaci hra, ve ktere se nahodne vygeneruje cislo v intervalu <1,100> a hrac
 * ho pote musi najit hadanim. Program je navic obohacen o barvy, takze to pekne vypada ^^.
 */
void guess_game() {
    int guess, target;

    srand (time(NULL));
    guess = rand() % 100 + 1;

    printf(GREEN "Nahodne cislo je v intervalu <1,100> \n" RESET);
    while(1) {
        printf(GREEN "Zadejte hadane cislo: " RESET);
        if (scanf("%d", &target) != 1){
            printf("Spatny vstup - learn your numbers\n");
            return;
        }
                
        if (target > guess) {
            printf(CYAN "Hledane cislo je mensi.\n" RESET);
        } else if (target < guess) {
            printf(CYAN "Hledane cislo je vetsi.\n" RESET);
        } else {
            printf(GREEN "Toto je hledane cislo. Gratuluji.\n" RESET);
            break;
        }
    }
}


/* main function */
int main(int argc, char **argv) {
    
    while(1) guess_game();

    return EXIT_SUCCESS;
}
