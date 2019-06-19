#ifndef CHECKER_H
#define CHECKER_H

#include <iostream>
#include <string>

#include "color.h"
#include "../sparse-matrix/sparse-matrix.h"
#include "../matrix/matrix.h"

template <typename T>
class Checker {
  public:
    Checker () {}
    void isEqual (const SparseMatrix <T>& sparse_matrix, const Matrix <T>& matrix, std::string message) {
      int n_rows = matrix.getNumberRows();
      int n_columns = matrix.getNumberColumns();
      for (int row = 0; row < n_rows; row++) {
        for (int column = 0; column < n_columns; column++) {
          if (sparse_matrix(row, column) != matrix(row, column)) {
            number_incorrect_tests++;
            std::cout << Color::bold << Color::red << "Test failed - " << message << std::endl << Color::normal;
            return;
          }
        }
      }
      number_correct_tests++;
      std::cout << Color::bold << Color::green << "Test passed - " << message << std::endl << Color::normal;
    }

  private:
    int number_correct_tests = 0;
    int number_incorrect_tests = 0;
};

#endif
