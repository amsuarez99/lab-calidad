#pragma once
#include <fstream>
#include <unordered_map>
using namespace std;

#include "Class_.h"
#include "Logger.h"
#include "FileReader.h"

//.i
class Environment {
  private:
    Logger logger;
    vector<string> fileNames;
    vector<string> classNames;
    unordered_map<string, Class_*> classMap;
    FileReader fileReader;
    string getClassName(string fileName);

  public:
    Environment(const vector<string> &fileNames, Logger &logger);
    unordered_map<string, Class_*> getClassMap();
    vector<string> getClassNames();
    void parseFiles();
    void printMap();
};

//.i
Environment :: Environment(const vector<string> &fileNames, Logger &logger) {
  this->logger = logger;
  this->fileNames = fileNames;
}

//.i
void Environment :: parseFiles() {
  string aux;
  // trim the fileExtension
  for(int i = 0; i < fileNames.size(); i++) {
    aux = getClassName(fileNames[i]);

    //check if the class isn't in the umap
    auto search = classMap.find(aux);
    if(search == classMap.end()) {
      classNames.push_back(aux);
      classMap.insert({ aux, new Class_()});
    }

    fileReader.openFile(fileNames[i], logger);
    fileReader.parseFile(classMap[aux]);
    if(classMap[aux]->getClassType() == UNKNOWN) logger.logErrMess("El archivo \"" + fileNames[i] + "\" no puede ser clasificado.");
    fileReader.closeFile();
  }
}

//.i
string Environment :: getClassName(string fName) {
  int pos = fName.find_last_of('.');
  string fileN = fName.substr(0, pos);
  return fileN;
}

unordered_map<string, Class_*> Environment :: getClassMap() {
  return classMap;
}

vector<string> Environment :: getClassNames() {
  return classNames;
}
