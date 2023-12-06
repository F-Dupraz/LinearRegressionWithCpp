/*
 * This software is crafted with logical guidance from the book
 * 'Applied Regression Analysis: A Research Tool, Second Edition'
 * by Springer Texts in Statistics.
 */

#include <iostream>
#include <vector>
#include "LinearRegressionClass.cpp"

int main() {

    // Initialization of the class
    LinearRegression<double> linearRegression;

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
    double xMean = linearRegression.meanFinder(X_values);
    double yMean = linearRegression.meanFinder(Y_values);

    // Calculate slope and intercept
    double slope = linearRegression.calculateSlope(X_values, Y_values, xMean, yMean);
    double intercept = linearRegression.calculateIntercept(xMean, yMean, slope);
    double R2 = linearRegression.calculateR2(X_values, Y_values, slope, intercept);

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

