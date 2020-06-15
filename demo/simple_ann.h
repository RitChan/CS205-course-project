//
// Created by chenh on 6/16/2020.
//

#ifndef COURSEPROJECT_SIMPLE_ANN_H
#define COURSEPROJECT_SIMPLE_ANN_H

#include <vector>
#include "matrix.h"

std::vector<int> activate(std::vector<int> input);
int operator*(const std::vector<int> &left, const std::vector<int> &right);
std::vector<int> operator+(const std::vector<int> &left, const std::vector<int> &right);

#endif //COURSEPROJECT_SIMPLE_ANN_H
