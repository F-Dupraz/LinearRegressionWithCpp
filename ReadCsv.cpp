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
        // Puedes almacenar el encabezado o realizar alguna acci�n seg�n tus necesidades
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
                // Manejar el caso en que la l�nea no tiene suficientes campos
                std::cerr << "Error: La l�nea no tiene suficientes campos." << std::endl;
                file.close();
                return std::vector<double>{};
            }

            if (i == columnIndex) {
                try {
                    columnData.push_back(std::stod(field));
                }
                catch (const std::invalid_argument& e) {
                    // Manejar el caso en que el campo no es un n�mero
                    std::cerr << "Error al convertir a double: " << e.what() << std::endl;
                    // Puedes decidir ignorar el campo no num�rico o manejarlo de otra manera
                }
            }
        }
    }

    // Cerrar el archivo despu�s de leer
    file.close();

    // Ahora 'columnData' contiene los datos de la columna espec�fica
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
        // Puedes almacenar el encabezado o realizar alguna acci�n seg�n tus necesidades
    }

    // Inicializar la matriz bidimensional para almacenar datos de m�ltiples columnas
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
                        // Manejar el caso en que el campo no es un n�mero
                        std::cerr << "Error al convertir a double: " << e.what() << " - Campo: " << field << std::endl;
                        // Puedes decidir ignorar el campo no num�rico o manejarlo de otra manera
                    }

                    currentIndex++; // Incrementa despu�s de agregar datos
                }
                else {
                    currentIndex++;  // Incrementa despu�s de agregar datos
                }
            }
            else {
                // Ignorar campos adicionales si hay m�s de los especificados en columnIndices
                break;
            }
        }
    }

    // Cerrar el archivo despu�s de leer
    file.close();

    return columnsData;
}

