#include <iostream>
#include <vector>

#include "tester.h"
#include "../mocker/mocker.h"

typedef int MT; // Matrix type for all the cases

void Tester::execute () {
  std::vector <Checker <MT>> checker(NUMBER_OF_TESTS);
  for (int test = 0; test < NUMBER_OF_TESTS; test++) {
    try {
      int n_rows = Mocker::generateRandomNumber <MT> ();
      // For simplicity in the tests we are gonna work with square matrices
      int n_columns = n_rows; //Mocker::generateRandomNumber <MT> ();
      int scalar = Mocker::generateRandomNumber <MT> ();
      n_columns = n_rows;
      Matrix <MT> matrix1 = createRandomMatrix <MT> (n_rows, n_columns);
      Matrix <MT> matrix2 = createRandomMatrix <MT> (n_rows, n_columns);
      testAssignment <MT> (matrix1, checker[test]);
      testSum <MT> (matrix1, matrix2, checker[test]);
      testMatrixMultiplication <MT> (matrix1, matrix2, checker[test]);
      testScalarMultiplication <MT> (scalar, matrix1, checker[test]);
    } catch (const char* message) {
      std::cerr << "Exception raised in test " << test + 1 << std::endl;
      std::cerr << message << std::endl;
      exit(-1);
    }
  }
}

// For testing purposes this function is implemented in a not optimal but
// simple way
template <typename T>
Matrix <T> Tester::createRandomMatrix (int n_rows, int n_columns) {
  Matrix <T> matrix(n_rows, n_columns);
  for (int row = 0; row < n_rows; row++) {
    for (int column = 0; column < n_columns; column++) {
      // [0, 1] range of values for the matrix to get a sparse matrix with
      // more probability
      matrix.set(row, column, Mocker::generateRandomNumber <T> (0, 1));
    }
  }
  return matrix;
}

template <typename T>
SparseMatrix <T> Tester::setSparseMatrix (const Matrix <T>& matrix) {
  int n_rows = matrix.getNumberRows();
  int n_columns = matrix.getNumberColumns();
  SparseMatrix <T> sparse_matrix(n_rows, n_columns);
  for (int row = 0; row < n_rows; row++) {
    for (int column = 0; column < n_columns; column++) {
      sparse_matrix.set(row, column, matrix(row, column));
    }
  }
  return sparse_matrix;
}

template <typename T>
void Tester::testAssignment (const Matrix <T>& matrix, Checker <T>& checker) {
  SparseMatrix <T> sparse_matrix = setSparseMatrix <T> (matrix);
  checker.isEqual(sparse_matrix, matrix, "Assignment is wrong");
}

template <typename T>
void Tester::testSum (const Matrix <T>& matrix1, const Matrix <T>& matrix2, Checker <T>& checker) {
  SparseMatrix <T> sparse_matrix1 = setSparseMatrix <T> (matrix1);
  SparseMatrix <T> sparse_matrix2 = setSparseMatrix <T> (matrix2);
  SparseMatrix <T> sparse_sum = sparse_matrix1 + sparse_matrix2;
  Matrix <T> matrix_sum = matrix1 + matrix2;
  checker.isEqual(sparse_sum, matrix_sum, "Sum is wrong");
}

template <typename T>
void Tester::testMatrixMultiplication (const Matrix <T>& matrix1, const Matrix <T>& matrix2, Checker <T>& checker) {
  SparseMatrix <T> sparse_matrix1 = setSparseMatrix <T> (matrix1);
  SparseMatrix <T> sparse_matrix2 = setSparseMatrix <T> (matrix2);
  SparseMatrix <T> sparse_multiplication = sparse_matrix1 * sparse_matrix2;
  Matrix <T> matrix_multiplication = matrix1 * matrix2;
  checker.isEqual(sparse_multiplication, matrix_multiplication, "Multiplication is wrong");
}

template <typename T>
void Tester::testScalarMultiplication (T scalar, const Matrix <T>& matrix, Checker <T>& checker) {
  SparseMatrix <T> sparse_matrix = setSparseMatrix <T> (matrix);
  SparseMatrix <T> sparse_scalar_multiplication = sparse_matrix * scalar;
  Matrix <T> matrix_scalar_multiplication = matrix * scalar;
  checker.isEqual(sparse_scalar_multiplication, matrix_scalar_multiplication,
      "Scalar multiplication is not working");
}
