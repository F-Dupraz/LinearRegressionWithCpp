#ifndef READ_CSV_H
#define READ_CSV_H

#include <vector>
#include <string>

/**
 * @class ReadCsv
 * @brief A class for reading data from CSV files.
 */
class ReadCsv {
public:
    /**
     * @brief Destructor for the ReadCsv class.
     */
    ~ReadCsv();

    /**
     * @brief Get target values from a CSV file.
     * @param filepath The path to the CSV file.
     * @param hasHeader Indicates whether the CSV file has a header row.
     * @param columnIndex The index of the target column in the CSV file.
     * @return A vector of target values.
     */
    std::vector<double> getTargetValues(std::string filepath, char hasHeader, unsigned int columnIndex);

    /**
     * @brief Get independent variables from a CSV file.
     * @param filepath The path to the CSV file.
     * @param hasHeader Indicates whether the CSV file has a header row.
     * @param xTargets A vector of indices specifying the columns of independent variables.
     * @return A vector of vectors containing the independent variables.
     */
    std::vector<std::vector<double>> getIndependentVariables(std::string filepath, char hasHeader, std::vector<unsigned int> xTargets);
};

#endif // READ_CSV_H
