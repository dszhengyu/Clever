#include "knn.h"

KNN::KNN(int k, KdTree::distanceFuncType distanceFunc)
    :k(k), tree(distanceFunc)
{
}
