// Descripción de programa:
// Programa que lee etiquetas de archvios, y cuenta las respectivas líneas que contienen
// esas etiquetas.
// Adrián Marcelo Suárez Ponce
// 10 de marzo de 2021

//.b=21
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
using namespace std;

#include "Environment.h" //.m
#include "Logger.h"

//.i
// Función main
int main() {
  try {
    Logger logger;
    vector<string> fileNames;
    string fileName; //.m
    logger.log("Introduce el nombre de los archivos\n"); //.m
    getline(cin,fileName); //.m
    while(fileName != "") {
      fileNames.push_back(fileName);
      getline(cin, fileName);
    }
    Environment env(fileNames, logger); //.m
    env.parseFiles(); //.m
    logger.logResult(env.getClassNames(), env.getClassMap()); //.m
    //.d=5
  } catch(exception &e) { cerr << e.what() << endl;}
  return 0;
}
