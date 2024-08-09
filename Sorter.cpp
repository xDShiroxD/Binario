#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "QuickSort.cpp"
#include "BubbleSort.cpp"
#include "InsertionSort.cpp"

void printUsage() {
    std::cerr << "Uso: sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>\n";
    std::cerr << "ALGORITMO puede ser QS (Quick Sort), IS (Insertion Sort) o BS (Bubble Sort)\n";
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        printUsage();
        return 1;
    }

    std::string inputFilePath;
    std::string outputFilePath;
    std::string algorithm;

    for (int i = 1; i < argc; i += 2) {
        if (std::strcmp(argv[i], "-input") == 0) {
            inputFilePath = argv[i + 1];
        } else if (std::strcmp(argv[i], "-output") == 0) {
            outputFilePath = argv[i + 1];
        } else if (std::strcmp(argv[i], "-alg") == 0) {
            algorithm = argv[i + 1];
        } else {
            printUsage();
            return 1;
        }
    }
    
    // Nombre del archivo binario a leer
    const char* filename = "Archivo Binario.bin";

    // Abrir el archivo en modo binario
    std::ifstream file(filename, std::ios::binary);

    // Verificar si el archivo se abrió correctamente
    if (!file) {
        std::cerr << "No se pudo abrir el archivo " << filename << std::endl;
        return 1;
    }

    // Obtener el tamaño del archivo
    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg(); 
    file.seekg(0, std::ios::beg);

    // Calcular el número de enteros en el archivo
    std::size_t numEnteros = size / sizeof(int);

    // Leer el contenido del archivo en un vector de enteros
    std::vector<int> numeros(numEnteros);
    file.read(reinterpret_cast<char*>(numeros.data()), size);

    // Verificar si la lectura fue exitosa
    if (!file) {
        std::cerr << "Error al leer el archivo" << std::endl;
        return 1;
    }
    
    if (algorithm == "QS") {
        QuickSort(numeros, "NumerosOrdenados QuickSort.txt");
    } else if (algorithm == "IS") {
        InsertionSort(numeros, "NumerosOrdenados InsertionSort.txt");
    } else if (algorithm == "BS") {
        BubbleSort(numeros, "NumerosOrdenados BubbleSort.txt");
    } else {
        printUsage();
        return 1;
    }
    // Cerrar los archivos
    file.close();

    return 0;
}