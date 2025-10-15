#include "Strategy.h"

// First Fit: busca el primer hueco que sea suficientemente grande
int FirstFit::elegir(const vector<Bloque>& mem, int tamano) {
    for (int i = 0; i < (int)mem.size(); i++)
        if (mem[i].libre && mem[i].tamano >= tamano) return i;
    return -1;  // no encontro hueco
}

string FirstFit::nombre() {
    return "First Fit";
}

// Best Fit: busca el hueco mas pequeño que quepa para minimizar desperdicio
int BestFit::elegir(const vector<Bloque>& mem, int tamano) {
    int idx = -1, minDesperdicio = 999999;
    for (int i = 0; i < (int)mem.size(); i++) {
        if (mem[i].libre && mem[i].tamano >= tamano) {
            int desperdicio = mem[i].tamano - tamano;
            if (desperdicio < minDesperdicio) {
                minDesperdicio = desperdicio;
                idx = i;
            }
        }
    }
    return idx;
}

string BestFit::nombre() {
    return "Best Fit";
}

// Worst Fit: busca el hueco mas grande para dejar huecos grandes reutilizables
int WorstFit::elegir(const vector<Bloque>& mem, int tamano) {
    int idx = -1, maxTamano = -1;
    for (int i = 0; i < (int)mem.size(); i++) {
        if (mem[i].libre && mem[i].tamano >= tamano) {
            if (mem[i].tamano > maxTamano) {
                maxTamano = mem[i].tamano;
                idx = i;
            }
        }
    }
    return idx;
}

string WorstFit::nombre() {
    return "Worst Fit";
}
