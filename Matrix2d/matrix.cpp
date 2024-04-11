#include <iostream>
#include <string>
#include <stdexcept> // std::out_of_range()
#include <iomanip>   // std::setw()

#include "matrixElement.h"

using namespace std;

#include "matrix.h"

TwoDimensionMatrix::TwoDimensionMatrix() {
    for (auto &i: matrix) {
        for (int &j: i) {
            j = 0;
        }
    }
}

TwoDimensionMatrix::TwoDimensionMatrix(const TwoDimensionMatrix &other_matrix) {
    for (size_t i = 0; i < size_; i++) {
        for (size_t j = 0; j < size_; j++) {
            matrix[i][j] = other_matrix.get(i, j);
        }
    }
}

TwoDimensionMatrix::TwoDimensionMatrix(const MatrixElement other_matrix[size_][size_]) {
    for (size_t i = 0; i < size_; i++) {
        for (size_t j = 0; j < size_; j++) {
            matrix[i][j] = other_matrix[i][j];
        }
    }
}

MatrixElement TwoDimensionMatrix::get(size_t row, size_t column) const {
    return matrix[row][column];
}

TwoDimensionMatrix &TwoDimensionMatrix::operator=(const TwoDimensionMatrix &other_matrix) {
    for (size_t i = 0; i < size_; i++) {
        for (size_t j = 0; j < size_; j++) {
            matrix[i][j] = other_matrix.get(i, j);
        }
    }
    return *this;
}

MatrixElement *TwoDimensionMatrix::operator[](size_t row) {
    return matrix[row];
}

const MatrixElement *TwoDimensionMatrix::operator[](size_t row) const {
    return matrix[row];
}

TwoDimensionMatrix &TwoDimensionMatrix::operator*=(MatrixElement number) {
    TwoDimensionMatrix m;
    for (auto &i: matrix) {
        for (int &j: i) {
            j *= number;
        }
    }
    return *this;
}

TwoDimensionMatrix TwoDimensionMatrix::operator&&(const TwoDimensionMatrix &other_matrix) const {
    TwoDimensionMatrix m;
    for (size_t i = 0; i < TwoDimensionMatrix::size(); i++) {
        for (size_t j = 0; j < TwoDimensionMatrix::size(); j++) {
            m.matrix[i][j] = (matrix[i][j] && other_matrix.get(i, j));
        }
    }
    return m;
}

TwoDimensionMatrix::operator size_t() const {
    return static_cast<size_t>(TwoDimensionMatrix::size_);
}

ostream &operator<<(ostream &output, const TwoDimensionMatrix &matrix) {
    for (size_t i = 0; i < TwoDimensionMatrix::size(); i++) {
        for (size_t j = 0; j < TwoDimensionMatrix::size(); j++) {
            output << matrix.get(i, j) << " ";
        }
        output << endl;
    }
    return output;
}

istream &operator>>(istream &input, TwoDimensionMatrix &_matrix) {
    for (auto &i: _matrix.matrix) {
        for (int &j: i) {
            input >> j;
        }
    }
    return input;
}

TwoDimensionMatrix operator+(const TwoDimensionMatrix &matrix1, const TwoDimensionMatrix &matrix2) {
    TwoDimensionMatrix m;
    for (size_t i = 0; i < TwoDimensionMatrix::size(); i++) {
        for (size_t j = 0; j < TwoDimensionMatrix::size(); j++) {
            m[i][j] = matrix1.get(i, j) + matrix2.get(i, j);
        }
    }
    return m;
}
