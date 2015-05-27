#ifndef NAIVEBAYES_H
#define NAIVEBAYES_H

#define DEBUG

#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <algorithm>
#include <utility>
#include <iostream>


#include "matrix.h"

using std::vector;
using std::map;
using std::set;
using std::back_inserter;
using std::unique_copy;
using std::sort;
using std::equal_range;
using std::partition;
using std::nth_element;
using std::pair;
using std::ostream;
using std::cout;
using std::end;

class NaiveBayes
{
public:
    NaiveBayes();
    ~NaiveBayes();
    void train(const Matrix &X, const Matrix &y);
    Matrix predict(const Matrix &X);
private:
    vector<double> labelDistinct;
    map<double, double> labelProbability;
    map<double, vector<map<double, double>>> attributeProbability;
};

#endif // NAIVEBAYES_H
