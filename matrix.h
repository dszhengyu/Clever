#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <iterator>
#include <numeric>

using std::vector;
using std::initializer_list;
using std::copy;
using std::transform;
using std::for_each;
using std::ostream;
using std::inserter;
using std::back_inserter;
using std::inner_product;
using std::cout;
using std::endl;

class Matrix
{
friend Matrix dotProduct(const Matrix &lhs, const Matrix &rhs);
friend Matrix sign(const Matrix &m);
public:
    typedef size_t size_type;
    explicit Matrix();
    explicit Matrix(initializer_list<initializer_list<double>> initArray);
    explicit Matrix(size_t row, size_t column, double initNum = 0);
    Matrix(const Matrix &origin);
    double &operator()(size_t, size_t);
    double operator()(size_t, size_t) const;
    size_t rowSize() {return row;};
    size_t columnSize() {return column;};
    size_t rowSize() const {return row;};
    size_t columnSize() const {return column;};
    Matrix operator+(const Matrix &rhs) const;
    Matrix operator-(const Matrix &rhs) const;
    Matrix operator*(const Matrix &rhs) const;
    Matrix operator*(const double c) const;
    bool operator==(const Matrix &rhs) const;
    double innerProduct(const Matrix &rhs);
    Matrix merge(const Matrix &rhs, int axis, bool inplace = false);
    Matrix splice(size_t start, size_t end, int axis, bool inplace = false);
    Matrix reverse(bool inplace = false);
    static Matrix sign(const Matrix &m);
    static Matrix dotProduct(const Matrix &lhs, const Matrix &rhs);

private:
    size_t row;
    size_t column;
    vector<double> mat;
};

Matrix operator*(const double c, const Matrix &lhs);
ostream &operator<<(ostream &out, Matrix &m);

#endif // MATRIX_H
