// Descripci√≥n: Calcula el valor de x tal que la integración de 0 a x es igual a un valor (p) introducido por el usuario
// Autor: Adri√°n Marcelo Su√°rez Ponce A01197108
// Fecha: 11 de abril de 2021

//.b=78
#include <iostream>
#include <iomanip>
#include <string>

#include "Calculation.h"
#include "Calculator.h"
#define NUM_SEGMENTS 10
#define ERROR 0.0000001
#define INITX 1.0
using namespace std;

//.i
// Funci√≥n: Despliega un mensaje de error.
// Par√°metros: message: string <- mensaje que se desea desplegar.
// Valor de retorno: void
void displayErrMess(string message) {
  cerr << "Error: " << message << endl;
}

//.i
// Funci√≥n: Funci√≥n que maneja los datos de entrada del programa
// Par√°metros: nada
// Valor de retorno: Calculation <- datos parseados en una clase
void setup(double &pTarget, Calculator &calculator){
  int dof;
  string input;
  bool isValidEntry;

  cout << "Este programa calcula el valor de x tal que integrar de 0 ";
  cout << "a x la distribución t con dof grados de " << endl;
  cout << "libertad nos da p." << endl;

  do {
    cout << "p?> ";
   cin >> input;
    isValidEntry = true;

    for(char c: input) {
      if(!isdigit(c) && c != '.' ) {
        isValidEntry = false;
        displayErrMess("el valor de p debe ser un número real entre 0 y 0.5");
        break;
      }
    }

    if (isValidEntry)
    { 
      pTarget = stod(input);
      if(pTarget < 0 || pTarget > 0.5) {
        displayErrMess("el valor de p debe ser un número real entre 0 y 0.5");
        isValidEntry = false;
      } 
    }
  } while (!isValidEntry);

  do {
    cout << "dof?> ";
   cin >> input;
    isValidEntry = true;

    for(char c: input) {
      if(!isdigit(c)) {
        isValidEntry = false;
        displayErrMess("el valor de dof debe ser un número entero mayor a 0");
        break;
      }
    }

    if (isValidEntry)
    { 
      dof = stoi(input);
      if(dof <= 0) {
        displayErrMess("el valor de dof debe ser un número entero mayor a 0");
        isValidEntry = false;
      } 
    }
  } while (!isValidEntry);

  calculator.setDof(dof);
}

//.i
// Funci√≥n: Funcion que contiene los pasos de ejecuci√≥n del programa
// Par√°metros: calculation <- datos introducidos, calc <- clase que hace los c√°lculos
// Valor de retorno: void
void integrate(Calculation &calculation, Calculator &calc) { //.m
  double oldRes, newRes;
  calc.setCalculation(calculation);
  
  int multiplier = 1;
  oldRes = calc.integrateSimpson(NUM_SEGMENTS * multiplier);
  multiplier *= 2;
  newRes = calc.integrateSimpson(NUM_SEGMENTS * multiplier);
  while(fabs(newRes - oldRes) > ERROR) {
    multiplier*=2;
    oldRes = newRes;
    newRes = calc.integrateSimpson(NUM_SEGMENTS * multiplier);
  }
  calculation.setP(newRes);
}

//.i
// Función que calcula la x dado que la integración de 0 a x = p
// Par√°metros: pTarget <- p recibida, calc <- calculadora con la que se realizan los cálculos
// Valor de retorno: Calculation <- datos parseados en una clase
Calculation calculateX(double const &pTarget, Calculator &calc) {
    double delta = INITX/2;
    Calculation oldCalc, newCalc;
    bool direction; 


    oldCalc.setX(INITX);
    integrate(oldCalc, calc);
    if(oldCalc.getP() < pTarget) {
        newCalc.setX(oldCalc.getX() + delta);
        direction = true;
    } else if(oldCalc.getP() > pTarget) {
        newCalc.setX(oldCalc.getX() - delta);
        direction = false;
    } else {
        return oldCalc;
    }
    integrate(newCalc, calc);

    // check acceptable error and loop setp 5
    while (fabs(oldCalc.getP() - newCalc.getP()) > ERROR) {
        oldCalc.setX(newCalc.getX());
        oldCalc.setP(newCalc.getP());
        if(oldCalc.getP() < pTarget) {
            delta /= direction ? 1 : 2;
            newCalc.setX(oldCalc.getX() + delta);
            direction = true;
        } else if(oldCalc.getP() > pTarget) {
            delta /= direction ? 2 : 1;
            newCalc.setX(oldCalc.getX() - delta);
            direction = false;
        } else {
            return oldCalc;
        }
        integrate(newCalc, calc);
    }

    return newCalc;
}

//.i
// Funci√≥n: Funci√≥n que imprime los datos en el formato esperado.
// Par√°metros: calculation <- datos introducidos
// Valor de retorno: void
void printResult(Calculation &calculation, const int &dof) { //.m
  cout << fixed << setprecision(5);
  cout << "  p = " << calculation.getP() << endl; //.m
  cout << fixed << setprecision(0);
  cout << "dof = " << dof << endl; //.m
  cout << fixed << setprecision(5);
  cout << "  x = " << calculation.getX() << endl; //.m
}

//.i
int main() {
  Calculator calculator;
  double pTarget;
  //.d
  setup(pTarget, calculator); //.m
  Calculation result = calculateX(pTarget, calculator); //.m
  printResult(result, calculator.getDof()); //.m
  return 0;
}