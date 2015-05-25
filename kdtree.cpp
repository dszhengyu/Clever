#include "kdtree.h"

KdTree::KdTree(int neighbour, distanceFuncType distanceFunction)
    :neighbour(neighbour), tree(), distanceFunction(distanceFunction)
{
}

void KdTree::formTree(const Matrix &X, const Matrix &y)
{  
    vector<Matrix> trainSet = X.merge(y, 1).splictRow();
    k = X.columnSize();

    int curDepth = 0;
    treePtr parentOfRoot(nullptr);
    tree = createNode(trainSet, curDepth, parentOfRoot);
    printTree();
}

KdTree::treePtr KdTree::createNode(vector<Matrix> &trainSet, int curDepth, treePtr parent)
{
    if (trainSet.size() <=0) {
        return nullptr;
    }

    int split = curDepth % k + 1;

    treePtr node(new treeNode);
    node->parent = parent;
    node->split = split;

    sort(trainSet.begin(), trainSet.end(), [split](Matrix &lhs, Matrix &rhs) {return lhs(0, split) < rhs(0, split);});
    Matrix dataCur = trainSet[trainSet.size() / 2];
    trainSet.erase(trainSet.begin() + trainSet.size() / 2);
    vector<Matrix> leftSet(trainSet.begin(), trainSet.begin() + trainSet.size() / 2);
    vector<Matrix> rightSet(trainSet.begin() + trainSet.size() / 2, trainSet.end());

    node->data = dataCur.splice(0, dataCur.columnSize() - 1, 1);
    node->label = dataCur(0, dataCur.columnSize() - 1);

    int childDepth = curDepth + 1;
    node->left = createNode(leftSet, childDepth, node);
    node->right = createNode(rightSet, childDepth, node);

    return node;
}

void KdTree::printTree(ostream & out) const
{
    deque<treePtr> q1;
    q1.push_back(tree);
    deque<treePtr> q2;
    while (!q1.empty() || !q2.empty()) {
        if (!q1.empty()) {
            for (treePtr node : q1) {
                if (node->left != nullptr)
                    q2.push_back(node->left);
                if (node->right != nullptr)
                    q2.push_back(node->right);
                out << node->data;
            }
            out << endl;
            q1.clear();
        }
        else {
            for (treePtr node : q2) {
                if (node->left != nullptr)
                    q1.push_back(node->left);
                if (node->right != nullptr)
                    q1.push_back(node->right);
                out << node->data;
            }
            out << endl;
            q2.clear();
        }
    }
}
