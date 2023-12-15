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

    // ordenar em ordem decrescente do numero de votos e em caso de desempate os mais velhos tem prioridade
    for (const auto &candidato : eleicao.getCandidatos()) {
        // cout << candidato.second->getNome() << endl;
        candidatos.push_back(*(Candidato *)candidato.second);
    }

    for (const auto &partido : eleicao.getPartidos()) {
        // cout << partido.second->getSigla() << endl;
        partidos.push_back(*(Partido *)partido.second);
    }
    // cout << "Salvou" << endl;

    sort(candidatos.begin(), candidatos.end(), [](Candidato &a, Candidato &b) {
        if (a.getVotosNominais() != b.getVotosNominais()) {
            return a.getVotosNominais() > b.getVotosNominais();
        }
        return a.getDataNascimento().getDia() < b.getDataNascimento().getDia();
    });

    sort(partidos.begin(), partidos.end(), [](Partido &a, Partido &b) {
        if (a.getVotosLegenda() + a.getVotosNominais() != b.getVotosLegenda() + b.getVotosNominais()) {
            return (a.getVotosLegenda() + a.getVotosNominais()) > (b.getVotosLegenda() + b.getVotosNominais());
        }
        return a.getNumero() < b.getNumero();
    });

    // cout << "Ordenou" << endl;

    // for (const auto &candidato : candidatos) {
    //     cout << candidato.getNome() << " Numero de votos: " << candidato.getVotosNominais()
    //          << " Data de nascimento: " << candidato.getDataNascimento().getDataNascimentoStr() << endl;
    // }

    // for (const auto &partido : partidos) {
    //     cout << partido.getNumero() << " - " << partido.getSigla() << " Numero de votos: " << partido.getVotosLegenda() + partido.getVotosNominais() << endl;
    // }
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

void Relatorio::numeroDeVagasEleicao() const {
    locale brasilLocale("pt_BR.UTF-8");
    cout.imbue(brasilLocale);
    cout << "Número de vagas: " << fixed << setprecision(0) << numeroDeVagas() << "\n" << endl;
}

void Relatorio::candidatosEleitos() const {
    locale brasilLocale("pt_BR.UTF-8");
    cout.imbue(brasilLocale);
    cout << (this->cargo == 6 ? "Deputados federais eleitos:" : "Deputados estaduais eleitos:") << endl;
    int i = 0;

    vector<Candidato> candidatosEleitos;
    for (const auto &candidato : candidatos) {
        if (candidato.isEleito()) {
            candidatosEleitos.push_back(candidato);
        }
    }

    for (const auto &candidato : candidatosEleitos) {
        Partido *partido = candidato.getPartido();
        cout << ++i << " - " << (partido->getFederacao() != -1 ? "*" : "");
        cout << candidato.getNome() << " (" + partido->getSigla() << ", " << candidato.getVotosNominais() << " votos)" << endl;
    }
    cout << endl;
}

void Relatorio::candidatosMaisVotados() const {
    locale brasilLocale("pt_BR.UTF-8");
    cout.imbue(brasilLocale);

    cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;
    int i = 0;

    vector<Candidato> candidatosOrdenadosVotos = candidatos;
    candidatosOrdenadosVotos.resize(numeroDeVagas());

    for (const auto &candidato : candidatosOrdenadosVotos) {
        Partido *partido = candidato.getPartido();
        cout << ++i << " - " << (partido->getFederacao() != -1 ? "*" : "");
        cout << candidato.getNome() << " (" + partido->getSigla() << ", " << candidato.getVotosNominais() << " votos)" << endl;
    }

    cout << endl;
}

void Relatorio::candidatosNaoEleitosEleitosMajoritariamente() const {
    locale brasilLocale("pt_BR.UTF-8");
    cout.imbue(brasilLocale);
    cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << endl;
    cout << "(com sua posição no ranking de mais votados)" << endl;
    int numDeVagas = numeroDeVagas();

    for (int i = 0; i < numDeVagas; i++) {
        if (!candidatos[i].isEleito()) {
            const Candidato &candidato = candidatos[i];
            Partido *partido = candidato.getPartido();
            cout << (i + 1) << " - " << (partido->getFederacao() != -1 ? "*" : "");
            cout << candidato.getNome() << " (" + partido->getSigla() << ", " << candidato.getVotosNominais() << " votos)" << endl;
        }
    }
    cout << endl;
}

void Relatorio::candidatosEleitosNaoEleitosMajoritariamente() const {
    locale brasilLocale("pt_BR.UTF-8");
    cout.imbue(brasilLocale);
    cout << "Eleitos, que se beneficiaram do sistema proporcional:" << endl;
    cout << "(com sua posição no ranking de mais votados)" << endl;

    for (int i = numeroDeVagas(); i < (long int)candidatos.size(); i++) {
        if (candidatos[i].isEleito()) {
            const Candidato &candidato = candidatos[i];
            Partido *partido = candidato.getPartido();
            cout << (i + 1) << " - " << (partido->getFederacao() != -1 ? "*" : "");
            cout << candidato.getNome() << " (" << partido->getSigla() << ", " << candidato.getVotosNominais() << " votos)" << endl;
        }
    }
    cout << endl;
}

void Relatorio::votacaoPartidos() const {
    locale brasilLocale("pt_BR.UTF-8");
    cout.imbue(brasilLocale);
    cout << "Votação dos partidos e número de candidatos eleitos:" << endl;
    int i = 0;
    for (const auto &partido : partidos) {
        int candEleitos = 0;
        for (const auto &candidato : partido.getCandidatos()) {
            if (candidato->isEleito()) {
                candEleitos++;
            }
        }

        int totalDeVotosNom = partido.getVotosNominais();
        int totalDeVotosLeg = partido.getVotosLegenda();
        int totalDeVotos = totalDeVotosNom + totalDeVotosLeg;

        cout << (++i) << " - " << partido.getSigla() << " - " << to_string(partido.getNumero()) << ", ";
        cout << totalDeVotos << (totalDeVotos > 1 ? " votos (" : " voto (");
        cout << totalDeVotosNom << (totalDeVotosNom > 1 ? " nominais e " : " nominal e ");
        cout << totalDeVotosLeg << (totalDeVotosLeg > 1 ? " de legenda), " : " de legenda), ");
        cout << candEleitos << (candEleitos > 1 ? " candidatos eleitos" : " candidato eleito") << endl;
    }
    cout << endl;
}

void Relatorio::primeiroUltimoColocadosPorPartido() const {
    locale brasilLocale("pt_BR.UTF-8");
    cout.imbue(brasilLocale);
    cout << "Primeiro e último colocados de cada partido:" << endl;
    int i = 0;

    vector<Partido> partidosOrdenados;
    for (const auto &partido : partidos) {
        if (partido.getCandidatos().size() > 0) {
            partidosOrdenados.push_back(partido);
        }
    }

    // partido ordenado em ordem decrescente a partir do numero de votos do maior candidato do partido
    sort(partidosOrdenados.begin(), partidosOrdenados.end(), [](const Partido &a, const Partido &b) {
        const vector<Candidato *> &candidatosPartidoA = a.getCandidatos();
        const vector<Candidato *> &candidatosPartidoB = b.getCandidatos();

        Candidato *maxCandidatoA = candidatosPartidoA[0];
        for (const auto &candidato : candidatosPartidoA) {
            if (candidato->getVotosNominais() != maxCandidatoA->getVotosNominais()) {
                if (candidato->getVotosNominais() > maxCandidatoA->getVotosNominais()) {
                    maxCandidatoA = candidato;
                }
            } else {
                if (candidato->getDataNascimento().getDia() < maxCandidatoA->getDataNascimento().getDia()) {
                    maxCandidatoA = candidato;
                }
            }
        }

        Candidato *maxCandidatoB = candidatosPartidoB[0];
        for (const auto &candidato : candidatosPartidoB) {
            if (candidato->getVotosNominais() != maxCandidatoB->getVotosNominais()) {
                if (candidato->getVotosNominais() > maxCandidatoB->getVotosNominais()) {
                    maxCandidatoB = candidato;
                }
            } else {
                if (candidato->getDataNascimento().getDia() < maxCandidatoB->getDataNascimento().getDia()) {
                    maxCandidatoB = candidato;
                }
            }
        }
        if (maxCandidatoA->getVotosNominais() != maxCandidatoB->getVotosNominais()) {
            return maxCandidatoA->getVotosNominais() > maxCandidatoB->getVotosNominais();
        }
        return a.getNumero() < b.getNumero();
    });

    for (const auto &partido : partidosOrdenados) {
        vector<Candidato *> candidatosPartido;
        for (const auto &candidato : partido.getCandidatos()) {
            if (candidato->isDeferido()) {
                candidatosPartido.push_back(candidato);
            }
        }

        if (candidatosPartido.size() == 0) {
            continue;
        }
        Candidato *maxCandidato = candidatosPartido[0];
        Candidato *minCandidato = candidatosPartido[0];
        for (const auto &candidato : candidatosPartido) {
            if (candidato->getVotosNominais() != maxCandidato->getVotosNominais()) {
                if (candidato->getVotosNominais() > maxCandidato->getVotosNominais()) {
                    maxCandidato = candidato;
                }
            } else {
                if (candidato->getDataNascimento().getDia() < maxCandidato->getDataNascimento().getDia()) {
                    maxCandidato = candidato;
                }
            }

            if (candidato->getVotosNominais() != minCandidato->getVotosNominais()) {
                if (candidato->getVotosNominais() < minCandidato->getVotosNominais()) {
                    minCandidato = candidato;
                }
            } else {
                if (candidato->getDataNascimento().getDia() > minCandidato->getDataNascimento().getDia()) {
                    minCandidato = candidato;
                }
            }
        }

        cout << (++i) << " - " << partido.getSigla() << " - " << to_string(partido.getNumero()) << ", ";
        cout << maxCandidato->getNome() << " (" << to_string(maxCandidato->getNumero()) << ", " << maxCandidato->getVotosNominais()
             << (maxCandidato->getVotosNominais() > 1 ? " votos)" : " voto)");

        cout << " / " << minCandidato->getNome() << " (" << to_string(minCandidato->getNumero()) << ", " << minCandidato->getVotosNominais()
             << (minCandidato->getVotosNominais() > 1 ? " votos)" : " voto)") << endl;
    }
    cout << endl;
}

void Relatorio::eleitosPorFaixaEtaria() const {
    locale brasilLocale("pt_BR.UTF-8");
    cout.imbue(brasilLocale);

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

    cout << "Eleitos, por faixa etária (na data da eleição):" << endl;
    cout << "      Idade < 30: " << (eleitosAte30) << " (" << fixed << setprecision(2) << (eleitosAte30 / totalEleitos * 100) << fixed << setprecision(0)
         << "%)" << endl;
    cout << "30 <= Idade < 40: " << (eleitos30a40) << " (" << fixed << setprecision(2) << (eleitos30a40 / totalEleitos * 100) << fixed << setprecision(0)
         << "%)" << endl;
    cout << "40 <= Idade < 50: " << (eleitos40a50) << " (" << fixed << setprecision(2) << (eleitos40a50 / totalEleitos * 100) << fixed << setprecision(0)
         << "%)" << endl;
    cout << "50 <= Idade < 60: " << (eleitos50a60) << " (" << fixed << setprecision(2) << (eleitos50a60 / totalEleitos * 100) << fixed << setprecision(0)
         << "%)" << endl;
    cout << "60 <= Idade     : " << (eleitos60mais) << " (" << fixed << setprecision(2) << (eleitos60mais / totalEleitos * 100) << fixed << setprecision(0)
         << "%)\n"
         << endl;
}

void Relatorio::eleitosPorGenero() const {
    locale brasilLocale("pt_BR.UTF-8");
    cout.imbue(brasilLocale);
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

    cout << "Eleitos, por gênero:" << endl;
    cout << fixed << setprecision(2);
    cout << "Feminino:  " << eleitosFeminino << " (" << fixed << setprecision(2) << (eleitosFeminino / totalEleitos * 100) << fixed << setprecision(0) << "%)"
         << endl;
    cout << "Masculino: " << eleitosMasculino << " (" << fixed << setprecision(2) << (eleitosMasculino / totalEleitos * 100) << fixed << setprecision(0)
         << "%)\n"
         << endl;
}

void Relatorio::totalDeVotos() const {
    locale brasilLocale("pt_BR.UTF-8");
    cout.imbue(brasilLocale);
    double totalDeVotos = 0;
    int totalDeVotosNominais = 0;
    int totalDeVotosLegenda = 0;
    for (const auto &partido : partidos) {
        totalDeVotosNominais += partido.getVotosNominais();
        totalDeVotosLegenda += partido.getVotosLegenda();
    }

    totalDeVotos = totalDeVotosNominais + totalDeVotosLegenda;

    cout << "Total de votos válidos:    " << totalDeVotos << endl;
    cout << "Total de votos nominais:   " << totalDeVotosNominais << " (" << fixed << setprecision(2) << (totalDeVotosNominais / totalDeVotos * 100) << fixed
         << setprecision(0) << "%)" << endl;
    cout << "Total de votos de legenda: " << totalDeVotosLegenda << " (" << fixed << setprecision(2) << (totalDeVotosLegenda / totalDeVotos * 100) << fixed
         << setprecision(0) << "%)\n"
         << endl;
}
