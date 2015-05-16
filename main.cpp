#include <iostream>

#include "matrix.h"

using std::cout;
using std::endl;

int main()
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

    //    m.reverse();
    //    cout << m << endl;

    return 0;
}

