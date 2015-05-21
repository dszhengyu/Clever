#ifndef KDTREE_H
#define KDTREE_H

#include <memory>
#include <functional>

#include "matrix.h"

using std::shared_ptr;
using std::function;

class L1
{
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

    explicit KdTree(distanceFuncType distanceFunction);
    void formTree(const Matrix &X, const Matrix &y);
    Matrix search(const Matrix &X);
private:
    shared_ptr<treeNode> tree;
    distanceFuncType distanceFunction;
};

#endif // KDTREE_H
