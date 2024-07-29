#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <climits>  // Para INT_MIN e INT_MAX

class GeneradorArchivoBinario {
private:
    std::string nombreArchivo;
    size_t cantidadEnteros;

    // Mapa para convertir los tamaños de archivo en bytes
    static std::unordered_map<std::string, size_t> tamaños;

public:
    GeneradorArchivoBinario(const std::string& nombreArchivo, size_t cantidadEnteros)
        : nombreArchivo(nombreArchivo), cantidadEnteros(cantidadEnteros) {}

    void generarArchivo() const {
        std::ofstream archivoSalida(nombreArchivo, std::ios::binary);
        if (!archivoSalida) {
            std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
            return;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribucion(INT_MIN, INT_MAX);

        for (size_t i = 0; i < cantidadEnteros; ++i) {
            int enteroAleatorio = distribucion(gen);
            archivoSalida.write(reinterpret_cast<const char*>(&enteroAleatorio), sizeof(enteroAleatorio));
        }

        archivoSalida.close();
        std::cout << "Archivo binario generado con éxito." << std::endl;
    }

    static size_t obtenerCantidadEnteros(const std::string& tamaño) {
        if (tamaños.find(tamaño) != tamaños.end()) {
            // Cada entero ocupa 4 bytes
            return tamaños[tamaño] / sizeof(int);
        } else {
            std::cerr << "Tamaño desconocido: " << tamaño << std::endl;
            exit(1);
        }
    }
};

// Inicialización del mapa de tamaños
std::unordered_map<std::string, size_t> GeneradorArchivoBinario::tamaños = {
    {"SMALL", 512ULL * 1024 * 1024},
    {"MEDIUM", 1ULL * 1024 * 1024 * 1024},
    {"LARGE", 2ULL * 1024 * 1024 * 1024}
};

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Uso: generator -size <SIZE> -output <OUTPUT FILE PATH>" << std::endl;
        std::cerr << "Tamaños válidos: SMALL, MEDIUM, LARGE" << std::endl;
        return 1;
    }

    std::string tamaño;
    std::string archivoSalida;

    for (int i = 1; i < argc; i += 2) {
        std::string opcion = argv[i];
        if (opcion == "-size") {
            tamaño = argv[i + 1];
        } else if (opcion == "-output") {
            archivoSalida = argv[i + 1];
        } else {
            std::cerr << "Opción desconocida: " << opcion << std::endl;
            return 1;
        }
    }

    if (tamaño.empty() || archivoSalida.empty()) {
        std::cerr << "Faltan parámetros." << std::endl;
        return 1;
    }

    // Asegúrate de que la extensión del archivo sea .bin
    if (archivoSalida.find(".bin") == std::string::npos) {
        archivoSalida += ".bin";
    }

    size_t cantidadEnteros = GeneradorArchivoBinario::obtenerCantidadEnteros(tamaño);
    GeneradorArchivoBinario generador(archivoSalida, cantidadEnteros);
    generador.generarArchivo();

    return 0;
}
