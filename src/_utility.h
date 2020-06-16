//
// Created by chenh on 6/16/2020.
//

#ifndef COURSEPROJECT__UTILITY_H
#define COURSEPROJECT__UTILITY_H
#include <vector>
#include "matrix.h"
#include "matrix_view.h"

int operator*(const std::vector<int> &left, const std::vector<int> &right);
std::vector<int> operator+(const std::vector<int> &left, const std::vector<int> &right);

template<typename T>
Matrix<T> scan(const Matrix<T> &scanner, const Matrix<T> &target);
template<typename T>
Matrix<T> scan(const Matrix<T> &scanner, const Matrix<T> &target) {
    if (scanner.get_d1size() > target.get_d1size() || scanner.get_d2size() > target.get_d2size())
        return Matrix<T>();

    size_t n_row = target.get_d1size() - scanner.get_d1size() + 1;
    size_t n_col = target.get_d2size() - scanner.get_d2size() + 1;
    Matrix<T> ret(n_row, n_col);

    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            MatrixView<T> view = MatrixView<T>(target, i, i+scanner.get_d1size(), j, j+scanner.get_d2size());
            Matrix<T> emult(view.get_d1size(), view.get_d2size());
            // element-wise multiplication
            for (int s = 0; s < emult.get_d1size(); s++) {
                for (int t = 0; t < emult.get_d2size(); t++) {
                    emult.at(s, t) = scanner.at(s, t) * view.at(s, t);
                }
            }
            ret.at(i, j) = emult.sum();
        }
    }

    return ret;
}
#endif //COURSEPROJECT__UTILITY_H
