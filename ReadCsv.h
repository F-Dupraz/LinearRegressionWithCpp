#ifndef READ_CSV_H
#define READ_CSV_H

#include <vector>
#include <string>

class ReadCsv {
public:

    ~ReadCsv();

    std::vector<double> getColumn(std::string filepath, char hasHeader, unsigned int columnIndex);
};

#endif // READ_CSV_H
