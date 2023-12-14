#include "leitorCsv.h"

#define INDICE_CARGO 13
#define INDICE_N_PARTIDO 27
#define INDICE_NOME_PARTIDO 28
#define INDICE_N_FED_PARTIDO 30
#define INDICE_N_CANDIDATO 16
#define INDICE_NOME_CANDIDATO 18
#define INDICE_DEFERIDO 68
#define INDICE_ELEITO 56
#define INDICE_GENERO 45
#define INDICE_TIPO_DST_VTS 67
#define INDICE_DATA_NASC 42

#define INDICE_CARGO_VOTACAO 17
#define INDICE_NUMERO_CANDIDATO 19
#define INDICE_QUANTIDADE_VOTOS 21
#define NUMERO_MINIMO_CANDIDATO 95
#define NUMERO_MAXIMO_CANDIDATO 98

using namespace std;

Genero intToGenero(const int &genero) {
    if (genero == 2) {
        return Genero::MASCULINO;
    } else {
        return Genero::FEMININO;
    }
}

TipoDestinoVotos strToTipoDestinoVotos(const string &tipoDestinoVotos) {
    if (tipoDestinoVotos == "Válido (legenda)") {
        return TipoDestinoVotos::VALIDO_LEGENDA;
    } else if (tipoDestinoVotos == "Válido") {
        return TipoDestinoVotos::VALIDO_NOMINAL;
    } else {
        return TipoDestinoVotos::INVALIDO;
    }
}

// nao houve outra solução a senão fazer cópia ou eu gastaria muitas linhas de código
string iso_8859_1_to_utf8(string str) {

    // adaptado de: https://stackoverflow.com/a/39884120 :-)
    string strOut;
    for (string::iterator it = str.begin(); it != str.end(); ++it) {
        uint8_t ch = *it;
        if (ch < 0x80) {
            // já está na faixa ASCII (bit mais significativo 0), só copiar para a saída
            strOut.push_back(ch);
        } else {
            // está na faixa ASCII-estendido, escrever 2 bytes de acordo com UTF-8
            // o primeiro byte codifica os 2 bits mais significativos do byte original (ISO-8859-1)
            strOut.push_back(0b11000000 | (ch >> 6));
            // o segundo byte codifica os 6 bits menos significativos do byte original (ISO-8859-1)
            strOut.push_back(0b10000000 | (ch & 0b00111111));
        }
    }
    return strOut;
}

void _processarLinhaCandidato(vector<string> &campos, map<int, Partido *> &partidos, map<int, Candidato *> &candidatos, int cargo) {
    campos[INDICE_CARGO] = iso_8859_1_to_utf8(campos[INDICE_CARGO].substr(1, campos[INDICE_CARGO].length() - 2));
    campos[INDICE_N_PARTIDO] = iso_8859_1_to_utf8(campos[INDICE_N_PARTIDO].substr(1, campos[INDICE_N_PARTIDO].length() - 2));
    campos[INDICE_NOME_PARTIDO] = iso_8859_1_to_utf8(campos[INDICE_NOME_PARTIDO].substr(1, campos[INDICE_NOME_PARTIDO].length() - 2));
    campos[INDICE_N_FED_PARTIDO] = iso_8859_1_to_utf8(campos[INDICE_N_FED_PARTIDO].substr(1, campos[INDICE_N_FED_PARTIDO].length() - 2));
    campos[INDICE_N_CANDIDATO] = iso_8859_1_to_utf8(campos[INDICE_N_CANDIDATO].substr(1, campos[INDICE_N_CANDIDATO].length() - 2));
    campos[INDICE_NOME_CANDIDATO] = iso_8859_1_to_utf8(campos[INDICE_NOME_CANDIDATO].substr(1, campos[INDICE_NOME_CANDIDATO].length() - 2));
    campos[INDICE_DEFERIDO] = iso_8859_1_to_utf8(campos[INDICE_DEFERIDO].substr(1, campos[INDICE_DEFERIDO].length() - 2));
    campos[INDICE_GENERO] = iso_8859_1_to_utf8(campos[INDICE_GENERO].substr(1, campos[INDICE_GENERO].length() - 2));
    campos[INDICE_TIPO_DST_VTS] = iso_8859_1_to_utf8(campos[INDICE_TIPO_DST_VTS].substr(1, campos[INDICE_TIPO_DST_VTS].length() - 2));
    campos[INDICE_ELEITO] = iso_8859_1_to_utf8(campos[INDICE_ELEITO].substr(1, campos[INDICE_ELEITO].length() - 2));
    campos[INDICE_DATA_NASC] = iso_8859_1_to_utf8(campos[INDICE_DATA_NASC].substr(1, campos[INDICE_DATA_NASC].length() - 2));

    try {
        int nPartido = stoi(campos[INDICE_N_PARTIDO]);
        string nomePartido = campos[INDICE_NOME_PARTIDO];
        int nFedPartido = stoi(campos[INDICE_N_FED_PARTIDO]);

        if (partidos.count(nPartido) == 0) {
            partidos.insert(pair<int, Partido *>(nPartido, new Partido(nPartido, nomePartido, nFedPartido)));
        }

        Partido *partido = partidos.at(nPartido);

        if (cargo == stoi(campos[INDICE_CARGO])) {
            bool deferido = stoi(campos[INDICE_DEFERIDO]) == 2 || stoi(campos[INDICE_DEFERIDO]) == 16;
            TipoDestinoVotos tipoDstVts = strToTipoDestinoVotos(campos[INDICE_TIPO_DST_VTS]);

            if (!deferido && tipoDstVts != TipoDestinoVotos::VALIDO_LEGENDA) {
                return;
            }

            int nCandidato = stoi(campos[INDICE_N_CANDIDATO]);
            string nomeCandidato = campos[INDICE_NOME_CANDIDATO];
            bool eleito = stoi(campos[INDICE_ELEITO]) == 2 || stoi(campos[INDICE_ELEITO]) == 3;
            Genero genero = intToGenero(stoi(campos[INDICE_GENERO]));
            Data dataNasc = campos[INDICE_DATA_NASC].empty() ? Data() : Data(campos[INDICE_DATA_NASC]);

            Candidato *candidato = new Candidato(nCandidato, nomeCandidato, partido, deferido, eleito, genero, tipoDstVts, dataNasc);
            candidatos.insert(pair<int, Candidato *>(nCandidato, candidato));
            partido->addCandidato(*candidato);
        }

    } catch (exception &e) {
        cout << "Erro ao processar linha do arquivo de candidatos: " << e.what() << endl;
    }
}

Eleicao *eleicaoFromCsv(string &nomeArquivo, int cargo, Data &dataEleicao) {
    ifstream inputStream(nomeArquivo);
    string linha;
    map<int, Partido *> partidos = map<int, Partido *>();
    map<int, Candidato *> candidatos = map<int, Candidato *>();

    getline(inputStream, linha); // cabeçalho
    while (getline(inputStream, linha)) {
        istringstream linhaStream(linha);
        vector<string> campos;
        string campo;
        while (getline(linhaStream, campo, ';')) {
            campos.push_back(campo);
        }
        _processarLinhaCandidato(campos, partidos, candidatos, cargo);
    }
    inputStream.close();

    return new Eleicao(candidatos, partidos, cargo, dataEleicao);
}

map<int, int> *mapaVotacaoFromCsv(string &nomeArquivo, int cargo) {
    map<int, int> votos;

    ifstream file(nomeArquivo);
    string linha;
    getline(file, linha); // ignora a primeira linha

    while (getline(file, linha)) {
        vector<string> campos;
        string campo;
        istringstream linhaStream(linha);
        while (getline(linhaStream, campo, ';')) {
            campos.push_back(campo);
        }

        int cargoLido = stoi(campos[INDICE_CARGO_VOTACAO].substr(1, campos[INDICE_CARGO_VOTACAO].length() - 2));
        if (cargo == cargoLido) {
            int numeroCandidato = stoi(campos[INDICE_NUMERO_CANDIDATO].substr(1, campos[INDICE_NUMERO_CANDIDATO].length() - 2));
            int quantidadeVotos = stoi(campos[INDICE_QUANTIDADE_VOTOS].substr(1, campos[INDICE_QUANTIDADE_VOTOS].length() - 2));

            if (numeroCandidato >= NUMERO_MINIMO_CANDIDATO && numeroCandidato <= NUMERO_MAXIMO_CANDIDATO) {
                continue;
            }

            if (votos.count(numeroCandidato)) {
                quantidadeVotos += votos.at(numeroCandidato);
            }

            votos.insert(pair<int, int>(numeroCandidato, quantidadeVotos));
        }
    }

    file.close();
    return new map<int, int>(votos);
}
