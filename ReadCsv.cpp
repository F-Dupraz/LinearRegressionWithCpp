#include <iostream>
#include <fstream>
#include <sstream>

#include "ReadCsv.h"

ReadCsv::~ReadCsv() {}

std::vector<double> ReadCsv::getColumn(std::string filepath, char hasHeader, unsigned int columnIndex) {
    // Abrir el archivo CSV
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return std::vector<double>{};
    }

    // Leer el encabezado si existe
    if (hasHeader) {
        std::string header;
        std::getline(file, header);
        // Puedes almacenar el encabezado o realizar alguna acción según tus necesidades
    }

    // Leer los datos del archivo CSV
    std::vector<double> columnData;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<double> row;

        for (size_t i = 0; i <= columnIndex; ++i) {
            std::string field;
            if (!std::getline(ss, field, ',')) {
                // Manejar el caso en que la línea no tiene suficientes campos
                std::cerr << "Error: La línea no tiene suficientes campos." << std::endl;
                file.close();
                return std::vector<double>{};
            }

            if (i == columnIndex) {
                try {
                    columnData.push_back(std::stod(field));
                }
                catch (const std::invalid_argument& e) {
                    // Manejar el caso en que el campo no es un número
                    std::cerr << "Error al convertir a double: " << e.what() << std::endl;
                    // Puedes decidir ignorar el campo no numérico o manejarlo de otra manera
                }
            }
        }
    }

    // Cerrar el archivo después de leer
    file.close();

    // Ahora 'columnData' contiene los datos de la columna específica
    return columnData;
}
