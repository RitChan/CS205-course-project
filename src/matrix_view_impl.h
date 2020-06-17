//
// Created by chenh on 6/16/2020.
//

#ifndef COURSEPROJECT_MATRIX_VIEW_IMPL_H
#define COURSEPROJECT_MATRIX_VIEW_IMPL_H

#include "matrix_view_decl.h"
#include "smart_array.h"
#include "exception.h"
#include <cstdlib>

namespace mat {

    template<typename T>
    MatrixView<T>::MatrixView(const Matrix<T> &parent, const std::vector<size_t> &row,
                              const std::vector<std::size_t> &col)
            :row(row), col(col) {
        d1size = row.size();
        d2size = col.size();
        p_d1size = parent.get_d1size();
        p_d2size = parent.get_d2size();
        elem = parent.shallow_copied_data();
        // TODO check boundary
    }

    template<typename T>
    MatrixView<T>::MatrixView(const Matrix<T> &parent, size_t row_low, size_t row_high, size_t col_low,
                              size_t col_high) {
        if (row_high > parent.get_d1size() || col_high > parent.get_d2size()) {
            char msg[256];
            sprintf(msg, "MatrixView<T>::MatrixView: Index out of range: "
                         "For row_high max = <%d>, given = <%d> "
                         "For col_high max = <%d>, given = <%d>",
                    parent.get_d1size(), row_high, parent.get_d2size(), col_high);
            throw Exception(msg);
        } else if (row_high <= row_low || col_high <= col_low) {
            throw std::exception();
        }
        row = std::vector<size_t>(row_high - row_low);
        col = std::vector<size_t>(col_high - col_low);
        for (size_t i = 0; i < row.size(); i++) {
            row[i] = i + row_low;
        }
        for (size_t i = 0; i < col.size(); i++) {
            col[i] = i + col_low;
        }
        d1size = row_high - row_low;
        d2size = col_high - col_low;
        p_d1size = parent.get_d1size();
        p_d2size = parent.get_d2size();
        elem = parent.shallow_copied_data();
    }

    template<typename T>
    Matrix<T> MatrixView<T>::to_matrix() {
        Matrix<T> ret(d1size, d2size);
        for (int i = 0; i < d1size; ++i) {
            for (int j = 0; j < d2size; ++j) {
                ret.at(i, j) = at(i, j);
            }
        }
        return ret;
    }

}
#endif //COURSEPROJECT_MATRIX_VIEW_IMPL_H
