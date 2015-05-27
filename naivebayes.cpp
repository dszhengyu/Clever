#include "naivebayes.h"

NaiveBayes::NaiveBayes()
{

}

NaiveBayes::~NaiveBayes()
{

}

void NaiveBayes::train(const Matrix &X, const Matrix &y)
{
    // y distinct
    vector<double> labels;
    for (Matrix::size_type i = 0; i < y.rowSize(); ++i) {
        labels.push_back(y(i, 0));
    }
    sort(labels.begin(), labels.end());
    unique_copy(labels.begin(), labels.end(), back_inserter(labelDistinct));

#ifdef DEBUG
    cout << "all labels" << endl;
    for (auto label : labels)
        cout << label << '\t';
    cout << endl;

    cout << "distinct labels" << endl;
    for (auto label : labelDistinct)
        cout << label << '\t';
    cout << endl << endl;
#endif

    // calculate labelPro
    auto N = y.rowSize();
    for (auto yEach : labelDistinct) {
        auto range = equal_range(labels.begin(), labels.end(), yEach);
        auto yCount = range.second - range.first;
        labelProbability[yEach] = yCount / static_cast<double>(N);

#ifdef DEBUG
        cout << "y = " << yEach << " ";
        cout << "labelPro = " << yCount / static_cast<double>(N) << endl;
#endif

    }


    // attributeProbability
    vector<Matrix> trainVec = X.merge(y, 1).splictRow();
    for (auto yEach : labelDistinct) {

#ifdef DEBUG
        cout << "y = " << yEach << endl;
#endif

        attributeProbability[yEach].resize(X.columnSize());
        auto partitionIter = partition(trainVec.begin(), trainVec.end(),
                  [=](const Matrix &m) {return m(0, m.columnSize() - 1) == yEach;});
        auto xWithSameY = partitionIter - trainVec.begin();
        vector<vector<double>> attributes(X.columnSize());
        for (vector<Matrix>::iterator it = trainVec.begin(); it != partitionIter; ++it) {
            for (Matrix::size_type col = 0; col < it->columnSize() - 1; ++col) {
                attributes[col].push_back(it->operator()(0, col));
            }
        }
        for (auto i = 0; i < attributes.size(); ++i) {
            vector<double> columnEach = attributes[i];
            sort(columnEach.begin(), columnEach.end());
            vector<double> columnDistinct;
            unique_copy(columnEach.begin(), columnEach.end(), back_inserter(columnDistinct));
            for (double &attributeEach : columnDistinct) {
                auto range = equal_range(columnEach.begin(), columnEach.end(), attributeEach);
                auto xCount = range.second - range.first;
                attributeProbability[yEach][i][attributeEach] = xCount / static_cast<double>(xWithSameY);
#ifdef DEBUG
                cout << "y = " << yEach << " " << i << "th column ";
                cout << " attribute = " << attributeEach ;
                cout << " attributePro = " << xCount / static_cast<double>(xWithSameY) << endl;
#endif
            }
        }
    }

}

Matrix NaiveBayes::predict(const Matrix &X)
{
#ifdef DEBUG
    cout << endl << "Start predicting..." << endl;
#endif
    Matrix result(X.rowSize(), 1);

    for (auto i = 0; i < X.rowSize(); ++i) {
        vector<pair<double, double>> yAndProb;
        for (auto label : labelDistinct) {
            double Py = labelProbability[label];
#ifdef DEBUG
            cout << endl;
            cout << "label = " << label <<" Py = " << Py << endl;
#endif
            double PxTotal = 1;
            for (auto j = 0; j < X.columnSize(); ++j) {
                double attribute = X(i, j);
                double PxSingle;
                auto &proMap = attributeProbability[label][j];
                if (proMap.find(attribute) == proMap.end()) {
                    PxSingle = 0;
                }
                else {
                    PxSingle = proMap[attribute];
                }
                PxTotal *= PxSingle;
#ifdef DEBUG
                cout << "attribute = " << attribute;
                cout << " PxSingle = " << PxSingle ;
                cout << endl;
#endif
            }
            yAndProb.push_back({label, PxTotal * Py});
        }
        nth_element(yAndProb.begin(), yAndProb.begin(), yAndProb.end(),
             [](const pair<double, double> &lhs, const pair<double, double> &rhs)
             {return lhs.second > rhs.second;});
        result(i, 0) = yAndProb[0].first;
#ifdef DEBUG
        cout << endl;
        for (auto &pairOfYAndProb : yAndProb)
            cout << "label = " << pairOfYAndProb.first << " Prob = " << pairOfYAndProb.second << endl;
#endif
    }

    return result;
}
