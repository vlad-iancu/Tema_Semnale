#include "exceptions.h"

//
// Created by iancu on 29.04.2021.
//
#include <string>
#include <sstream>

MatrixMultiplicationException::MatrixMultiplicationException(int N1, int M1, int N2, int M2) {
    n1 = N1; m1 = M1; n2 = N2; m2 = M2;
}
std::string MatrixMultiplicationException::what() {
    std::stringstream err;
    err << "Cannot multiply matrices of sizes (" << n1 << "," << m1 << ") and (" << n2 << "," << m2 << ")";
    return err.str();
}


std::string InvalidLayersException::what() {
    std::stringstream err;
    err << "The layers of a MLP must have a strictly-positive integer number of neurons and must be at least two of them";
    return err.str();
}