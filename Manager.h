#ifndef GESTOR_H
#define GESTOR_H

#include <vector>
#include <memory>
#include "Block.h"
#include "Strategy.h"
using namespace std;

// Clase que gestiona toda la memoria y las operaciones
class Gestor {
private:
    vector<Bloque> memoria;               // lista de bloques de memoria
    unique_ptr<Estrategia> estrategia;    // algoritmo de asignacion (first/best/worst)
    int memoriaTotal;                     // tamaño total de memoria

    void fusionar();  // une bloques libres adyacentes (coalescing)

public:
    Gestor(int tamano, string algoritmo);
    bool asignar(string pid, int tamano);  // asigna memoria a un proceso
    bool liberar(string pid);              // libera memoria de un proceso
    void mostrar();                        // muestra el estado actual
};

#endif
