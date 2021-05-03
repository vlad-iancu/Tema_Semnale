//
// Created by iancu on 29.04.2021.
//

#ifndef TEMASEMNALE_MATRIX_H
#define TEMASEMNALE_MATRIX_H

#include "activation_function.h"
#include <vector>
class Matrix {
private:
    int x_size;
    int y_size;
    double **a;
public:
    Matrix(int n, int m);
    Matrix();
    Matrix(const double *elements, int n, int m);
    Matrix(const Matrix &mat);
    ~Matrix();

    int get_x_size() const;
    int get_y_size() const;

    Matrix *multiply(Matrix *mat) const;
    void transform(activation_function f);

    double *operator[](int) const;
    Matrix& operator=(const Matrix &mat);

};


#endif //TEMASEMNALE_MATRIX_H
