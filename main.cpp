
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

#include "candidato.h"
#include "data.h"
#include "eleicao.h"
#include "genero.h"
#include "partido.h"
#include "tipoDestinoVotos.h"

string strGenero(Genero genero) {
    switch (genero) {
    case Genero::MASCULINO:
        return "Masculino";
    case Genero::FEMININO:
        return "Feminino";
    default:
        return "Não informado";
    }
}

string strData(Data data) { return to_string(data.getDia()) + "/" + to_string(data.getMes()) + "/" + to_string(data.getAno()); }

string strTipoDestinoVotos(TipoDestinoVotos tipoDestinoVotos) {
    switch (tipoDestinoVotos) {
    case TipoDestinoVotos::VALIDO_LEGENDA:
        return "valido_legenda";
    case TipoDestinoVotos::VALIDO_NOMINAL:
        return "valido_nominal";
    default:
        return "invalido";
    }
}

int main(int argc, char **argv) {

    // Criação de partidos
    Partido partido1(12, "ABC", 1);
    Partido partido2(13, "DEF", 1);
    Partido partido3(14, "GHI", 1);

    // Criação de candidatos
    Candidato candidato1(12345, "Fulano", &partido1, true, true, Genero::MASCULINO, TipoDestinoVotos::VALIDO_NOMINAL, Data(1, 1, 1990));
    Candidato candidato2(12346, "Ciclano", &partido2, true, true, Genero::MASCULINO, TipoDestinoVotos::VALIDO_NOMINAL, Data(1, 1, 1990));
    Candidato candidato3(12347, "Beltrano", &partido3, true, true, Genero::MASCULINO, TipoDestinoVotos::VALIDO_NOMINAL, Data(1, 1, 1990));
    Candidato candidato4(12348, "Fulana", &partido1, true, true, Genero::FEMININO, TipoDestinoVotos::VALIDO_NOMINAL, Data(1, 1, 1990));
    Candidato candidato5(12349, "Ciclana", &partido2, true, true, Genero::FEMININO, TipoDestinoVotos::VALIDO_NOMINAL, Data(1, 1, 1990));
    Candidato candidato6(12350, "Beltrana", &partido3, true, true, Genero::FEMININO, TipoDestinoVotos::VALIDO_NOMINAL, Data(1, 1, 1990));

    // Criação de eleição
    map<int, Candidato> candidatos = {{candidato1.getNumero(), candidato1}, {candidato2.getNumero(), candidato2}, {candidato3.getNumero(), candidato3},
                                      {candidato4.getNumero(), candidato4}, {candidato5.getNumero(), candidato5}, {candidato6.getNumero(), candidato6}};

    map<int, Partido> partidos = {{partido1.getNumero(), partido1}, {partido2.getNumero(), partido2}, {partido3.getNumero(), partido3}};

    Eleicao eleicao(candidatos, partidos, 1, Data(1, 1, 2020));

    // Votação
    map<int, int> votos = {{partido1.getNumero(), 100},  {partido2.getNumero(), 200},  {partido3.getNumero(), 300},
                           {candidato1.getNumero(), 10}, {candidato2.getNumero(), 20}, {candidato3.getNumero(), 30},
                           {candidato4.getNumero(), 40}, {candidato5.getNumero(), 50}, {candidato6.getNumero(), 60}};
    eleicao.processaVotacao(votos);

    // Impressão de resultados
    cout << "Eleição " << eleicao.getData().getAno() << endl;
    cout << "Cargo: " << eleicao.getCargo() << endl;
    cout << "Data: " << strData(eleicao.getData()) << endl;
    cout << endl;

    cout << "Partidos:" << endl;
    for (const auto &partido : eleicao.getPartidos()) {
        cout << "Número: " << partido.second.getNumero() << endl;
        cout << "Sigla: " << partido.second.getSigla() << endl;
        cout << "Federação: " << partido.second.getFederacao() << endl;
        cout << "Votos de legenda: " << partido.second.getVotosLegenda() << endl;
        cout << "Votos nominais: " << partido.second.getVotosNominais() << endl;
        cout << endl;
    }

    cout << "Candidatos:" << endl;

    for (const auto &candidato : eleicao.getCandidatos()) {
        cout << "Número: " << candidato.second.getNumero() << endl;
        cout << "Nome: " << candidato.second.getNome() << endl;
        cout << "Partido: " << candidato.second.getPartido()->getSigla() << endl;
        cout << "Deferido: " << (candidato.second.isDeferido() ? "Sim" : "Não") << endl;
        cout << "Eleito: " << (candidato.second.isEleito() ? "Sim" : "Não") << endl;
        cout << "Gênero: " << strGenero(candidato.second.getGenero()) << endl;
        cout << "Tipo de destino dos votos: " << strTipoDestinoVotos(candidato.second.getTipoDestinoVotos()) << endl;
        cout << "Data de nascimento: " << strData(candidato.second.getDataNascimento()) << endl;
        cout << "Votos nominais: " << candidato.second.getVotosNominais() << endl;
        cout << endl;
    }

    return 0;
}