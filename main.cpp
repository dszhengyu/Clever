#include <iostream>

#include "matrix.h"
#include "perceptron.h"
#include "knn.h"

using std::cout;
using std::endl;

void MatrixUnitTest();
void PerceptronUnitTest();
void KnnUnitTest();

int main()
{
    KnnUnitTest();
    return 0;
}

void KnnUnitTest()
{
    Matrix X{{4, 4}, {3, 2}, {7, 3}, {1, 1}, {2, 5}, {6, 6}};
    Matrix y{{1},    {-1},   {1},    {1},    {-1},   {1}};
    cout << "X" << endl << X << endl;
    cout << "y" << endl << y << endl;

    KNN knnModel(1);
    knnModel.train(X, y);
}

void PerceptronUnitTest()
{
    Matrix X{{3, 3}, {4, 3}, {1, 1}};
    Matrix y{{1}, {1}, {-1}};
    cout << "X" << endl << X << endl;
    cout << "y" << endl << y << endl;

    // Origin algorithm
    Perceptron percetronModel(1, 100);
    percetronModel.train(X, y);
    auto weight = percetronModel.getWeight();
    cout << "weight" << endl << weight << endl;

    auto yPredict = percetronModel.predict(X);
    cout << "yPredict" << endl << yPredict << endl;

    // Parallelism algorithm
    Perceptron percetronModel2(1, 100, Perceptron::Parallelism);
    percetronModel2.train(X, y);
    weight = percetronModel2.getWeight();
    cout << "weight" << endl <<weight << endl;

    yPredict = percetronModel2.predict(X);
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

    cout << "m" << endl << m << endl;
    auto mReverse = m.reverse();
    cout << "mReverse" << endl << mReverse << endl;

    m = Matrix{{1, 2, 3}};
    cout << "m" << endl << m << endl;

    n = Matrix{{4, 5, 6}};
    cout << "n" << endl << n << endl;

    double innerProductExample = m.innerProduct(n);
    cout << "innerProductExample" << endl << innerProductExample << endl;
    cout << endl;

    m = Matrix{{-1, 1, -10, -100, 3}};
    cout << "m" << endl << m << endl;

    auto mSign = m.sign();
    cout << "mSign" << endl << mSign << endl;

    n = Matrix{{4}, {5}, {6}};
    cout << "n" << endl << n << endl;
    auto k = n * n.reverse();
    cout << "k" << endl << k << endl;

    m = Matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "m" << endl << m << endl;

    n = Matrix{{0, 0, 0}, {1, 1, 1}, {2, 2, 2}};
    cout << "n" << endl << n << endl;

    auto dotProductExample = m.dotProduct(n);
    cout << "dotProductExample" << endl << dotProductExample << endl;

    m = Matrix{{1, -2, 3}, {4, -5, 6}, {7, -8, 9}};
    cout << "m" << endl << m << endl;

    m.abs(true);
    cout << "mAbs" << endl << m << endl;

    m = Matrix{{1, -2, 3}, {4, -5, 6}, {7, -8, 9}};
    cout << "m" << endl << m << endl;

    m.square(true);
    cout << "mSquare" << endl << m << endl;

    m = Matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "m" << endl << m << endl;

    auto mSum = m.sum();
    cout << "mSum" << endl << mSum << endl << endl;

    m = Matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cout << "m" << endl << m << endl;

    auto mMax = m.max();
    cout << "mMax" << endl << mMax << endl << endl;

    cout << "m" << endl << m << endl;
    auto mVec = m.splictRow();
    for (auto &unit : mVec)
        cout << "row: " << unit;


}
