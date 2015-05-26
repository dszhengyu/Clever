#include "knn.h"

KNN::KNN(int neighbour, KdTree::distanceFuncType distanceFunc)
    :neighbour(neighbour), tree(distanceFunc)
{
}

void KNN::train(const Matrix &X, const Matrix &y)
{
    tree.formTree(X, y);
}

Matrix KNN::predict(const Matrix &X)
{
    return tree.search(neighbour, X);
}
