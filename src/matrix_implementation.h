//
// Created by chenh on 5/11/2020.
//
// TODO 10 functions remained
#ifndef COURSEPROJECT_MATRIX_IMPLEMENTATION_H
#define COURSEPROJECT_MATRIX_IMPLEMENTATION_H

#include "matrix_template.h"
#include <iostream>
#include <vector>


template<typename T>
Matrix<T>::Matrix(int d1size, int d2size): d1size(d1size), d2size(d2size), entry(d1size, std::vector<T>(d2size)),
                                           _valid(true) {
    if (d1size <= 0 || d2size <= 0)
        _valid = false;
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
            entry = std::vector<std::vector<T>>();
            break;
        }
        if (d2size != row.size()) {
            d2size = row.size();
            entry = std::vector<std::vector<T>>(d1size, std::vector<T>(d2size, T{}));
        }
        d2size = row.size();
        j = 0;
        for (T elem: row)
            entry[i][j++] = elem;
        i++;
    }
}

template<typename T>
Matrix<T> &Matrix<T>::operator*=(const T &other) {
    for (std::vector<T> &v: entry) {
        for (T &e: v) {
            e *= other;
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
            ret[i][j] += other[i][j];
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
            entry[i][j] += other[i][j];
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
            ret[i][j] -= other[i][j];
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
            entry[i][j] -= other[i][j];
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
            ret[i][j] = 0;
            for (int p = 0; p < align_len; p++) {
                ret[i][j] += entry[i][p] * other[p][j];
            }
        }
    }
    return ret;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T &other) const {
    Matrix<T> ret = *this;
    for (std::vector<T> &v: ret.entry) {
        for (T &e: v)
            e *= other;
    }
    return ret;
}


template<typename T>
std::vector<T> &Matrix<T>::operator[](int index) {
    return entry[index];
}

template<typename T>
const std::vector<T> &Matrix<T>::operator[](int index) const {
    return entry[index];
}

template<typename T>
std::vector<T> &Matrix<T>::at(int index) {
    return entry.at(index);
}


template<typename T>
Matrix<T> operator*(const T &c, const Matrix<T> &matrix) {
    Matrix<T> ret = matrix;
    for (std::vector<T> &v: ret.entry) {
        for (T &e: v)
            e *= c;
    }
    return ret;
}

template<typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &other) {
    static Matrix<T> INVALID;
    return INVALID;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const T &c) {
    Matrix<T> ret{*this}; // TODO handle zero division
    for (std::vector<T> &v: ret.entry) {
        for (T &e: v)
            e /= c;
    }
    return ret;
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> ret(d2size, d1size);
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            ret[j][i] = entry[i][j];
        }
    }
    return ret;
}

template<typename T>
T Matrix<T>::max() const {
    T max_T = entry.at(0).at(0);
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            max_T = max_T < entry[i][j] ? entry[i][j] : max_T;
        }
    }
    return max_T;
}

template<typename T>
T Matrix<T>::min() const {
    T min_T = entry.at(0).at(0);
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            min_T = min_T > entry[i][j] ? entry[i][j] : min_T;
        }
    }
    return min_T;
}

template<typename T>
T Matrix<T>::sum() const {
    T sum_T = entry.at(0).at(0);
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            sum_T += entry[i][j];
        }
    }
    return sum_T - entry.at(0).at(0);
}

template<typename T>
T Matrix<T>::avg() const {
    return '\0';
}

template<typename T>
std::list<EigenPair<T>> Matrix<T>::eigen_decompose() const {
    return std::list<EigenPair<T>>();
}

template<typename T>
T Matrix<T>::trace() const {
    return nullptr;
}

template<typename T>
T Matrix<T>::determinant() const {
    return nullptr;
}

template<typename T>
Matrix<T> Matrix<T>::cross(const Matrix<T> &other) const {
    return Matrix<T>();
}

template<typename T>
Matrix<T> Matrix<T>::hadamard(const Matrix<T> &other) const {
    if (!_valid || !other.valid() || !shape_equal_to(other))
        return Matrix<T>();
    Matrix<T> ret{*this};
    for (int i = 0; i < d1size; i++) {
        for (int j = 0; j < d2size; j++) {
            ret.at(i, j) *= other.at(i, j);
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
    T best = entry.at(row).at(0);
    for (int i = 1; i < entry.at(row).size(); i++) {
        if (entry.at(row).at(i) > best) {
            best = entry.at(row).at(i);
        }
    }
    return best;
}

template<typename T>
T Matrix<T>::col_max(int col) const {
    T best = entry.at(0).at(col);
    for (int i = 1; i < entry.size(); i++) {
        if (entry.at(i).at(col) > best) {
            best = entry.at(i).at(col);
        }
    }
    return best;
}

template<typename T>
T Matrix<T>::row_min(int row) const {
    T best = entry.at(row).at(0);
    for (int i = 1; i < entry.at(row).size(); i++) {
        if (entry.at(row).at(i) < best) {
            best = entry.at(row).at(i);
        }
    }
    return best;
}

template<typename T>
T Matrix<T>::col_min(int col) const {
    T best = entry.at(0).at(col);
    for (int i = 1; i < entry.size(); i++) {
        if (entry.at(i).at(col) < best) {
            best = entry.at(i).at(col);
        }
    }
    return best;
}

template<typename T>
T Matrix<T>::row_sum(int row) const {
    T sum = entry.at(row).at(0);
    for (int i = 1; i < entry.at(row).size(); i++) {
        sum += entry.at(row).at(i);
    }
    return sum;
}

template<typename T>
T Matrix<T>::col_sum(int col) const {
    T sum = entry.at(0).at(col);
    for (int i = 1; i < entry.size(); i++) {
        sum += entry.at(i).at(col);
    }
    return sum;
}


#endif //COURSEPROJECT_MATRIX_IMPLEMENTATION_H
