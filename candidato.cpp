#include "candidato.h"

Candidato::Candidato(const int &numero, const string &nome, Partido *partido, const bool &deferido, const bool &eleito, const Genero &genero,
                     const TipoDestinoVotos &tipoDestinoVotos, const Data &dataNascimento)
    : numero(numero), nome(nome), partido(partido), deferido(deferido), eleito(eleito), genero(genero), tipoDestinoVotos(tipoDestinoVotos),
      dataNascimento(dataNascimento), votosNominais(0) {}

Candidato::Candidato() {}

const int &Candidato::getNumero() const { return numero; }

const string &Candidato::getNome() const { return nome; }

Partido *Candidato::getPartido() const { return partido; }

const bool &Candidato::isDeferido() const { return deferido; }

const bool &Candidato::isEleito() const { return eleito; }

const int &Candidato::getVotosNominais() const { return votosNominais; }

const Genero &Candidato::getGenero() const { return genero; }

const TipoDestinoVotos &Candidato::getTipoDestinoVotos() const { return tipoDestinoVotos; }

const Data &Candidato::getDataNascimento() const { return dataNascimento; }

void Candidato::setVotosNominais(int votosNominais) { this->votosNominais = votosNominais; }

void Candidato::addVotosNominais(int votosNominais) { this->votosNominais += votosNominais; }

bool Candidato::operator>(const Candidato &candidato) const {
    if (this->votosNominais > candidato.getVotosNominais()) {
        return true;
    } else if (this->votosNominais == candidato.getVotosNominais()) {
        return this->dataNascimento.operator<(candidato.getDataNascimento());
    }
    return false;
}

bool Candidato::operator==(const Candidato &candidato) const {
    return this->votosNominais == candidato.getVotosNominais() && this->dataNascimento.operator==(candidato.getDataNascimento());
}

bool Candidato::operator<(const Candidato &candidato) const {
    if (this->votosNominais < candidato.getVotosNominais()) {
        return true;
    } else if (this->votosNominais == candidato.getVotosNominais()) {
        return this->dataNascimento.operator>(candidato.getDataNascimento());
    }
    return false;
}