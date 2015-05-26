#include "kdtree.h"

KdTree::KdTree(distanceFuncType distanceFunction)
    :tree(), distanceFunction(distanceFunction)
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

Matrix KdTree::search(int neighbour, const Matrix &X)
{
    Matrix predict(X.rowSize(), 1);
    vector<Matrix> xVec(X.splictRow());
    for (auto it = xVec.begin(); it != xVec.end(); ++it){
        Matrix xSingle(*it);
        stack<treePtr> path;
        // 1. down to leaf, push node into path
        treePtr curNode(tree);
        while (curNode != nullptr) {
            path.push(curNode);
            int curSplit = curNode->split;
            if (xSingle(0, curSplit) < curNode->data(0, curSplit)) {
                curNode = curNode->left;
            }
            else {
                curNode = curNode->right;
            }
        }

        vector<treePtr> kNearestNeighbour;
        //should be Inf
        double longestInVec = 655536;
        set<treePtr> nodeWalked;
        // 2. start search, go back according to path, use set to record walked node,
        //      put node into vector, sort every time and pop last one, remember the longest
        //      in the vector
        while (!path.empty()) {
            curNode = path.top();

#ifdef DEBUG
            cout << "debug" << endl;
            cout << curNode->data << endl;
#endif

            path.pop();
            nodeWalked.insert(curNode);
            // insert into vec
            double curDistance = distanceFunction(curNode->data, xSingle);
            if (kNearestNeighbour.size() < neighbour) {
                kNearestNeighbour.push_back(curNode);
            }
            else if (curDistance < longestInVec) {
                kNearestNeighbour[neighbour - 1] = curNode;
                sort(kNearestNeighbour.begin(), kNearestNeighbour.end(),
                     [=](const treePtr &lhs, const treePtr &rhs)
                        {return (distanceFunction(lhs->data, xSingle) < distanceFunction(rhs->data, xSingle));});
                longestInVec = distanceFunction(kNearestNeighbour[neighbour - 1]->data, xSingle);
            }

            int curSplit =  curNode->split;
            double hyperplaneDistance = abs(curNode->data(0,curSplit) - xSingle(0, curSplit));
            if (hyperplaneDistance < longestInVec) {
                if (curNode->left != nullptr && nodeWalked.find(curNode->left) == nodeWalked.end()) {
                    path.push(curNode->left);
                }
                if (curNode->right != nullptr && nodeWalked.find(curNode->right) == nodeWalked.end()) {
                    path.push(curNode->right);
                }
            }
        }

        // 3. calculate the predict label
        vector<double> labelAll;
        labelAll.reserve(kNearestNeighbour.size());
        for (treePtr &node : kNearestNeighbour)
            labelAll.push_back(node->label);
        sort(labelAll.begin(), labelAll.end());

        int numMax = 0;
        double labelMax = labelAll[0];
        int curNum = 0;
        double curLabel = labelAll[0];
        for (auto label : labelAll) {
            if (label == curLabel) {
                ++curNum;
            }
            else {
                if (curNum > numMax) {
                    numMax = curNum;
                    labelMax = curLabel;
                }
                curNum = 1;
                curLabel = label;
            }
        }
        if (curNum > numMax) {
            labelMax = curLabel;
        }

#ifdef DEBUG
        for (auto label : labelAll)
            cout << label << '\t';
        cout << endl;
#endif

        auto indexOfMatrix = it - xVec.begin();
        predict(indexOfMatrix, 0) = labelMax;
    }

    return predict;
}

KdTree::treePtr KdTree::createNode(vector<Matrix> &trainSet, int curDepth, treePtr parent)
{
    if (trainSet.size() <=0) {
        return nullptr;
    }

    int split = curDepth % k;

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
