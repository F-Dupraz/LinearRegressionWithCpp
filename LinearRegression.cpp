/*
 * This software is crafted with logical guidance from the book
 * 'Applied Regression Analysis: A Research Tool, Second Edition'
 * by Springer Texts in Statistics.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
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

    linearRegression.fit(X_values, Y_values);

    if (linearRegression.fit(X_values, Y_values) == 1) {
        std::cout << std::endl;
        std::cout << "The slope is " << linearRegression.slope << "." << std::endl;
        std::cout << "The intercept is " << linearRegression.intercept << "." << std::endl;
        std::cout << "The coefficient of determination is " << linearRegression.R2 << "." << std::endl;
    }
    else {
        std::cout << "Error in linear regression fit." << std::endl;
        return -1;
    }
    
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
        double newY = linearRegression.slope * newX + linearRegression.intercept;

        // Display the predicted Y value for the entered X value.
        std::cout << "Predicted Y for X=" << newX << " is: " << newY << std::endl;

        // Ask the user if they want to enter another X value.
        std::cout << "Do you want to enter another X value? (y/n): ";
        std::cin >> continueInput;

    } while (continueInput == 'y' || continueInput == 'Y');

    // Return 0 to indicate successful execution.
    return 0;
}

