
#include "eleicao.h"
/**
 * Esta classe representa uma eleição.
 */

/**
 * Constrói um objeto Eleicao com os candidatos, partidos, cargo e data especificados.
 *
 * @param candidatos Os candidatos da eleição.
 * @param partidos Os partidos da eleição.
 * @param cargo O cargo da eleição.
 * @param data A data da eleição.
 */
Eleicao::Eleicao(const unordered_map<int, Candidato *> &candidatos, const unordered_map<int, Partido *> &partidos, int cargo, const Data &data)
    : candidatos(candidatos), partidos(partidos), cargo(cargo), data(data) {}

/**
 * Obtém os candidatos da eleição.
 * @return Os candidatos da eleição.
 */
const unordered_map<int, Candidato *> &Eleicao::getCandidatos() const { return candidatos; }

/**
 * Obtém os partidos da eleição.
 * @return Os partidos da eleição.
 */
const unordered_map<int, Partido *> &Eleicao::getPartidos() const { return partidos; }

/**
 * Obtém o cargo da eleição.
 * @return O cargo da eleição.
 */
const int &Eleicao::getCargo() const { return cargo; }

/**
 * Obtém a data da eleição.
 * @return A data da eleição.
 */
const Data &Eleicao::getData() const { return data; }

/**
 * Processa a votação com base nos votos fornecidos.
 *
 * @param votos um mapa dos votos, onde a chave é o número do candidato ou partido e o valor é o número de votos
 */
void Eleicao::processaVotacao(const unordered_map<int, int> &votos) {
    for (const auto &voto : votos) {
        int numero = voto.first;
        int numeroVotos = voto.second;

        if (candidatos.count(numero)) {
            Candidato *candidato = candidatos.at(numero);
            if (candidato->getTipoDestinoVotos() == TipoDestinoVotos::VALIDO_LEGENDA) {
                candidato->getPartido()->addVotosLegenda(numeroVotos);
            } else if (candidato->isDeferido()) {
                candidato->addVotosNominais(numeroVotos);
                candidato->getPartido()->addVotosNominais(numeroVotos);
            }
        } else if (partidos.count(numero)) {
            Partido *partido = partidos.at(numero);
            partido->addVotosLegenda(numeroVotos);
        }
    }
}
