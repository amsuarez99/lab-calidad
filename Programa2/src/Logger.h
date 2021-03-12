//.b=20
#pragma once
#include <unordered_map>
#include <fstream>

class Logger {
  public:
    //.d=1
    void log(string msg);
    void logErrMess(string errMsg);
    void logResult(const vector<string> classNames, unordered_map<string, Class_*> classMap); //.m
};

//.d=1

//.i
// Función: Imprime mensaje de error en consola
// Parámetros: El mensaje a imprimir
// Valor de retorno: nada
void Logger :: log(string msg) {
  cout << msg;
}

//.i
// Función: Imprime mensaje de error en consola
// Parámetros: El mensaje a imprimir
// Valor de retorno: nada
void Logger :: logErrMess(string msg) {
  throw invalid_argument("ERROR: " + msg); //.m
}

//.i
// Función: Imprime el resultado en el formato especificado
// Parámetros: string fileName -> nombre del archivo,
// int lineCount[3] -> el resultado de conteo de líneas
// Valor de retorno: nada
void Logger :: logResult(vector<string> classNames, //.m
                         unordered_map<string, Class_*> classMap) {
  Class_* auxClass;
  ofstream oFile;
  oFile.open("ConteoLDC.txt");
  cout << "CLASES BASE:" << endl; //.m
  oFile << "CLASES BASE:" << endl; //.m

  for(int i = 0; i < classNames.size(); i++) {
    auxClass = classMap[classNames[i]];
    if(auxClass->getClassType() == BASE) {
      cout << "   " << classNames[i] << ": "; //.m
      oFile << "   " << classNames[i] << ": "; //.m
      auxClass->printClass(oFile);
      cout << endl;
      oFile << endl;
    }
  }
  cout << "--------------------------------------------" << endl;
  oFile << "--------------------------------------------" << endl;
  cout << "CLASES NUEVAS:" << endl; //.m
  oFile << "CLASES NUEVAS:" << endl; //.m
  for(int i = 0; i < classNames.size(); i++) {
    auxClass = classMap[classNames[i]];
    if(auxClass->getClassType() == NEW) {
      cout << "   " << classNames[i] << ": ";
      oFile << "   " << classNames[i] << ": ";
      auxClass->printClass(oFile);
      cout << endl;
      oFile << endl;
    }
  }
  cout << "--------------------------------------------" << endl;
  oFile << "--------------------------------------------" << endl;
  cout << "CLASES REUSADAS:" << endl; //.m
  oFile << "CLASES REUSADAS:" << endl; //.m
  for(int i = 0; i < classNames.size(); i++) {
    auxClass = classMap[classNames[i]];
    if(auxClass->getClassType() == REUSED) {
      cout << "   " << classNames[i] << ": ";
      oFile << "   " << classNames[i] << ": ";
      auxClass->printClass(oFile);
      cout << endl;
      oFile << endl;
    }
  }
  cout << "--------------------------------------------" << endl;
  oFile << "--------------------------------------------" << endl;
  cout << "Total de LDC="; //.m
  oFile << "Total de LDC="; //.m
  int count = 0;
  for(int i = 0; i < classNames.size(); i++) {
    auxClass = classMap[classNames[i]];
    count += auxClass->getT();
  }
  cout << count << endl;
  oFile << count << endl;
}
