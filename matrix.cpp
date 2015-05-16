#include "matrix.h"

Matrix::Matrix(initializer_list<initializer_list<double>> initArray)
    :row(initArray.size()), column(initArray.begin()->size()),
    mat(row * column, 0)
{
    auto copyPlace = mat.begin();
    for (auto &rowInArray : initArray)
        copyPlace = copy(rowInArray.begin(), rowInArray.end(), copyPlace);
}

Matrix::Matrix(size_t row, size_t column)
    :row(row), column(column), mat(row * column, 0)
{

}

Matrix::Matrix(const Matrix &origin)
    :row(origin.row), column(origin.column),
      mat(origin.mat)
{

}

double &Matrix::operator()(int i, int j)
{
    assert(i < row);
    assert(j < column);

    return mat[i * row + j];
}

double Matrix::operator()(int i, int j) const
{
    assert(i < row);
    assert(j < column);

    return mat[i * row + j];
}
Matrix Matrix::operator+(const Matrix &rhs) const
{
    assert(row == rhs.row);
    assert(column == rhs.column);
    Matrix result(row, column);
    transform(mat.begin(), mat.end(), rhs.mat.begin(), result.mat.begin(),
              [](const double lhs, const double rhs) {return lhs + rhs;});

    return result;
}

Matrix Matrix::operator-(const Matrix &rhs) const
{
    assert(row == rhs.row);
    assert(column == rhs.column);
    Matrix result(row, column);
    transform(mat.begin(), mat.end(), rhs.mat.begin(), result.mat.begin(),
              [](const double lhs, const double rhs)->double {return lhs - rhs;});

    return result;
}

Matrix Matrix::operator*(const Matrix &rhs) const
{
    assert(column == rhs.row);
    Matrix result(row, rhs.column);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j)
            for (int k = 0; k < column; ++k)
                result(i, j) += this->operator ()(i, k) * rhs(k, j);
     }

    return result;
}

Matrix Matrix::operator*(const double c) const
{
    Matrix result(row, column);
    transform(mat.begin(), mat.end(), result.mat.begin(),
              [c](const double unitInVector) {return c * unitInVector;});
    return result;
}
//void Matrix::reverse()
//{
//    auto sizeTmp = row;
//    row = column;
//    column = sizeTmp;
//}


Matrix operator*(const double c, const Matrix &lhs)
{
    Matrix result(lhs * c);
    return result;
}

ostream &operator<<(ostream &out, Matrix &m)
{
    for (int i = 0; i < m.rowSize(); ++i) {
        for (int j = 0; j < m.columnSize(); ++j)
            out << m(i, j) << '\t';
        out << endl;
    }
    return out;
}
