#pragma once
#include <numeric>
#include <vector>
#include <algorithm>
#include <utility>

class HistoricalData {
  private:
    int N;
    double sumXY, sumX2, sumY2, sumX, sumY;
    double difXXavg2, stdev;
    double xAvg, yAvg, x2Avg;
    vector<pair<double, double> > obs;
    double sum(vector<double> v);

    void updateMetrics();
    void updateSumXY();
    void updateSumX2();
    void updateSumY2();
    void updateSumX();
    void updateSumY();
    void updateXAvg();
    void updateYAvg();
    void updateX2Avg();
    void updateDifXXavg2();
    void updateStdev();


  public:
    HistoricalData(); //.m
    void addData(pair<double, double> newObs);
    void analize();
    int getN() {return obs.size();};
    double getSumXY() {return sumXY;};
    double getSumX2() {return sumX2;};
    double getSumY2() {return sumY2;};
    double getSumX() {return sumX;};
    double getSumY() {return sumY;};
    double getXAvg() {return xAvg;};
    double getYAvg() {return yAvg;};
    double getX2Avg() {return x2Avg;};
    vector<pair<double, double> > getData() {return obs;};
};

//.i
HistoricalData :: HistoricalData() {
  this->N = 0;
}

//.i
double HistoricalData :: sum(vector<double> v) {
  double sum = accumulate(v.begin(), v.end(), 0.0, [](double x, double y) { return x + y;});
  return sum;
}

//.i
void HistoricalData::updateSumXY() {
  vector<double> xy;
  xy.resize(obs.size());
  transform(obs.begin(), obs.end(), xy.begin(), [](pair<double, double> p){ return p.first * p.second;} );
  sumXY = sum(xy);
}

//.i
void HistoricalData::updateSumX2() {
  vector<double> x2;
  x2.resize(obs.size());
  transform(obs.begin(), obs.end(), x2.begin(), [](pair<double, double> p){ return p.first * p.first;} );
  sumX2 = sum(x2);
}


//.i
void HistoricalData::updateSumY2() {
  vector<double> y2;
  y2.resize(obs.size());
  transform(obs.begin(), obs.end(), y2.begin(),
      [](pair<double, double> p){ return p.second * p.second;} );
  sumY2 = sum(y2);
}

//.i
void HistoricalData::updateSumX() {
  vector<double> x;
  x.resize(obs.size());
  transform(obs.begin(), obs.end(), x.begin(), [](pair<double, double> p){ return p.first;});
  sumX = sum(x);
}


//.i
void HistoricalData::updateSumY() {
  vector<double> y;
  y.resize(obs.size());
  transform(obs.begin(), obs.end(), y.begin(),
              [](pair<double, double> p){ return p.second; });
  sumY = sum(y);
}

//.i
void HistoricalData::updateXAvg() {
  xAvg = sumX/N;
}

//.i
void HistoricalData::updateYAvg() {
  yAvg = sumY/N;
}

//.i
void HistoricalData::updateX2Avg() {
  x2Avg = sumX2/N;
}

//.i
void HistoricalData::updateMetrics() {
  updateSumXY();
  updateSumX2();
  updateSumY2();
  updateSumX();
  updateSumY();
  updateXAvg();
  updateYAvg();
  updateX2Avg();
}


//.i
void HistoricalData:: addData(pair<double, double> newObs) {
  obs.push_back(newObs);
  N = obs.size();
  updateMetrics();
}
