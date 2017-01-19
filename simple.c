#include <stdlib.h>
#include <stdio.h>

/*
 * Nekolik velmi basic algoritmu a funkci pro zacatecniky.
 * Author: Jakub Kulik
 */

/* Vypisuje jmeno dne podle jeho cisla (poradi v tydnu). */
void day_name(int day) {
    switch(day) {
    case 1:
        printf("Podndeli\n");
        break;
    case 2:
        printf("Utery\n");
        break;
    case 3:
        printf("Streda\n");
        break;
    case 4:
        printf("Ctvrtek\n");
        break;
    case 5:
        printf("Patek\n");
        break;
    case 6:
        printf("Sobota\n");
        break;
    case 7:
        printf("Nedele\n");
        break;
    default:
        printf("Chyba - dneska neni zadny den!!!!!\n");
        break;
    }
}

/* 
 * Funkce zjisti, jestli je zadany rok prestupny a nebo ne. 
 * Pozn: Gregoriansky kalendar, podle ktereho se urcuji prestupne roky, zacal platit v roce 1584.
 */
void check_leap_year(int year) {
    if (year < 1584) {
        printf("Moc stary\n");
    }
    else if (year%400 == 0) {
        printf("Rok %d je prestupny(delitelne 400)\n", year);
    }
    else if (year%100 == 0) {
        printf("Rok %d je neprestupny(delitelne 100)\n", year);
    }
    else if (year%4 == 0) {
        printf("Rok %d je prestupny(delitelne 4)\n", year);
    }
    else{
        printf("Rok %d je neprestupny\n", year);
    }
}

/* Vypisuje cisla v intervalu od a do b. */
void print_interval(int a, int b) {
    for (; a <= b; a++)
        printf("%d ", a);
    printf("\n");
}

/* Vypisuje pouze suda cisla v intervalu od a do b. */
void print_even_interval(int a, int b) {
    for (; a <= b; a++) {
        if (a % 2 == 0)
            printf("%d ", a);
    }
    printf("\n");
}

/* Vypisuje pouze licha cisla v intervalu od a do b. */
void print_odd_interval(int a, int b) {
    for (; a <= b; a++) {
        if (a % 2 == 1)
            printf("%d ", a);
    }
    printf("\n");
}

/* Vypisuje cisla v intervalu delitelna zadanym faktorem */
void print_interval_with_factor(int a, int b, int factor) {
    for (; a <= b; a++) {
        if (a % factor == 0)
            printf("%d ", a);
    }
    printf("\n");
}

/* Stejne jako predchozi funkce, ale o dost efektivnejsi. */
void print_interval_with_factor2(int a, int b, int factor) {
    int i;
    for (; a <= b; a++) {
        if (a % factor == 0) {
            for(i = a; i <= b; i += factor) { 
                printf("%d ", i);
            }
            break;
        }
    }
    printf("\n");
}

/* Dle zadanych stran trojuhelniku vypise nejake informace o nem. */
void check_triangle(double a, double b, double c) {
    printf("Strana a: %lg\n", a);
    printf("Strana b: %lg\n", b);
    printf("Strana c: %lg\n", c);
    
    if (((a+b)<= c) || ((c+b)<= a) || ((a+c)<= b)) {
        printf("trojuhelnik nelze sestrojit\n");
    } else {
        printf("trojuhelnik lze sestrojit\n");
    }
    
    if ((a == b) && (b == c)) {
        printf("trojuhelnik je rovnostranny\n");
    } else {
        printf("trojuhelnik neni rovnostranny\n");
    }
    
    if (((a == b) && a != c) || ((c == b) && c != a) || ((a == c) && a != b)) {
        printf("trojuhelnik je rovnoramenny\n");
    } else {
        printf("trojuhelnik neni rovnoramenny\n");
    }
    
    if ((a*a + b*b == c*c) || (a*a + c*c == b*b) || (c*c + b*b == a*a)) {
        printf("trojuhelnik je pravouhly\n");
    } else {
        printf("trojuhelnik neni pravouhly\n");
    }
}

/* Vypise na obrazovku trojuhelnik z hvezdicek zadane velikosti. */
void print_triangle(int size) {
    int i, j;
    for (i = 1; i <= size; i++) {
        for (j = 1; j <= i; j++)
            printf("*");
        printf("\n");
    }
}

/* Nalezne prunik dvou zadanych intervalu a vypise ho na obrazovku */
void intersection_of_intervals(int a1, int a2, int b1, int b2){
    if (a1 < b1) {
        if (a2 > b1) {
            printf("<%d,", b1);
        } else {
            printf("<0,0>");
            return;
        }
    }
    if (b1 < a1) {
        if (b2 > a1) {
            printf("<%d,", a1);
        } else {
            printf("<0,0>");
            return;
        }
    }
    if (a2 > b2) {
        if (a1 < b2) {
            printf("%d>", b2);
        } else {
            printf("<0,0>");
            return;
        }
    }
    if (b2 > a2) {
        if (b1 < a2) {
            printf("%d>", a2);
        } else {
            printf("<0,0>");
            return;
        }
    }
}


/* main function */
int main(int argc, char **argv) {

    day_name(3);
    day_name(6);
    day_name(8);

    printf("\n");

    check_leap_year(2000);
    check_leap_year(2004);
    check_leap_year(2005);

    printf("\n");

    print_interval(6, 18);
    print_even_interval(2, 21);
    print_odd_interval(2, 21);
    print_interval_with_factor(23, 84, 7);
    print_interval_with_factor2(23, 84, 7);

    printf("\n");

    check_triangle(4,7,6);

    printf("\n");

    print_triangle(8);

    printf("\n");
    intersection_of_intervals(1, 20, 12, 19);

    return EXIT_SUCCESS;
}
