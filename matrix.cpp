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

Matrix::Matrix(size_t row, size_t column, double initNum)
    :row(row), column(column), mat(row * column, initNum)
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

    return mat[i * column + j];
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
    for (int i = 0; i < result.row; ++i) {
        for (int j = 0; j < result.column; ++j)
            for (int k = 0; k < this->column; ++k)
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

double Matrix::innerProduct(const Matrix &rhs)
{
    assert(this->row == 1 || this->column == 1);
    assert(this->row == rhs.row && this->column == rhs.column);

    double sum = inner_product(this->mat.begin(), this->mat.end(),
                              rhs.mat.begin(), 0.0);
    return sum;
}

Matrix Matrix::merge(const Matrix &rhs, int axis, bool inplace)
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
    const Matrix *rhsPtr = nullptr;
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

    result->mat.reserve(row * column + rhsPtr->row * rhsPtr->column);
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

Matrix Matrix::merge(const Matrix &rhs, int axis) const
{
    return const_cast<Matrix *>(this)->merge(rhs, axis, false);
}
Matrix Matrix::splice(size_t start, size_t end, int axis, bool inplace)
{
    // assert base condition
    assert(axis == 0 || axis == 1);
    assert(start >= 0 && start < end);
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

Matrix Matrix::splice(size_t start, size_t end, int axis) const
{
    Matrix *matrixPtr = const_cast<Matrix *>(this);
    return matrixPtr->splice(start, end, axis, false);
}

Matrix Matrix::reverse(bool inplace)
{
    Matrix result(this->column, this->row);
    for (decltype(result.row) i = 0; i < result.row; ++i) {
        for (decltype(result.row) j = 0; j < result.column; ++j) {
            result(i, j) = this->operator ()(j, i);
        }
    }

    if (inplace) {
        *this = result;
        return Matrix();
    }
    else
        return result;
}

Matrix Matrix::reverse() const
{
    Matrix result = const_cast<Matrix *>(this)->reverse(false);
    return result;
}

Matrix Matrix::dotProduct(const Matrix &rhs)
{
    assert(this->row== rhs.row);
    assert(this->column == rhs.column);

    Matrix result(this->row, this->column);
    transform(this->mat.begin(), this->mat.end(), rhs.mat.begin(), result.mat.begin(),
              [](double left, double right) {return left * right;});
    return result;
}

Matrix Matrix::sign(bool inplace)
{
    Matrix result(*this);
    for_each(result.mat.begin(), result.mat.end(), [](double &unit) {unit = unit > 0 ? 1 : -1;});

    if (inplace) {
        *this = result;
        return Matrix();
    }
    else
        return result;
}

Matrix Matrix::abs(bool inplace)
{
    Matrix result(*this);
    for_each(result.mat.begin(), result.mat.end(), [](double &unit) {unit = unit > 0 ? unit : -unit;});

    if (inplace) {
        *this = result;
        return Matrix();
    }
    else
        return result;
}
Matrix Matrix::square(bool inplace)
{
    Matrix result(*this);
    for_each(result.mat.begin(), result.mat.end(), [](double &unit) {unit = unit * unit;});

    if (inplace) {
        *this = result;
        return Matrix();
    }
    else
        return result;
}

double Matrix::sum()
{
    double sum = accumulate(mat.begin(), mat.end(), 0.0);
    return sum;
}

double Matrix::max()
{
    double max = 0;
    for_each(mat.begin(), mat.end(),
             [&](double current) {max = max > current ? max : current;});
    return max;
}

vector<Matrix> Matrix::splictRow() const
{
    vector<Matrix> matrixVec(this->row);
    for (decltype(this->row) i = 0; i < this->row; ++i) {
        matrixVec[i] = this->splice(i, i + 1, 0);
    }
    return matrixVec;
}

double Matrix::toDouble() const
{
    assert(row == 1 && column == 1);
    return mat[0];
}

vector<vector<double>> Matrix::distinctColumn() const
{
    vector<vector<double>> result(column);
    for (size_type i = 0; i < column; ++i) {
        set<double> distinct;
        for (size_type j = 0; j < row; ++j) {
            distinct.insert(this->operator ()(j, i));
        }
        result[i].assign(distinct.begin(), distinct.end());
    }
    return result;
}

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

ostream &operator<<(ostream &out, vector<vector<double>> vV)
{
    for (auto &v : vV) {
        for (auto cell : v)
            out << cell << '\t';
        out << endl;
    }
    return out;
}
