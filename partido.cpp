#include "partido.h"

Partido::Partido(const int &numero, const string &sigla, const int &federacao)
    : numero(numero), sigla(sigla), federacao(federacao), votosLegenda(0), votosNominais(0) {}

const int &Partido::getNumero() const { return numero; }

const string &Partido::getSigla() const { return sigla; }

const int &Partido::getFederacao() const { return federacao; }

const std::set<Candidato> &Partido::getCandidatos() const { return candidatos; }

const int &Partido::getVotosLegenda() const { return votosLegenda; }

const int &Partido::getVotosNominais() const { return votosNominais; }

void Partido::addCandidato(Candidato &candidato) { candidatos.insert(candidato); }

void Partido::addVotosLegenda(int votosLegenda) { this->votosLegenda += votosLegenda; }

void Partido::addVotosNominais(int numeroVotos) { this->votosNominais += numeroVotos; }
