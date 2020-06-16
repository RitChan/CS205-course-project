/**
 * @file matrix_template.h
 * @ingroup matrix
 * @brief Defines the template for class Matrix.
 */

#ifndef COURSEPROJECT_MATRIX_TEMP_H
#define COURSEPROJECT_MATRIX_TEMP_H

#include "smart_array.h"
#include <vector>
#include <list>
#include <utility>
#include <initializer_list>

/**
 * <Eigen-value, Eigen-vector> pair structure.
 */
template<typename T>
class EigenPair {
public:
    T val;
    std::vector<T> vec;
};

/**
 * %Matrix class.
 * The interface is inevitably complicated due to the requirements.
 */
template<typename T>
class Matrix {
public:
    typedef std::initializer_list<std::initializer_list<T>> MatrixInitList;

    Matrix() : _valid(false) {};

    Matrix(int d1size, int d2size);

    Matrix(MatrixInitList init_list);

    Matrix(const Matrix<T> &other) { *this = other; };

    Matrix(Matrix<T> &&other) noexcept = default;

    virtual ~Matrix() = default;

    /**
     * Deep copy. All matrix entries will get allocated in a new place.
     */
    Matrix<T> &operator=(const Matrix<T> &other);

    Matrix<T> &operator=(Matrix<T> &&other) noexcept = default;

    bool operator==(const Matrix<T> &other) const;

    bool operator!=(const Matrix<T> &other) const { return !(*this == other); }

    Matrix<T> operator+(const Matrix<T> &other) const;

    Matrix<T> &operator+=(const Matrix<T> &other);

    Matrix<T> operator-(const Matrix<T> &other) const;

    Matrix<T> &operator-=(const Matrix<T> &other);

    Matrix<T> operator*(const Matrix<T> &other) const;

    Matrix<T> operator*(const T &other) const;

    std::vector<T> operator*(const std::vector<T> &vec) const;

    Matrix<T> &operator*=(const T &other);

    Matrix<T> operator/(const T &c) const;

    Matrix<T> &operator/=(const T& c);

    virtual T &at(int i, int j) {
        return elem[i * d2size + j];
    };

    virtual const T &at(int i, int j) const {
        return elem[i * d2size + j];
    };

    T max() const;

    T row_max(int row) const;

    T col_max(int col) const;

    T min() const;

    T row_min(int row) const;

    T col_min(int col) const;

    T sum() const;

    T row_sum(int row) const;

    T col_sum(int col) const;

    T avg() const; // TODO discuss about the signature

    std::list<EigenPair<T>> eigen_decompose() const;

    Matrix<T> transpose() const;

    T trace() const;

    T determinant() const;

    Matrix<T> dot(const Matrix<T> &other) const;

    std::vector<T> cross(const Matrix<T> &other) const;

    Matrix<T> hadamard(const Matrix<T> &other) const;

    Matrix<T> gaussian_eliminated(bool row_reduced = false) const;

    void swap_rows(int r0, int r1);

    bool reshape(size_t row, size_t col);

    int get_d1size() const { return d1size; };

    int get_d2size() const { return d2size; };

    SmartArray<T> shallow_copied_data() const { return elem.shallow_copy(); }

    bool valid() const { return _valid; };

    template<typename M>
    friend Matrix<M> operator*(const M &c, const Matrix<M> &matrix);

    // TODO convolution operations
protected:
    bool shape_equal_to(const Matrix<T> &other) const { return d1size == other.d1size && d2size == other.d2size; }

    size_t d1size{0};
    size_t d2size{0};
    SmartArray<T> elem{};
    bool _valid{true};
};

#endif //COURSEPROJECT_MATRIX_TEMP_H
