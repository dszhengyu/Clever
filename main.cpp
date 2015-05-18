#include <iostream>

#include "matrix.h"
#include "perceptron.h"

using std::cout;
using std::endl;

void MatrixUnitTest();
void PerceptronUnitTest();

int main()
{
    MatrixUnitTest();
    PerceptronUnitTest();
    return 0;
}

void PerceptronUnitTest()
{
    Matrix X{{1, 1}, {3, 3}, {4, 3}};
    Matrix y{{-1}, {1}, {1}};
    cout << "X" << endl << X << endl;
    Matrix Xtrain(X.rowSize(), 1, 1);
    Xtrain.merge(X, 1, true);
    cout << "Xtrain" << endl << Xtrain << endl;
    cout << "y" << endl << y << endl;

    Perceptron percetronModel(1, 100);
    percetronModel.train(X, y);
    auto weight = percetronModel.getWeight();
    cout << "weight" << endl << weight << endl;

    auto yPredict = percetronModel.predict(X);
    cout << "yPredict" << endl << yPredict << endl;

}

void MatrixUnitTest()
{
    Matrix m{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "m" << endl << m << endl;

    m(1, 1) = 99;
    cout << "m" << endl << m << endl;

    Matrix n{{0, 0, 0}, {1, 1, 1}, {2, 2, 2}};
    cout << "n" << endl << n << endl;

    auto plus = m + n;
    cout << "plus" << endl << plus << endl;

    auto minus = m - n;
    cout << "minus" << endl << minus << endl;

    auto mutipleWithConstRight = n * 4;
    cout << "mutipleWithConstRight" << endl << mutipleWithConstRight << endl;

    auto mutipleWithConstLeft = 4 * n;
    cout << "mutipleWithConstLeft" << endl << mutipleWithConstLeft << endl;

    m = Matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "m" << endl << m << endl;

    n = Matrix{{0, 0, 0}, {1, 1, 1}, {2, 2, 2}};
    cout << "n" << endl << n << endl;

    auto mutipleWithMatrix = m * n;
    cout << "mutipleWithMatrix" << endl << mutipleWithMatrix << endl;

    m.merge(n, 1, true);
    cout << "mMergeNAxis1Inplace" << endl << m << endl;

    auto mMergeMAxis0 = m.merge(m, 0, true);
    cout << "mMergeMAxis0" << endl << mMergeMAxis0 << endl;

    cout << "equal test" << endl;
    cout << "m == n" << '\t' << (m == n) << endl;
    cout << "m == m" << '\t' << (m == m) << endl;

    cout << "m" << endl << m << endl;
    m.splice(1, 2, 1, true);
    cout << "m after splice" << endl << m << endl;

    m.merge(m, 1, true);
    cout << "m merge self" << endl << m << endl;

    auto mSpliceAxis0 = m.splice(2, m.rowSize(), 0);
    cout << "mSpliceAxis0" << endl << mSpliceAxis0 << endl;

    m = Matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "m" << endl << m << endl;

    n = Matrix{{0, 0, 0}, {1, 1, 1}, {2, 2, 2}};
    cout << "n" << endl << n << endl;

    auto dotProductExample = Matrix::dotProduct(m, n);
    cout << "dotProductExample" << endl << dotProductExample << endl;

    cout << "m" << endl << m << endl;
    auto mReverse = m.reverse();
    cout << "mReverse" << endl << mReverse << endl;

    m = Matrix{{1, 2, 3}};
    cout << "m" << endl << m << endl;

    n = Matrix{{4}, {5}, {6}};
    cout << "n" << endl << n << endl;

    double innerProductExample = m.innerProduct(n);
    cout << "innerProductExample" << endl << innerProductExample << endl;
    cout << endl;

    m = Matrix{{-1, 1, -10, -100, 3}};
    cout << "m" << endl << m << endl;

    auto mSign = Matrix::sign(m);
    cout << "mSign" << endl << mSign << endl;
}
