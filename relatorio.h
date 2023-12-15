#if !defined(RELATORIO_H)
#define RELATORIOS_H

#include "candidato.h"
#include "data.h"
#include "eleicao.h"
#include "partido.h"
#include <string>
#include <vector>

using namespace std;

class Relatorio {
  private:
    vector<Candidato> candidatos;
    vector<Partido> partidos;
    int cargo;
    Data data;
    const int numeroDeVagas() const;

  public:
    Relatorio(Eleicao eleicao);
    void numeroDeVagasEleicao() const;
    void candidatosEleitos() const;
    void candidatosMaisVotados() const;
    void candidatosNaoEleitosEleitosMajoritariamente() const;
    void candidatosEleitosNaoEleitosMajoritariamente() const;
    void votacaoPartidos() const;
    void primeiroUltimoColocadosPorPartido() const;
    void eleitosPorFaixaEtaria() const;
    void eleitosPorGenero() const;
    void totalDeVotos() const;
};

#endif // RELATORIOS_H
