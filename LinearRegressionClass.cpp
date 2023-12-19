#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>

#include "LinearRegressionClass.h"

template <typename num>
LinearRegression<num>::~LinearRegression() {}

template <typename num>
num LinearRegression<num>::fit(const std::vector<std::vector<num>>& xValues, const std::vector<num>& yValues) {
    // Check if input vectors are non-empty
    if (xValues.empty() || yValues.empty()) {
        std::cerr << "Error: One or both vectors are empty." << std::endl;
        return std::numeric_limits<num>::quiet_NaN();
    }

    // Determine the number of coefficients (including intercept)
    size_t numCoefficients = xValues.size() + 1;
    coefficients.resize(numCoefficients, 0);

    // Calculate mean values for each column in the input matrix
    std::vector<num> xMeans(numCoefficients, 0);
    calculateMeans(xValues, xMeans);

    // Perform linear regression using the method of least squares
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

    // Calculate and store the intercept
    calculateIntercept(xMeans);

    return 1;
}

template <typename num>
num LinearRegression<num>::predict(const std::vector<num>& xValues) const {
    // Check if the number of features for prediction is correct
    if (xValues.size() != coefficients.size() - 1) {
        std::cerr << "Error: Incorrect number of features for prediction." << std::endl;
        return std::numeric_limits<num>::quiet_NaN();
    }

    // Calculate the predicted dependent variable value
    num result = coefficients[0];  // Intercept

    for (size_t j = 1; j < coefficients.size(); ++j) {
        result += coefficients[j] * xValues[j - 1];
    }

    return result;
}

template <typename num>
num LinearRegression<num>::getSlope() const {
    // Return the slope (coefficient) assuming simple linear regression with one feature
    return coefficients[1];
}

template <typename num>
num LinearRegression<num>::getIntercept() const {
    // Return the intercept assuming simple linear regression with one feature
    return coefficients[0];
}

template <typename num>
num LinearRegression<num>::meanFinder(const std::vector<num>& findMean) const {
    // Calculate the mean of a vector of numeric values
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
    // Calculate means for each column in a matrix
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
    // Calculate the intercept of the linear regression model
    coefficients[0] = meanFinder(xMeans);
    for (size_t j = 1; j < coefficients.size(); ++j) {
        coefficients[0] -= coefficients[j] * xMeans[j - 1];
    }

    this->intercept = coefficients[0];
}
