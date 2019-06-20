// 0-indexing sparse matrix with fixed number of rows and columns

#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <iostream>
#include <vector>
#include <functional>

#include "node.h"
#include "helper.h"

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

    SparseMatrix (unsigned n_rows, unsigned n_columns,
        std::vector <Node <T>*> row_first_node,
        std::vector <Node <T>*> row_column_node,
        std::vector <unsigned> row_size,
        std::vector <unsigned> column_size):
      n_rows(n_rows), n_columns(n_columns),
      row_first_node(row_first_node), column_first_node(row_column_node),
      row_size(row_size), column_size(column_size) {}

    ~SparseMatrix() {
      for (auto& node: row_first_node) if (node) node -> clear();
      row_first_node.clear();
      column_first_node.clear();
      row_size.clear();
      column_size.clear();
    }

    // It also deletes
    void set (unsigned row, unsigned column, T value) {
      if (not (0 <= row and row < n_rows)) throw "Row index out of scope";
      if (not (0 <= column and column < n_columns)) throw "Column index out of scope";
      Node <T>* new_node = new Node <T> (row, column, value);
      node_to_delete = nullptr;
      setRow(row, column, new_node);
      setColumn(row, column, new_node);
      if (node_to_delete) delete node_to_delete;
    }

    T operator () (unsigned row, unsigned column) const {
      if (not (0 <= row and row < n_rows)) throw "Row index out of scope";
      if (not (0 <= column and column < n_columns)) throw "Column index out of scope";
      // By intuition, this should make the code faster in promedy
      if (row_size[row] <= column_size[column]) return getByRow(row, column);
      return getByColumn(row, column);
    }

    int getNumberRows () const { return n_rows; }

    int getNumberColumns () const { return n_columns; }

    Node <T>* getRowList (unsigned row) const {
      if (not (0 <= row and row < n_rows)) throw "Row index out of range";
      return row_first_node[row];
    }

    Node <T>* getColumnList (unsigned column) const {
      if (not (0 <= column and column < n_columns)) throw "Column index out of range";
      return column_first_node[column];
    }

    // A little heavy implementation but in O(number of 1s in both matrices)
    // Substraction, multiplication and transpose are basically a copy-paste of this
    // function
    SparseMatrix <T> operator + (const SparseMatrix <T>& other) const {
      if (n_rows != other.getNumberRows()) throw "The number of rows doest not match";
      if (n_columns != other.getNumberColumns()) throw "The number of columns doest not match";
      std::vector <Node <T>*> ret_row_first_node(n_rows);
      std::vector <Node <T>*> ret_column_first_node(n_columns);
      std::vector <unsigned> ret_row_size(n_rows);
      std::vector <unsigned> ret_column_size(n_columns);
      std::vector <Node <T>*> ret_column_last_node(n_columns);
      for (int row = 0; row < n_rows; row++) {
        Node <T>* ret_row_last_node = nullptr;
        Node <T>* cur_node_operand1 = row_first_node[row];
        Node <T>* cur_node_operand2 = other.getRowList(row);
        while (cur_node_operand1 and cur_node_operand2) {
          if (cur_node_operand1 -> column == cur_node_operand2 -> column) {
            int new_val = cur_node_operand1 -> value + cur_node_operand2 -> value;
            int column = cur_node_operand1 -> column;
            if (new_val != 0) {
              update(row, column, new_val, ret_row_first_node, ret_column_first_node,
                  ret_row_size, ret_column_size, ret_row_last_node, ret_column_last_node);
            }
            cur_node_operand1 = cur_node_operand1 -> next;
            cur_node_operand2 = cur_node_operand2 -> next;
          } else if (cur_node_operand1 -> column < cur_node_operand2 -> column) {
            int new_val = cur_node_operand1 -> value;
            int column = cur_node_operand1 -> column;
            update(row, column, new_val, ret_row_first_node, ret_column_first_node,
                ret_row_size, ret_column_size, ret_row_last_node, ret_column_last_node);
            cur_node_operand1 = cur_node_operand1 -> next;
          } else if (cur_node_operand2 -> column < cur_node_operand1 -> column) {
            int new_val = cur_node_operand2 -> value;
            int column = cur_node_operand2 -> column;
            update(row, column, new_val, ret_row_first_node, ret_column_first_node,
                ret_row_size, ret_column_size, ret_row_last_node, ret_column_last_node);
            cur_node_operand2 = cur_node_operand2 -> next;
          }
        }
        while (cur_node_operand1) {
          int new_val = cur_node_operand1 -> value;
          int column = cur_node_operand1 -> column;
          update(row, column, new_val, ret_row_first_node, ret_column_first_node,
              ret_row_size, ret_column_size, ret_row_last_node, ret_column_last_node);
          cur_node_operand1 = cur_node_operand1 -> next;
        }
        while (cur_node_operand2) {
          int new_val = cur_node_operand2 -> value;
          int column = cur_node_operand2 -> column;
          update (row, column, new_val, ret_row_first_node, ret_column_first_node,
              ret_row_size, ret_column_size, ret_row_last_node, ret_column_last_node);
          cur_node_operand2 = cur_node_operand2 -> next;
        }
      }
      return SparseMatrix(n_rows, n_columns, ret_row_first_node, ret_column_first_node,
          ret_row_size, ret_column_size);
    }

    SparseMatrix <T> operator * (const SparseMatrix <T>& other) const {
      if (n_columns != other.getNumberRows()) throw "Can not multiply these matrices";
      std::vector <Node <T>*> ret_row_first_node(n_rows);
      std::vector <Node <T>*> ret_column_first_node(n_columns);
      std::vector <unsigned> ret_row_size(n_rows);
      std::vector <unsigned> ret_column_size(n_columns);
      std::vector <Node <T>*> ret_column_last_node(n_columns);
      for (int row = 0; row < n_rows; row++) {
        Node <T>* ret_row_last_node = nullptr;
        for (int column = 0; column < n_columns; column++) {
          Node <T>* cur_node_operand1 = row_first_node[row];
          Node <T>* cur_node_operand2 = other.getColumnList(column);
          T new_val = dotProduct(cur_node_operand1, cur_node_operand2);
          update (row, column, new_val, ret_row_first_node, ret_column_first_node,
              ret_row_size, ret_column_size, ret_row_last_node, ret_column_last_node);
        }
      }
      return SparseMatrix(n_rows, n_columns, ret_row_first_node, ret_column_first_node,
          ret_row_size, ret_column_size);
    }

    SparseMatrix <T> operator * (T scalar) const {
      std::vector <Node <T>*> ret_row_first_node(n_rows);
      std::vector <Node <T>*> ret_column_first_node(n_columns);
      std::vector <unsigned> ret_row_size(n_rows);
      std::vector <unsigned> ret_column_size(n_columns);
      std::vector <Node <T>*> ret_column_last_node(n_columns);
      for (int row = 0; row < n_rows; row++) {
        Node <T>* ret_row_last_node = nullptr;
        Node <T>* cur_node_operand1 = row_first_node[row];
        while (cur_node_operand1) {
          int column = cur_node_operand1 -> column;
          T new_val = scalar * cur_node_operand1 -> value;
          update (row, column, new_val, ret_row_first_node, ret_column_first_node,
              ret_row_size, ret_column_size, ret_row_last_node, ret_column_last_node);
          cur_node_operand1 = cur_node_operand1 -> next;
        }
      }
      return SparseMatrix(n_rows, n_columns, ret_row_first_node, ret_column_first_node,
          ret_row_size, ret_column_size);
    }

    SparseMatrix <T> operator - (const SparseMatrix <T>& other) const {
      return (*this) + (other * -1);
    }
    
    SparseMatrix <T> transpose () const {
      std::vector <Node <T>*> ret_row_first_node(n_columns);
      std::vector <Node <T>*> ret_column_first_node(n_rows);
      std::vector <unsigned> ret_row_size(n_columns);
      std::vector <unsigned> ret_column_size(n_rows);
      std::vector <Node <T>*> ret_column_last_node(n_rows);
      SparseMatrix ret(n_columns, n_rows);
      for (int column = 0; column < n_columns; column++) {
        Node <T>* ret_row_last_node = nullptr;
        Node <T>* cur_node_operand1 = column_first_node[column];
        while (cur_node_operand1) {
          int row = cur_node_operand1 -> row;
          T new_val = cur_node_operand1 -> value;
          update (column, row, new_val, ret_row_first_node, ret_column_first_node,
              ret_row_size, ret_column_size, ret_row_last_node, ret_column_last_node);
          cur_node_operand1 = cur_node_operand1 -> down;
        }
      }
      return SparseMatrix(n_rows, n_columns, ret_row_first_node, ret_column_first_node,
          ret_row_size, ret_column_size);
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
    Node <T>* node_to_delete;

    void setRow (int row, int column, Node <T>*& node) {
      Node <T>* prev = nullptr;
      Node <T>* cur = row_first_node[row];
      if (not cur) {
        if (node -> value == 0) return;
        row_first_node[row] = node;
        row_size[row]++;
        return;
      }
      while (cur) {
        if (cur -> column == column) {
          if (node -> value == 0) {
            node_to_delete = cur;
            if (not prev) {
              row_first_node[row] = cur -> next;
            } else {
              Node <T>* tmp = cur;
              prev -> next = cur -> next;
            }
            row_size[row]--;
          } else { 
            cur -> value = node -> value;
          }
          return;
        }
        if (not (cur -> column <= column)) {
          if (node -> value == 0) return;
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
      if (node -> value != 0) {
        prev -> next = node;
        row_size[row]++;
      }
    }

    void setColumn (int row, int column, Node <T>*& node) {
      Node <T>* prev = nullptr;
      Node <T>* cur = column_first_node[column];
      if (not cur) {
        if (node -> value == 0) return;
        column_first_node[column] = node;
        column_size[column]++;
        return;
      }
      while (cur) {
        if (cur -> row == row) {
          if (node -> value == 0) {
            if (not prev) {
              column_first_node[column] = cur -> down;
            } else {
              Node <T>* tmp = cur;
              prev -> down = cur -> down;
            }
            column_size[column]--;
          } else { 
            cur -> value = node -> value;
          }
          return;
        }
        if (not (cur -> row <= row)) {
          if (node -> value == 0) return;
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
      if (node -> value != 0) {
        prev -> down = node;
        column_size[column]++;
      }
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
