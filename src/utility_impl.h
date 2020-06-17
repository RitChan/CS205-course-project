//
// Created by chenh on 6/17/2020.
//

#ifndef COURSEPROJECT_UTILITY_IMPL_H
#define COURSEPROJECT_UTILITY_IMPL_H

#include "utility_decl.h"
#include "matrix_view.h"

namespace mat {

    template<typename T>
    Matrix<T> scan(const Matrix<T> &scanner, const Matrix<T> &target) {
        if (scanner.get_d1size() > target.get_d1size() || scanner.get_d2size() > target.get_d2size())
            return Matrix<T>();

        size_t n_row = target.get_d1size() - scanner.get_d1size() + 1;
        size_t n_col = target.get_d2size() - scanner.get_d2size() + 1;
        Matrix<T> ret(n_row, n_col);

        for (int i = 0; i < n_row; i++) {
            for (int j = 0; j < n_col; j++) {
                MatrixView<T> view = MatrixView<T>(target, i, i + scanner.get_d1size(), j, j + scanner.get_d2size());
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

}

#endif //COURSEPROJECT_UTILITY_IMPL_H
