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

    /**
     * Default constructor where _valid flag is set to false.
     */
    Matrix() : _valid(false) {};

    /**
     * Constructor with shape specified.
     *
     * @param d1size Number of rows.
     * @param d2size Number of columns.
     */
    Matrix(int d1size, int d2size);

    /**
     * Easy initialization with nested two dimensional initializer_list.
     *
     * Usage example:
     *     Matrix<int> matrix{
     *         {1, 2, 3},
     *         {4, 5, 6},
     *         {7, 8, 9}
     *     };
     *
     * Note that length of rows must be consistent. If row lengths are not consistent, the matrix is constructed with
     * Matrix::valid() flag set to false.
     *
     * @param init_list Nested initializer_list.
     */
    Matrix(MatrixInitList init_list);

    /**
     * Overloads operator "+".
     *
     * @param other Another matrix for "+".
     * @return Newly constructed matrix resulting from "+".
     */
    // TODO /=, matrix * vector
    Matrix<T> operator+(const Matrix<T> &other) const;

    /**
     * Overloads operator "+=".
     *
     * @param other %Matrix to be added into *this.
     * @return Reference to *this.
     */
    Matrix<T> &operator+=(const Matrix<T> &other);

    /**
     * Overloads operator "-".
     *
     * @param other Another operand.
     * @return Newly constructed matrix resulting from "-".
     */
    Matrix<T> operator-(const Matrix<T> &other) const;

    /**
     * Overloads operator "-=".
     *
     * @param other %Matrix to be subtracted from *this.
     * @return Reference to *this.
     */
    Matrix<T> &operator-=(const Matrix<T> &other);

    /**
     * Overloads operator "*".
     *
     * @param other Another operand.
     * @return Newly constructed matrix resulting from "*".
     */
    Matrix<T> operator*(const Matrix<T> &other) const;

    // TODO delete this function
    Matrix<T> &operator*=(const Matrix<T> &other);

    /**
     * Overloads operator "*".
     *
     * @param other Scalar.
     * @return Newly constructed matrix resulting from "*".
     */
    Matrix<T> operator*(const T &other) const;

    /**
     * Overloads operator "*=".
     *
     * @param other Scalar.
     * @return Reference to *this.
     */
    Matrix<T> &operator*=(const T &other);

    /**
     * Overloads operator "/"
     *
     * @param c scalar.
     * @return Newly constructed Matrix resulting from "/".
     */
    Matrix<T> operator/(const T &c);

    /**
     * Overloads operator "[]".
     *
     * @param index Row index.
     * @return Row selected by index.
     */
    std::vector<T> &operator[](int index);

    /**
     * Overloads operator "[]".
     *
     * @param index Row index.
     * @return Row selected by index.
     */
    const std::vector<T> &operator[](int index) const;

    /**
     * Throws exception if index is out of range.
     *
     * @param index Row index.
     * @return Row selected by index.
     */
    std::vector<T> &at(int index);

    /**
     * Throws exception if index is out of range.
     *
     * @param index Row index.
     * @return Row selected by index.
     */
    const std::vector<T> &at(int index) const { return entry.at(index); };

    /**
     * Get a matrix entry.
     *
     * Throws exception if index is out of range.
     *
     * @param i Row index.
     * @param j Column index.
     * @return Selected element.
     */
    T &at(int i, int j) { return entry.at(i).at(j); };

    /**
     * Get a matrix element.
     *
     * Throws exception if index is out of range.
     *
     * @param i Row index.
     * @param j Column index.
     * @return Selected element.
     */
    const T &at(int i, int j) const { return entry.at(i).at(j); };

    /**
     * Max element.
     */
    T max() const;

    /**
     * Max element in a row.
     */
    T row_max(int row) const;

    /**
     * Max element in a column.
     */
    T col_max(int col) const;

    /**
     * Min element.
     */
    T min() const;

    /**
     * Min element in a row.
     */
    T row_min(int row) const;

    /**
     * Min element in a column.
     */
    T col_min(int col) const;

    /**
     * Sum of all elements.
     */
    T sum() const;

    /**
     * Sum of elements in a row.
     */
    T row_sum(int row) const;

    /**
     * Sum of elements in a column.
     */
    T col_sum(int col) const;

    /**
     * Average of all elements.
     */
    T avg() const; // TODO discuss about the signature

    /**
     * Find all eigenvalues and corresponding eigen-vectors.
     *
     * @return A list of EigenPair
     */
    std::list<EigenPair<T>> eigen_decompose() const;

    /**
     * Return transposed matrix.
     */
    Matrix<T> transpose() const;

    /**
     * Trace of this matrix.
     */
    T trace() const;

    /**
     * Determinant of this matrix.
     */
    T determinant() const;

    /**
     * TODO in progress...
     *
     * @param other
     * @return
     */
    Matrix<T> dot(const Matrix<T> &other) const; // TODO make a test

    /**
     * TODO in progress...
     *
     * @param other
     * @return
     */
    Matrix<T> cross(const Matrix<T> &other) const;

    Matrix<T> hadamard(const Matrix<T> &other) const;

    /**
     * Number of rows.
     */
    int get_d1size() const { return d1size; };

    /**
     * Number of columns.
     */
    int get_d2size() const { return d2size; };

    /**
     * Is this matrix valid?.
     */
    bool valid() const { return _valid; };

    /**
     * Overloads operator "*" for M and Matrix<M> to support "scalar * matrix".
     *
     * @return New constructed matrix resulting from "*".
     */
    template<typename M>
    friend Matrix<M> operator*(const M &c, const Matrix<M> &matrix);

    // TODO slicing
    Matrix<T> sub_matrix(int row_low, int row_high, int col_low, int col_high);
    Matrix<T> sub_matrix(std::initializer_list<int> rows, std::initializer_list<int> cols);
    // TODO convolution operations
protected:
    /**
     * Test whether another matrix has the same number of row and columns with this
     * matrix or not.
     *
     * @param other Another matrix.
     */
    bool shape_equal_to(const Matrix<T> &other) const { return d1size == other.d1size && d2size == other.d2size; }


    int d1size{0}; /**< Size of dimension 1. */
    int d2size{0}; /**< Size of dimension 2. */
    std::vector<std::vector<T>> entry{}; /**< Matrix elements. */
    bool _valid{true}; /**< Valid-flag. */
};

#endif //COURSEPROJECT_MATRIX_TEMPLATE_H
