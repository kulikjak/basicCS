#include <iostream>
#include <cmath>

/*
 * Trida reprezentujici komplexni cislo
 * Obsahuje i pokrocilejsi metody pro pretezovani operatoru.
 * Author: Jakub Kulik
 */

using namespace std;

class Complex {
private:
  float real, imag;

public:
  /* konstruktor, kopirujici kontruktor a destruktor */
  Complex(float re = 0, float im = 0) : real(re), imag(im) {}
  Complex(const Complex& orig) : real(orig.real), imag(orig.imag) {}
  ~Complex() {}

  /* vypise komplexni cislo ve znamem formatu */
  void print() {
    cout << real << showpos << imag << "i" << noshowpos << endl;
  }

  /* vrati absolutni hodnotu komlexniho cisla (Pythagorova veta) */
  float abs() {
    return sqrt(real * real + imag * imag);
  }

  /* vraci realnou resp. imaginarni cat komplexniho cisla */
  float getReal() {
    return real;
  }
  float getImag() {
    return imag;
  }

  /* nastavuje realnou resp. imaginarni cat komplexniho cisla */
  void setReal(float real) {
    this->real = real;
  }
  void setImag(float imag) {
    this->imag = imag;
  }

  /* funkce pro aritmeticke operace s komplexnimi cisly */
  Complex add(Complex a) {
    return Complex(real + a.real, imag + a.imag);
  }
  Complex diff(Complex a) {
    return Complex(real - a.real, imag - a.imag);
  }
  Complex multiple(Complex a) {
    return Complex(real * a.real - imag * a.imag, real * a.imag + imag * a.real);
  }
  Complex divide(Complex a) {
    return Complex (
             (real * a.real + imag * a.imag) / (a.real * a.real + a.imag * a.imag),
             (imag * a.real - real * a.imag) / (a.real * a.real + a.imag * a.imag));
  }

  /* pretezovani operatoru */
  friend Complex operator+(Complex a, Complex b) {
    return a.add(b);
  }
  friend Complex operator-(Complex a, Complex b) {
    return a.diff(b);
  }
  friend Complex operator*(Complex a, Complex b) {
    return a.multiple(b);
  }
  friend Complex operator/(Complex a, Complex b) {
    return a.divide(b);
  }

  /* pretezovani operatoru vstupu a vystupu */
  friend ostream& operator<<(ostream& os, Complex x) {
    os << x.getReal() << showpos << x.getImag() << "i" << noshowpos;
    return os;
  }
  friend istream& operator>>(istream& is, Complex &x) {
    char i;
    is >> x.real >> x.imag >> i;
    return is;
  }
};


/* main function */
int main(int argc, char **argv) {
  Complex a(3, 3);
  Complex b(2, 4);
  Complex c, d, e, f;
  c = a.add(b);
  d = a.diff(b);
  c.print();
  d.print();


  e = a + b;
  f = a - b;
  cout << e << endl;
  cout << f << endl;

  cout << a + b << endl;
  cout << a - b << endl;

  Complex x(2, 2);
  Complex y(1, 1);
  cout << x * y << endl;

  Complex z(0, 0);
  cin >> z;
  cout << z << endl;

  return EXIT_SUCCESS;
}
