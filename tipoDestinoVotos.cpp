#include "tipoDestinoVotos.h"

TipoDestinoVotos tipoDestinoVotos(string tipoDestinoVotos) {
    if (tipoDestinoVotos == "Válido (legenda)") {
        return TipoDestinoVotos::VALIDO_LEGENDA;
    } else if (tipoDestinoVotos == "Válido") {
        return TipoDestinoVotos::VALIDO_NOMINAL;
    } else {
        return TipoDestinoVotos::INVALIDO;
    }
}