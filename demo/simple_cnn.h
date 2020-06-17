//
// Created by chenh on 6/16/2020.
//

#ifndef COURSEPROJECT_SIMPLE_CNN_H
#define COURSEPROJECT_SIMPLE_CNN_H
#include "matrix.h"
#include <vector>

std::vector<double> activate(const std::vector<double> &input);
mat::Matrix<double> activate(const mat::Matrix<double> &input);
std::vector<mat::Matrix<double>> cnn_scan(const mat::Matrix<double> &input);
void print_01_matrix(const mat::Matrix<double> &matrix);

#endif //COURSEPROJECT_SIMPLE_CNN_H
