#include <iostream>
#include <complex>
#include "matrix_.h"
using namespace mat;

int main() {
    Matrix<int> matrix{
            {1, 2, 3, 4}
    };

    Matrix<int> matrix1{
            {1},
            {2},
            {3},
            {4}
    };

    auto m = matrix.dot(matrix1);

    std::cout << m << std::endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
