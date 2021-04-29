//
// Created by iancu on 29.04.2021.
//

#ifndef TEMASEMNALE_EXCEPTIONS_H
#define TEMASEMNALE_EXCEPTIONS_H

#include <exception>
#include <string>
class MatrixMultiplicationException : std::exception {
private:
    int n1, m1, n2, m2;
public :
    MatrixMultiplicationException(int N1, int M1, int N2, int M2);
    virtual std::string what();
};

class InvalidLayersException : std::exception {
public:
    virtual std::string what();
};

#endif //TEMASEMNALE_EXCEPTIONS_H
