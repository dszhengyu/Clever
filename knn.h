#ifndef KNN_H
#define KNN_H


#include "matrix.h"
#include "kdtree.h"

class KNN
{
public:
    explicit KNN(int neighbour, KdTree::distanceFuncType distanceFunc = L1());
    void train(const Matrix &X, const Matrix &y);
    Matrix predict(const Matrix &X);
private:
    int neighbour;
    KdTree tree;
};

#endif // KNN_H
