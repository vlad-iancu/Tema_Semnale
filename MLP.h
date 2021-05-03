//
// Created by iancu on 29.04.2021.
//

#ifndef TEMASEMNALE_MLP_H
#define TEMASEMNALE_MLP_H

#include "activation_function.h"
#include "Matrix.h"

class MLP {
private:
    int *neurons;
    double *weights;
    int layers;
    activation_function activation;
    Matrix **matrices;
public:
    static double sigmoid(const double x);
    static double relu(const double x);
    static double tanh(const double x);

    MLP(int layers, int *neurons);

    MLP(int layers, int *neurons, double* weights);

    MLP(int layers, int *neurons, activation_function activation);

    MLP(int layers, int *neurons, double *weights, activation_function _activation);

    ~MLP();

    double *predict(double *input);

    int input_size() const;

    int output_size() const;

    const int *get_neurons() const;

    const double *get_weights() const;
};


#endif //TEMASEMNALE_MLP_H
