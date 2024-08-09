#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

// Función para realizar el Bubble Sort y guardar los datos ordenados en un archivo
void BubbleSort(std::vector<int>& vec, const std::string& filename) {
    int n = vec.size();
    bool swapped;
    
    //Inicio contador de segundnos
    auto inicio = std::chrono::high_resolution_clock::now();

    // Bubble Sort
    do {
        swapped = false;
        for (int i = 0; i < n - 1; ++i) {
            if (vec[i] > vec[i + 1]) {
                std::swap(vec[i], vec[i + 1]);
                swapped = true;
            }
        }
        --n; // Reduce el rango de comparación en cada pasada
    } while (swapped);
    
    //Fin contador de segundos
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempo = fin - inicio;

    // Guardar los datos ordenados en un archivo
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int num : vec) {
            outFile << num << std::endl;
        }
        outFile.close();
        std::cout << "Uso BubbleSort, tiempo trascurrido: " << tiempo.count() << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
    }
}