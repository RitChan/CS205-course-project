//
// Created by chenh on 5/11/2020.
//

#ifndef COURSEPROJECT_MATRIX_TEMPLATE_H
#define COURSEPROJECT_MATRIX_TEMPLATE_H

#include <vector>
#include <list>
#include <utility>

template<typename T>
class Matrix {
public:
    typedef std::pair<T, std::vector<T>> EigenPair; // <eigen_value, eigen_vector>
    static Matrix<T> dot(const Matrix<T> &left, const Matrix<T> &right);
    static Matrix<T> cross(const Matrix<T> &left, const Matrix<T> &right);
    Matrix() = default;
    Matrix(int d1size, int d2size);
    Matrix<T> operator+(const Matrix<T> &other) const;
    Matrix<T> operator-(const Matrix<T> &other) const;
    Matrix<T> operator*(const Matrix<T> &other) const;
    std::vector<T> &operator[](int index);
    Matrix<T> transpose() const;
    std::vector<T> &at(int index);
    T max() const; // TODO support axis
    T min() const;
    T sum() const;
    T avg() const;
    std::list<EigenPair> eigen_decompose() const;
    T trace() const;
    T determinant() const;
    int get_d1size() const { return d1size; };
    int get_d2size() const { return d2size; };

    template<typename M>
    friend Matrix<M> operator*(const M &c, const Matrix<M> &matrix);

    template<typename M>
    friend Matrix<M> operator/(const M &c, const Matrix<M> &matrix);

    // TODO slicing
    // TODO convolution operations
protected:
    int d1size{0}; // size of dimension 1
    int d2size{0}; // size of dimension 2
    std::vector<std::vector<T>> entry{}; // 2 choices: 1: raw array, 2: vector

};

#endif //COURSEPROJECT_MATRIX_TEMPLATE_H
