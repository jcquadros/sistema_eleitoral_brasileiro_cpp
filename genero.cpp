#include "genero.h"

Genero intToGenero(const int &genero) {
    if (genero == 2) {
        return Genero::MASCULINO;
    } else {
        return Genero::FEMININO;
    }
}