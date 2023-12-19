#include <iostream>
#include <fstream>
#include <sstream>

#include "ReadCsv.h"

ReadCsv::~ReadCsv() {}

std::vector<double> ReadCsv::getTargetValues(std::string filepath, char hasHeader, unsigned int columnIndex) {
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

std::vector<std::vector<double>> ReadCsv::getIndependentVariables(std::string filepath, char hasHeader, std::vector<unsigned int> columnIndices) {
    // Abrir el archivo CSV
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return std::vector<std::vector<double>>{};
    }

    // Leer el encabezado si existe
    if (hasHeader) {
        std::string header;
        std::getline(file, header);
        // Puedes almacenar el encabezado o realizar alguna acción según tus necesidades
    }

    // Inicializar la matriz bidimensional para almacenar datos de múltiples columnas
    std::vector<std::vector<double>> columnsData(columnIndices.size());

    // Leer los datos del archivo CSV
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string field;
        unsigned int currentIndex = 0;

        while (std::getline(ss, field, ',')) {
            if (currentIndex < columnIndices.size()) {
                auto column = std::find(columnIndices.begin(), columnIndices.end(), currentIndex);
                if (column != columnIndices.end()) {
                    try {
                        columnsData[currentIndex].push_back(std::stod(field));
                    }
                    catch (const std::invalid_argument& e) {
                        // Manejar el caso en que el campo no es un número
                        std::cerr << "Error al convertir a double: " << e.what() << " - Campo: " << field << std::endl;
                        // Puedes decidir ignorar el campo no numérico o manejarlo de otra manera
                    }

                    currentIndex++; // Incrementa después de agregar datos
                }
                else {
                    currentIndex++;  // Incrementa después de agregar datos
                }
            }
            else {
                // Ignorar campos adicionales si hay más de los especificados en columnIndices
                break;
            }
        }
    }

    // Cerrar el archivo después de leer
    file.close();

    return columnsData;
}

