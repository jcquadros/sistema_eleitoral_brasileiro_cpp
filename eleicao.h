#ifndef ELEICAO_H
#define ELEICAO_H

#include <map>
#include <string>

#include "candidato.h"
#include "data.h"
#include "partido.h"

using namespace std;

class Eleicao {
  private:
    std::map<int, Candidato *> candidatos;
    std::map<int, Partido *> partidos;
    int cargo;
    Data data;

  public:
    Eleicao(const std::map<int, Candidato *> &candidatos, const std::map<int, Partido *> &partidos, int cargo, const Data &data);
    const std::map<int, Candidato *> &getCandidatos() const;
    const std::map<int, Partido *> &getPartidos() const;
    const int &getCargo() const;
    const Data &getData() const;

    void processaVotacao(const std::map<int, int> &votos);
};

#endif // ELEICAO_H
