#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Algoritmy a funkce pro praci s maticemi.
 * Author: Jakub Kulik
 */


/*
 * Nasobeni matice skalarem
 * Jednoduse vynasobi kazde cislo v matici zadanym skalarem
 */
void scalar_multiplication(int **matrix, int rows, int cols, int scalar) {
  int i, j;
  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++)
      matrix[i][j] *= scalar;
}

/*
 * Soucet matic
 * Secte dve matice do te prvni. Scita se asi tak, ja kby clovek ocekaval.
 */
void matrix_addition(int **matrix1, int **matrix2, int rows, int cols) {
  int i, j;
  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++)
      matrix1[i][j] += matrix2[i][j];
}

/*
 * Soucet vsech cisel v matici
 * Nema uplne vyuziti v matematice, da se ale pouzit jinde.
 */
int sum_matrix(int **matrix, int rows, int cols) {
  int i, j, sum;

  sum = 0;
  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++)
      sum += matrix[i][j];
  return sum;
}

/*
 * Vypocet dereminantu pro matice 2x2
 * vice o determinantu zde:https://cs.wikipedia.org/wiki/Determinant
 */
int determinant2x2(int **matrix) {
  return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

/*
 * Vypocet dereminantu pro matice 3x3
 * Determinant pro matice vetsi nez 3x3 se pocita sloziteji pres permutace.
 */
int determinant3x3(int **matrix) {
  return matrix[0][0] * matrix[1][1] * matrix[2][2] +
         matrix[0][1] * matrix[1][2] * matrix[2][0] +
         matrix[0][2] * matrix[1][0] * matrix[2][1] -
         matrix[0][2] * matrix[1][1] * matrix[2][0] -
         matrix[0][1] * matrix[1][0] * matrix[2][2] -
         matrix[0][0] * matrix[1][2] * matrix[2][1];
}

/*
 * Maticove nasobeni
 * Vynasobi mezi sebou dve matice a vrati treti (novou).
 *
 * Pro pochopeni algoritmu je nutne vedet, jak funguje maticove nasobeni!
 * Pokud clovek nasobeni rozumi, chape proc nas zajimaji pouze tri rozmery ze dvou matic (4 nepotrebujeme).
 * vice zde: https://cs.wikipedia.org/wiki/N%C3%A1soben%C3%AD_matic
 */
int** matrix_multiplication(int **matrix1, int **matrix2, int rows1, int cols1, int cols2) {
  int i, j, k;
  int **matrix;

  matrix = (int**) malloc (rows1 * sizeof(int*));
  for (i = 0; i < rows1; i++)
    matrix[i] = (int*) calloc (cols2, sizeof(int));

  for (i = 0; i < rows1; i++) {
    for (j = 0; j < cols2; j++) {
      for (k = 0; k < cols1; k++) {
        matrix[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
  return matrix;
}

/*
 * Generator nahodnych matic
 * Algoritmus vygeneruje nahodnou matici o zadane velikosti s hodnotami v zadanem rozmezi.
 */
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

/*
 * Uvolni pamet alokovanou pro matici
 * Ve vyssich programovacich jazycich se casto nemusi resit.
 */
void destroy_matrix(int **matrix, int rows) {
  int i;

  for (i = 0; i < rows; i++)
    free(matrix[i]);
  free(matrix);
}

/*
 * Vypis matice
 * Vypise matici na obrazovku.
 */
void print_matrix(int **matrix, int rows, int cols) {
  int i, j;
  for (i = 0; i < rows; i++) {
    printf("| ");
    for (j = 0; j < cols; j++)
      printf("%3d ", matrix[i][j]);
    printf("|\n");
  }
}

/*
 * Vypis transponovane matice
 * Vypise transponovanou matici na obrazovku (tj. matice preevracena podle jeji hlavni diagonaly).
 */
void print_transposed(int **matrix, int rows, int cols) {
  int i, j;
  for (j = 0; j < cols; j++) {
    printf("| ");
    for (i = 0; i < rows; i++)
      printf("%3d ", matrix[i][j]);
    printf("|\n");
  }
}


/* main function */
int main(int argc, char **argv) {
  int rows1, cols1, rows2, cols2;
  int **matrix, **matrix1, **matrix2;

  srand(time(NULL));

  rows1 = 3;
  cols1 = 3;

  rows2 = 3;
  cols2 = 3;

  matrix1 = generate_matrix(rows1, cols1, 0, 3);
  matrix2 = generate_matrix(rows2, cols2, 0, 3);

  print_matrix(matrix1, rows1, cols1);
  printf("*\n");
  print_matrix(matrix2, rows2, cols2);
  printf("=\n");

  matrix = matrix_multiplication(matrix1, matrix2, rows1, cols1, cols2);

  print_matrix(matrix, rows1, cols2);
  printf("\nDeterminant: %d\n", determinant3x3(matrix));

  destroy_matrix(matrix, rows1);
  destroy_matrix(matrix1, rows1);
  destroy_matrix(matrix2, rows2);

  return EXIT_SUCCESS;
}
