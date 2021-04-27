// Descripción del programa: Predice el valor de una y dado una x, mediante el regresión lineal dado un set de puntos
// 20 de marzo de 2021

//.b=129
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

#include "HistoricalData.h"
#include "Regression.h"
#include "FileReader.h"

//.i
pair<double, double> generatePair(string &line) {
  string sX, sY;
  double dX, dY;

  int commaPos = line.find(',');
	if(commaPos == -1) {
		throw invalid_argument("Error: Una de las líneas de pares no contiene pares.");
	}
  sX = line.substr(0, commaPos);
  sY = line.substr(commaPos+1);

  try {
    dX = stod(sX);
    dY = stod(sY);
  } catch(exception &e) { throw invalid_argument("Error: La lista de pares debe contener valores numéricos."); }

  if(dX < 0 || dY < 0) {
    throw invalid_argument("Error: La lista de pares debe de contener valores mayores o iguales a 0.");
  }

  return make_pair(dX, dY);
}


//.i
void parseData(string &fileName, HistoricalData &data, Regression &regression) {
  double xk; //.m
  pair<double, double> tempData; //.m
  FileReader fileReader(fileName); //.m
  string line;

  fileReader.openFile(); //.m

  line = fileReader.readLine();
  try {
    xk = stod(line);
  } catch(exception &e) { throw invalid_argument("Error: El valor de xk debe ser un número real mayor o igual a 0"); }

  if(xk < 0) throw invalid_argument("Error: El valor de xk debe ser un número real mayor o igual a 0");
  while (!fileReader.eof()) { //.m
    line = fileReader.readLine(); //.m
    tempData = generatePair(line); //.m
    data.addData(tempData); //.m
  }

  regression.setXk(xk);
  regression.setData(data);
  fileReader.closeFile();
}

//.i
void printResults(Regression &regression) {
  cout << fixed << setprecision(5);
  cout << "N = " << regression.getN() << endl; //.m
  cout << "xk = " << regression.getXk() << endl; //.m
  cout << "r = " << regression.getR() << endl; //.m
  cout << "r2 = " << regression.getR2() << endl; //.m
  cout << "b0 = " << regression.getB0() << endl; //.m
  cout << "b1 = " << regression.getB1() << endl; //.m
  cout << "yk = " << regression.getYk() << endl; //.m
  cout << fixed << setprecision(10); //.m
  cout << "sig = " << regression.getSig() << endl; //.m
  cout << fixed << setprecision(5);
  cout << "ran = " << regression.getRan() << endl; //.m
  cout << "LS = " << regression.getLS() << endl; //.m
  cout << "LI = " << regression.getLI() << endl; //.m
}

//.i
int main() {
  try {
    string fileName;//.m
    HistoricalData data;//.m
    Regression regression;//.m
    double xk;
    //.d
    cout << "Introduce el nombre del archivo\n> ";
    getline(cin,fileName);
    //.d
    parseData(fileName, data, regression);//.m
    if(data.getN() < 2) throw invalid_argument("Error: Para calcular la regresión, se requiren 2 puntos.");
    regression.calcParameters();

    printResults(regression);
  } catch(exception &e) { cerr << e.what() << endl;}
  return 0;
}

//.d=70
