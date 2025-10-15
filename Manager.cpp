#include "Manager.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
using namespace std;

// Constructor: inicializa la memoria como un bloque libre grande
Gestor::Gestor(int tamano, string algoritmo) : memoriaTotal(tamano) {
    memoria.push_back(Bloque(true, "", tamano));
    
    // selecciona el algoritmo segun el parametro
    if (algoritmo == "first") estrategia = make_unique<FirstFit>();
    else if (algoritmo == "best") estrategia = make_unique<BestFit>();
    else if (algoritmo == "worst") estrategia = make_unique<WorstFit>();
    else throw runtime_error("Algoritmo invalido");
}

// Fusiona bloques libres que estan uno al lado del otro (coalescing)
void Gestor::fusionar() {
    vector<Bloque> fusionada;
    for (auto& b : memoria) {
        // si el ultimo bloque y el actual son libres, los combina
        if (!fusionada.empty() && fusionada.back().libre && b.libre)
            fusionada.back().tamano += b.tamano;
        else
            fusionada.push_back(b);
    }
    memoria = fusionada;
}

// Asigna memoria a un proceso usando la estrategia elegida
bool Gestor::asignar(string pid, int tamano) {
    // validaciones
    if (tamano <= 0) {
        cout << "Error: tamaño debe ser > 0\n";
        return false;
    }
    
    // no permite procesos duplicados
    for (auto& b : memoria) {
        if (!b.libre && b.pid == pid) {
            cout << "Error: proceso " << pid << " ya existe\n";
            return false;
        }
    }

    // usa la estrategia para elegir el hueco
    int i = estrategia->elegir(memoria, tamano);
    if (i < 0) {
        cout << "Error: no hay espacio suficiente\n";
        return false;
    }

    // si el hueco es del tamaño exacto, lo usa completo
    if (memoria[i].tamano == tamano) {
        memoria[i].libre = false;
        memoria[i].pid = pid;
    } else {
        // si el hueco es mas grande, lo parte en dos
        Bloque asignado(false, pid, tamano);
        Bloque resto(true, "", memoria[i].tamano - tamano);
        memoria[i] = asignado;
        memoria.insert(memoria.begin() + i + 1, resto);
    }
    
    cout << "Proceso " << pid << " asignado (" << tamano << " unidades)\n";
    return true;
}

// Libera la memoria de un proceso
bool Gestor::liberar(string pid) {
    bool encontrado = false;
    
    // busca todos los bloques del proceso y los marca como libres
    for (auto& b : memoria) {
        if (!b.libre && b.pid == pid) {
            b.libre = true;
            b.pid = "";
            encontrado = true;
        }
    }
    
    // si encontro el proceso, fusiona bloques libres adyacentes
    if (encontrado) {
        fusionar();
        cout << "Proceso " << pid << " liberado\n";
    } else {
        cout << "Error: proceso " << pid << " no encontrado\n";
    }
    return encontrado;
}

// Muestra el estado actual de la memoria y calcula fragmentacion
void Gestor::mostrar() {
    cout << "\n=== Estado de Memoria (" << estrategia->nombre() << ") ===\n";
    
    // imprime todos los bloques en formato [Proceso:X] o [Libre:X]
    for (auto& b : memoria) cout << b.toString();
    cout << "\n";
    
    // calcula metricas de fragmentacion
    int totalLibre = 0, mayorLibre = 0;
    for (auto& b : memoria) {
        if (b.libre) {
            totalLibre += b.tamano;
            mayorLibre = max(mayorLibre, b.tamano);
        }
    }
    
    // fragmentacion interna es 0 porque uso particiones variables con corte exacto
    cout << "Fragmentacion interna: 0\n";
    // fragmentacion externa es la memoria libre que no se puede usar por no ser contigua
    cout << "Fragmentacion externa: " << (totalLibre - mayorLibre)
         << " (total libre=" << totalLibre << ", mayor hueco=" << mayorLibre << ")\n";
    cout << "================================\n\n";
}
