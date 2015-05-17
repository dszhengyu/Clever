#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <iterator>

using std::vector;
using std::initializer_list;
using std::copy;
using std::transform;
using std::ostream;
using std::inserter;
using std::back_inserter;
using std::cout;
using std::endl;

class Matrix
{
public:
    explicit Matrix();
    explicit Matrix(initializer_list<initializer_list<double>> initArray);
    explicit Matrix(size_t row, size_t column);
    Matrix(const Matrix &origin);
    double &operator()(size_t, size_t);
    double operator()(size_t, size_t) const;
    size_t rowSize() {return row;};
    size_t columnSize() {return column;};
    void reverse();
    Matrix operator+(const Matrix &rhs) const;
    Matrix operator-(const Matrix &rhs) const;
    Matrix operator*(const Matrix &rhs) const;
    Matrix operator*(const double c) const;
    bool operator==(const Matrix &rhs) const;
    Matrix merge(Matrix &rhs, int axis, bool inplace = 0);
    Matrix splice(size_t start, size_t end, int axis, bool inplace = 0);
    Matrix reverse(bool inplace = 0);
private:
    size_t row;
    size_t column;
    vector<double> mat;
};

Matrix operator*(const double c, const Matrix &lhs);
ostream &operator<<(ostream &out, Matrix &m);

#endif // MATRIX_H
