// Sparse matrix with fixed number of rows and columns

#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include "node.h"

template <typename T>
class SparseMatrix {
  public:
    SparseMatrix (unsigned rows, unsigned columns) {

    }

    void set (unsigned row, unsigned col, T) {

    }

    T operator () (unsigned, unsigned) const {

    }

    SparseMatrix <T> operator * (T scalar) const;
    SparseMatrix <T> operator * (const SparseMatrix <T>& other) const;
    SparseMatrix <T> operator + (const SparseMatrix <T>& other) const;
    SparseMatrix <T> operator - (const SparseMatrix <T>& other) const;
    SparseMatrix <T> transpose () const;
    void print () const;

    ~SparseMatrix();
};

#endif 
