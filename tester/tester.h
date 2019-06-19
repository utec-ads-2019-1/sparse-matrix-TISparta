#ifndef TESTER_H
#define TESTER_H

const int NUMBER_OF_TESTS = 1;

#include "../checker/checker.h"
#include "../matrix/matrix.h"
#include "../sparse-matrix/sparse-matrix.h"

class Tester {
  public:
    static void execute ();
  private:
    template <typename T>
    static Matrix <T> createRandomMatrix (int rows, int columns);

    template <typename T>
    static SparseMatrix <T> setSparseMatrix (const Matrix <T>& matrix);

    template <typename T>
    static void testAssignment (const Matrix <T>& matrix, Checker <T>& checker);

    template <typename T>
    static void testSum (const Matrix <T>& matrix1, const Matrix <T>& matrix2, Checker <T>& checker);

    template <typename T>
    static void testMatrixMultiplication (const Matrix <T>& matrix1, const Matrix <T>& matrix2, Checker <T>& checker);

    template <typename T>
    static void testScalarMultiplication (T scalar, const Matrix <T>& matrix, Checker <T>& checker);

    template <typename T>
    static void testSubstractionMultiplication (const Matrix <T>& matrix1, const Matrix <T>& matrix2, Checker <T>& checker);
   
    template <typename T>
    static void testTranspose (const Matrix <T>& matrix, Checker <T>& checker);

};

#endif
