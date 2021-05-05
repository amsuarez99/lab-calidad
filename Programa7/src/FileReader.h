//.b=28
#pragma once
#include <fstream>
#include <string>
using namespace std;

class FileReader {
  private:
  ifstream inputFile;
  string fileName;


  public:
  FileReader(string fileName);
  void openFile();
  string readLine();
  void closeFile();
  bool eof();
};

//.i
FileReader :: FileReader(string fileName) {
  this->fileName = fileName;
}

//.i
void FileReader :: openFile() {
  inputFile.open(this->fileName);
  if(!inputFile) throw invalid_argument("Error: El archivo no existe");
  if(inputFile.peek() == ifstream::traits_type::eof()) throw invalid_argument("Error: El archivo está vacío");
}

//.i
void FileReader :: closeFile() {
  inputFile.close();
}

//.i
string FileReader::readLine() {
    string linea;
    getline(inputFile, linea);
    return linea;
}

//.i
bool FileReader::eof() {
  return inputFile.eof();
}
