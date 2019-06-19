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

    void printResults (int n_test) {
      std::cout << Color::bold << Color::cyan << "Test " << n_test << std::endl << Color::normal;
      std::cout << Color::bold << Color::green << "Tests passed " << number_correct_tests << std::endl << Color::normal;
      std::cout << Color::bold << Color::red << "Tests not passed " << number_incorrect_tests << std::endl << Color::normal;
    }

    int getNumberCorrectTests () { return number_correct_tests; }

    int getNumberIncorrectTests () { return number_incorrect_tests; }

    static void printFinalResults (int n_correct, int n_incorrect) {
      const int W = 20;
      std::string wall(W, '#');
      std::cout << Color::bold << Color::cyan << wall << std::endl << Color::normal;
      std::cout << Color::bold << Color::cyan << "Final stadistics" << std::endl << Color::normal;
      std::cout << Color::bold << Color::green << "Tests passed " << n_correct << std::endl << Color::normal;
      std::cout << Color::bold << Color::red << "Tests not passed " << n_incorrect << std::endl << Color::normal;
      std::cout << Color::bold << Color::cyan << wall << std::endl << Color::normal;
    }

  private:
    int number_correct_tests = 0;
    int number_incorrect_tests = 0;
};

#endif
