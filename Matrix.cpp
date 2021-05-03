//
// Created by iancu on 29.04.2021.
//

#include "Matrix.h"
#include "exceptions.h"

Matrix::Matrix() : Matrix(0, 0) {}

Matrix::Matrix(int n, int m) {
    x_size = n;
    y_size = m;
    a = new double *[x_size];
    for (int i = 0; i < x_size; i++) a[i] = new double[y_size];
}

Matrix::Matrix(const double *elements, int n, int m) : Matrix(n, m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            a[i][j] = elements[i * m + j];
}


Matrix::Matrix(const Matrix &mat) : Matrix(mat.x_size, mat.y_size) {
    for (int i = 0; i < x_size; i++)
        for (int j = 0; j < y_size; j++)
            a[i][j] = mat[i][j];
}

Matrix::~Matrix() {
    for (int i = 0; i < x_size; i++)
        delete a[i];
    delete[] a;
}

Matrix *Matrix::multiply(Matrix *matrix) const {
    Matrix mat = *matrix;
    if (y_size != mat.x_size) throw MatrixMultiplicationException(x_size, y_size, mat.x_size, mat.y_size);
    int n = x_size;
    int m = mat.y_size;
    auto result = new Matrix(n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            (*result)[i][j] = 0;
            for (int k = 0; k < y_size; k++)
                (*result)[i][j] += a[i][k] * mat[k][j];
        }
    return result;
}

void Matrix::transform(activation_function f) {
    for (int i = 0; i < x_size; i++)
        for (int j = 0; j < y_size; j++)
            a[i][j] = f(a[i][j]);
}

int Matrix::get_x_size() const { return x_size; }

int Matrix::get_y_size() const { return y_size; }

Matrix &Matrix::operator=(const Matrix &mat) {
    if (&mat == this) return *this;
    for (int i = 0; i < x_size; i++) delete a[i];
    delete a;
    x_size = mat.x_size;
    y_size = mat.y_size;
    a = new double *[x_size];
    for (int i = 0; i < x_size; i++) {
        a[i] = new double[y_size];
        std::copy(mat[i], mat[i] + y_size * sizeof(double), a[i]);
    }
    return *this;
}

double *Matrix::operator[](const int i) const {
    return a[i];
}
