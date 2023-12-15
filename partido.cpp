#include "partido.h"

/**
 * Esta classe representa um partido político.
 */

/**
 * Constrói um objeto Partido com o número, sigla e federação especificados.
 *
 * @param numero O número do partido.
 * @param sigla  A sigla do partido.
 * @param federacao O número da federação do partido.
 */
Partido::Partido(const int &numero, const string &sigla, const int &federacao)
    : numero(numero), sigla(sigla), federacao(federacao), votosLegenda(0), votosNominais(0) {}

/**
 * Obtém o número do partido.
 *
 * @return O número do partido.
 */
const int &Partido::getNumero() const { return numero; }

/**
 * Obtém a sigla do partido.
 *
 * @return A sigla do partido.
 */
const string &Partido::getSigla() const { return sigla; }

/**
 * Obtém o número da federação do partido.
 *
 * @return O número da federação do partido.
 */
const int &Partido::getFederacao() const { return federacao; }

/**
 * Obtém a lista de candidatos filiados ao partido.
 *
 * @return Um vetor de candidatos filiados ao partido.
 */
const std::vector<Candidato *> &Partido::getCandidatos() const { return candidatos; }

/**
 * Obtém a quantidade de votos de legenda recebidos pelo partido.
 *
 * @return A quantidade de votos de legenda recebidos pelo partido.
 */
const int &Partido::getVotosLegenda() const { return votosLegenda; }

/**
 * Obtém a quantidade de votos nominais recebidos pelo partido.
 *
 * @return A quantidade de votos nominais recebidos pelo partido.
 */
const int &Partido::getVotosNominais() const { return votosNominais; }

/**
 * Adiciona um candidato filiado ao partido.
 *
 * @param candidato O candidato a ser adicionado ao partido.
 */
void Partido::addCandidato(Candidato *candidato) { candidatos.push_back(candidato); }

/**
 * Adiciona votos de legenda ao partido.
 *
 * @param votosLegenda A quantidade de votos de legenda a serem adicionados ao partido.
 */
void Partido::addVotosLegenda(int votosLegenda) { this->votosLegenda += votosLegenda; }

/**
 * Adiciona votos nominais ao partido.
 *
 * @param numeroVotos A quantidade de votos nominais a serem adicionados ao partido.
 */
void Partido::addVotosNominais(int numeroVotos) { this->votosNominais += numeroVotos; }

/**
 * Compara dois partidos.
 *
 * @param partido O partido a ser comparado.
 * @return true se o partido atual tiver mais votos que o partido passado como parâmetro, ou se tiver a mesma quantidade de votos e um número menor.
 * @return false caso contrário.
 */
bool Partido::operator>(const Partido &partido) const {
    if (this->votosNominais + this->votosLegenda > partido.getVotosNominais() + partido.getVotosLegenda()) {
        return true;
    } else if (this->votosNominais + this->votosLegenda == partido.getVotosNominais() + partido.getVotosLegenda()) {
        return this->numero < partido.getNumero();
    }
    return false;
}

/**
 * Compara dois partidos.
 *
 * @param partido O partido a ser comparado.
 * @return true se o partido atual tiver a mesma quantidade de votos que o partido passado como parâmetro, e se tiver o mesmo número.
 * @return false caso contrário.
 */
bool Partido::operator==(const Partido &partido) const {
    return this->votosNominais + this->votosLegenda == partido.getVotosNominais() + partido.getVotosLegenda() && this->numero == partido.getNumero();
}

/*
 * Compara dois partidos.
 *
 * @param partido O partido a ser comparado.
 * @return true se o partido atual tiver menos votos que o partido passado como parâmetro, ou se tiver a mesma quantidade de votos e um número maior.
 * @return false caso contrário.
 */
bool Partido::operator<(const Partido &partido) const {
    if (this->votosNominais + this->votosLegenda < partido.getVotosNominais() + partido.getVotosLegenda()) {
        return true;
    } else if (this->votosNominais + this->votosLegenda == partido.getVotosNominais() + partido.getVotosLegenda()) {
        return this->numero > partido.getNumero();
    }
    return false;
}