#include <iomanip>
#include <iostream>

/*
 * Algoritmy a funkce pro praci s maticemi, tentokrat v maticovem 
 * podani s kopirujicim konstruktorem a pretizenymi operatory.
 * Author: Jakub Kulik
 */

using namespace std;

class Matrix {
private:
	int rows;
	int cols;
	int **matrix;

	/* Vypocet dereminantu pro matice 2x2 */
	int determinant2x2() {
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}

	/* Vypocet dereminantu pro matice 3x3 */
	int determinant3x3() {
		return matrix[0][0] * matrix[1][1] * matrix[2][2] + 
		   matrix[0][1] * matrix[1][2] * matrix[2][0] +
		   matrix[0][2] * matrix[1][0] * matrix[2][1] -
		   matrix[0][2] * matrix[1][1] * matrix[2][0] -
		   matrix[0][1] * matrix[1][0] * matrix[2][2] -
		   matrix[0][0] * matrix[1][2] * matrix[2][1];
	}

public:
	/* Constructor - Pouze alokuje pamet pro matici a ulozi si rozmery matice. */
	Matrix(int rows, int cols) {
		this->rows = rows;
		this->cols = cols;

		matrix = new int* [rows];
		for (int i = 0; i < rows; i++)
			matrix[i] = new int [cols](); // zavorka na konci zaruci, ze alokovana pamet je vynulovana!
	}

	/* Destructor - Uvolnuje pamet alokovanou pro matici */
	~Matrix() {
		for (int i = 0; i < rows; i++)
			delete[] matrix[i];
		delete[] matrix;
	}

	/*
	 * Generator nahodnych matic
	 * Algoritmus vygeneruje nahodnou matici s hodnotami v zadanem rozmezi.
	 */
	void generateRandom(int min, int max) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++)
				matrix[i][j] = (rand() % (max-min+1)) + min;
		}
	}

	/* Vypis matice na obrazovku */
	void printMatrix() {
		for (int i = 0; i < rows; i++) {
			cout << "| ";
			for (int j = 0; j < cols; j++)
				cout << setw(3) << matrix[i][j] << " ";
			cout << "|" << endl;
		}
	}

	/*
	 * Vypis transponovane matice
	 * Vypise transponovanou matici na obrazovku (tj. matice preevracena podle jeji hlavni diagonaly).
	 */
	void printTransposedMatrix() {
		for (int j = 0; j < cols; j++) {
			cout << "| ";
			for (int i = 0; i < rows; i++)
				cout << setw(3) << matrix[i][j] << " ";
			cout << "|" << endl;
		}
	}

	/*
	 * Nasobeni matice skalarem
	 * Jednoduse vynasobi kazde cislo v matici zadanym skalarem
	 */
	void multiply(int scalar) {
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				matrix[i][j] *= scalar;
	}

	/* 
	 * Maticove nasobeni
	 * Vynasobi mezi sebou dve matice a vrati treti (novou).
	 *
	 * Pro pochopeni algoritmu je nutne vedet, jak funguje maticove nasobeni!
	 * Pokud clovek nasobeni rozumi, chape proc nas zajimaji pouze tri rozmery ze dvou matic (4 nepotrebujeme).
	 * vice zde: https://cs.wikipedia.org/wiki/N%C3%A1soben%C3%AD_matic
	 */
	Matrix* multiply(Matrix *a) {
		Matrix *temp = new Matrix(rows, a->cols);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < a->cols; j++) {
				for (int k = 0; k < cols; k++) {
					temp->matrix[i][j] += matrix[i][k] * a->matrix[k][j];
				}
			}
		}
		return temp;
	}

	/* Soucet matic - pricte zadanou matici k teto. */
	void addMatrix(Matrix* a) {
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				matrix[i][j] += a->matrix[i][j];
	}

	/* Secte vsechna cisla z matice (nema uplne vyuziti v matematice, da se ale pouzit jinde). */
	int sumMatrix() {
		int sum = 0;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				sum += matrix[i][j];
		return sum;
	}

	/* 
	 * Vypocet dereminantu
	 * Determinant se da pocitat pouze pro ctvrcove matice, pro ostatni vyhodi metoda vyjimku.
	 * Determinant se pocita jednoduse pro matice 3x3 a mensi, pro ostatni neni tento algoritmus implementovan.
	 *
	 * vice o determinantu zde:https://cs.wikipedia.org/wiki/Determinant
	 */
	int getDeterminant() {
		if (rows != cols) throw;
		if (rows == 2)
			return determinant2x2();
		if (rows == 3)
			return determinant2x2();
		throw;
	}
};


/* main function */
int main(int argc, char **argv) {

	srand(time(NULL));

	Matrix* matrix1 = new Matrix(3, 3);
	matrix1->generateRandom(0, 10);
	matrix1->printMatrix();
	cout << endl;

	Matrix* matrix2 = new Matrix(3, 3);
	matrix2->generateRandom(0, 10);
	matrix2->printMatrix();
	cout << endl;

	matrix1->multiply(2);
	matrix1->printMatrix();
	cout << endl;

	Matrix* matrix3 = matrix1->multiply(matrix2);
	matrix3->printMatrix();
	cout << endl;
	
	cout << "Determinant:" << matrix3->getDeterminant() << endl;
	cout << "Matrix sum:" << matrix3->sumMatrix() << endl;

	cout << "Transposed matrix:" << endl;
	matrix3->printTransposedMatrix();

	delete matrix1;
	delete matrix2;
	delete matrix3;

	return EXIT_SUCCESS;
}
