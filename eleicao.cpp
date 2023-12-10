
#include "eleicao.h"

Eleicao::Eleicao(const std::map<int, Candidato> &candidatos, const std::map<int, Partido> &partidos, int cargo, const Data &data)
    : candidatos(candidatos), partidos(partidos), cargo(cargo), data(data) {}

const std::map<int, Candidato> &Eleicao::getCandidatos() const { return candidatos; }

const std::map<int, Partido> &Eleicao::getPartidos() const { return partidos; }

const int &Eleicao::getCargo() const { return cargo; }

const Data &Eleicao::getData() const { return data; }

void Eleicao::processaVotacao(const std::map<int, int> &votos) {
    for (const auto &voto : votos) {
        int numero = voto.first;
        int numeroVotos = voto.second;

        if (candidatos.count(numero)) {
            Candidato &candidato = candidatos.at(numero);
            if (candidato.getTipoDestinoVotos() == TipoDestinoVotos::VALIDO_LEGENDA) {
                candidato.getPartido()->addVotosLegenda(numeroVotos);
            } else if (candidato.isDeferido()) {
                candidato.addVotosNominais(numeroVotos);
                candidato.getPartido()->addVotosNominais(numeroVotos);
            }
        } else if (partidos.count(numero)) {
            Partido &partido = partidos.at(numero);
            partido.addVotosLegenda(numeroVotos);
        }
    }
}
