#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <filesystem>

class GeneradorArchivoBinario {
private:
    std::string nombreArchivo = "Archivo Binario";
    size_t cantidadEnteros;

    // Mapa para convertir los tamaños de archivo en bytes
    static std::unordered_map<std::string, size_t> tamaños;

public:
    GeneradorArchivoBinario(const std::string& nombreArchivo, size_t cantidadEnteros)
        : nombreArchivo(nombreArchivo), cantidadEnteros(cantidadEnteros) {}

    void generarArchivo() const {
        std::ofstream archivoSalida(nombreArchivo, std::ios::binary);
        if (!archivoSalida) {
            std::cerr << "No se pudo abrir el archivo para escribir: " << nombreArchivo << std::endl;
            return;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribucion(0, 9);

        for (size_t i = 0; i < cantidadEnteros; ++i) {
            int enteroAleatorio = distribucion(gen);
            archivoSalida.write(reinterpret_cast<const char*>(&enteroAleatorio), sizeof(enteroAleatorio));
        }

        // Asegura que el archivo se cierra y libera los recursos asociados
        archivoSalida.close();
        std::cout << "Archivo binario generado con éxito en la ruta: " << nombreArchivo << std::endl;
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

    static std::string obtenerNombreArchivo(const std::string& tamaño, const std::string& ruta) {
        std::string nombreBase = "Archivo Binario.bin";
        std::filesystem::path rutaCompleta = std::filesystem::path(ruta) / nombreBase;
        return rutaCompleta.string();
    }
};

// Inicialización del mapa de tamaños
std::unordered_map<std::string, size_t> GeneradorArchivoBinario::tamaños = {
    {"SMALL", 265ULL},
    {"MEDIUM", 1024ULL * 512},
    {"LARGE", 1024ULL * 1024}
};

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Uso: generator -size <SIZE> -output <OUTPUT FILE PATH>" << std::endl;
        std::cerr << "Tamaños válidos: SMALL, MEDIUM, LARGE" << std::endl;
        return 1;
    }

    std::string tamaño;
    std::string rutaSalida;

    for (int i = 1; i < argc; i += 2) {
        std::string opcion = argv[i];
        if (opcion == "-size") {
            tamaño = argv[i + 1];
        } else if (opcion == "-output") {
            rutaSalida = argv[i + 1];
        } else {
            std::cerr << "Opción desconocida: " << opcion << std::endl;
            return 1;
        }
    }

    if (tamaño.empty() || rutaSalida.empty()) {
        std::cerr << "Faltan parámetros." << std::endl;
        return 1;
    }

    // Asegurarse de que el directorio de salida existe
    if (!std::filesystem::exists(rutaSalida)) {
        std::cerr << "El directorio de salida no existe: " << rutaSalida << std::endl;
        return 1;
    }

    // Asegurarse de que la ruta de salida es un directorio
    if (!std::filesystem::is_directory(rutaSalida)) {
        std::cerr << "La ruta de salida no es un directorio: " << rutaSalida << std::endl;
        return 1;
    }

    // Obtener la cantidad de enteros a generar en función del tamaño del archivo
    size_t cantidadEnteros = GeneradorArchivoBinario::obtenerCantidadEnteros(tamaño);
    std::string nombreArchivo = GeneradorArchivoBinario::obtenerNombreArchivo(tamaño, rutaSalida);

    // Crear una instancia del generador y generar el archivo binario
    GeneradorArchivoBinario generador(nombreArchivo, cantidadEnteros);
    generador.generarArchivo();

    return 0;
}
