#ifndef KDTREE_H
#define KDTREE_H

//#define DEBUG

#include <memory>
#include <functional>
#include <algorithm>
#include <deque>
#include <iostream>
#include <stack>
#include <set>
#include <cmath>

#include "matrix.h"

using std::shared_ptr;
using std::function;
using std::sort;
using std::deque;
using std::stack;
using std::set;
using std::ostream;
using std::endl;

class L1
{
public:
    double operator() (const Matrix& lhs, const Matrix &rhs)
    {
        assert(lhs.rowSize() == 1);
        assert(lhs.rowSize() == rhs.rowSize());
        assert(lhs.columnSize() == rhs.columnSize());
        Matrix result = lhs - rhs;
        result.abs(true);
        return result.sum();
    }
};

class L2
{
public:
    double operator() (const Matrix& lhs, const Matrix &rhs)
    {
        assert(lhs.rowSize() == 1);
        assert(lhs.rowSize() == rhs.rowSize());
        assert(lhs.columnSize() == rhs.columnSize());
        Matrix result = lhs - rhs;
        result.square(true);
        return result.sum();
    }
};

class LInfinite
{
public:
    double operator() (const Matrix& lhs, const Matrix &rhs)
    {
        assert(lhs.rowSize() == 1);
        assert(lhs.rowSize() == rhs.rowSize());
        assert(lhs.columnSize() == rhs.columnSize());
        Matrix result = lhs - rhs;
        result.abs(true);
        return result.max();
    }
};

typedef struct treeNode
{
    Matrix data;
    double label;
    int split;
    shared_ptr<treeNode> parent;
    shared_ptr<treeNode> left;
    shared_ptr<treeNode> right;
}treeNode;

class KdTree
{
public:
    typedef function<double(const Matrix&, const Matrix &)> distanceFuncType;
    typedef shared_ptr<treeNode> treePtr;
    explicit KdTree(distanceFuncType distanceFunction);
    void formTree(const Matrix &X, const Matrix &y);
    Matrix search(int neighbour, const Matrix &X);
private:
    treePtr createNode(vector<Matrix> &trainSet, int curDepth, treePtr parent);
    void printTree(std::ostream &out = cout) const;
    Matrix::size_type k;
    treePtr tree;
    distanceFuncType distanceFunction;
};


#endif // KDTREE_H
