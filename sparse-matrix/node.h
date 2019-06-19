#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

#include <iostream>

template <typename T>
class Matrix;

template <typename T>
class Node {
  public:
    unsigned row;
    unsigned column;
    T value;
    Node <T>* next = 0;
    Node <T>* down = 0;
  public:
    explicit Node();
    Node (unsigned row, unsigned column, T value):
      row(row), column(column), value(value) {}
    void clear () {
      if (next) next -> clear();
      delete this;
    }
    void print () {
      std::cout << "Row " << row << ", Column " << column << ", Value " << value << std::endl;
    }
    friend class Matrix <T>;
};

#endif //SPARSE_MATRIX_NODE_H
