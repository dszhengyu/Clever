#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <random>
#include "matrix.h"

using std::default_random_engine;
using std::uniform_int_distribution;

class Perceptron
{
    enum Algorithm
    {
        Origin,
        Parallelism
    };
public:
    explicit Perceptron(double learningRate, int iterationMax,
                        Algorithm algorithmUse = Algorithm::Origin);
    void train(const Matrix &X, const Matrix &y);
    Matrix predict(const Matrix &X) const;
    Matrix getWeight() const;
private:
    double learningRate;
    int iterationMax;
    Algorithm algorithmUse;
    Matrix weight;
    Matrix alpha;
};

#endif // PERCEPTRON_H
