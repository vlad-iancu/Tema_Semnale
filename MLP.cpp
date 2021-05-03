//
// Created by iancu on 29.04.2021.
//

#include "MLP.h"
#include "exceptions.h"
#include <random>

double *random_weights(int layers, const int *neurons);

MLP::MLP(int layers, int *neurons) : MLP(layers, neurons, nullptr, relu) {}

MLP::MLP(int layers, int *neurons, double *weights) : MLP(layers, neurons, weights, relu) {}

MLP::MLP(int layers, int *neurons, activation_function activation) : MLP(layers, neurons, nullptr, activation) {}

/**
 * In order to construct a Multi-Layered Perceptron, we need to specify:
 * @param _layers is the total number of layers (including the input and the output ones)
 * @param _neurons must be an array of strictly-positive integers (otherwise an exception will be thrown)
 * @param _weights is the array of weights between neurons of adjacent layers, if nullptr is passed then a list of
 * random weights will be used, these weights are being used to build the matrices of weights used to calculate output
 * @param _activation is the activation function which will be applied to the value in the neurons as
 * the input is propagated forward
 */
MLP::MLP(int _layers, int *_neurons, double *_weights, activation_function _activation) {
    activation = _activation;
    layers = _layers;
    if(layers < 2) throw InvalidLayersException();
    neurons = new int[layers];
    std::copy(_neurons, _neurons + layers, neurons);
    if (_weights != nullptr) {
        int weights_count = 0;
        for (int i = 0; i < layers - 1; i++) {
            if (neurons[i] <= 0) throw InvalidLayersException();
            weights_count += neurons[i] * neurons[i + 1];
        }
        weights = new double[weights_count];
        std::copy(_weights, _weights + weights_count, weights);
    } else
        weights = random_weights(layers, neurons);
    matrices = new Matrix *[layers - 1];
    int k = 0;
    for (int l = 0; l < layers - 1; l++) {
        matrices[l] = new Matrix(weights + k, neurons[l], neurons[l + 1]);
        k += neurons[l] * neurons[l + 1];
    }
}

MLP::~MLP() {
    delete weights;
    for (int i = 0; i < layers - 1; i++) delete matrices[i];
    delete matrices;
}
/**
 * This function calculates the output for a given input by multiplying the current input with the matrix
 * of weights corresponding to the current layer and then applying the activation function to the result
 * @param input
 * @return a dynamically allocated array containing the output for a given input
 */
double *MLP::predict(double *input) {
    auto current = new Matrix(input, 1, input_size());
    for (int i = 0; i < layers - 1; i++) {
        auto result = current->multiply(matrices[i]);
        result->transform(activation);
        delete current;
        current = result;
    }
    auto *result = new double[current->get_y_size()];
    std::copy((*current)[0], (*current)[0] + current->get_y_size(), result);
    delete current;
    return result;
}

const int *MLP::get_neurons() const { return neurons; }

const double *MLP::get_weights() const { return weights; }

int MLP::input_size() const {
    return neurons[0];
}

int MLP::output_size() const {
    return neurons[layers - 1];
}


double MLP::sigmoid(const double x) {
    return x / (1 + std::abs(x));
}

double MLP::relu(const double x) {
    return std::max(0.0, x);
}

double MLP::tanh(const double x) {
    return std::tanh(x);
}
/**
 * This function generates a list of random weights for a given set of layers
 * @param layers
 * @param neurons
 * @return a dynamically allocated list of weights
 */
double *random_weights(int layers, const int *neurons) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    int weight_count = 0;
    for (int i = 0; i < layers - 1; i++) {
        if (neurons[i] <= 0) throw InvalidLayersException();
        weight_count += neurons[i] * neurons[i + 1];
    }
    auto w = new double[weight_count];
    for (int i = 0; i < weight_count; i++) w[i] = dist(mt);
    return w;
}
