// 0-indexing matrix with static number of rows and colums

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

template <typename T>
class Matrix {
  public:
    Matrix (unsigned n, unsigned m) {
    }
    
    ~Matrix () {

    }
    
    void set (unsigned row, unsigned col, T val) {}
    
    T operator () (unsigned, unsigned) const {

    }

    Matrix <T> operator + (const Matrix& other) const {

    }

    Matrix <T> operator - (const Matrix& other) const {

    }

    Matrix <T> operator * (const Matrix& other) const {

    }

    Matrix <T> operator ^ (const int power) const {

    }
    
    Matrix <T> operator * (const int scalar) const {

    }

    Matrix <T> transpose () const {

    }

    void print () const {

    }


  private:
    std::vector <std::vector <int>> matrix;
    
};

#endif
