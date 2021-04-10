// Descripción: Encapsula los datos de entrada
// Autor: Adrián Marcelo Suárez Ponce A01197108
// Fecha: 27 de marzo de 2021
//.b=12
#pragma once
class Calculation {
    private: 
    double x, p; //.m
    //.d=3
    public: 
    double getX() {return x;};
    void setX(double x) {this->x = x;};
    double getP() {return p;}; //.m
    void setP(double p) {this->p = p;}; //.m
};