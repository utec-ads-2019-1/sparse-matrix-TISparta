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
      if (n_rows != other.getNumberRows()) throw "The number of rows doest not match";
      if (n_columns != other.getNumberColumns()) throw "The number of columns doest not match";
      Matrix ret(n_rows, n_columns);
      for (int row = 0; row < n_rows; row++) {
        for (int column = 0; column < n_columns; column++) {
          ret.set(row, column, (*this)(row, column) + other(row, column));
        }
      }
      return ret;
    }

    Matrix <T> operator - (const Matrix& other) const {
      if (n_rows != other.getNumberRows()) throw "The number of rows doest not match";
      if (n_columns != other.getNumberColumns()) throw "The number of columns doest not match";
      Matrix ret(n_rows, n_columns);
      for (int row = 0; row < n_rows; row++) {
        for (int column = 0; column < n_columns; column++) {
          ret.set(row, column, (*this)(row, column) - other(row, column));
        }
      }
      return ret;
    }

    Matrix <T> operator * (const Matrix& other) const {
      if (n_columns != other.getNumberRows()) throw "Can not multiply these matrices";
      Matrix ret(n_rows, other.getNumberColumns());
      for (int row = 0; row < n_rows; row++) {
        for (int column = 0; column < n_columns; column++) {
          T new_value = 0;
          for (int it = 0; it < n_columns; it++) {
            new_value += (*this)(row, it) * other(it, column);
          }
          ret.set(row, column, new_value);
        }
      }
      return ret;
    }

    Matrix <T> operator * (const int scalar) const {
      Matrix ret(n_rows, n_columns);
      for (int row = 0; row < n_rows; row++) {
        for (int column = 0; column < n_columns; column++) {
          ret.set(row, column, scalar * (*this)(row, column));
        }
      }
      return ret;
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
