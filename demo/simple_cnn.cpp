//
// Created by chenh on 6/16/2020.
//

#include "simple_cnn.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <utility_.h>
#include <cstdio>
#include <float.h>

using namespace std;
using namespace mat;

static void run_network(const Matrix<double> &input);

int main() {
    // 3
    Matrix<double> input0{
            {0, 1, 1, 1, 1, 0},
            {0, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 0, 0},
            {0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 1, 0},
            {0, 1, 1, 1, 0, 0}
    };

    // 2
    Matrix<double> input1{
            {0, 1, 1, 1, 1, 0},
            {0, 1, 0, 0, 1, 0},
            {0, 0, 0, 0, 1, 0},
            {0, 0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 0},
            {0, 1, 1, 1, 1, 0}
    };

    // 1
    Matrix<double> input2{
            {0, 0, 1, 1, 0, 0},
            {0, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0, 0},
            {0, 0, 1, 1, 1, 0}
    };

    run_network(input0);
    run_network(input1);
    run_network(input2);
}

static void run_network(const Matrix<double> &input) {
    static Matrix<double> O0_P0{
            {-0.53, 0.73},
            {-1.78, 0.55}
    };

    static Matrix<double> O0_P1{
            {-4.96, 0.17},
            {0.54, -0.93}
    };

    static Matrix<double> O0_P2{
            {-2.00, -1.78},
            {-0.89, 0.04}
    };

    static Matrix<double> O1_P0{
            {-0.69, -0.47},
            {-3.15, 2.82}
    };

    static Matrix<double> O1_P1{
            {2.77, -0.73},
            {-0.58, 2.42}
    };

    static Matrix<double> O1_P2{
            {0.77, 1.49},
            {2.19, -0.20}
    };

    static Matrix<double> O2_P0{
            {-0.22,  -0.41},
            {5.30, -1.58}
    };

    static Matrix<double> O2_P1{
            {1.48,  0.20},
            {-1.76, -2.69}
    };

    static Matrix<double> O2_P2{
            {1.15, -0.75},
            {-0.36, -1.48}
    };

    static vector<double> bias{3.15, -4.27, -2.25};

    vector<Matrix<double>> F = cnn_scan(input); // filtering
    vector<Matrix<double>> P(F.size());

    // pooling
    int k = 0;
    for (auto &matrix: P) {
        matrix = Matrix<double>(2, 2);
        for (int i = 0; i < matrix.get_d1size(); i++) {
            for (int j = 0; j < matrix.get_d2size(); ++j) {
                MatrixView<double> view(F[k], i * 2, i * 2 + 2, j * 2, j * 2 + 2);
                matrix.at(i, j) = DBL_MIN;
                // max pooling
                for (int s = 0; s < view.get_d1size(); s++) {
                    for (int t = 0; t < view.get_d2size(); t++) {
                        if (matrix.at(i, j) < view.at(s, t))
                            matrix.at(i, j) = view.at(s, t);
                    }
                }
            }
        }
        k++;
    }

    // output layer
    vector<double> a(3, 0);

    auto z00 = P[0].hadamard(O0_P0);
    auto z01 = P[1].hadamard(O0_P1);
    auto z02 = P[2].hadamard(O0_P2);
    a[0] = z00.sum() + z01.sum() + z02.sum() + bias[0];

    auto z10 = P[0].hadamard(O1_P0);
    auto z11 = P[1].hadamard(O1_P1);
    auto z12 = P[2].hadamard(O1_P2);
    a[1] = z10.sum() + z11.sum() + z12.sum() + bias[1];

    auto z20 = P[0].hadamard(O2_P0);
    auto z21 = P[1].hadamard(O2_P1);
    auto z22 = P[2].hadamard(O2_P2);
    a[2] = z20.sum() + z21.sum() + z22.sum() + bias[2];

    a = activate(a);

    cout << endl << "[Input]" << endl;
    print_01_matrix(input);

    cout << endl << "[Output]" << endl;
    for (int i = 0; i < a.size(); ++i) {
        printf("Probability of %d = %.2f\n", i + 1, a[i]);
    }
}

std::vector<double> activate(const std::vector<double> &input) {
    vector<double> ret(input.size());

    int i = 0;
    for (double &d: ret) {
        d = 1 / (1 + exp(-input[i++]));
    }

    return ret;
}

Matrix<double> activate(const Matrix<double> &input) {
    Matrix<double> ret(input.get_d1size(), input.get_d2size());

    for (int i = 0; i < ret.get_d1size(); i++) {
        for (int j = 0; j < ret.get_d2size(); j++) {
            ret.at(i, j) = 1 / (1 + exp(-input.at(i, j)));
        }
    }

    return ret;
}

std::vector<Matrix<double>> cnn_scan(const Matrix<double> &input) {
    // scanners
    static Matrix<double> scanner0{
            {-0.65, -0.78,  0.35},
            {2.40,  -3.78, -2.74},
            {0.73,  1.98,   1.33}
    };

    static Matrix<double> scanner1{
            {-0.70,  3.92, 1.98},
            {2.96,  -1.39, -2.97},
            {-0.98, -2.72, -1.17}
    };

    static Matrix<double> scanner2{
            {-1.82, 2.64,  -1.29},
            {-1.72, -2.37, -3.01},
            {-0.03, -1.69, 0.35}
    };

    vector<double> bias{-3.46, -3.64, -2.53};

    vector<Matrix<double>> ret(3);

    ret[0] = activate(scan(scanner0, input) + bias[0]);
    ret[1] = activate(scan(scanner1, input) + bias[1]);
    ret[2] = activate(scan(scanner2, input) + bias[2]);

    return ret;
}

void print_01_matrix(const Matrix<double> &matrix) {
    for (int i= 0; i < matrix.get_d1size(); i++) {
        for (int j = 0; j < matrix.get_d2size(); j++) {
            if (matrix.at(i, j) == 0)
                printf(". ");
            else
                printf("%g ", matrix.at(i, j));
        }
        printf("\n");
    }
}