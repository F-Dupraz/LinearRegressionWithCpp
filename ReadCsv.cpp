#include <iostream>
#include <fstream>
#include <sstream>

#include "ReadCsv.h"

// Destructor for the ReadCsv class.
ReadCsv::~ReadCsv() {}

// Get target values from a CSV file.
std::vector<double> ReadCsv::getTargetValues(std::string filepath, char hasHeader, unsigned int columnIndex) {
    // Open the CSV file
    std::ifstream file(filepath);

    // Check if the file is successfully opened
    if (!file.is_open()) {
        std::cerr << "Unable to open the file." << std::endl;
        return std::vector<double>{};
    }

    // Read the header if it exists
    if (hasHeader) {
        std::string header;
        std::getline(file, header);
        // Additional actions can be performed based on the header if needed
    }

    // Read data from the CSV file
    std::vector<double> columnData;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);

        // Parse each field in the line
        for (size_t i = 0; i <= columnIndex; ++i) {
            std::string field;
            if (!std::getline(ss, field, ',')) {
                // Handle the case where the line does not have enough fields
                std::cerr << "Error: The line does not have enough fields." << std::endl;
                file.close();
                return std::vector<double>{};
            }

            // If the desired column is reached, convert the field to a double and add it to the vector
            if (i == columnIndex) {
                try {
                    columnData.push_back(std::stod(field));
                }
                catch (const std::invalid_argument& e) {
                    // Handle the case where the field is not a number
                    std::cerr << "Error converting to double: " << e.what() << std::endl;
                    // You can decide to ignore the non-numeric field or handle it differently
                }
            }
        }
    }

    // Close the file after reading
    file.close();

    // 'columnData' now contains the data from the specific column
    return columnData;
}

// Get independent variables from a CSV file.
std::vector<std::vector<double>> ReadCsv::getIndependentVariables(std::string filepath, char hasHeader, std::vector<unsigned int> columnIndices) {
    // Open the CSV file
    std::ifstream file(filepath);

    // Check if the file is successfully opened
    if (!file.is_open()) {
        std::cerr << "Unable to open the file." << std::endl;
        return std::vector<std::vector<double>>{};
    }

    // Read the header if it exists
    if (hasHeader) {
        std::string header;
        std::getline(file, header);
        // Additional actions can be performed based on the header if needed
    }

    // Initialize the 2D vector to store data from multiple columns
    std::vector<std::vector<double>> columnsData(columnIndices.size());

    // Read data from the CSV file
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string field;
        unsigned int currentIndex = 0;

        // Parse each field in the line
        while (std::getline(ss, field, ',')) {
            // Check if the current column index is within the specified column indices
            if (currentIndex < columnIndices.size()) {
                auto column = std::find(columnIndices.begin(), columnIndices.end(), currentIndex);
                if (column != columnIndices.end()) {
                    // Convert the field to a double and add it to the corresponding vector
                    try {
                        columnsData[currentIndex].push_back(std::stod(field));
                    }
                    catch (const std::invalid_argument& e) {
                        // Handle the case where the field is not a number
                        std::cerr << "Error converting to double: " << e.what() << " - Field: " << field << std::endl;
                        // You can decide to ignore the non-numeric field or handle it differently
                    }

                    currentIndex++; // Increment after adding data
                }
                else {
                    currentIndex++;  // Increment after skipping data
                }
            }
            else {
                // Ignore additional fields if there are more than specified in columnIndices
                break;
            }
        }
    }

    // Close the file after reading
    file.close();

    return columnsData;
}
