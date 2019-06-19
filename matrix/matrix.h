// 0-indexing matrix with static number of rows and colums

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

template <typename T>
class Matrix {
  public:
    Matrix (unsigned n_rows, unsigned n_columns):
      n_rows(n_rows), n_columns(n_columns) {
      matrix.resize(n_rows, std::vector <T> (n_columns, 0));
    }
    
    ~Matrix () {
      matrix.clear();
    }

    unsigned getNumberRows () const { return n_rows; }
    unsigned getNumberColumns () const { return n_columns; }

    void set (unsigned row, unsigned column, T val) {
      if (not (0 <= row and row < n_rows)) throw "Row index out of scope";
      if (not (0 <= column and column < n_columns)) throw "Column index out of scope";
      matrix[row][column] = val;
    }
    
    T operator () (unsigned row, unsigned column) const {
      if (not (0 <= row and row < n_rows)) throw "Row index out of scope";
      if (not (0 <= column and column < n_columns)) throw "Column index out of scope";
      return matrix[row][column];
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
      for (int row = 0; row < n_rows; row++) {
        for (int column = 0; column < n_columns; column++) {
          std::cout << matrix[row][column] << " \n"[column + 1 == n_columns];
        }
      }
    }


  private:
    unsigned n_rows;
    unsigned n_columns;
    std::vector <std::vector <int>> matrix;
    
};

#endif
