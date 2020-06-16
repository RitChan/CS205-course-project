//
// Created by chenh on 6/16/2020.
//

#include "simple_cnn.h"
#include "matrix_view.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <_utility.h>

using namespace std;

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

    Matrix<double> input1{
            {0, 1, 1, 1, 1, 0},
            {0, 1, 0, 0, 1, 0},
            {0, 0, 0, 0, 1, 0},
            {0, 0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 0},
            {0, 1, 1, 1, 1, 0}
    };

    Matrix<double> input2{
            {0, 0, 1, 1, 1, 0},
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
            {-0.317, 0.151},
            {-3.223, 1.323}
    };

    static Matrix<double> O0_P1{
            {-25.887, -0.494},
            {0.402,   -1.571}
    };

    static Matrix<double> O0_P2{
            {-3.661, 1.908},
            {0.009,  -0.159}
    };

    static Matrix<double> O1_P0{
            {0.010,   -0.642},
            {-11.069, 9.001}
    };

    static Matrix<double> O1_P1{
            {12.096, 0.003},
            {-0.352, 10.159}
    };

    static Matrix<double> O1_P2{
            {0.430, 1.672},
            {2.060, -0.093}
    };

    static Matrix<double> O2_P0{
            {2.775,  -0.233},
            {43.616, 0.045}
    };

    static Matrix<double> O2_P1{
            {0.755,  0.213},
            {-0.138, -8.731}
    };

    static Matrix<double> O2_P2{
            {-1.086, -0.851},
            {-0.167, -3.019}
    };

    static vector<double> bias{14.764, -21.116, -9.164};

    vector<Matrix<double>> F = cnn_scan(input); // filtering
    vector<Matrix<double>> P(F.size());

    // pooling
    int k = 0;
    for (auto &matrix: P) {
        matrix = Matrix<double>(2, 2);
        for (int i = 0; i < matrix.get_d1size(); i++) {
            for (int j = 0; j < matrix.get_d2size(); ++j) {
                MatrixView<double> view(F[k], i * 2, i * 2 + 2, j * 2, j * 2 + 2);
                matrix.at(i, j) = view.to_matrix().max(); // max pooling
            }
        }
        k++;
    }

    vector<double> a(3, 0);

    auto z00 = P[0].hadamard(O0_P0);
    auto z01 = P[0].hadamard(O0_P1);
    auto z02 = P[0].hadamard(O0_P2);
    a[0] = z00.sum() + z01.sum() + z02.sum() + bias[0];

    auto z10 = P[1].hadamard(O1_P0);
    auto z11 = P[1].hadamard(O1_P1);
    auto z12 = P[1].hadamard(O1_P2);
    a[1] = z10.sum() + z11.sum() + z12.sum() + bias[1];

    auto z20 = P[2].hadamard(O2_P0);
    auto z21 = P[2].hadamard(O2_P1);
    auto z22 = P[2].hadamard(O2_P2);
    a[2] = z20.sum() + z21.sum() + z22.sum() + bias[2];

    a = activate(a);

    cout << endl << "[Output]" << endl;
    for (int i = 0; i < a.size(); ++i) {
        cout << "Confidence of " << i + 1 << " = " << a[i] << endl;
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
            {1.161, -0.848,  1.356},
            {5.825,  -14.571, -6.945},
            {4.389,  8.317,   1.214}
    };

    static Matrix<double> scanner1{
            {1.950,  14.210, 5.029},
            {4.344,  -1.471, -12.478},
            {-1.346, -5.859, -2.408}
    };

    static Matrix<double> scanner2{
            {-0.785, 4.159,  -0.542},
            {0.468,  -8.465, -4.508},
            {0.183,  -2.567, 0.231}
    };

    vector<double> bias{-14.706, -13.572, -4.879};

    vector<Matrix<double>> ret(3);

    ret[0] = activate(scan(scanner0, input) + bias[0]);
    ret[1] = activate(scan(scanner1, input) + bias[1]);
    ret[2] = activate(scan(scanner2, input) + bias[2]);

    return ret;
}