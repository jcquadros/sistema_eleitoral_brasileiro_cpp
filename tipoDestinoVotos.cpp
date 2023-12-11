#include "tipoDestinoVotos.h"

TipoDestinoVotos strToTipoDestinoVotos(const string &tipoDestinoVotos) {
    if (tipoDestinoVotos == "Válido (legenda)") {
        return TipoDestinoVotos::VALIDO_LEGENDA;
    } else if (tipoDestinoVotos == "Válido") {
        return TipoDestinoVotos::VALIDO_NOMINAL;
    } else {
        return TipoDestinoVotos::INVALIDO;
    }
}