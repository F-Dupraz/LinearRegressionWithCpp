#include <iostream>

#include "LinearRegressionClass.h"

template <typename num>
LinearRegression<num>::~LinearRegression() {
    std::cout << std::endl;
}

template <typename num>
num LinearRegression<num>::meanFinder(const std::vector<num>& findMean) {
    if (findMean.empty()) {
        std::cerr << "Error: The vector was empty." << std::endl;
        // Devuelve un valor representativo en caso de error
        return std::numeric_limits<num>::quiet_NaN();
    }

    num accumulativeSum = 0;
    for (const auto& value : findMean) {
        accumulativeSum += value;
    }

    num meanSum = accumulativeSum / static_cast<num>(findMean.size());
    return meanSum;
}

template <typename num>
void LinearRegression<num>::calculateSlope(const std::vector<num>& xValues, const std::vector<num>& yValues, const num& xMean, const num& yMean) {
    num accumulativeNumeratorSum = 0;
    num accumulativeDenominatorSum = 0;

    for (size_t i = 0; i < xValues.size(); i++) {
        accumulativeNumeratorSum += (xValues[i] - xMean) * (yValues[i] - yMean);
        accumulativeDenominatorSum += (xValues[i] - xMean) * (xValues[i] - xMean);
    }

    // Avoid division by zero
    if (accumulativeDenominatorSum == 0) {
        std::cout << "Error: Division by zero in slope calculation." << std::endl;
    }

    this->slope = accumulativeNumeratorSum / accumulativeDenominatorSum;
}

template <typename num>
void LinearRegression<num>::calculateIntercept(const num& xMean, const num& yMean) {
    this->intercept = yMean - this->slope * xMean;
}

template <typename num>
void LinearRegression<num>::calculateR2(const std::vector<num>& xValues, const std::vector<num>& yValues, const num& yMean) {
    // Calculate predicted Y values
    std::vector<num> predictedY;
    for (const auto& x : xValues) {
        predictedY.push_back(this->slope * x + this->intercept);
    }

    // Calculate total sum of squares
    num totalSumSquares = 0;
    for (const auto& y : yValues) {
        totalSumSquares += (y - yMean) * (y - yMean);
    }

    // Calculate residual sum of squares
    num residualSumSquares = 0;
    for (size_t i = 0; i < yValues.size(); i++) {
        residualSumSquares += (yValues[i] - predictedY[i]) * (yValues[i] - predictedY[i]);
    }

    // Calculate R^2
    this->R2 = 1 - (residualSumSquares / totalSumSquares);
}


template <typename num>
num LinearRegression<num>::fit(const std::vector<num>& xValues, const std::vector<num>& yValues) {
    if (xValues.empty() || yValues.empty()) {
        std::cerr << "Error: One or both vectors are empty." << std::endl;
        // Devuelve un valor representativo en caso de error
        return std::numeric_limits<num>::quiet_NaN();
    }

    num xMean = this->meanFinder(xValues);
    num yMean = this->meanFinder(yValues);

    if (std::isnan(xMean) || std::isnan(yMean)) {
        std::cerr << "Error: Mean calculation failed." << std::endl;
        // Devuelve un valor representativo en caso de error
        return std::numeric_limits<num>::quiet_NaN();
    }

    this->calculateSlope(xValues, yValues, xMean, yMean);
    this->calculateIntercept(xMean, yMean);
    this->calculateR2(xValues, yValues, yMean);

    // Devuelve algún valor representativo de éxito
    return 1;
}
