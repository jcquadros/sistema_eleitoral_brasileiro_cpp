#if !defined(TIPODESTINOVOTOS_H)
#define TIPODESTINOVOTOS_H

#include <string>
using namespace std;

enum class TipoDestinoVotos { VALIDO_LEGENDA, VALIDO_NOMINAL, INVALIDO };

TipoDestinoVotos strToTipoDestinoVotos(const string &tipoDestinoVotos);
#endif // TIPODESTINOVOTOS_H
