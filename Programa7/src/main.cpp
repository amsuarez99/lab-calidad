// Descripción del programa: Predice el valor de una y dado una x, mediante el regresión lineal dado un set de puntos
// 20 de marzo de 2021
//.b=69
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <utility>
#include <numeric>
#include <math.h>
#include <algorithm>
#include <exception>
using namespace std;

#include "FileReader.h"
#include "HistoricalData.h"
#include "MultipleRegression.h"

//.i
vector<double> parseLine(string &line) { //.m
  vector<double> aux;
  int commaPos;
  double dAux;

  // Check if empty line

  // Search for comma
  commaPos = line.find(',');

  // while commas are found
  while(commaPos != -1) {
    // Cast to double from beginning to before comma
    try {
      dAux = stod(line.substr(0, commaPos));
    } catch(exception &e) {
      throw invalid_argument("Error: Todos los valores deben ser números reales mayor o iguales a 0");
    }

    // Check if number is >= 0
    if(dAux < 0) {
      throw invalid_argument("Error: Todos los valores deben ser números reales mayor o iguales a 0");
    }

    // Add to vector
    aux.push_back(dAux);

    // Trim from commaPos + 1 to end
    line = line.substr(commaPos + 1);
    commaPos = line.find(',');
  }

  // convert remaining line to double
  try {
    dAux = stod(line);
  } catch(exception &e) {
    throw invalid_argument("Error: Todos los valores deben ser números reales mayor o iguales a 0");
  }

  // Check if number is >= 0
  if(dAux < 0) {
    throw invalid_argument("Error: Todos los valores deben ser números reales mayor o iguales a 0");
  }

  // Add to vector
  aux.push_back(dAux);
  return aux;
}
//.d=24

//.i
vector<double> parseFile(string &fileName, HistoricalData &data) {
  //.d=2
  // Declare Variables to return
  vector<double> x, obs;

  // Initialize File reader
  FileReader fileReader(fileName);
  string line;

  // Open File
  fileReader.openFile();

  try {
    // Read line
    line = fileReader.readLine();

    // Parse wk, xk, yk
    x = parseLine(line);

    data.setM(x.size() + 1);

    // Parse Data (observations)
    while(!fileReader.eof()) {
      line = fileReader.readLine();
      obs = parseLine(line);
      // Add obs to historical data
      data.addData(obs);
    }

    // Check that there are more than two points
    if(data.getN() < 2) throw invalid_argument("Error: Para calcular la regresión, se requiren al menos 2 puntos.");
  } catch(exception &e) {
    // Close the file and rethrow
    fileReader.closeFile();
    throw invalid_argument(e.what());
  }

  // Close File
  fileReader.closeFile();

  // Return x
  return x;
}

//.i
void printResults(const size_t &n, const vector<double> &x, const vector<double> &regressionParams, const double &prediction) {
  cout << "N  = " << n << endl; //.m
  cout << fixed << setprecision(5); //.m
  cout << "wk = " << x[0] << endl; //.m
  cout << "xk = " << x[1] << endl; //.m
  cout << "yk = " << x[2] << endl; //.m
  cout << "------------" << endl; //.m
  cout << "b0 = " << regressionParams[0] << endl; //.m
  cout << "b1 = " << regressionParams[1] << endl; //.m
  cout << "b2 = " << regressionParams[2] << endl; //.m
  cout << "b3 = " << regressionParams[3] << endl; //.m
  cout << "------------" << endl; //.m
  cout << "zk = " << prediction << endl; //.m
}

//.i
int main() {
  try {
    string fileName;
    HistoricalData data;
    vector<double> x;
    double prediction;
    
    // User Input
    cout << "Introduce el nombre del archivo\n> ";
    getline(cin,fileName);

    // Parse File and receiv xk, yk, zk
    x = parseFile(fileName, data); //.m

    // Initialize regression
    MultipleRegression mRegression; //.m
    // Fit Regression
    mRegression.fit(data);

    // Predict with xk, yk and zk
    prediction = mRegression.predict(x);

    // Print Results
    printResults(data.getN(), x, mRegression.getRegressionParams(), prediction);
    //.d=1
  } catch(exception &e) { cerr << e.what() << endl;}
  return 0;
}
