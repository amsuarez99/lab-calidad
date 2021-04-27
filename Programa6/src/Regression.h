// Descripción: Clase que calcula la integral de simpson
// Autor: Adrián Marcelo Suárez Ponce A01197108
// Fecha: 27 de marzo de 2021
//.b=87
#pragma once
#include <algorithm>
#include "HistoricalData.h"
#include "Calculator.h"

class Regression {
  private:
    double xk, yk;
    double b0, b1, r, r2, sig, ran, ls, li;
    HistoricalData data;
    double calcSigX();

    void calcB0();
    void calcB1();
    void calcR();
    void calcR2();
    void calcSig();
    void calcPredictionInterval();
    void calcYk();
    double stdev();
    double calcRange();
    double sumDifXiXavg2();
  public:
    void calcParameters();
    double getB0() {return b0;};
    double getB1() {return b1;};
    double getR() {return r;};
    double getR2() {return r2;};
    double getXk() {return xk;};
    double getYk() {return yk;};
    double getSig() {return sig;};
    double getLI() {return li;};
    double getLS() {return ls;};
    double getRan() {return ran;};
    void setXk(double xk) { this->xk = xk;};
    void setData(HistoricalData &data) {this->data = data;};
    int getN() {return data.getN();};
};

//.i
void Regression::calcParameters() {
  calcB1();
  calcB0();
  calcR();
  calcR2();
  calcYk();
  calcSig();
  calcPredictionInterval();
}

//.i
void Regression :: calcB1() {
  double numerator = data.getSumXY() - (data.getN() * data.getXAvg() * data.getYAvg());
  double denominator = data.getSumX2() - (data.getN() * data.getXAvg() * data.getXAvg());
  b1 = numerator/denominator;
}

//.i
void Regression :: calcB0() {
  b0 = data.getYAvg() - b1 * data.getXAvg();
}

//.i
void Regression :: calcR() {
  double numerator = data.getN() * data.getSumXY() - (data.getSumX() * data.getSumY());
  double denominator = sqrt((data.getN() * data.getSumX2() - pow(data.getSumX(),2)) * (data.getN() * data.getSumY2() - pow(data.getSumY(), 2)));
  r = numerator/denominator;
}

//.i
void Regression :: calcR2() {
  r2 = r*r;
}

//.i
void Regression :: calcYk() {
  yk = b0 + b1*xk;
}

//.i
double Regression :: calcSigX() {
  double numerator = fabs(r) * sqrt(data.getN() - 2);
  double denominator = sqrt(1 - (r2));
  return numerator/denominator;
}

//.i
void Regression :: calcSig() {
  double x = calcSigX();
  Calculator calc;
  calc.setDof(data.getN() - 2);
  double p = calc.integrate(x);
  sig = 1 - 2*p;
}

//.i
double Regression :: stdev() {
  vector<pair<double, double> > dataCpy = data.getData();
  double sum = 0;
  for(int i = 0; i < data.getN(); i++) {
    sum += pow(dataCpy[i].second - b0 - (b1*dataCpy[i].first), 2);
  }
  double res = (1.0/(data.getN() - 2)) * sum;
  return sqrt(res);
}

//.i
double Regression :: sumDifXiXavg2() {
  vector<pair<double, double> > dataCpy = data.getData();
  double sum = 0;
  for(int i = 0; i < data.getN(); i++) {
    sum += pow(dataCpy[i].first - data.getXAvg(), 2);
  }
  return sum;
}

//.i
double Regression :: calcRange() {
  Calculator calc;
  calc.setDof(data.getN() - 2);
  double difxkavg2 = (xk - data.getXAvg()) * (xk - data.getXAvg());
  double range70 = calc.calculateXgivenP(0.35);
  double stdv = stdev();
  double thirdPart = difxkavg2/sumDifXiXavg2();
  return  range70 * stdv * sqrt(1.0 + (1.0/data.getN()) + thirdPart);
}

//.i
void Regression :: calcPredictionInterval() {
  ran = calcRange();
  ls = yk + ran;
  li = std::max(yk - ran, 0.0);
}