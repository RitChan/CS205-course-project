/**
 * @file matrix_template.h
 * @ingroup matrix
 * @brief Defines the template for class Matrix.
 */

#ifndef COURSEPROJECT_MATRIX_TEMPLATE_H
#define COURSEPROJECT_MATRIX_TEMPLATE_H

#include <vector>
#include <list>
#include <utility>
#include <initializer_list>

/**
 * <Eigen-value, Eigen-vector> pair structure.
 */
template<typename T>
class EigenPair {
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

    Matrix(const Matrix<T> &other);

    Matrix(Matrix<T> &&other) noexcept;

    ~Matrix();

    Matrix<T> &operator=(const Matrix<T> &other);

    Matrix<T> &operator=(Matrix<T> &&other) noexcept;

    // TODO /=, matrix * vector
    Matrix<T> operator+(const Matrix<T> &other) const;

    Matrix<T> &operator+=(const Matrix<T> &other);

    Matrix<T> operator-(const Matrix<T> &other) const;

    Matrix<T> &operator-=(const Matrix<T> &other);

    Matrix<T> operator*(const Matrix<T> &other) const;

    Matrix<T> operator*(const T &other) const;

    std::vector<T> operator*(const std::vector<T> &vec) const;

    Matrix<T> &operator*=(const T &other);

    Matrix<T> &operator*=(const Matrix<T> &other);

    Matrix<T> &operator*=(const std::vector<T> &vec);

    Matrix<T> operator/(const T &c) const;

    T &at(int i, int j) {
        return entry[i * d2size + j];
    };

    const T &at(int i, int j) const { return entry[i * d2size + j]; };

    size_t num_elem() const { return d1size * d2size; }

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

    Matrix<T> dot(const Matrix<T> &other) const; // TODO make a test

    std::vector<T> cross(const Matrix<T> &other) const;

    Matrix<T> hadamard(const Matrix<T> &other) const;

    int get_d1size() const { return d1size; };

    int get_d2size() const { return d2size; };

    bool valid() const { return _valid; };

    template<typename M>
    friend Matrix<M> operator*(const M &c, const Matrix<M> &matrix);

    // TODO slicing
    Matrix<T> sub_matrix(int row_low, int row_high, int col_low, int col_high);

    Matrix<T> sub_matrix(std::initializer_list<int> rows, std::initializer_list<int> cols);
    // TODO convolution operations
protected:
    bool shape_equal_to(const Matrix<T> &other) const { return d1size == other.d1size && d2size == other.d2size; }

    void release();

    static void swap(Matrix<T> &left, Matrix<T> &right);

    size_t d1size{0};
    size_t d2size{0};
    T *entry{nullptr};
    bool _valid{true};
};

#endif //COURSEPROJECT_MATRIX_TEMPLATE_H
