#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

// Función para intercambiar dos elementos en el vector
void swap(std::vector<int>& vec, int i, int j) {
    int temp = vec[i];
    vec[i] = vec[j];
    vec[j] = temp;
}

// Función de partición para el algoritmo Quick Sort
int partition(std::vector<int>& vec, int low, int high) {
    int pivot = vec[high]; // Elegimos el último elemento como pivote
    int i = low - 1; // Índice del elemento menor
    
    for (int j = low; j < high; ++j) {
        if (vec[j] <= pivot) {
            ++i;
            swap(vec, i, j);
        }
    }
    swap(vec, i + 1, high);
    return i + 1;
}

// Función recursiva para ordenar el vector
void quickSort(std::vector<int>& vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high); // Índice de partición
        
        // Ordenar las dos mitades
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

// Función que genera un archivo de texto con el vector ordenado
void QuickSort(std::vector<int>& vec, const std::string& filePath) {

    //Inicio contador de segundnos
    auto inicio = std::chrono::high_resolution_clock::now();

    quickSort(vec, 0, vec.size() - 1); // Ordenar el vector

    //Fin contador de segundos
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempo = fin - inicio;


    std::ofstream outFile(filePath); // Crear un archivo de salida

    if (outFile.is_open()) {
        for (int num : vec) {
            outFile << num << std::endl; // Escribir cada número en el archivo
        }
        outFile.close(); // Cerrar el archivo
        std::cout << "Uso QuickSort, tiempo transcurrido: " << tiempo.count() << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo: " << filePath << std::endl;
    }
}

