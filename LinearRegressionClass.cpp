#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>

#include "LinearRegressionClass.h"

template <typename num>
LinearRegression<num>::~LinearRegression() {}

template <typename num>
num LinearRegression<num>::fit(const std::vector<std::vector<num>>& xValues, const std::vector<num>& yValues) {
    if (xValues.empty() || yValues.empty()) {
        std::cerr << "Error: One or both vectors are empty." << std::endl;
        return std::numeric_limits<num>::quiet_NaN();
    }

    size_t numCoefficients = xValues.size() + 1;  // Include the intercept
    coefficients.resize(numCoefficients, 0);

    std::vector<num> xMeans(numCoefficients, 0);
    calculateMeans(xValues, xMeans);

    for (size_t j = 0; j < numCoefficients; ++j) {
        num accumulativeNumeratorSum = 0;
        num accumulativeDenominatorSum = 0;

        for (size_t i = 0; i < xValues.size(); ++i) {
            num xValue = (j == 0) ? 1 : xValues[i][j - 1];  // Intercept or Xj
            accumulativeNumeratorSum += (xValue - xMeans[j]) * (yValues[i] - meanFinder(yValues));
            accumulativeDenominatorSum += (xValue - xMeans[j]) * (xValue - xMeans[j]);
        }

        // Avoid division by zero
        if (accumulativeDenominatorSum == 0) {
            std::cerr << "Error: Division by zero in coefficient calculation." << std::endl;
            return std::numeric_limits<num>::quiet_NaN();
        }

        coefficients[j] = accumulativeNumeratorSum / accumulativeDenominatorSum;
    }

    calculateIntercept(xMeans);

    return 1;
}

template <typename num>
num LinearRegression<num>::predict(const std::vector<num>& xValues) const {
    if (xValues.size() != coefficients.size() - 1) {
        std::cerr << "Error: Incorrect number of features for prediction." << std::endl;
        return std::numeric_limits<num>::quiet_NaN();
    }

    num result = coefficients[0];  // Intercept

    for (size_t j = 1; j < coefficients.size(); ++j) {
        result += coefficients[j] * xValues[j - 1];
    }

    return result;
}

template <typename num>
num LinearRegression<num>::getSlope() const {
    return coefficients[1];  // Assuming simple linear regression with one feature
}

template <typename num>
num LinearRegression<num>::getIntercept() const {
    return coefficients[0];  // Assuming simple linear regression with one feature
}

template <typename num>
num LinearRegression<num>::meanFinder(const std::vector<num>& findMean) const {
    if (findMean.empty()) {
        std::cerr << "Error: The vector was empty." << std::endl;
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
void LinearRegression<num>::calculateMeans(const std::vector<std::vector<num>>& xValues, std::vector<num>& means) const {
    for (size_t i = 0; i < xValues.size(); ++i) {
        num accumulatedMeans = 0;
        for (size_t j = 0; j < xValues[i].size(); ++j) {
            if (j < xValues[i].size()) {
                accumulatedMeans += xValues[i][j];
            }
            else {
                std::cerr << "Warning: Column index out of range for row " << i << std::endl;
            }
        }
        means[i] = accumulatedMeans / means.size();
    }
}

template <typename num>
void LinearRegression<num>::calculateIntercept(const std::vector<num>& xMeans) {
    coefficients[0] = meanFinder(xMeans);
    for (size_t j = 1; j < coefficients.size(); ++j) {
        coefficients[0] -= coefficients[j] * xMeans[j - 1];
    }

    this->intercept = coefficients[0];
}
