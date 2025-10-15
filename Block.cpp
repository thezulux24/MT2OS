#include "Block.h"

// Constructor del bloque
Bloque::Bloque(bool l, string p, int t) : libre(l), pid(p), tamano(t) {}

// Convierte el bloque a string para mostrarlo en pantalla
string Bloque::toString() {
    if (libre) return "[Libre:" + to_string(tamano) + "]";
    return "[" + pid + ":" + to_string(tamano) + "]";
}
