//
// Created by chenh on 6/16/2020.
//

#ifndef COURSEPROJECT_MATRIX_VIEW_TEMP_H
#define COURSEPROJECT_MATRIX_VIEW_TEMP_H
#include "matrix_temp.h"
#include "matrix_impl.h"
#include "smart_array.h"
#include <vector>

template<typename T>
class MatrixView: public Matrix<T> {
public:
    using Matrix<T>::d1size;
    using Matrix<T>::d2size;
    using Matrix<T>::_valid;
    using Matrix<T>::elem;

    MatrixView(const Matrix<T> &parent, std::vector<size_t> row, std::vector<std::size_t> col);

    MatrixView(const Matrix<T> &parent, size_t row_low, size_t row_high, size_t col_low, size_t col_high);

    ~MatrixView() override = default;

    T &at(int i, int j) override {
        return elem[row[i] * p_d2size + col[j]];
    }

    const T &at(int i, int j) const override {
        return elem[row[i] * p_d2size + col[j]];
    }

private:
    size_t p_d1size{0}; // parent size
    size_t p_d2size{0}; // parent size
    std::vector<size_t> row{};
    std::vector<size_t> col{};
};

#endif //COURSEPROJECT_MATRIX_VIEW_TEMP_H
