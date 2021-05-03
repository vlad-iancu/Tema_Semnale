#include <iostream>
#include "MLP.h"
#include "exceptions.h"

int main() {
    try {
        int *neurons = new int[3];
        double *weights = new double[24];
        neurons[0] = 3;
        neurons[1] = 4;
        neurons[2] = 3;
        for (int i = 0; i < 24; i++) weights[i] = 1;
        MLP mlp(3, neurons, MLP::tanh);

        double *input = new double[3] {1,2,3};
        auto result = mlp.predict(input);
        for(int i = 0;i < 3;i++) std::cout << result[i] << " ";

        return 0;
    } catch (InvalidLayersException &e) {
        std::cout << e.what();
        return -1;
    }

}
