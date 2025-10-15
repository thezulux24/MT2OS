#ifndef BLOQUE_H
#define BLOQUE_H

#include <string>
using namespace std;

// Representa un bloque de memoria que puede estar libre u ocupado
class Bloque {
public:
    bool libre;      // true si esta libre, false si esta ocupado
    string pid;      // nombre del proceso que lo ocupa
    int tamano;      // tamaño del bloque en unidades

    Bloque(bool l, string p, int t);
    string toString();  // convierte el bloque a formato [Proceso:X] o [Libre:X]
};

#endif
