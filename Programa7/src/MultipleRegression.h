//.b=92
#pragma once

#define M 4
#define N 5

class MultipleRegression {
  private:
  //.d=15
    HistoricalData data;
    vector<vector<double> > matrix;
    vector<double> regressionParams;

    void fillMatrix();
    vector<double> gauss();
    void triangularization();
    void solveTerms();
    double dot(vector<double> a,vector<double> b);
    void swap(int i, int j);
    int findPivot(int it);
    void mult(int i, double coef);
    void sub(int i, int j, double coef);

  public:
  //.d=14
    double predict(vector<double> x);
    void fit(HistoricalData &data);
    vector<double> getRegressionParams() {return this-> regressionParams;};
};

//.i
double MultipleRegression :: dot(vector<double> a,vector<double> b) {
  double sum = 0.0;
  for(size_t i = 0; i < a.size(); i++) {
    sum += (a[i] * b[i]);
  }
  return sum;
}

//.i
double MultipleRegression :: predict(vector<double> x) {
  double prediction;
  x.insert(x.begin(), 1);
  prediction = dot(x, regressionParams);
  return prediction;
}

//.i
void MultipleRegression :: fit(HistoricalData &data) {
  this->data = data;
  // fill Matrix
  fillMatrix();
  // get regressionParams with gauss
  regressionParams = gauss();
}

//.i
void MultipleRegression :: mult(int i, double coef) {
  for(auto &val: matrix[i]) {
    val *= coef;
  }
}

//.i
void MultipleRegression :: sub(int i, int j, double coef) {
  for(size_t x = 0; x < N; x++) {
    matrix[i][x] -= (coef * matrix[j][x]);
  }
}

//.i
void MultipleRegression :: triangularization() {
  int pivotIndex;
  double coef;
  // Iterate N-1 times 
  for(int it = 0; it < M; it++) {
    // find pivot element
    pivotIndex = findPivot(it);

    // Swap the pivot row to the top
    swap(it, pivotIndex);

    // Reduce coefficient of pivot term to 1
    coef = 1.0/matrix[it][it];
    mult(it, coef);

    // subtract the pivot row to every row below by the coeficient of the first element
    for(int i = it + 1; i < M; i++) {
      coef = matrix[i][it];
      // subtract Ai - (C*Ait) to reduce pivot row to 0
      sub(i, it, coef);
    }
  }
}

//.i
void MultipleRegression :: solveTerms() {
  double coef;
  for(int i = M - 1; i > 0; i--) {
    for(int j = i - 1; j >= 0; j--) {
      coef = matrix[j][i];
      sub(j, i, coef);
    }
  }
}

//.i
vector<double> MultipleRegression :: gauss() {
  vector<double> params;
  triangularization();
  solveTerms();
  for(int i = 0; i < M; i++) {
    params.push_back(matrix[i][N-1]);
  }
  return params;
}

//.i
void MultipleRegression :: swap(int i, int j) {
  matrix[i].swap(matrix[j]);
}


//.i
int MultipleRegression :: findPivot(int it) {
  // current max
  int max = matrix[it][it];
  // where the max is
  int index = it;
  for(int i = it; i <M; i++) {
    // current > max?
    index = (matrix[index][it] < matrix[i][it]) ? i : index;
  }
  return index;
}

//.i
void MultipleRegression :: fillMatrix() {
  // Resize matrix to 4x5
  matrix.resize(M, vector<double>(N));
  matrix[0][0] = data.getN();
  matrix[0][1] = data.sum(make_pair(0,1));
  matrix[0][2] = data.sum(make_pair(1,1));
  matrix[0][3] = data.sum(make_pair(2,1));
  matrix[0][4] = data.sum(make_pair(3,1));

  matrix[1][0] = data.sum(make_pair(0,1));
  matrix[1][1] = data.sum(make_pair(0,2));
  matrix[1][2] = data.sum(make_pair(0,1), make_pair(1,1));
  matrix[1][3] = data.sum(make_pair(0,1), make_pair(2,1));
  matrix[1][4] = data.sum(make_pair(0,1), make_pair(3,1));

  matrix[2][0] = data.sum(make_pair(1,1));
  matrix[2][1] = data.sum(make_pair(0,1), make_pair(1,1));
  matrix[2][2] = data.sum(make_pair(1,2));
  matrix[2][3] = data.sum(make_pair(1,1), make_pair(2,1));
  matrix[2][4] = data.sum(make_pair(1,1), make_pair(3,1));

  matrix[3][0] = data.sum(make_pair(2,1));
  matrix[3][1] = data.sum(make_pair(0,1), make_pair(2,1));
  matrix[3][2] = data.sum(make_pair(1,1), make_pair(2,1));
  matrix[3][3] = data.sum(make_pair(2,2));
  matrix[3][4] = data.sum(make_pair(2,1), make_pair(3,1));
}

//.d=58