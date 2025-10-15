#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "Manager.h"
using namespace std;

// Programa principal que simula gestion de memoria
int main(int argc, char** argv) {
    // valida que haya suficientes argumentos
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <memoria> <first|best|worst> [archivo]\n";
        return 1;
    }

    // lee los parametros de linea de comandos
    int memoriaTotal = stoi(argv[1]);
    string algoritmo = argv[2];

    // valida que la memoria sea al menos 100
    if (memoriaTotal < 100) {
        cerr << "Error: memoria debe ser >= 100\n";
        return 1;
    }

    // determina si lee de archivo o de consola
    unique_ptr<ifstream> archivo;
    if (argc >= 4) {
        archivo = make_unique<ifstream>(argv[3]);
        if (!*archivo) {
            cerr << "Error: no se pudo abrir " << argv[3] << "\n";
            return 1;
        }
    }
    istream& entrada = (archivo ? *archivo : cin);

    try {
        // crea el gestor de memoria con el algoritmo elegido
        Gestor gestor(memoriaTotal, algoritmo);
        
        cout << "\n=== Simulador de Memoria ===\n";
        cout << "Memoria: " << memoriaTotal << " | Algoritmo: " << algoritmo << "\n\n";

        // lee y procesa comandos linea por linea
        string linea;
        while (getline(entrada, linea)) {
            // quita espacios en blanco
            linea.erase(0, linea.find_first_not_of(" \t\r\n"));
            linea.erase(linea.find_last_not_of(" \t\r\n") + 1);
            
            // ignora lineas vacias y comentarios
            if (linea.empty() || linea[0] == '#') continue;

            stringstream ss(linea);
            string comando;
            ss >> comando;

            // procesa cada tipo de comando
            if (comando == "A") {
                string pid; int tamano;
                ss >> pid >> tamano;
                gestor.asignar(pid, tamano);
            }
            else if (comando == "L") {
                string pid;
                ss >> pid;
                gestor.liberar(pid);
            }
            else if (comando == "M") {
                gestor.mostrar();
            }
            else {
                cout << "Comando desconocido: " << comando << "\n";
            }
        }

    } catch (exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
