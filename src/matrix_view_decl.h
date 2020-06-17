//
// Created by chenh on 6/16/2020.
//

#ifndef COURSEPROJECT_MATRIX_VIEW_DECL_H
#define COURSEPROJECT_MATRIX_VIEW_DECL_H

#include "matrix_.h"
#include "smart_array.h"
#include <vector>

namespace mat {

    template<typename T>
    class MatrixView {
    public:

        MatrixView() = default;

        MatrixView(const Matrix <T> &parent, const std::vector<size_t> &row, const std::vector<std::size_t> &col);

        MatrixView(const Matrix <T> &parent, size_t row_low, size_t row_high, size_t col_low, size_t col_high);

        ~MatrixView() = default;

        T &at(int i, int j) {
            return elem[row[i] * p_d2size + col[j]];
        }

        const T &at(int i, int j) const {
            return elem[row[i] * p_d2size + col[j]];
        }

        size_t get_d1size() { return d1size; }

        size_t get_d2size() { return d2size; }

        Matrix <T> to_matrix();

    private:

        SmartArray<T> elem{};
        size_t d1size{0};
        size_t d2size{0};
        size_t p_d1size{0}; // parent size
        size_t p_d2size{0}; // parent size
        std::vector<size_t> row{};
        std::vector<size_t> col{};
    };

}
#endif //COURSEPROJECT_MATRIX_VIEW_DECL_H
