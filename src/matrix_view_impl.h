//
// Created by chenh on 6/16/2020.
//

#ifndef COURSEPROJECT_MATRIX_VIEW_IMPL_H
#define COURSEPROJECT_MATRIX_VIEW_IMPL_H

#include "matrix_view_temp.h"
#include "smart_array.h"

template<typename T>
MatrixView<T>::MatrixView(const Matrix<T> &parent, std::vector<size_t> row, std::vector<std::size_t> col)
        :row(row), col(col) {
    d1size = row.size();
    d2size = col.size();
    p_d1size = parent.get_d1size();
    p_d2size = parent.get_d2size();
    elem = parent.shallow_copied_data();
    // TODO check boundary
}

template<typename T>
MatrixView<T>::MatrixView(const Matrix<T> &parent, size_t row_low, size_t row_high, size_t col_low, size_t col_high) {
    if (row_high - row_low > parent.get_d1size() || col_high - col_low > parent.get_d2size()) {
        throw std::exception();
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

#endif //COURSEPROJECT_MATRIX_VIEW_IMPL_H
