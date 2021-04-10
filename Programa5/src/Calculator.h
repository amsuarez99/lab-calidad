// Descripción: Clase que calcula la integral de simpson
// Autor: Adrián Marcelo Suárez Ponce A01197108
// Fecha: 27 de marzo de 2021

//.b=60
#include <math.h>
#include <cstdio>
#define DEBUG 0

class Calculator {
  private:
    Calculation calculation; //.m
    int dof;
    double F(double x);
    double Gamma(double x);
    double GammaHelper(double x);
    double calcFactorial(int x);
  public:
    double integrateSimpson(int nSegments); //.m
    void setCalculation(Calculation calculation) {this->calculation = calculation;}; //.m
    Calculation getCalculation() {return calculation;};
    int getDof() {return dof;};
    void setDof(int dof) {this->dof = dof;};
};

//.i
// Función: Función que calcula el factorial de un número
// Parámetros: x: double <- valor que se desea calcular
// Valor de retorno: el factorial de x: int
double Calculator :: calcFactorial(int x) {
  double factorial = 1;
  for(int i = x; i > 1; i--) {
    factorial *= i;
  }
  return factorial;
}

//.i
// Función: Función que calcula el valor de la F(x) con pero de una distirbución T
// Parámetros: x: double <- valor que se desea calcular
// Valor de retorno: el resultado de F(x) : double
double Calculator :: F(double x) {
  double aux = pow(1 + x*x/(double) dof, -1 * ((dof + 1)/2.0));
  double numerator = Gamma((dof + 1) / 2.0);
  double denominator = sqrt(dof * M_PI) * Gamma(dof / 2.0);
  #if DEBUG==1
    printf("for x = %f\n", x);
    printf("numerator: %f * %f\n", numerator, aux);
    printf("denominator: %f * %f = %f \n", sqrt(dof * M_PI), Gamma(dof / 2.0), denominator);
    printf("result: %f\n", numerator * aux / denominator);
  #endif
  return numerator * aux / denominator;
}

//.i
// Función: Función que ayuda al cálculo recursivo de la función Gamma
// Parámetros: x: double <- valor que se desea calcular
// Valor de retorno: el resultado de Gamma(x) : double
double Calculator :: GammaHelper(double x) {
  double accum = 1;
  for(int i = 1; i <= (int) x; i++) {
    accum *= (x - i);
  }
  accum *= sqrt(M_PI);
  return accum;
}

//.i
// Función: Fucnión recursiva que regresa la función gamma de una x
// Parámetros: x: double <- valor que se desea calcular
// Valor de retorno: el resultado de Gamma(x) : double
double Calculator :: Gamma(double x) {
  double val;
  if(x - (int)x > 0) { // it is not an integer
    val = GammaHelper(x);
  } else { // it is an integer
    val = calcFactorial((int) x - 1);
  }
  return val;
}

//.i
// Función: Calcula la integral con el método simpson dado un número de segmentos
// Parámetros: nSegments <- número de segmentos
// Valor de retorno: double
double Calculator :: integrateSimpson(int nSegments) {
  double x = calculation.getX(); //.m
  double w = x / nSegments;
  double f0 = F(0);
  double fx = F(nSegments * w);
  double secondTerm = 0;
  double thirdTerm = 0;

  double aux, p;
  for(int i = 1; i < nSegments; i++) {
    if(i % 2 == 0) {
      aux = 2 * F(i*w);
      secondTerm += aux;
    } else {
      aux = 4 * F(i*w);
      thirdTerm += aux;
    }
  }

  p = (w /3) * (f0 + secondTerm + thirdTerm + fx);
  return p;
}