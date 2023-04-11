#include <iostream>
#include "stdafx.h"
/*!
\addtogroup Matrix_ Класс матрица
\file
\brief Здесь находятся исходные коды методов класса. Описание методов приведено в Matrix.hpp.
@{
*/

Matrix::Matrix(int rows, int cols)
{
    //cout << "Вызван конструктор " << this << endl;
    this->rows = rows;
    this->cols = cols;
    matrix = new double* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
}
/*************************************************************************/
Matrix::Matrix(const Matrix& other)
{
    //cout << "Вызван конструктор копирования " << this << endl;
    this->rows = other.rows;
    this->cols = other.cols;
    matrix = new double* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}
/*************************************************************************/
Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    //cout << "Вызван деструктор " << this << endl;
}
/*************************************************************************/
Matrix& Matrix::operator= (const Matrix& other)
{
    if (this == &other)
    return *this;

    rows = other.rows;
    cols = other.cols;

    if (other.matrix) {
        matrix = new double* [rows];
        for (size_t i = 0; i < rows; ++i)
            matrix[i] = new double[cols];
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                matrix[i][j] = other.matrix[i][j];
    }
    else
        matrix = 0;

    return *this;
}
/*************************************************************************/
double& Matrix::operator() (int row, int col)
{
    return matrix[row][col];
}
/*************************************************************************/
Matrix Matrix::operator+(const Matrix& other)
{
    if (rows != other.cols) {
        std::cerr << "Число строк матриц не совпадают" << std::endl;
        return *this;
    }
    if (cols != other.cols) {
        std::cerr << "Число столбцов матриц не совпадают" << std::endl;
        return *this;
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
        }
    }
    return result;
}
/*************************************************************************/
Matrix Matrix::operator-(const Matrix& other)
{
    if (rows != other.cols) {
        std::cerr << "Число строк матриц не совпадают" << std::endl;
        return *this;
    }
    if (cols != other.cols) {
        std::cerr << "Число столбцов матриц не совпадают" << std::endl;
        return *this;
    }
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
        }
    }
    return result;
}
/*************************************************************************/
Matrix Matrix::operator*(const Matrix& other)
{
    if (cols != other.rows) {
        std::cerr << "Неверные размерности матриц" << std::endl;
        return *this;
    }
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            double sum = 0;
            for (int k = 0; k < cols; k++) {
                sum += matrix[i][k] * other.matrix[k][j];
            }
            result.matrix[i][j] = sum;
        }
    }
    return result;
}
/*************************************************************************/
Matrix Matrix::operator* (const double scalar)
{
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.matrix[i][j] = matrix[i][j] * scalar;
        }
    }
    return result;
}
/*************************************************************************/
void Matrix::multiply(const Matrix& other)
{
    if (cols != other.rows) {
        std::cerr << "Неверные размерности матриц" << std::endl;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            double sum = 0;
            for (int k = 0; k < cols; k++) {
                sum += matrix[i][k] * other.matrix[k][j];
            }
            matrix[i][j] = sum;
        }
    }
}
/*************************************************************************/
void Matrix::multiply(const double scalar)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] *= scalar;
        }
    }
}
/*************************************************************************/
Matrix Matrix::transpose() const
{
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.matrix[j][i] = matrix[i][j];
        }
    }
    return result;
}
/*************************************************************************/
double Matrix::det()
{
    if (rows != cols) {
        std::cerr << "Матрица не квадратная" << std::endl;
        return 0;
    }
    if (rows == 1) {
        return matrix[0][0];
    }
    if (rows == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    double result = 0;
    for (int i = 0; i < cols; i++) {
        result += pow(-1, i) * matrix[0][i] * minor(0, i).det();
    }
    return result;
}
/*************************************************************************/
Matrix Matrix::minor(int row, int col)
{
    Matrix result(rows - 1, cols - 1);
    int m = 0, n = 0;
    for (int i = 0; i < rows; i++) {
        if (i == row) continue;
        n = 0;
        for (int j = 0; j < cols; j++) {
            if (j == col) continue;
            result.matrix[m][n] = matrix[i][j];
            n++;
        }
        m++;
    }
    return result;
}
/*************************************************************************/
Matrix Matrix::inverse()
{
    Matrix result(rows, cols);
    double determinant = det();
    if (determinant == 0) {
        std::cerr << "Матрица не обращаема" << std::endl;
        return result;
    }
    Matrix cofactor(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            //cofactor.matrix[i][j] = pow(-1, i + j) * minor(i, j).det();
            cofactor(i, j) = pow(-1, i + j) * minor(i, j).det();
        }
    }
    result = cofactor.transpose();

    result.multiply(1.0 / determinant);
    return result;
}
/*************************************************************************/
void Matrix::identity()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (i == j) ? 1 : 0;
        }
    }
}
/*************************************************************************/
void Matrix::print(const std::string name) const
{
    if (name != "") {
        std::cout << name << ": " << std::endl;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/*! @} */