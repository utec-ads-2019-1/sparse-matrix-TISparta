#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    Node <T>* next = 0;
    Node <T>* down = 0;

public:
    explicit Node();

    friend class Matrix <T>;
};

#endif //SPARSE_MATRIX_NODE_H
