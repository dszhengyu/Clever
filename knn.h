#ifndef KNN_H
#define KNN_H

#include "matrix.h"
#include "kdtree.h"

class KNN
{
public:
    explicit KNN(int k, KdTree::distanceFuncType distanceFunc = L1());
    void train(Matrix X, Matrix y);
    Matrix predict(Matrix X);
private:
    int k;
    KdTree tree;
};

#endif // KNN_H
