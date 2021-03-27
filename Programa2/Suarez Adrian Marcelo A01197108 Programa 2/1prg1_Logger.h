#pragma once
class Logger {
  public:
    Logger();
    void log(string msg);
    void logErrMess(string errMsg);
    void logResult(string fileName, int (&lineCount)[3]);
};

// Constructor de la clase
Logger :: Logger() {
}

// Función: Imprime mensaje de error en consola
// Parámetros: El mensaje a imprimir
// Valor de retorno: nada
void Logger :: log(string msg) {
  cout << msg;
}

// Función: Imprime mensaje de error en consola
// Parámetros: El mensaje a imprimir
// Valor de retorno: nada
void Logger :: logErrMess(string msg) {
  cout << msg << endl;
}

// Función: Imprime el resultado en el formato especificado
// Parámetros: string fileName -> nombre del archivo,
// int lineCount[3] -> el resultado de conteo de líneas
// Valor de retorno: nada
void Logger :: logResult(string fileName, int (&lineCount)[3]) {
  cout << "Nombre del archivo: " << fileName << endl;
  cout << "--------------------------------------------" << endl;
  cout << "Cantidad de líneas en blanco: " << lineCount[0] << endl;
  cout << "Cantidad de líneas con comentarios: " << lineCount[1] << endl;
  cout << "Cantidad de líneas con código: " << lineCount[2] << endl;
  cout << "--------------------------------------------" << endl;
  cout << "Cantidad total de líneas: " << (lineCount[0] + lineCount[1] + lineCount[2]) << endl;
}
