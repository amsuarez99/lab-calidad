//.b=74
#pragma once
#include <algorithm> //.m
#include "Logger.h" //.m
//.d=1

//.d=7
//.i
class FileReader {
  private:
    string fileName;
    ifstream inputFile;
    //.d=3
    void classifyLine(string line, Class_ *class_, bool &isMultiline); //.m
    string deleteTrailingLeadingSpace(string line);
    bool isSurroundedByString(string line, string tag);

  public:
    //.d=1
    void openFile(string fileName, Logger &logger); //.m
    void parseFile(Class_ *class_); //.m
    void closeFile();
    //.d=2
};

//.d=4
//.i
void FileReader :: openFile(string fileName, Logger &logger) { //.m
  this->fileName = fileName;
  inputFile.open(fileName);
  if(!inputFile) logger.logErrMess("El archivo \"" + fileName + "\" no existe.");
  if(inputFile.peek() == ifstream::traits_type::eof()) logger.logErrMess("El archivo \"" + fileName + "\" está vacío.");
}

//.i
void FileReader :: closeFile() {
  this->fileName = "";
  inputFile.close();
}

//.i
// Función: Lee el archivo línea por línea y guarda los tipos de líneas en variables
// locales.
// Parámetros: ninguno
// Valor de retorno: nada
void FileReader :: parseFile(Class_ *class_) { //.m
  string line, cleanLine; //.m
  //.d=1
  bool inMultiline = false;
  while (!inputFile.eof()) {
    getline(inputFile, line);
    cleanLine = deleteTrailingLeadingSpace(line);
    classifyLine(cleanLine, class_, inMultiline); //.m
    //.d=18
  }
  int n = class_->getT() - class_->getB() + class_->getD();
  class_->setA(n);
}

//.i
void FileReader :: classifyLine(string line, Class_ *class_, bool &inMultiline) { //.m
  int posAux, startPos, x; //.m
  string stringToFind;
  if (!inMultiline) {
    if(line != "" && line != "}" && line != "};" && line != "{") {
      // TODO add when it is not surrounded by string
      if(line.find("/*") != -1) { //.m
        if(line.find("/*") == 0) {
          if(line.find("*/") == -1) inMultiline = true;
        } else {
          // Missing when /* is not in beginning
        }
      } else if(line.find("//") >= 0 && !isSurroundedByString(line, "//")) { //.m
        if(line.find("//.d=") != -1) {
          startPos = line.find("//.d=");
          x = stoi(line.substr(startPos + 5));
          class_->incD(x);
        } else if (line.find("//.b=") != -1){
          startPos = line.find(stringToFind);
          x = stoi(line.substr(startPos + 5));
          class_->incB(x);
        } else if (line.find("//.m") != -1){
          class_->incM();
          class_->incT();
        } else if (line.find("//.i") != -1){
          class_->incI();
        } else if(line.find("//") > 0) { // At beginning{ // It means it is //
          class_->incT();
        }
        } else {
          class_->incT();
          return;
        }
      }
    } else if(line.find("*/") != -1) inMultiline = false; //.m
    //.d=4
}

//.d=11
//.i
string FileReader :: deleteTrailingLeadingSpace(string line) {
    string::const_iterator start = line.begin(), end = line.end();

    // leading spaces
    while (isspace(*start)) {
        ++start;
    }
    // trailing spaces
    if (start != end) {
        while (isspace(*(end-1))){
            --end;
        }
    }
    return line.assign(start, end);
}

//.i
bool FileReader :: isSurroundedByString(string line, string tag) {
  int tagPos = line.find(tag);
  if(tagPos == -1) {
    return false;
  }
  string lString, rString;
  int quoteCountLeft = count(line.begin(), line.begin() + tagPos, '"');
  int quoteCountRight = count(line.begin() + tagPos + tag.length(), line.end(), '"');
  return (quoteCountLeft % 2 != 0 && quoteCountRight % 2 != 0);
}
