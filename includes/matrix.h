//
// Created by chenh on 5/11/2020.
//

#ifndef COURSEPROJECT_MATRIX_H
#define COURSEPROJECT_MATRIX_H
#include "matrix_template.h"

template<typename T>
Matrix<T> Matrix<T>::dot(const Matrix<T> &left, const Matrix<T> &right) {
    return Matrix<T>();
}

template<typename T>
Matrix<T> Matrix<T>::cross(const Matrix<T> &left, const Matrix<T> &right) {
    return Matrix<T>();
}

template<typename T>
Matrix<T>::Matrix(int d1size, int d2size): d1size(d1size), d2size(d2size), entry(d1size, std::vector<T>(d2size)), _valid(true) {

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
    if (d1size != other.d1size || d2size != other.d2size) {
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
    static Matrix<T> invalid;
    if (d1size != other.d1size || d2size != other.d2size)
        return invalid;
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
    if (d1size != other.d1size || d2size != other.d2size) {
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
    return Matrix<T>();
}


template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const {
    return Matrix<T>();
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
std::vector <T> &Matrix<T>::operator[](int index) {
    return entry[index];
}

template<typename T>
const std::vector<T> &Matrix<T>::operator[](int index) const {
    return entry[index];
}

template<typename T>
std::vector <T> &Matrix<T>::at(int index) {
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
Matrix<T> operator/(const Matrix<T> &matrix, const T &c) {
    Matrix<T> ret = matrix; // TODO handle zero division
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
    return nullptr;
}

template<typename T>
T Matrix<T>::min() const {
    return nullptr;
}

template<typename T>
T Matrix<T>::sum() const {
    return nullptr;
}

template<typename T>
T Matrix<T>::avg() const {
    return nullptr;
}

template<typename T>
std::list<std::pair<T, std::vector<T>>> Matrix<T>::eigen_decompose() const {
    return std::list<EigenPair>();
}

template<typename T>
T Matrix<T>::trace() const {
    return nullptr;
}

template<typename T>
T Matrix<T>::determinant() const {
    return nullptr;
}

#endif //COURSEPROJECT_MATRIX_H
