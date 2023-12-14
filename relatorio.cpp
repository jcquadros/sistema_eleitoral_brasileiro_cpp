#include "relatorio.h"
#include "candidato.h"
#include "eleicao.h"
#include "partido.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <locale>
#include <vector>

using namespace std;

Relatorio::Relatorio(Eleicao eleicao) : cargo(eleicao.getCargo()), data(eleicao.getData()) {
    for (const auto &candidato : eleicao.getCandidatos()) {
        candidatos.push_back(*(Candidato *)candidato.second);
    }

    for (const auto &partido : eleicao.getPartidos()) {
        partidos.push_back(*(Partido *)partido.second);
    }

    sort(candidatos.begin(), candidatos.end(), [](const Candidato &a, const Candidato &b) { return a.getNumero() < b.getNumero(); });
    sort(partidos.begin(), partidos.end(), [](const Partido &a, const Partido &b) { return a.getNumero() < b.getNumero(); });
}

const int Relatorio::numeroDeVagas() const {
    int count = 0;
    for (const auto &candidato : candidatos) {
        if (candidato.isEleito()) {
            count++;
        }
    }
    return count;
}

const string Relatorio::numeroDeVagasEleicao() const { return "Número de vagas: " + to_string(numeroDeVagas()) + "\n"; }

const string Relatorio::candidatosEleitos() const {
    string response = this->cargo == 6 ? "Deputados federais eleitos:\n" : "Deputados estaduais eleitos:\n";
    int i = 0;

    vector<Candidato> candidatosEleitos;
    for (const auto &candidato : candidatos) {
        if (candidato.isEleito()) {
            candidatosEleitos.push_back(candidato);
        }
    }

    for (const auto &candidato : candidatosEleitos) {
        response += to_string(++i) + " - " + candidato.getNome() + "\n";
    }

    return response;
}

const string Relatorio::candidatosMaisVotados() const {
    string response = "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):\n";
    int i = 0;

    vector<Candidato> candidatosOrdenadosVotos = candidatos;
    sort(candidatosOrdenadosVotos.begin(), candidatosOrdenadosVotos.end(),
         [](const Candidato &a, const Candidato &b) { return a.getVotosNominais() > b.getVotosNominais(); });

    candidatosOrdenadosVotos.resize(numeroDeVagas());

    for (const auto &candidato : candidatosOrdenadosVotos) {
        response += to_string(++i) + " - " + candidato.getNome() + "\n";
    }

    return response;
}

const string Relatorio::candidatosNaoEleitosEleitosMajoritariamente() const {
    string response = "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:\n";
    response += "(com sua posição no ranking de mais votados)\n";
    int numDeVagas = numeroDeVagas();

    for (int i = 0; i < numDeVagas; i++) {
        if (!candidatos[i].isEleito()) {
            response += to_string(i + 1) + " - " + candidatos[i].getNome() + "\n";
        }
    }

    return response;
}

const string Relatorio::candidatosEleitosNaoEleitosMajoritariamente() const {
    string response = "Eleitos, que se beneficiaram do sistema proporcional:\n";
    response += "(com sua posição no ranking de mais votados)\n";

    for (int i = numeroDeVagas(); i < (long int)candidatos.size(); i++) {
        if (candidatos[i].isEleito()) {
            response += to_string(i + 1) + " - " + candidatos[i].getNome() + "\n";
        }
    }
    return response;
}

const string Relatorio::votacaoPartidos() const {
    locale loc("pt_BR.UTF-8");
    string response = "Votação dos partidos e número de candidatos eleitos:\n";
    int i = 0;
    for (const auto &partido : partidos) {
        int candEleitos = 0;
        for (const auto &candidato : partido.getCandidatos()) {
            if (candidato.isEleito()) {
                candEleitos++;
            }
        }

        int totalDeVotosNom = partido.getVotosNominais();
        int totalDeVotosLeg = partido.getVotosLegenda();
        int totalDeVotos = totalDeVotosNom + totalDeVotosLeg;

        response += to_string(++i) + " - " + partido.getSigla() + " - " + to_string(partido.getNumero()) + ", ";
        response += to_string(totalDeVotos) + (totalDeVotos > 1 ? " votos (" : " voto (");
        response += to_string(totalDeVotosNom) + (totalDeVotosNom > 1 ? " nominais e " : " nominal e ");
        response += to_string(totalDeVotosLeg) + (totalDeVotosLeg > 1 ? " de legenda), " : " de legenda), ");
        response += to_string(candEleitos) + (candEleitos > 1 ? " candidatos eleitos\n" : " candidato eleito\n");
    }
    return response;
}

const string Relatorio::primeiroUltimoColocadosPorPartido() const {
    locale loc("pt_BR.UTF-8");
    string response = "Primeiro e último colocados de cada partido:\n";
    int i = 0;

    vector<Partido> partidosOrdenados;
    for (const auto &partido : partidos) {
        if (partido.getCandidatos().size() > 0) {
            partidosOrdenados.push_back(partido);
        }
    }

    sort(partidosOrdenados.begin(), partidosOrdenados.end(), [](const Partido &a, const Partido &b) { return a.getSigla() < b.getSigla(); });

    for (const auto &partido : partidosOrdenados) {
        vector<Candidato> candidatosPartido;
        for (const auto &candidato : partido.getCandidatos()) {
            if (candidato.isDeferido()) {
                candidatosPartido.push_back(candidato);
            }
        }

        if (candidatosPartido.size() == 0) {
            continue;
        }

        response += to_string(++i) + " - " + partido.getSigla() + " - " + to_string(partido.getNumero()) + ", ";
        auto maxCandidato = max_element(candidatosPartido.begin(), candidatosPartido.end(),
                                        [](const Candidato &a, const Candidato &b) { return a.getVotosNominais() < b.getVotosNominais(); });
        response += maxCandidato->getNome() + " (" + to_string(maxCandidato->getNumero()) + ", " + to_string(maxCandidato->getVotosNominais()) +
                    (maxCandidato->getVotosNominais() > 1 ? " votos)" : " voto)");

        auto minCandidato = min_element(candidatosPartido.begin(), candidatosPartido.end(),
                                        [](const Candidato &a, const Candidato &b) { return a.getVotosNominais() < b.getVotosNominais(); });
        response += " / " + minCandidato->getNome() + " (" + to_string(minCandidato->getNumero()) + ", " + to_string(minCandidato->getVotosNominais()) +
                    (minCandidato->getVotosNominais() > 1 ? " votos)\n" : " voto)\n");
    }
    return response;
}

const string Relatorio::eleitosPorFaixaEtaria() const {
    locale loc("pt_BR.UTF-8");
    vector<Candidato> candidatosEleitos;
    for (const auto &candidato : candidatos) {
        if (candidato.isEleito()) {
            candidatosEleitos.push_back(candidato);
        }
    }

    int eleitosAte30 = 0;
    int eleitos30a40 = 0;
    int eleitos40a50 = 0;
    int eleitos50a60 = 0;
    int eleitos60mais = 0;
    double totalEleitos = candidatosEleitos.size();

    for (const auto &candidato : candidatosEleitos) {
        int idadeCandidato = candidato.getDataNascimento().numeroAnos(data);

        if (idadeCandidato < 30) {
            eleitosAte30++;
        } else if (idadeCandidato < 40) {
            eleitos30a40++;
        } else if (idadeCandidato < 50) {
            eleitos40a50++;
        } else if (idadeCandidato < 60) {
            eleitos50a60++;
        } else {
            eleitos60mais++;
        }
    }

    string response = "Eleitos, por faixa etária (na data da eleição):\n";
    response += "      Idade < 30: " + to_string(eleitosAte30) + " (" + to_string(eleitosAte30 / totalEleitos) + ")\n";
    response += "30 <= Idade < 40: " + to_string(eleitos30a40) + " (" + to_string(eleitos30a40 / totalEleitos) + ")\n";
    response += "40 <= Idade < 50: " + to_string(eleitos40a50) + " (" + to_string(eleitos40a50 / totalEleitos) + ")\n";
    response += "50 <= Idade < 60: " + to_string(eleitos50a60) + " (" + to_string(eleitos50a60 / totalEleitos) + ")\n";
    response += "60 <= Idade     : " + to_string(eleitos60mais) + " (" + to_string(eleitos60mais / totalEleitos) + ")\n";

    return response;
}

const string Relatorio::eleitosPorGenero() const {
    locale loc("pt_BR.UTF-8");
    vector<Candidato> candidatosEleitos;
    for (const auto &candidato : candidatos) {
        if (candidato.isEleito()) {
            candidatosEleitos.push_back(candidato);
        }
    }

    int eleitosFeminino = 0;
    int eleitosMasculino = 0;
    double totalEleitos = candidatosEleitos.size();

    for (const auto &candidato : candidatosEleitos) {
        if (candidato.getGenero() == Genero::FEMININO) {
            eleitosFeminino++;
        } else {
            eleitosMasculino++;
        }
    }

    string response = "Eleitos, por gênero:\n";
    response += "Feminino:  " + to_string(eleitosFeminino) + " (" + to_string(eleitosFeminino / totalEleitos) + ")\n";
    response += "Masculino: " + to_string(eleitosMasculino) + " (" + to_string(eleitosMasculino / totalEleitos) + ")\n";
    return response;
}

const string Relatorio::totalDeVotos() const {
    locale loc("pt_BR.UTF-8");
    double totalDeVotos = 0;
    int totalDeVotosNominais = 0;
    int totalDeVotosLegenda = 0;
    for (const auto &partido : partidos) {
        totalDeVotosNominais += partido.getVotosNominais();
        totalDeVotosLegenda += partido.getVotosLegenda();
    }

    totalDeVotos = totalDeVotosNominais + totalDeVotosLegenda;

    string response = "Total de votos válidos:    " + to_string(totalDeVotos) + "\n";
    response += "Total de votos nominais:   " + to_string(totalDeVotosNominais) + " (" + to_string(totalDeVotosNominais / totalDeVotos) + ")\n";
    response += "Total de votos de legenda: " + to_string(totalDeVotosLegenda) + " (" + to_string(totalDeVotosLegenda / totalDeVotos) + ")\n";

    return response;
}
