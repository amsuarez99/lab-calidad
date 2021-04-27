// Descripción: Clase que calcula la integral de simpson
// Autor: Adrián Marcelo Suárez Ponce A01197108
// Fecha: 27 de marzo de 2021

//.b=60
#pragma once
#include <math.h>
#define DEBUG 0
#define NUM_SEGMENTS 10
#define ERROR 0.0000001
#define INITX 1.0

class Calculator { //.m
  private:
    int dof;
    double F(double x);
    double Gamma(double x);
    double GammaHelper(double x);
    double calcFactorial(int x);
    double integrateSimpson(double x, int nSegments); //.m
  public:
    double integrate(double x);
    double calculateXgivenP(double pTarget);
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
  double aux = pow(1 + x*x/(double) dof, -1 * ((dof + 1)/2.0)); //.m
  double numerator = Gamma((dof + 1) / 2.0);
  double denominator = sqrt(dof * M_PI) * Gamma(dof / 2.0); //.m
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
double Calculator :: integrateSimpson(double x, int nSegments) {
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

//.i
// Funci√≥n: Funcion que contiene los pasos de ejecuci√≥n del programa
// Par√°metros: calculation <- datos introducidos, calc <- clase que hace los c√°lculos
// Valor de retorno: void
double Calculator::integrate(double x) { //.m
  double oldRes, newRes; //.m
  
  int multiplier = 1;
  oldRes = integrateSimpson(x, NUM_SEGMENTS * multiplier); //.m
  multiplier *= 2;
  newRes = integrateSimpson(x, NUM_SEGMENTS * multiplier); //.m
  while(fabs(newRes - oldRes) > ERROR) {
    multiplier*=2;
    oldRes = newRes;
    newRes = integrateSimpson(x, NUM_SEGMENTS * multiplier); //.m
  }
  return newRes;
}

//.i
// Función que calcula la x dado que la integración de 0 a x = p
// Par√°metros: pTarget <- p recibida, calc <- calculadora con la que se realizan los cálculos
// Valor de retorno: Calculation <- datos parseados en una clase
double Calculator::calculateXgivenP(double pTarget) { //.m
    double delta = INITX/2;
    double oldP, newP, oldX, newX; //.m
    bool direction; 


    oldX = INITX; //.m
    oldP = integrate(oldX); //.m
    if(oldP < pTarget) { //.m
      newX = oldX + delta; //.m
      direction = true;
    } else if(oldP > pTarget) { //.m
      newX = oldX - delta; //.m
      direction = false;
    } else {
      return oldX; //.m
    }
    newP = integrate(newX); //.m

    // check acceptable error and loop setp 5
    while (fabs(oldP - newP) > ERROR) { //.m
      oldX = newX; //.m
      oldP = newP; //.m
      if(oldP < pTarget) { //.m
          delta /= direction ? 1 : 2;
          newX = oldX + delta; //.m
          direction = true;
      } else if(oldP > pTarget) { //.m
          delta /= direction ? 2 : 1;
          newX = oldX - delta; //.m
          direction = false;
      } else {
          return oldX; //.m
      }
      newP = integrate(newX); //.m
    }

    return newX; //.m
}