#include "naivebayes.h"

NaiveBayes::NaiveBayes(int lambda)
    :lambda(lambda)
{

}

NaiveBayes::~NaiveBayes()
{

}

void NaiveBayes::train(const Matrix &X, const Matrix &y)
{
    // clear last data
    labelDistinct.clear();
    attributeUniqueNumber.clear();
    labelProbability.clear();
    attributeProbability.clear();

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
    double yDistinct = static_cast<double>(y.distinctColumn()[0].size());
    for (auto yEach : labelDistinct) {
        auto range = equal_range(labels.begin(), labels.end(), yEach);
        auto yCount = range.second - range.first;
        labelProbability[yEach] = (yCount + lambda) / (static_cast<double>(N) + yDistinct * lambda);
#ifdef DEBUG
        cout << "y = " << yEach << " ";
        cout << "labelPro = " << labelProbability[yEach] << endl;
#endif
    }

    // calculate distinct number of attribute in each column
    vector<vector<double>> distinctAttribute = X.distinctColumn();
    attributeUniqueNumber.resize(X.columnSize());
    transform(distinctAttribute.begin(), distinctAttribute.end(), attributeUniqueNumber.begin(),
              [](const vector<double> &distinctUnit) {return distinctUnit.size();});
#ifdef DEBUG
    for (auto &distinctNumber : attributeUniqueNumber)
        cout << distinctNumber << '\t';
    cout << endl;
#endif

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
                attributeProbability[yEach][i][attributeEach] =
                        (xCount + lambda) / (static_cast<double>(xWithSameY) + attributeUniqueNumber[i] * lambda);
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
                double Sj = attributeUniqueNumber[j];
                auto &proMap = attributeProbability[label][j];
                if (proMap.find(attribute) == proMap.end()) {
                    PxSingle = 1 / Sj;
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
