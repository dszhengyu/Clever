#include "matrix.h"

Matrix::Matrix()
    :row(0), column(0), mat()
{

}

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

double &Matrix::operator()(size_t i, size_t j)
{
    assert(i < row);
    assert(j < column);

    return mat[i * column + j];
}

double Matrix::operator()(size_t i, size_t j) const
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

bool Matrix::operator==(const Matrix &rhs) const
{
    bool rowEqual = (row == rhs.row);
    bool columnEqual = (column == rhs.column);
    bool matEqual = (mat == rhs.mat);
    return rowEqual && columnEqual && matEqual;
}

Matrix Matrix::merge(Matrix &rhs, int axis, bool inplace)
{
    // check the limit condition
    assert(axis == 0 || axis == 1);
    if (axis == 1) {
        assert(row == rhs.row);
    }
    else {
        assert(column == rhs.column);
    }

    // Matrix merge it self inplace
    Matrix rhsCopy(0, 0);
    Matrix *rhsPtr = nullptr;
    if (this == &rhs && inplace) {
        rhsCopy = rhs;
        rhsPtr = &rhsCopy;
    }
    else {
        rhsPtr = &rhs;
    }

    // inplace? initialize result matrix
    Matrix copyMatrix(0, 0);
    Matrix *result = nullptr;
    if (inplace)
        result = this;
    else {
        copyMatrix = *this;
        result = &copyMatrix;
    }

    result->mat.resize(row * column + rhsPtr->row * rhsPtr->column);
    if (axis == 1) {
        result->column += rhsPtr->column;
        int insertPosition = -static_cast<int>(rhsPtr->column);
        for (int i = 0; i < row; ++i) {
            auto sourceStart = rhsPtr->mat.begin() + i * rhsPtr->column;
            auto sourceEnd = sourceStart + rhsPtr->column;
            insertPosition += static_cast<int>(result->column);
            auto destStart = result->mat.begin() + insertPosition;
            result->mat.insert(destStart, sourceStart, sourceEnd);
        }
    }
    else {
        auto sourceStart = rhsPtr->mat.begin();
        auto sourceEnd = rhsPtr->mat.end();
        auto destStart = result->mat.begin() + result->row * result->column;
        result->mat.insert(destStart, sourceStart, sourceEnd);
        result->row += rhsPtr->row;
    }
    if (inplace)
        return Matrix();
    else
        return *result;
}

Matrix Matrix::splice(size_t start, size_t end, int axis, bool inplace)
{
    // assert base condition
    assert(axis == 0 || axis == 1);
    assert(start > 0 && start < end);
    if (axis == 1) {
        assert(end <= column);
    }
    else {
        assert(end <= row);
    }

    // put number in result
    Matrix result;
    if (axis == 1) {
        result.row = row;
        result.column = end - start;
        result.mat.reserve(result.column * result.row);
        for (auto i = start; i < end; ++i) {
            for (decltype(row) j = 0; j < row; ++j) {
                result.mat.insert(result.mat.end(), this->operator ()(j, i));
            }
        }
    }
    else {
        result.row = end - start;
        result.column = column;
        result.mat.reserve(result.column * result.row);
        auto sourceStart = mat.begin() + start * column;
        auto sourceEnd = sourceStart + result.row * column;
        result.mat.insert(result.mat.end(), sourceStart, sourceEnd);
    }

    // inplace ?
    if (inplace) {
        *this = result;
        return Matrix();
    }
    else
        return result;

}

Matrix Matrix::reverse(bool inplace)
{
    assert(this->row == this->column);
    Matrix result(*this);
    for (decltype(result.row) i = 0; i < result.row; ++i) {
        for (auto j = i; j < result.column; ++j) {
            auto tmp = result(i, j);
            result(i, j) = result(j, i);
            result(j, i) = tmp;
        }
    }

    if (inplace) {
        *this = result;
        return Matrix();
    }
    else
        return result;
}

Matrix operator*(const double c, const Matrix &lhs)
{
    Matrix result(lhs * c);
    return result;
}

Matrix dotProduct(const Matrix &lhs, const Matrix &rhs)
{
    assert(lhs.row== rhs.row);
    assert(lhs.column == rhs.column);

    Matrix result(lhs.row, lhs.column);
    transform(lhs.mat.begin(), lhs.mat.end(), rhs.mat.begin(), result.mat.begin(),
              [](double left, double right) {return left * right;});
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
