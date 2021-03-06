#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <set>
#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <iterator>
#include <numeric>

using std::vector;
using std::set;
using std::initializer_list;
using std::copy;
using std::transform;
using std::for_each;
using std::accumulate;
using std::ostream;
using std::inserter;
using std::back_inserter;
using std::inner_product;
using std::cout;
using std::endl;

class Matrix
{
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
    Matrix merge(const Matrix &rhs, int axis) const;
    Matrix splice(size_t start, size_t end, int axis, bool inplace = false);
    Matrix splice(size_t start, size_t end, int axis) const;
    Matrix reverse(bool inplace = false);
    Matrix reverse() const;
    Matrix sign(bool inplace = false);
    Matrix dotProduct(const Matrix &rhs);
    Matrix abs(bool inplace = false);
    Matrix square(bool inplace = false);
    double sum();
    double max();
    vector<Matrix> splictRow() const;
    double toDouble() const;
    vector<vector<double>> distinctColumn() const;
private:
    size_t row;
    size_t column;
    vector<double> mat;
};

Matrix operator*(const double c, const Matrix &lhs);
ostream &operator<<(ostream &out, Matrix &m);
ostream &operator<<(ostream &out, vector<vector<double>>);

#endif // MATRIX_H
