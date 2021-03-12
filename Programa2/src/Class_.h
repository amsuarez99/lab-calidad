#pragma once
//.i
enum CLASSTYPE {
  BASE,
  NEW,
  REUSED,
  UNKNOWN
};

//.i
class Class_ {
  public:
    Class_() : T(0), B(0), D(0), M(0), A(0), I(0) {};
    int getT(), getB(), getD(), getM(), getA(), getI();
    void incT(), incB(int n), incD(int n), incM(), setA(int n), incI();
    void printClass();
    CLASSTYPE getClassType();
  private:
    int T, B, D, M, A, I;
};

//.i
void Class_ :: printClass() {
  switch(getClassType()) {
    case BASE:
      cout << "T=" << T << ", ";
      cout << "I=" << I << ", ";
      cout << "B=" << B << ", ";
      cout << "D=" << D << ", ";
      cout << "M=" << M << ", ";
      cout << "A=" << A;
      break;
    case NEW:
      cout << "T=" << T << ", ";
      cout << "I=" << I;
      break;
    case REUSED:
      cout << "T=" << T << ", ";
      cout << "I=" << I << ", ";
      cout << "B=" << B;
      break;
    default:
      break;
  };
}

int Class_ :: getT() {
  return T;
}

void Class_ :: incT() {
  ++T;
}

int Class_ :: getB() {
  return B;
}

void Class_ :: incB(int n) {
  B += n;
}

int Class_ :: getD() {
  return D;
}

void Class_ :: incD(int n) {
  D += n;
}

int Class_ :: getM() {
  return M;
}

void Class_ :: incM() {
  ++M;
}

int Class_ :: getA() {
  return A;
}

void Class_ :: setA(int n) {
  A = n;
}

int Class_ :: getI() {
  return I;
}

void Class_ :: incI() {
  ++I;
}

//.i
CLASSTYPE Class_ :: getClassType() {
  if(B > 0 && (M > 0 || D > 0 || A > 0)) return BASE;
  if(B == 0 && M == 0 && D == 0 && A > 0) return NEW;
  if(B > 0 && M == 0 && D == 0 && A == 0) return REUSED;
  return UNKNOWN;
}

