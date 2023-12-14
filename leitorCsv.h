#if !defined(LEITORCSV_H)
#define LEITORCSV_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "candidato.h"
#include "data.h"
#include "eleicao.h"
#include "partido.h"

using namespace std;

Eleicao *eleicaoFromCsv(string &nomeArquivo, int cargo, Data &dataEleicao);
unordered_map<int, int> *mapaVotacaoFromCsv(string &nomeArquivo, int cargo);

#endif // LEITORCSV_H
