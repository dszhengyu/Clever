#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <assert.h>

using std::vector;
using std::initializer_list;
using std::copy;
using std::transform;
using std::ostream;

using std::cout;
using std::endl;

class Matrix
{
public:
    explicit Matrix(initializer_list<initializer_list<double>> initArray);
    explicit Matrix(size_t row, size_t column);
    Matrix(const Matrix &origin);
    double &operator()(int, int);
    double operator()(int, int) const;
    size_t rowSize() {return row;};
    size_t columnSize() {return column;};
    void reverse();
    Matrix operator+(const Matrix &rhs) const;
    Matrix operator-(const Matrix &rhs) const;
    Matrix operator*(const Matrix &rhs) const;
    Matrix operator*(const double c) const;
private:
    size_t row;
    size_t column;
    vector<double> mat;
};

Matrix operator*(const double c, const Matrix &lhs);
ostream &operator<<(ostream &out, Matrix &m);

#endif // MATRIX_H
