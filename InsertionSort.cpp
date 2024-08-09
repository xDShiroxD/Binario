#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

// Función para realizar el Insertion Sort y guardar los datos ordenados en un archivo
void InsertionSort(std::vector<int>& vec, const std::string& filename) {
    int n = vec.size();
    
    //Inicio contador de segundnos
    auto inicio = std::chrono::high_resolution_clock::now();

    // Insertion Sort
    for (int i = 1; i < n; ++i) {
        int key = vec[i];
        int j = i - 1;
        
        // Mover los elementos del vector que son mayores que la clave
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            --j;
        }
        vec[j + 1] = key;
    }

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
        std::cout << "Uso InsertionSort, tiempo trascurrido: " << tiempo.count() << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
    }
}