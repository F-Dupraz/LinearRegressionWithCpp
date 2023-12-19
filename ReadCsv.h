#ifndef READ_CSV_H
#define READ_CSV_H

#include <vector>
#include <string>

class ReadCsv {
public:

    ~ReadCsv();

    std::vector<double> getTargetValues(std::string filepath, char hasHeader, unsigned int columnIndex);

    std::vector<std::vector<double>> getIndependentVariables(std::string filepath, char hasHeader, std::vector<unsigned int> xTargets);
};

#endif // READ_CSV_H
