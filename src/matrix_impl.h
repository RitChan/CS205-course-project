//
// Created by chenh on 5/11/2020.
//
#ifndef COURSEPROJECT_MATRIX_IMPL_H
#define COURSEPROJECT_MATRIX_IMPL_H

#include "matrix_temp.h"
#include <iostream>
#include <vector>


template<typename T>
Matrix<T>::Matrix(int d1size, int d2size): d1size(d1size), d2size(d2size),
                                           _valid(true) {
    if (d1size <= 0 || d2size <= 0) {
        _valid = false;
        return;
    }
    elem = SmartArray<T>::make_array(d1size * d2size);
}

template<typename T>
Matrix<T>::Matrix(Matrix::MatrixInitList init_list): d1size(init_list.size()), d2size(0), _valid(true) {
    int i = 0;
    int j = 0;
    for (const std::initializer_list<T> &row: init_list) {
        if (row.size() <= 0 || (d2size > 0 && row.size() != d2size)) {
            _valid = false;
            d1size = 0;
            d2size = 0;
            elem.release();
            break;
        }
        if (d2size != row.size()) {
            d2size = row.size();
            elem = SmartArray<T>::make_array(d1size * d2size);
        }
        j = 0;
        for (T e: row)
            elem[i * d2size + (j++)] = e;
        i++;
    }
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other) {
    d1size = other.d1size;
    d2size = other.d2size;
    elem = SmartArray<T>::make_array(d1size * d2size);
    for (int i = 0; i < d1size * d2size; i++) {
        elem[i] = other.at(i / d2size, i % d2size);
    }
    _valid = other._valid;
    return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> &other) const {
    if (!shape_equal_to(other))
        return false;
    for(size_t i = 0; i < d1size; i++) {
        for (size_t j = 0; j < d2size; j++) {
            if (at(i, j) != other.at(i, j))
                return false;
        }
    }
    return true;
}

template<typename T>
Matrix<T> &Matrix<T>::operator*=(const T &other) {
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            at(i, j) *= other;
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const {
    Matrix<T> ret;
    if (!shape_equal_to(other)) {
        ret._valid = false;
        return ret;
    }
    ret = *this;
    for (int i = 0; i < ret.d1size; i++) {
        for (int j = 0; j < ret.d2size; j++) {
            ret.at(i, j) += other.at(i, j);
        }
    }
    return ret;
}

template<typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &other) {
    static Matrix<T> INVALID;
    if (!shape_equal_to(other))
        return INVALID;
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            at(i, j) += other.at(i, j);
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) const {
    Matrix<int> ret; // default invalid matrix
    if (!shape_equal_to(other)) {
        return ret;
    }
    ret = *this;
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            ret.at(i, j) -= other.at(i, j);
        }
    }
    return ret;
}

template<typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &other) {
    static Matrix<T> INVALID;
    if (!shape_equal_to(other))
        return INVALID;
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            at(i, j) -= other.at(i, j);
        }
    }
    return *this;
}


template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const {
    if (d2size != other.d1size)
        return Matrix<T>();
    int align_len = d2size;
    Matrix<T> ret(d1size, other.d2size);
    for (int i = 0; i < ret.d1size; i++) {
        for (int j = 0; j < ret.d2size; j++) {
            ret.at(i, j) = 0;
            for (int p = 0; p < align_len; p++) {
                ret.at(i, j) += at(i, p) * other.at(p, j);
            }
        }
    }
    return ret;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T &other) const {
    Matrix<T> ret = *this;
    for (int i = 0; i < ret.d1size; i++) {
        for (int j = 0; j < ret.d2size; j++) {
            ret.at(i, j) *= other;
        }
    }
    return ret;
}


template<typename T>
Matrix<T> operator*(const T &c, const Matrix<T> &matrix) {
    Matrix<T> ret = matrix;
    for (int i = 0; i < ret.d1size; i++) {
        for (int j = 0; j < ret.d2size; j++) {
            ret.at(i, j) *= c;
        }
    }
    return ret;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const T &c) const {
    Matrix<T> ret{*this}; // TODO handle zero division
    for (int i = 0; i < ret.d1size; i++) {
        for (int j = 0; j < ret.d2size; j++) {
            ret.at(i, j) /= c;
        }
    }
    return ret;
}

template<typename T>
Matrix<T> &Matrix<T>::operator/=(const T &c) {
    if (c == '\0') {
        throw std::exception();
    }
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            at(i, j) /= c;
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> ret(d2size, d1size);
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            ret.at(j, i) = at(i, j);
        }
    }
    return ret;
}

template<typename T>
T Matrix<T>::max() const {
    T max_T = at(0, 0);
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            max_T = max_T < at(i, j) ? at(i, j) : max_T;
        }
    }
    return max_T;
}

template<typename T>
T Matrix<T>::min() const {
    T min_T = at(0, 0);
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            min_T = min_T > at(i, j) ? at(i, j) : min_T;
        }
    }
    return min_T;
}

template<typename T>
T Matrix<T>::sum() const {
    T sum_T = at(0, 0);
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            sum_T += at(i, j);
        }
    }
    return sum_T - at(0, 0);
}

template<typename T>
T Matrix<T>::avg() const {
    T sum = at(0, 0);
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            sum += at(i, j);
        }
    }
    sum -= at(0, 0);
    return sum / (d1size * d2size);
}

template<typename T>
T Matrix<T>::col_avg() const {
    return '\0';
}

template<typename T>
T Matrix<T>::row_avg() const {
    return '\0';
}

template<typename T>
std::list<EigenPair<T>> Matrix<T>::eigen_decompose() const {
    return std::list<EigenPair<T>>();
}

template<typename T>
T Matrix<T>::trace() const {
    if (d1size != d2size)
        throw std::exception();
    T ret = at(0, 0);
    for (int k = 1; k < d1size; k++) {
        ret += at(k, k);
    }
    return ret;
}

template<typename T>
T Matrix<T>::determinant() const {
    if (d1size != d2size)
        throw std::exception();
    T det;
    Matrix<T> row_reduced = gaussian_eliminated();
    det = row_reduced.at(0, 0);
    for (int k = 1; k < d1size; k++) {
        det *= row_reduced.at(k, k);
    }
    return det;
}

template<typename T>
std::vector<T> Matrix<T>::cross(const Matrix<T> &other) const {
    throw std::exception();
}

template<typename T>
Matrix<T> Matrix<T>::hadamard(const Matrix<T> &other) const {
    if (!_valid || !other.valid() || !shape_equal_to(other))
        return Matrix<T>();
    Matrix<T> ret{*this};
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            ret.at(i, j) = at(i, j) * other.at(i, j);
        }
    }
    return ret;
}

template<typename T>
Matrix<T> Matrix<T>::dot(const Matrix<T> &other) const {
    // TODO need more specifications
    if (!shape_equal_to(other) || d1size != 1)
        return Matrix<T>();
    return other * (*this);
}

template<typename T>
T Matrix<T>::row_max(int row) const {
    T best = at(row, 0);
    for (int i = 1; i < d2size; i++) {
        if (at(row, i) > best) {
            best = at(row, i);
        }
    }
    return best;
}

template<typename T>
T Matrix<T>::col_max(int col) const {
    T best = at(0, col);
    for (int i = 1; i < d1size; i++) {
        if (at(i, col) > best) {
            best = at(i, col);
        }
    }
    return best;
}

template<typename T>
T Matrix<T>::row_min(int row) const {
    T best = at(row, 0);
    for (int i = 1; i < d2size; i++) {
        if (at(row, i) < best) {
            best = at(row, i);
        }
    }
    return best;
}

template<typename T>
T Matrix<T>::col_min(int col) const {
    T best = at(0, col);
    for (int i = 1; i < d1size; i++) {
        if (at(i, col) < best) {
            best = at(i, col);
        }
    }
    return best;
}

template<typename T>
T Matrix<T>::row_sum(int row) const {
    T sum = at(row, 0);
    for (int i = 1; i < d2size; i++) {
        sum += at(row, i);
    }
    return sum;
}

template<typename T>
T Matrix<T>::col_sum(int col) const {
    T sum = at(0, col);
    for (int i = 1; i < d1size; i++) {
        sum += at(i, col);
    }
    return sum;
}

template<typename T>
std::vector<T> Matrix<T>::operator*(const std::vector<T> &vec) const {
    if (d2size != vec.size())
        throw std::exception();
    std::vector<T> ret(d1size);
    for (int i = 0; i < d1size; i++) {
        ret[i] = T{};
        for (int j = 0; j < d2size; j++) {
            ret[i] += at(i, j) * vec[j];
        }
    }
    return ret;
}

template<typename T>
bool Matrix<T>::reshape(size_t row, size_t col) {
    if (row * col != d1size * d2size)
        return false;
    d1size = row;
    d2size = col;
    return true;
}

template<typename T>
void Matrix<T>::swap_rows(int r0, int r1) {
    if (r0 < 0 || r0 >= d1size || r1 < 0 || r1 >= d2size) {
        throw std::out_of_range("swap_rows: out_of_range");
    }
    T temp;
    for (int j = 0; j < d2size; j++) {
        temp = at(r0, j);
        at(r0, j) = at(r1, j);
        at(r1, j) = temp;
    }
}

/**
 * Refer to github matrix implementation.
 * @see https://github.com/akalicki/matrix
 */
template<typename T>
Matrix<T> Matrix<T>::gaussian_eliminated(const bool row_reduced) const {
    Matrix<T> ret(*this);
    bool pivot_found; // whether current row has a pivot or not
    int i = 0;
    int j = 0;
    while (i < d1size) {
        pivot_found = false;
        while (j < d2size && !pivot_found) {
            // not zero -> pivot
            if (ret.at(i, j) != 0) {
                pivot_found = true;
                break;
            }
            // find possible row exchange
            int max_row = i;
            int max_at_j = 0; // max element at j-th col
            for (int k = i + 1; k < d1size; k++) {
                if (max_at_j < ret.at(k, j)) {
                    max_row = k;
                    max_at_j = ret.at(k, j);
                }
            }
            if (max_row != i) {
                ret.swap_rows(i, max_row);
                pivot_found = true;
            } else {
                // below (i, j) all are zeros
                j++;
            }
        }

        if (pivot_found) {
            for (int t = i + 1; t < d1size; ++t) {
                T factor = ret.at(t, j) / ret.at(i, j);
                for (int s = j + 1; s < d2size; ++s) {
                    ret.at(t, s) = ret.at(t, s) - ret.at(i, s) * factor;
                    // TODO tackle precision problem
                }
                ret.at(t, j) = 0;
            }

            if (row_reduced) {
                T denominator = ret.at(i, j);
                ret.at(i, j) = 1;
                for (int k = j+1; k < d2size; k++) {
                    ret.at(i, k) /= denominator;
                }
            }
        }

        i++;
        j++;
    }

    return ret;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const T &other) const {
    Matrix<T> ret(*this);
    for (int i = 0; i < d1size; ++i) {
        for (int j = 0; j < d2size; ++j) {
            ret.at(i, j) += other;
        }
    }
    return ret;
}

template<typename T>
Matrix<T> &Matrix<T>::operator+=(const T &other) {
    for (int i = 0; i < d1size; ++i) {
        for (int j = 0; j < d2size; ++j) {
            at(i, j) += other;
        }
    }
}


#endif //COURSEPROJECT_MATRIX_IMPL_H
