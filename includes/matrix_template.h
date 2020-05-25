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
    typedef std::pair<T, std::vector<T>> EigenPair; // <eigen_value, eigen_vector> TODO make the type more readable
    Matrix(): _valid(false) {};
    Matrix(int d1size, int d2size);
    // TODO /=, matrix * vector
    Matrix<T> operator+(const Matrix<T> &other) const;
    Matrix<T> &operator+=(const Matrix<T> &other);
    Matrix<T> operator-(const Matrix<T> &other) const;
    Matrix<T> &operator-=(const Matrix<T> &other);
    Matrix<T> operator*(const Matrix<T> &other) const;
    Matrix<T> &operator*=(const Matrix<T> &other);
    Matrix<T> operator*(const T &other) const;
    Matrix<T> &operator*=(const T &other);
    std::vector<T> &operator[](int index);
    const std::vector<T> &operator[](int index) const;
    Matrix<T> transpose() const;
    std::vector<T> &at(int index);
    const std::vector<T> &at(int index) const { return entry.at(index); };
    T &at(int i, int j) { return entry.at(i).at(j); };
    const T &at(int i, int j) const { return entry.at(i).at(j); };
    T max() const; // TODO support axis
    T row_max(int row) const;
    T col_max(int col) const;
    T min() const;
    T row_min(int row) const;
    T col_min(int col) const;
    T sum() const;
    T row_sum(int row) const;
    T col_sum(int col) const;
    T avg() const; // TODO discuss about the signature
    std::list<EigenPair> eigen_decompose() const;
    T trace() const;
    T determinant() const;
    Matrix<T> dot(const Matrix<T> &other) const; // TODO make a test
    Matrix<T> cross(const Matrix<T> &other) const;
    int get_d1size() const { return d1size; };
    int get_d2size() const { return d2size; };
    bool valid() const { return _valid; };

    template<typename M>
    friend Matrix<M> operator*(const M &c, const Matrix<M> &matrix);

    template<typename M>
    friend Matrix<M> operator/(const Matrix<M> &matrix, const M &c);

    // TODO slicing
    // TODO convolution operations
protected:
    int d1size{0}; // size of dimension 1
    int d2size{0}; // size of dimension 2
    std::vector<std::vector<T>> entry{};
    bool _valid{true};
    bool shape_equal_to(const Matrix<T> &other) const { return d1size == other.d1size && d2size == other.d2size; }

};

#endif //COURSEPROJECT_MATRIX_TEMPLATE_H
