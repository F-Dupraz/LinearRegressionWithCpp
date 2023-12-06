#include <iostream>

#include "LinearRegressionClass.h"

template <typename num>
num LinearRegression<num>::meanFinder(const std::vector<num>& findMean) {
    if (findMean.empty()) {
        std::cout << "Error: The vector was empty." << std::endl;
        return -1;
    }

    num accumulativeSum = 0;
    for (const auto& value : findMean) {
        accumulativeSum += value;
    }

    num meanSum = accumulativeSum / static_cast<num>(findMean.size());
    return meanSum;
}

template <typename num>
num LinearRegression<num>::calculateSlope(const std::vector<num>& xValues, const std::vector<num>& yValues, const num& xMean, const num& yMean) {
    num accumulativeNumeratorSum = 0;
    num accumulativeDenominatorSum = 0;

    for (size_t i = 0; i < xValues.size(); i++) {
        accumulativeNumeratorSum += (xValues[i] - xMean) * (yValues[i] - yMean);
        accumulativeDenominatorSum += (xValues[i] - xMean) * (xValues[i] - xMean);
    }

    // Avoid division by zero
    if (accumulativeDenominatorSum == 0) {
        std::cout << "Error: Division by zero in slope calculation." << std::endl;
        return -1;
    }

    num slope = accumulativeNumeratorSum / accumulativeDenominatorSum;
    return slope;
}

template <typename num>
num LinearRegression<num>::calculateIntercept(const num& xMean, const num& yMean, const num& slope) {
    num intercept = yMean - slope * xMean;
    return intercept;
}

template <typename num>
num LinearRegression<num>::calculateR2(const std::vector<num>& xValues, const std::vector<num>& yValues, const num& slope, const num& intercept) {
    // Calculate predicted Y values
    std::vector<num> predictedY;
    for (const auto& x : xValues) {
        predictedY.push_back(slope * x + intercept);
    }

    // Calculate mean of observed Y values
    num yMean = meanFinder(yValues);

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
    num rSquared = 1 - (residualSumSquares / totalSumSquares);
    return rSquared;
}
