#ifndef ELEICAO_H
#define ELEICAO_H

#include <string>
#include <unordered_map>

#include "candidato.h"
#include "data.h"
#include "partido.h"

using namespace std;

class Eleicao {
  private:
    unordered_map<int, Candidato *> candidatos;
    unordered_map<int, Partido *> partidos;
    int cargo;
    Data data;

  public:
    Eleicao(const unordered_map<int, Candidato *> &candidatos, const unordered_map<int, Partido *> &partidos, int cargo, const Data &data);
    const unordered_map<int, Candidato *> &getCandidatos() const;
    const unordered_map<int, Partido *> &getPartidos() const;
    const int &getCargo() const;
    const Data &getData() const;

    void processaVotacao(const unordered_map<int, int> &votos);
};

#endif // ELEICAO_H
