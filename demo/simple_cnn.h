//
// Created by chenh on 6/16/2020.
//

#ifndef COURSEPROJECT_SIMPLE_CNN_H
#define COURSEPROJECT_SIMPLE_CNN_H
#include "matrix.h"
#include <vector>

std::vector<double> activate(const std::vector<double> &input);
Matrix<double> activate(const Matrix<double> &input);
std::vector<Matrix<double>> cnn_scan(const Matrix<double> &input);
void print_matrix(const Matrix<double> &matrix);

#endif //COURSEPROJECT_SIMPLE_CNN_H
