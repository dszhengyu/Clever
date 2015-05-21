#include "kdtree.h"

KdTree::KdTree(distanceFuncType distanceFunction)
    :tree(new treeNode), distanceFunction(distanceFunction)
{
}

void KdTree::formTree(const Matrix &X, const Matrix &y)
{

}
