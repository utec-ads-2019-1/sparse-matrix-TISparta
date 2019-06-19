// 0-indexing sparse matrix with fixed number of rows and columns

#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <iostream>
#include <vector>

#include "node.h"

template <typename T>
class SparseMatrix {
  public:
    SparseMatrix (unsigned n_rows, unsigned n_columns):
      n_rows(n_rows), n_columns(n_columns) {
        row_first_node.resize(n_rows, nullptr);
        row_size.resize(n_rows, 0);
        column_first_node.resize(n_columns, nullptr);
        column_size.resize(n_columns, 0);
      }

    ~SparseMatrix() {
      for (auto& node: row_first_node) if (node) node -> clear();
      row_first_node.clear();
      column_first_node.clear();
      row_size.clear();
      column_size.clear();
    }

    void set (unsigned row, unsigned column, T value) {
      if (not (0 <= row and row < n_rows)) throw "Row index out of scope";
      if (not (0 <= column and column < n_columns)) throw "Column index out of scope";
      if (value == 0) return;
      Node <T>* new_node = new Node <T> (row, column, value);
      setRow(row, column, new_node);
      setColumn(row, column, new_node);
    }

    T operator () (unsigned row, unsigned column) const {
      if (not (0 <= row and row < n_rows)) throw "Row index out of scope";
      if (not (0 <= column and column < n_columns)) throw "Column index out of scope";
      if (row_size[row] <= column_size[column]) return getByRow(row, column);
      return getByColumn(row, column);
    }

    SparseMatrix <T> operator * (T scalar) const {
    }
    SparseMatrix <T> operator * (const SparseMatrix <T>& other) const {
    }
    SparseMatrix <T> operator + (const SparseMatrix <T>& other) const {
    }
    SparseMatrix <T> operator - (const SparseMatrix <T>& other) const {
    }
    SparseMatrix <T> transpose () const {
    }
    void print () const {
      for (int row = 0; row < n_rows; row++) {
        for (int column = 0; column < n_columns; column++) {
          std::cout << (*this)(row, column) << " \n"[column + 1 == n_columns];
        }
      }
    }

  private:
    unsigned n_rows, n_columns;
    std::vector <Node <T>*> row_first_node;
    std::vector <unsigned> row_size;
    std::vector <Node <T>*> column_first_node;
    std::vector <unsigned> column_size;

    void setRow (int row, int column, Node <T>*& node) {
      Node <T>* prev = nullptr;
      Node <T>* cur = row_first_node[row];
      if (not cur) {
        row_first_node[row] = node;
        row_size[row]++;
        return;
      }
      while (cur) {
        if (cur -> column == column) {
          cur -> value = node -> value;
          return;
        }
        if (not (cur -> column <= column)) {
          if (not prev) {
            row_first_node[row] = node;
          } else {
            prev -> next = node;
          }
          node -> next = cur;
          row_size[row]++;
          return;
        }
        prev = cur;
        cur = cur -> next;
      }
      prev -> next = node;
      row_size[row]++;
    }

    void setColumn (int row, int column, Node <T>*& node) {
      Node <T>* prev = nullptr;
      Node <T>* cur = column_first_node[column];
      if (not cur) {
        column_first_node[column] = node;
        column_size[column]++;
        return;
      }
      while (cur) {
        if (cur -> row == row) {
          cur -> value = node -> value;
          return;
        }
        if (not (cur -> row <= row)) {
          if (not prev) {
            column_first_node[column] = node;
          }
          else {
            prev -> down = node;
          }
          node -> down = cur;
          column_size[column]++;
          return;
        }
        prev = cur;
        cur = cur -> down;
      }
      prev -> down = node;
      column_size[column]++;
    }

    T getByRow (int row, int column) const {
      Node <T>* pib = row_first_node[row];
      while (pib) {
        if (pib -> column == column) return pib -> value;
        if (column <= pib -> column) break;
        pib = pib -> next;
      }
      return 0;
    }

    T getByColumn (int row, int column) const {
      Node <T>* pib = column_first_node[column];
      while (pib) {
        if (pib -> row == row) return pib -> value;
        if (row <= pib -> row) break;
        pib = pib -> down;
      }
      return 0;
    }

};

#endif
