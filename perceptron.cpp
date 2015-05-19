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

    if (algorithmUse == Algorithm::Origin) {
        //add intercept, column of ones
        Matrix Xtrain(X.rowSize(), 1, 1);
        Xtrain.merge(X, 1, true);
        default_random_engine randomEngin;
        uniform_int_distribution<Matrix::size_type> uniDistri(0, Xtrain.rowSize() - 1);

        weight = Matrix(Xtrain.columnSize(), 1, 0);
        for (int i = 0; i < iterationMax; ++i) {
            auto xTrainIndex = uniDistri(randomEngin);
            auto xSingle = Xtrain.splice(xTrainIndex, xTrainIndex + 1, 0);
            auto ySingle = y(xTrainIndex, 0);
            double yPredictSingle = xSingle.reverse().innerProduct(weight) * ySingle;
            if (yPredictSingle <= 0) {
                Matrix delta = learningRate * ySingle * xSingle;
                delta.reverse(true);
                weight = weight + delta;
            }
        }

    }
    else {
        Matrix Xtrain(X);
        default_random_engine randomEngin;
        uniform_int_distribution<Matrix::size_type> uniDistri(0, Xtrain.rowSize() - 1);

        Matrix alpha = Matrix(Xtrain.rowSize(), 1);
        double b = 0;
        Matrix Gram = Xtrain * Xtrain.reverse();
        for (int i = 0; i < iterationMax; ++i) {
            auto xTrainIndex = uniDistri(randomEngin);
            auto xSingleGram = Gram.splice(xTrainIndex, xTrainIndex + 1, 1);
            auto ySingle = y(xTrainIndex, 0);
            double yPredictSingle = (alpha.dotProduct(y).innerProduct(xSingleGram) + b) * ySingle;
            if (yPredictSingle <= 0) {
                alpha(xTrainIndex, 0) = alpha(xTrainIndex, 0) = 1;
                b = b + learningRate * ySingle;
            }
        }
        auto weightLast = alpha.dotProduct(y).reverse() * Xtrain;
        weight = Matrix(1, 1, b);
        weight.merge(weightLast.reverse(), 0, true);
    }
}

Matrix Perceptron::predict(const Matrix &X) const
{ 
    Matrix Xtrain(X.rowSize(), 1, 1);
    Xtrain.merge(X, 1, true);
    assert(Xtrain.columnSize() == weight.rowSize());
    Matrix yPredict = Xtrain * weight;
    yPredict.sign(true);
    return yPredict;
}

Matrix Perceptron::getWeight() const
{
    return weight;

}
