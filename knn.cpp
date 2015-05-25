#include "knn.h"

KNN::KNN(int neighbour, KdTree::distanceFuncType distanceFunc)
    :neighbour(neighbour), tree(neighbour, distanceFunc)
{
}

void KNN::train(const Matrix &X, const Matrix &y)
{
    tree.formTree(X, y);
}
