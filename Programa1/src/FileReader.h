#pragma once
#include <fstream>
#include <string>
using namespace std;

enum LINETYPE {
  BLANK,
  COMMENT,
  COMMENTSTART,
  COMMENTEND,
  CODE
};

class FileReader {
  private:
    string fileName;
    ifstream inputFile;
    int blankLines;
    int commentedLines;
    int codeLines;
    LINETYPE classifyLine(string line);

  public:
    FileReader();
    void openFile(string fileName);
    string fileStatus();
    void readFile();
    void getResults(int *results);
};

// Función: Constructor de clase que inicializa las variables que contabilizan
// las líneas del archivo.
// Parámetros: ninguno
// Valor de retorno: nada
FileReader :: FileReader() {
  blankLines = 0;
  commentedLines = 0;
  codeLines = 0;
}

// Función: Guarda el nombre del archivo en la variable fileName y lo abre para
// posteriormente leerlo.
// Parámetros: fileName -> nombre del archivo
// Valor de retorno: nada
void FileReader :: openFile(string fileName) {
  this->fileName = fileName;
  inputFile.open(fileName);
}

// Función: Lee el archivo línea por línea y guarda los tipos de líneas en variables
// locales.
// Parámetros: ninguno
// Valor de retorno: nada
void FileReader :: readFile() {
  string line;
  string trimmedLine;

  while (!inputFile.eof()) {
    getline(inputFile, line);
    switch(classifyLine(line)) {
      case BLANK:
        blankLines++;
        break;

      case COMMENT:
        commentedLines++;
        break;

      case COMMENTSTART:
        do {
          commentedLines++;
          getline(inputFile, line);
        } while(classifyLine(line) != COMMENTEND);
        // Contar la línea que cierra el comentario multilínea
        commentedLines++;
        break;

      case CODE:
        codeLines++;
        break;

      default:
        break;
    }
  }

}

// Función: Clasifica la línea dependiendo de los primeros caracteres
// Parámetros: string line -> la línea que se quiere clasificar
// Valor de retorno: El tipo de línea clasificado con un ENUM
LINETYPE FileReader :: classifyLine(string line) {
  if(line.find("//") != -1) return COMMENT;
  if(line.find("/*") != -1) return COMMENTSTART;
  if(line.find("*/") != -1) return COMMENTEND;
  for(char c : line) {
    if(!isspace(c)) {
      return CODE;
    }
  }
  return BLANK;
}

// Función: Regresa el resultado de contar las líneas en un arreglo
// Parámetros: int *results -> El arreglo donde se guardan los resultados pasado por referencia;
// Valor de retorno: nada
void FileReader :: getResults(int *results) {
  results[0] = blankLines;
  results[1] = commentedLines;
  results[2] = codeLines;
}

// Función: Arroja errores si hubo problemas con el cargado del archivo
// Parámetros: ninguno
// Valor de retorno: el mensaje de error, si es que hay
string FileReader :: fileStatus() {
  string error = "";
  if(!inputFile) {
    error = "Error: Se introdujo un archivo no existente.";
  }
  else if(inputFile.peek() == EOF){
    error = "Error: Se introdujo un archivo vacío.";
  }
  return error;
}

