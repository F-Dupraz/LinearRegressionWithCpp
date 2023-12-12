#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "LinearRegressionClass.cpp"
#include "ReadCsv.cpp"

int main() {

    // Initialization of the class
    LinearRegression<double> linearRegression;
    ReadCsv myCsvReader;

    std::string filepath;
    std::cout << "Put the path to the file: ";
    std::cin >> filepath;
    std::cout << std::endl;

    size_t targetIndexY;
    std::cout << "Enter the column index of the values of Y: ";
    std::cin >> targetIndexY;
    std::cout << std::endl;

    size_t targetIndexX;
    std::cout << "Enter the column index of the values of X: ";
    std::cin >> targetIndexX;
    std::cout << std::endl;

    char hasHeader;
    std::cout << "Does your file have a header? (y/n) ";
    std::cin >> hasHeader;
    std::cout << std::endl;

    std::vector<double> X_values = myCsvReader.getColumn(filepath, hasHeader, targetIndexX);
    std::vector<double> Y_values = myCsvReader.getColumn(filepath, hasHeader, targetIndexY);

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

    return 0;
}
