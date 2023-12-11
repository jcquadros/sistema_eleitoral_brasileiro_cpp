
#include <map>
#include <string>

#include "data.h"
#include "eleicao.h"
#include "leitorCsv.h"
#include "relatorio.h"

#define CARGO_ESTADUAL 6
#define CARGO_FEDERAL 7

using namespace std;

int getCargoFromArgs(const string &arg) {
    if (arg == "--estadual") {
        return CARGO_ESTADUAL;
    } else if (arg == "--federal") {
        return CARGO_FEDERAL;
    }
    return 0; // Opção de cargo inválida
}

void printRelatorios(const Relatorio &r) {
    cout << r.numeroDeVagasEleicao() << endl;
    cout << r.candidatosEleitos() << endl;
    cout << r.candidatosMaisVotados() << endl;
    cout << r.candidatosNaoEleitosEleitosMajoritariamente() << endl;
    cout << r.candidatosEleitosNaoEleitosMajoritariamente() << endl;
    cout << r.votacaoPartidos() << endl;
    cout << r.primeiroUltimoColocadosPorPartido() << endl;
    cout << r.eleitosPorFaixaEtaria() << endl;
    cout << r.eleitosPorGenero() << endl;
    cout << r.totalDeVotos() << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        cout << "Usage: ./deputados <opção_de_cargo> <caminho_arquivo_candidatos> <caminho_arquivo_votacao> <data>" << endl;
        return 0;
    }

    int cargo = getCargoFromArgs(argv[1]);
    if (cargo == 0) {
        cout << "Opção de cargo inválida" << endl;
        return 0;
    }

    string caminhoArquivoCandidatos = argv[2];
    string caminhoArquivoVotacao = argv[3];
    string dataStr = argv[4];

    Data data(dataStr);

    Eleicao *eleicao = eleicaoFromCsv(caminhoArquivoCandidatos, cargo, data);
    map<int, int> *mapaVotacao = mapaVotacaoFromCsv(caminhoArquivoVotacao, cargo);
    eleicao->processaVotacao(*mapaVotacao);

    Relatorio r(*eleicao);
    printRelatorios(r);

    delete eleicao;
    delete mapaVotacao;

    return 0;
}
