#pragma once

#include <vector>

#include "node.h"

template <typename T>
static void update (int row, int column, int new_val,
    std::vector <Node <T>*>& ret_row_first_node,
    std::vector <Node <T>*>& ret_column_first_node,
    std::vector <unsigned>& ret_row_size,
    std::vector <unsigned>& ret_column_size,
    Node <T>*& ret_row_last_node,
    std::vector <Node <T>*>& ret_column_last_node) {
  Node <T>* new_node = new Node <T> (row, column, new_val);
  if (ret_row_size[row] == 0) {
    ret_row_first_node[row] = new_node;
    ret_row_last_node = new_node;
  } else {
    ret_row_last_node -> next = new_node;
    ret_row_last_node = ret_row_last_node -> next;
  }
  if (ret_column_size[column] == 0) {
    ret_column_first_node[column] = new_node;
    ret_column_last_node[column] = new_node;
  } else {
    ret_column_last_node[column] -> down = new_node;
    ret_column_last_node[column] = ret_column_last_node[column] -> down;
  }
  ret_row_size[row]++;
  ret_column_size[column]++;
}
