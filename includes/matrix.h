//
// Created by chenh on 5/11/2020.
//

#ifndef COURSEPROJECT_MATRIX_H
#define COURSEPROJECT_MATRIX_H
#include "matrix_template.h"

template<typename T>
Matrix<T> Matrix<T>::dot(const Matrix<T> &left, const Matrix<T> &right) {
    return Matrix<T>(0, 0);
}

template<typename T>
Matrix<T> Matrix<T>::cross(const Matrix<T> &left, const Matrix<T> &right) {
    return Matrix<T>(0, 0);
}

template<typename T>
Matrix<T>::Matrix(int d1size, int d2size): d1size(d1size), d2size(d2size), entry(d1size, std::vector<T>(d2size)) {

}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const {
    return Matrix<T>(0, 0);
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) const {
    return Matrix<T>(0, 0);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const {
    return Matrix<T>(0, 0);
}

template<typename T>
std::vector <T> &Matrix<T>::operator[](int index) {
    return entry[index];
}

template<typename T>
std::vector <T> &Matrix<T>::at(int index) {
    return entry.at(index);
}

template<typename T>
Matrix<T> operator*(const T &c, const Matrix<T> &matrix) {
    return Matrix<T>(0, 0);
}

template<typename T>
Matrix<T> operator/(const T &c, const Matrix<T> &matrix) {
    return Matrix<T>(0, 0);
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const {
    return Matrix<T>(0, 0);
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
