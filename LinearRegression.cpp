/*
 * This software is crafted with logical guidance from the book 
 * 'Applied Regression Analysis: A Research Tool, Second Edition'
 * by Springer Texts in Statistics.
 */

#include <windows.h>
#include <iostream>
#include <vector>

/**
 * @brief Calculates the mean (average) of a vector of numeric values.
 *
 * @param findMean The vector for which to calculate the mean.
 * @return The mean of the vector.
 */
template <typename num>
num meanFinder(const std::vector<num>& findMean) {
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

/**
 * @brief Calculates the slope of a linear regression model.
 *
 * @param xValues The vector of X values.
 * @param yValues The vector of Y values.
 * @param xMean The mean of X values.
 * @param yMean The mean of Y values.
 * @return The slope of the linear regression model.
 */
template <typename num>
num calculateSlope(const std::vector<num>& xValues, const std::vector<num>& yValues, const num& xMean, const num& yMean) {
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

/**
 * @brief Calculates the intercept of a linear regression model.
 *
 * @param xMean The mean of X values.
 * @param yMean The mean of Y values.
 * @param slope The slope of the linear regression model.
 * @return The intercept of the linear regression model.
 */
template <typename num>
num calculateIntercept(const num& xMean, const num& yMean, const num& slope) {
    num intercept = yMean - slope * xMean;
    return intercept;
}

/**
 * @brief Calculates the coefficient of determination (R^2) for a linear regression model.
 *
 * @param xValues The vector of X values.
 * @param yValues The vector of Y values.
 * @param slope The slope of the linear regression model.
 * @param intercept The intercept of the linear regression model.
 * @return The coefficient of determination (R^2).
 */
template <typename num>
num calculateR2(const std::vector<num>& xValues, const std::vector<num>& yValues, const num& slope, const num& intercept) {
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

int main() {
    // Example data
    std::vector<double> X_values = { 0.02, 0.07, 0.11, 0.15 };
    std::vector<double> Y_values = { 242, 237, 231, 201 };

    // Error handling for empty vectors or different data lengths
    if (X_values.empty() || Y_values.empty()) {
        std::cout << "Error: Vectors are empty." << std::endl;
        return -1;
    }

    if (X_values.size() != Y_values.size()) {
        std::cout << "Error: Different number of data points for the variables." << std::endl;
        return -1;
    }

    // Calculate means of X and Y values
    double xMean = meanFinder(X_values);
    double yMean = meanFinder(Y_values);

    // Calculate slope and intercept
    double slope = calculateSlope(X_values, Y_values, xMean, yMean);
    double intercept = calculateIntercept(xMean, yMean, slope);
    double R2 = calculateR2(X_values, Y_values, slope, intercept);

    // Output results
    std::cout << std::endl;
    std::cout << "The slope is " << slope << "." << std::endl;
    std::cout << "The intercept is " << intercept << "." << std::endl;
    std::cout << "The coefficient of determination is " << R2 << "." << std::endl;

    char continueInput;

    // A do-while loop to interactively gather new X values from the user and make predictions.
    do {
        std::cout << std::endl;

        // Declare a variable to store the user-inputted X value.
        double newX;
        std::cout << "Enter a new X value: ";

        // Receive the user's input for the new X value.
        std::cin >> newX;

        // Make a prediction using the linear regression model.
        double newY = slope * newX + intercept;

        // Display the predicted Y value for the entered X value.
        std::cout << "Predicted Y for X=" << newX << " is: " << newY << std::endl;

        // Ask the user if they want to enter another X value.
        std::cout << "Do you want to enter another X value? (y/n): ";
        std::cin >> continueInput;

    } while (continueInput == 'y' || continueInput == 'Y');

    // Return 0 to indicate successful execution.
    return 0;
}

