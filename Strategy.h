#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

#include <vector>
#include "Block.h"
using namespace std;

// Clase base para las estrategias de asignacion de memoria
class Estrategia {
public:
    virtual ~Estrategia() = default;
    virtual int elegir(const vector<Bloque>& mem, int tamano) = 0;  // elige el hueco donde asignar
    virtual string nombre() = 0;  // retorna el nombre del algoritmo
};

// First Fit: elige el primer hueco que quepa
class FirstFit : public Estrategia {
public:
    int elegir(const vector<Bloque>& mem, int tamano) override;
    string nombre() override;
};

// Best Fit: elige el hueco mas pequeño que quepa
class BestFit : public Estrategia {
public:
    int elegir(const vector<Bloque>& mem, int tamano) override;
    string nombre() override;
};

// Worst Fit: elige el hueco mas grande disponible
class WorstFit : public Estrategia {
public:
    int elegir(const vector<Bloque>& mem, int tamano) override;
    string nombre() override;
};

#endif
