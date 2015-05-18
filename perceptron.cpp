#include "perceptron.h"

Perceptron::Perceptron(double learningRate, int iterationMax,
                       Algorithm algorithmUse)
    :learningRate(learningRate),
      iterationMax(iterationMax),
      algorithmUse(algorithmUse)
{
}

void Perceptron::train(const Matrix &X, const Matrix &y)
{
    // basic condition
    assert(X.rowSize() > 0);
    assert(X.rowSize() == y.rowSize());
    assert(X.columnSize() > 0);

    //add intercept, column of ones
    Matrix Xtrain(X.rowSize(), 1, 1);
    Xtrain.merge(X, 1, true);

    default_random_engine randomEngin;
    uniform_int_distribution<Matrix::size_type> uniDistri(0, Xtrain.rowSize() - 1);

    if (algorithmUse == Algorithm::Origin) {
        weight = Matrix(Xtrain.columnSize(), 1, 0);
        for (int i = 0; i < iterationMax; ++i) {
            auto xTrainIndex = uniDistri(randomEngin);
            auto xSingle = Xtrain.splice(xTrainIndex, xTrainIndex + 1, 0);
            auto ySingle = y(xTrainIndex, 0);
            double yPredictSingle = xSingle.innerProduct(weight) * ySingle;
            if (yPredictSingle <= 0) {
                Matrix delta = learningRate * ySingle * xSingle;
                delta.reverse(true);
                weight = weight + delta;
            }
        }

    }
    else {
        alpha = Matrix(Xtrain.columnSize(), 1);

    }
}

Matrix Perceptron::predict(const Matrix &X) const
{
    Matrix Xtrain(X.rowSize(), 1, 1);
    Xtrain.merge(X, 1, true);

    if (algorithmUse == Algorithm::Origin) {
        assert(Xtrain.columnSize() == weight.rowSize());
        Matrix yPredict = Xtrain * weight;
        Matrix yPredictSign = Matrix::sign(yPredict);
        return yPredictSign;
    }
    else {

    }
}

Matrix Perceptron::getWeight() const
{
    if (algorithmUse == Algorithm::Origin)
        return weight;
    else
        return alpha;
}
