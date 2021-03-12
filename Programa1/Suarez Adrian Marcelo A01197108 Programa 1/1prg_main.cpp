// Descripción de programa:
//  Programa que lee un archivo e indica qué lineas contienen comentarios, así
//  como líneas en blanco y líneas de código.
// Adrián Marcelo Suárez Ponce
// 26 de febrero de 2021
#include <iostream>
#include <string>
using namespace std;

#include "FileReader.h"
#include "Logger.h"


// Función main
int main() {
  int results[3];
  string fName, error;

  Logger logger;
  FileReader fileReader;

  logger.log("Introduce el nombre del archivo que deseas leer\n> ");
  cin >> fName;

  fileReader.openFile(fName);
  error = fileReader.fileStatus();
  if(error != "") {
    logger.logErrMess(error);
  } else {
    fileReader.readFile();
    fileReader.getResults(results);
    logger.logResult(fName, results);
  }
  return 0;
}
