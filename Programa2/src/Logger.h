//.b=20
#pragma once
#include <unordered_map>

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
  cout << "CLASES BASE:" << endl; //.m
  for(int i = 0; i < classNames.size(); i++) {
    auxClass = classMap[classNames[i]];
    if(auxClass->getClassType() == BASE) {
      cout << "   " << classNames[i] << ": "; //.m
      auxClass->printClass();
      cout << endl;
    }
  }
  cout << "--------------------------------------------" << endl;
  cout << "CLASES NUEVAS:" << endl; //.m
  for(int i = 0; i < classNames.size(); i++) {
    auxClass = classMap[classNames[i]];
    if(auxClass->getClassType() == NEW) {
      cout << "   " << classNames[i] << ": ";
      auxClass->printClass();
      cout << endl;
    }
  }
  cout << "--------------------------------------------" << endl;
  cout << "CLASES REUSADAS:" << endl; //.m
  for(int i = 0; i < classNames.size(); i++) {
    auxClass = classMap[classNames[i]];
    if(auxClass->getClassType() == REUSED) {
      cout << "   " << classNames[i] << ": ";
      auxClass->printClass();
      cout << endl;
    }
  }
  cout << "--------------------------------------------" << endl;
  cout << "Total de LDC="; //.m
  int count = 0;
  for(int i = 0; i < classNames.size(); i++) {
    auxClass = classMap[classNames[i]];
    count += auxClass->getT();
  }
  cout << count << endl;
}
