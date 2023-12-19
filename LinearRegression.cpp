#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "LinearRegressionClass.cpp"
#include "ReadCsv.h"

int main() {

    // Initialization of the class
    LinearRegression<double> linearRegression;
    ReadCsv myCsvReader;

    std::string filepath;
    std::cout << "Put the path to the file: ";
    std::cin >> filepath;
    std::cout << std::endl;

    unsigned int targetIndexY;
    std::cout << "Enter the column index of the values of Y: ";
    std::cin >> targetIndexY;
    std::cout << std::endl;

    int numberOfValues;
    std::cout << "How many values for the independent variable? ";
    std::cin >> numberOfValues;
    std::cout << std::endl;

    std::vector<unsigned int> targetIndexX;
    for (int i = 0; i < numberOfValues; i++) {
        int index;
        std::cout << "Enter on of the indexes: ";
        std::cin >> index;
        targetIndexX.push_back(index);
        std::cout << std::endl;
    }

    char hasHeader;
    std::cout << "Does your file have a header? (y/n) ";
    std::cin >> hasHeader;
    std::cout << std::endl;


    //
    // --------------- ARREGLAR LA FUNCION PARA LOS VALORES INDEPENDIENTES ---------------
    //
    std::vector<std::vector<double>> X_values = myCsvReader.getIndependentVariables(filepath, hasHeader, targetIndexX);
    std::vector<double> Y_values = myCsvReader.getTargetValues(filepath, hasHeader, targetIndexY);

    // Error handling for empty vectors or different data lengths
    if (X_values.empty() || Y_values.empty()) {
        std::cout << "Error: Vectors are empty." << std::endl;
        return -1;
    }

    if (X_values[0].size() != Y_values.size()) {
        std::cout << "Error: Different number of data points for the variables." << std::endl;
        return -1;
    }

    linearRegression.fit(X_values, Y_values);

    if (linearRegression.fit(X_values, Y_values) == 1) {
        std::cout << "Intercept: " << linearRegression.intercept << std::endl;
        std::cout << "Coefficients: ";
        for (int i = 1; i < linearRegression.coefficients.size(); ++i) {
            std::cout << linearRegression.coefficients[i] << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Error in linear regression fit." << std::endl;
    }

    return 0;
}
