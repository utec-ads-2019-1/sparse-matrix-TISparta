#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "tester.h"
#include "../mocker/mocker.h"

typedef int MT; // Matrix type for all the cases

void Tester::execute () {
  std::vector <Checker <MT>> checker(NUMBER_OF_TESTS);
  for (int test = 0; test < NUMBER_OF_TESTS; test++) {
    try {
      std::cout << "Running test " << test + 1 << std::endl;
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
      testSubstractionMultiplication <MT> (matrix1, matrix2, checker[test]);
      testTranspose(matrix1, checker[test]);
      testDelete(matrix1, checker[test]);
    } catch (const char* message) {
      std::cerr << "Exception raised in test " << test + 1 << std::endl;
      std::cerr << message << std::endl;
      exit(-1);
    }
  }
  int n_correct = 0;
  int n_incorrect = 0;
  for (int test = 0; test < NUMBER_OF_TESTS; test++) {
    checker[test].printResults(test + 1);
    n_correct += checker[test].getNumberCorrectTests();
    n_incorrect += checker[test].getNumberIncorrectTests();
  }
  Checker<MT>::printFinalResults(n_correct, n_incorrect);
}

// For testing purposes this function is implemented in a not optimal but
// simple way
template <typename T>
Matrix <T> Tester::createRandomMatrix (int n_rows, int n_columns) {
  Matrix <T> matrix(n_rows, n_columns);
  std::vector <std::pair <T, std::pair <int, int>>> positions;
  for (int row = 0; row < n_rows; row++) {
    for (int column = 0; column < n_columns; column++) {
      // [0, 1] range of values for the matrix to get a sparse matrix with
      // more probability
      T new_value = Mocker::generateRandomNumber <T> (0, 1);
      positions.push_back({new_value, {row, column}});
    }
  }
  std::random_shuffle(begin(positions), end(positions));
  for (auto elem: positions) {
    int row = elem.second.first;
    int column = elem.second.second;
    T new_val = elem.first;
    matrix.set(row, column, new_val);
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
  checker.isEqual(sparse_matrix, matrix, "assignment");
}

template <typename T>
void Tester::testSum (const Matrix <T>& matrix1, const Matrix <T>& matrix2, Checker <T>& checker) {
  SparseMatrix <T> sparse_matrix1 = setSparseMatrix <T> (matrix1);
  SparseMatrix <T> sparse_matrix2 = setSparseMatrix <T> (matrix2);
  SparseMatrix <T> sparse_sum = sparse_matrix1 + sparse_matrix2;
  Matrix <T> matrix_sum = matrix1 + matrix2;
  checker.isEqual(sparse_sum, matrix_sum, "sum ");
}

template <typename T>
void Tester::testMatrixMultiplication (const Matrix <T>& matrix1, const Matrix <T>& matrix2, Checker <T>& checker) {
  if (matrix1.getNumberColumns() != matrix2.getNumberRows()) return;
  SparseMatrix <T> sparse_matrix1 = setSparseMatrix <T> (matrix1);
  SparseMatrix <T> sparse_matrix2 = setSparseMatrix <T> (matrix2);
  SparseMatrix <T> sparse_multiplication = sparse_matrix1 * sparse_matrix2;
  Matrix <T> matrix_multiplication = matrix1 * matrix2;
  checker.isEqual(sparse_multiplication, matrix_multiplication, "matrix multiplication");
}

template <typename T>
void Tester::testScalarMultiplication (T scalar, const Matrix <T>& matrix, Checker <T>& checker) {
  SparseMatrix <T> sparse_matrix = setSparseMatrix <T> (matrix);
  SparseMatrix <T> sparse_scalar_multiplication = sparse_matrix * scalar;
  Matrix <T> matrix_scalar_multiplication = matrix * scalar;
  checker.isEqual(sparse_scalar_multiplication, matrix_scalar_multiplication, "scalar multiplication");
}

template <typename T>
void Tester::testSubstractionMultiplication (const Matrix <T>& matrix1, const Matrix <T>& matrix2, Checker <T>& checker) {
  SparseMatrix <T> sparse_matrix1 = setSparseMatrix <T> (matrix1);
  SparseMatrix <T> sparse_matrix2 = setSparseMatrix <T> (matrix2);
  SparseMatrix <T> sparse_sum = sparse_matrix1 - sparse_matrix2;
  Matrix <T> matrix_sum = matrix1 - matrix2;
  checker.isEqual(sparse_sum, matrix_sum, "substraction");
}

template <typename T>
void Tester::testTranspose (const Matrix <T>& matrix, Checker <T>& checker) {
  SparseMatrix <T> sparse_matrix = setSparseMatrix <T> (matrix);
  SparseMatrix <T> sparse_transpose = sparse_matrix.transpose();
  Matrix <T> matrix_transpose = matrix.transpose();
  checker.isEqual(sparse_transpose, matrix_transpose, "transpose");
}

template <typename T>
void Tester::testDelete (const Matrix <T>& matrix, Checker <T>& checker) {
  SparseMatrix <T> sparse_delete = setSparseMatrix <T> (matrix);
  Matrix <T> matrix_delete = matrix;
  int number_elements = matrix.getNumberRows() * matrix.getNumberColumns();
  int iterations = number_elements / 2;
  while (iterations--) {
    int pos = Mocker::generateRandomNumber <T> (0, number_elements - 1);
    int row = pos / matrix.getNumberColumns();
    int column = pos % matrix.getNumberColumns();
    sparse_delete.set(row, column, 0);
    matrix_delete.set(row, column, 0);
  }
  checker.isEqual(sparse_delete, matrix_delete, "deletion");
}

