//.b=89
#pragma once

class HistoricalData {
  private:
    size_t N, M; //.m
    //.d=14
    vector<vector<double> > data; //.m

  public:
    HistoricalData();
    void addData(vector<double> obs); //.m
    //.d=10
    void setM(size_t M);
    size_t getN() {return this->N;};
    size_t getM() {return this->M;};
    double sum(pair<int, int> param); //.m
    double sum(pair<int, int> param1, pair<int, int> param2);
    void printData();
};

//.i
HistoricalData :: HistoricalData() {
  this->N = 0;
}



//.i
double HistoricalData :: sum(pair<int, int> param) { //.m
  vector<double> a;
  double sum = 0.0;

  a = data[param.first];

  //fold
  for(size_t i = 0; i < a.size(); i++) {
    sum += pow(a[i], param.second);
  }

  // return sum
  return sum;
}

//.i
double HistoricalData :: sum(pair<int, int> param1, pair<int, int> param2) {
  vector<double> a, b;
  vector<pair<double,double> > zipped;
  double sum = 0.0;

  a = data[param1.first];
  b = data[param2.first];

  //fold
  for(size_t i = 0; i < a.size(); i++) {
    sum += (pow(a[i], param1.second) * pow(b[i], param2.second));
  }

  // return sum
  return sum;
}

//.i
void HistoricalData :: setM(size_t M) {
  this->M = M;
  data.resize(M);
}

//.i
void HistoricalData :: addData(vector<double> obs) { //.m
  // Iterate through the observations and push them to their respective "row"
  // in the data vector
  if(obs.size() != M) throw invalid_argument("Error: Una de las líneas de datos contiene una cantidad de datos incongruente.");
  for(size_t i = 0; i < obs.size(); i++) {
    data[i].push_back(obs[i]);
  }
  // update n
  N++;
}

//.i
void HistoricalData :: printData() {
  for (auto rows : data) {
    for(auto data: rows) {
      cout << data << " ";
    }
    cout << endl;
  }
}
//.d=43