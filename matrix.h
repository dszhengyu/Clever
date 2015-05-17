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
friend Matrix dotProduct(const Matrix &lhs, const Matrix &rhs);
public:
    explicit Matrix();
    explicit Matrix(initializer_list<initializer_list<double>> initArray);
    explicit Matrix(size_t row, size_t column);
    Matrix(const Matrix &origin);
    double &operator()(size_t, size_t);
    double operator()(size_t, size_t) const;
    size_t rowSize() {return row;};
    size_t columnSize() {return column;};
    Matrix operator+(const Matrix &rhs) const;
    Matrix operator-(const Matrix &rhs) const;
    Matrix operator*(const Matrix &rhs) const;
    Matrix operator*(const double c) const;
    bool operator==(const Matrix &rhs) const;
    Matrix merge(Matrix &rhs, int axis, bool inplace = false);
    Matrix splice(size_t start, size_t end, int axis, bool inplace = false);
    Matrix reverse(bool inplace = false);
private:
    size_t row;
    size_t column;
    vector<double> mat;
};

Matrix operator*(const double c, const Matrix &lhs);
Matrix dotProduct(const Matrix &lhs, const Matrix &rhs);
ostream &operator<<(ostream &out, Matrix &m);

#endif // MATRIX_H
