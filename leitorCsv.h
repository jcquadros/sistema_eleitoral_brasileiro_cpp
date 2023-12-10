#if !defined(LEITORCSV_H)
#define LEITORCSV_H

#include <string>
using namespace std;

#include <map>

#include "eleicao.h"
#include "data.h"
#include "candidato.h"
#include "partido.h"
#include "genero.h"
#include "tipoDestinoVotos.h"

Eleicao &eleicaoFromCsv(string &nomeArquivo, int cargo, Data &dataEleicao);
map<int, int> &mapaVotacaoFromCsv(string &nomeArquivo, int cargo);


#endif // LEITORCSV_H
