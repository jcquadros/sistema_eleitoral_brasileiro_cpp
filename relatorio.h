#if !defined(RELATORIO_H)
#define RELATORIOS_H

#include "candidato.h"
#include "data.h"
#include "eleicao.h"
#include "genero.h"
#include "partido.h"
#include "tipoDestinoVotos.h"
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
    const string numeroDeVagasEleicao() const;
    const string candidatosEleitos() const;
    const string candidatosMaisVotados() const;
    const string candidatosNaoEleitosEleitosMajoritariamente() const;
    const string candidatosEleitosNaoEleitosMajoritariamente() const;
    const string votacaoPartidos() const;
    const string primeiroUltimoColocadosPorPartido() const;
    const string eleitosPorFaixaEtaria() const;
    const string eleitosPorGenero() const;
    const string totalDeVotos() const;
};

#endif // RELATORIOS_H
