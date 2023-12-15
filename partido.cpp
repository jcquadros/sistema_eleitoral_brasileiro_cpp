#include "partido.h"

Partido::Partido(const int &numero, const string &sigla, const int &federacao)
    : numero(numero), sigla(sigla), federacao(federacao), votosLegenda(0), votosNominais(0) {}

const int &Partido::getNumero() const { return numero; }

const string &Partido::getSigla() const { return sigla; }

const int &Partido::getFederacao() const { return federacao; }

const std::vector<Candidato *> &Partido::getCandidatos() const { return candidatos; }

const int &Partido::getVotosLegenda() const { return votosLegenda; }

const int &Partido::getVotosNominais() const { return votosNominais; }

void Partido::addCandidato(Candidato *candidato) {
    // cout << "addCandidato" << candidato.getNome() << endl;
    candidatos.push_back(candidato);
}

void Partido::addVotosLegenda(int votosLegenda) { this->votosLegenda += votosLegenda; }

void Partido::addVotosNominais(int numeroVotos) { this->votosNominais += numeroVotos; }

bool Partido::operator>(const Partido &partido) const {
    if (this->votosNominais + this->votosLegenda > partido.getVotosNominais() + partido.getVotosLegenda()) {
        return true;
    } else if (this->votosNominais + this->votosLegenda == partido.getVotosNominais() + partido.getVotosLegenda()) {
        return this->numero < partido.getNumero();
    }
    return false;
}

bool Partido::operator==(const Partido &partido) const {
    return this->votosNominais + this->votosLegenda == partido.getVotosNominais() + partido.getVotosLegenda() && this->numero == partido.getNumero();
}

bool Partido::operator<(const Partido &partido) const {
    if (this->votosNominais + this->votosLegenda < partido.getVotosNominais() + partido.getVotosLegenda()) {
        return true;
    } else if (this->votosNominais + this->votosLegenda == partido.getVotosNominais() + partido.getVotosLegenda()) {
        return this->numero > partido.getNumero();
    }
    return false;
}