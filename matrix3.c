#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Algoritmy a funkce pro efektivni scitani casti matice.
 * Author: Jakub Kulik
 */


/* Obycejny soucet vsech cisel v matici. */
int sum_matrix(int **matrix, int rows, int cols) {
  int i, j, sum;

  sum = 0;
  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++)
      sum += matrix[i][j];
  return sum;
}

/*
 * Soucet vsech cisel v podmatici zadane levym hornim a pravym spodnim prvkem matice.
 * Pozn: Nema zadne kontroly spravne zadanych hranic. V realnem programu by neuskodili.
 */
int sum_matrix_range(int **matrix, int upper, int left, int bottom, int right) {
  int i, j, sum;

  sum = 0;
  for (i = upper; i <= bottom; i++)
    for (j = left; j <= right; j++)
      sum += matrix[i][j];
  return sum;
}

/* Predchozi funkce funguje spravne, neni ale moc rychla. Algoritmus vyhovuje, pokud chceme najit
* jen jeden soucet nejake podmatice, v pripade ze ale budeme chtit nad jednou obri matici delat
* dotazu tisice, bude vyse napsany algoritmus pomaly.
* Nektere dotazy se mohou opakovat a budeme je zbytecne pocitat vickrat, stejne tak nektere
* casti se mohou prekryvat a je proto zbytecne je pocitat znovu.
*
* Nasledujici funkce jsou vylepsenim predchoziho algoritmu. Nejprve je predpocitana pomocna
* tabulka, pomoci ktere jsou pozdeji dopocitavany vsechny matice v konstantnim case
* (tj. velmi rychle a bez zavislosti na velikosti podmatice a puvodni matice).
*
* Pozn: Uvedenemu postupu, kdy si predpocitame hodnoty za ucelem zrychleni vypoctu
* (zpravidla za cenu pameti) se rika Dynamicke programovani.
*/

/*
 * Vytvori pomocnou matici, ktera obsahuje v nultem radku a sloupci same nuly a v kazde dalsi bunce
 * soucet podmatice od leveho horniho rohu az po danou bunku v puvodni matici.
 */
int** build_aux_matrix(int** matrix, int rows, int cols) {
  int i, j;
  int** aux;

  aux = (int**) malloc ((rows + 1) * sizeof(int*));
  for (i = 0; i <= rows; i++)
    aux[i] = (int*) malloc ((cols + 1) * sizeof(int));

  for (i = 0; i <= rows; i++)
    aux[i][0] = 0;
  for (i = 0; i <= cols; i++)
    aux[0][i] = 0;

  for (i = 1; i <= rows; i++)
    for (j = 1; j <= cols; j++)
      aux[i][j] = aux[i - 1][j] + aux[i][j - 1] - aux[i - 1][j - 1] + matrix[i - 1][j - 1];

  return aux;
}

/* Ziska soucet zadane podmatice z pomocne tabulky (sami si nakreslete, jak to funguje). */
int sum_matrix_range2(int **aux, int upper, int left, int bottom, int right) {
  return aux[bottom + 1][right + 1] - aux[upper][left];
}


/* pomocne funkce */

int** generate_matrix(int rows, int cols, int min, int max) {
  int i, j, **matrix;

  matrix = (int**) malloc (rows * sizeof(int*));
  for (i = 0; i < rows; i++) {
    matrix[i] = (int*) malloc (cols * sizeof(int));
    for (j = 0; j < cols; j++)
      matrix[i][j] = (rand() % (max - min + 1)) + min;
  }
  return matrix;
}
void destroy_matrix(int **matrix, int rows) {
  int i;

  for (i = 0; i < rows; i++)
    free(matrix[i]);
  free(matrix);
}
void print_matrix(int **matrix, int rows, int cols) {
  int i, j;
  for (i = 0; i < rows; i++) {
    printf("| ");
    for (j = 0; j < cols; j++)
      printf("%3d ", matrix[i][j]);
    printf("|\n");
  }
}


/* main function */
int main(int argc, char **argv) {
  int rows, cols;
  int **matrix, **aux;

  rows = 6;
  cols = 4;

  matrix = generate_matrix(rows, cols, 0, 8);
  print_matrix(matrix, rows, cols);

  printf("%d\n", sum_matrix_range(matrix, 1, 1, 3, 2));
  printf("%d\n", sum_matrix_range(matrix, 0, 0, 5, 3));
  printf("%d\n", sum_matrix(matrix, rows, cols));

  aux = build_aux_matrix(matrix, rows, cols);
  printf("%d\n", sum_matrix_range2(aux, 0, 0, 5, 3));

  destroy_matrix(matrix, rows);
  destroy_matrix(aux, rows + 1);

  return EXIT_SUCCESS;
}
