#include "leitorCsv.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>


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


using namespace std;

string iso_8859_1_to_utf8(string &str)
{
    // adaptado de: https://stackoverflow.com/a/39884120 :-)
    string strOut;
    for (string::iterator it = str.begin(); it != str.end(); ++it)
    {
        uint8_t ch = *it;
        if (ch < 0x80)
        {
            // já está na faixa ASCII (bit mais significativo 0), só copiar para a saída
            strOut.push_back(ch);
        }
        else
        {
            // está na faixa ASCII-estendido, escrever 2 bytes de acordo com UTF-8
            // o primeiro byte codifica os 2 bits mais significativos do byte original (ISO-8859-1)
            strOut.push_back(0b11000000 | (ch >> 6));
            // o segundo byte codifica os 6 bits menos significativos do byte original (ISO-8859-1)
            strOut.push_back(0b10000000 | (ch & 0b00111111));
        }
    }
    return strOut;
}

// void leDepartamentos(Empresa &e)
// {
//     ifstream inputStream("departamentos.csv");
//     string linha;
//     getline(inputStream,linha); // cabeçalho
//     while (getline(inputStream,linha))
//     {
//         istringstream linhaStream(linha);
//         string codigoDepStr;
//         getline(linhaStream,codigoDepStr,';');
//         int codigoDep = stoi(codigoDepStr);
//         string nomeDepartamento;
//         getline(linhaStream,nomeDepartamento,';');
//         e.createDepartamento(codigoDep,nomeDepartamento);
//     }
//     inputStream.close();
// }

void _processarLinhaCandidato(vector<string> &campos, map<int, Partido> &partidos, map<int, Candidato> &candidatos, int cargo){
    campos[INDICE_CARGO]=iso_8859_1_to_utf8(campos[INDICE_CARGO].substr(1,campos[INDICE_CARGO].length()-2));
    campos[INDICE_N_PARTIDO]=iso_8859_1_to_utf8(campos[INDICE_N_PARTIDO].substr(1,campos[INDICE_N_PARTIDO].length()-2));
    campos[INDICE_NOME_PARTIDO]=iso_8859_1_to_utf8(campos[INDICE_NOME_PARTIDO].substr(1,campos[INDICE_NOME_PARTIDO].length()-2));
    campos[INDICE_N_FED_PARTIDO]=iso_8859_1_to_utf8(campos[INDICE_N_FED_PARTIDO].substr(1,campos[INDICE_N_FED_PARTIDO].length()-2));
    campos[INDICE_N_CANDIDATO]=iso_8859_1_to_utf8(campos[INDICE_N_CANDIDATO].substr(1,campos[INDICE_N_CANDIDATO].length()-2));
    campos[INDICE_NOME_CANDIDATO]=iso_8859_1_to_utf8(campos[INDICE_NOME_CANDIDATO].substr(1,campos[INDICE_NOME_CANDIDATO].length()-2));
    campos[INDICE_DEFERIDO]=iso_8859_1_to_utf8(campos[INDICE_DEFERIDO].substr(1,campos[INDICE_DEFERIDO].length()-2));
    campos[INDICE_GENERO]=iso_8859_1_to_utf8(campos[INDICE_GENERO].substr(1,campos[INDICE_GENERO].length()-2));
    campos[INDICE_TIPO_DST_VTS]=iso_8859_1_to_utf8(campos[INDICE_TIPO_DST_VTS].substr(1,campos[INDICE_TIPO_DST_VTS].length()-2));
    campos[INDICE_ELEITO]=iso_8859_1_to_utf8(campos[INDICE_ELEITO].substr(1,campos[INDICE_ELEITO].length()-2));
    campos[INDICE_DATA_NASC]=iso_8859_1_to_utf8(campos[INDICE_DATA_NASC].substr(1,campos[INDICE_DATA_NASC].length()-2));
    
    
}


Eleicao &eleicaoFromCsv(string &nomeArquivo, int cargo, Data &dataEleicao)
{
    ifstream inputStream(nomeArquivo);
    string linha;
    map<int, Partido> partidos;
    map<int, Candidato> candidatos;

    getline(inputStream, linha); // cabeçalho
    while (getline(inputStream, linha))
    {
        istringstream linhaStream(linha);
        vector<string> campos;
        string campo;
        while (getline(linhaStream, campo, ';'))
        {
            campos.push_back(campo);
        }
        _processarLinhaCandidato(campos, partidos, candidatos, cargo);
    }
    inputStream.close(); 
}






void processarLinhaCandidato(std::vector<std::string>& linha, std::map<int, Partido>& partidos,
                             std::map<int, Candidato>& candidatos, int cargo) {
    int INDICE_CARGO = 13;
    int INDICE_N_PARTIDO = 27;
    int INDICE_NOME_PARTIDO = 28;
    int INDICE_N_FED_PARTIDO = 30;
    int INDICE_N_CANDIDATO = 16;
    int INDICE_NOME_CANDIDATO = 18;
    int INDICE_DEFERIDO = 68;
    int INDICE_ELEITO = 56;
    int INDICE_GENERO = 45;
    int INDICE_TIPO_DST_VTS = 67;
    int INDICE_DATA_NASC = 42;

    linha[INDICE_CARGO] = linha[INDICE_CARGO].substr(1, linha[INDICE_CARGO].length() - 2);
    linha[INDICE_N_PARTIDO] = linha[INDICE_N_PARTIDO].substr(1, linha[INDICE_N_PARTIDO].length() - 2);
    linha[INDICE_NOME_PARTIDO] = linha[INDICE_NOME_PARTIDO].substr(1, linha[INDICE_NOME_PARTIDO].length() - 2);
    linha[INDICE_N_FED_PARTIDO] = linha[INDICE_N_FED_PARTIDO].substr(1, linha[INDICE_N_FED_PARTIDO].length() - 2);
    linha[INDICE_N_CANDIDATO] = linha[INDICE_N_CANDIDATO].substr(1, linha[INDICE_N_CANDIDATO].length() - 2);
    linha[INDICE_NOME_CANDIDATO] = linha[INDICE_NOME_CANDIDATO].substr(1, linha[INDICE_NOME_CANDIDATO].length() - 2);
    linha[INDICE_DEFERIDO] = linha[INDICE_DEFERIDO].substr(1, linha[INDICE_DEFERIDO].length() - 2);
    linha[INDICE_GENERO] = linha[INDICE_GENERO].substr(1, linha[INDICE_GENERO].length() - 2);
    linha[INDICE_TIPO_DST_VTS] = linha[INDICE_TIPO_DST_VTS].substr(1, linha[INDICE_TIPO_DST_VTS].length() - 2);
    linha[INDICE_ELEITO] = linha[INDICE_ELEITO].substr(1, linha[INDICE_ELEITO].length() - 2);
    linha[INDICE_DATA_NASC] = linha[INDICE_DATA_NASC].substr(1, linha[INDICE_DATA_NASC].length() - 2);

    try {
        int nPartido = std::stoi(linha[INDICE_N_PARTIDO]);
        std::string nomePartido = linha[INDICE_NOME_PARTIDO];
        int nFedPartido = std::stoi(linha[INDICE_N_FED_PARTIDO]);

        if (partidos.find(nPartido) == partidos.end()) {
            partidos[nPartido] = Partido(nPartido, nomePartido, nFedPartido);
        }

        Partido partido = partidos[nPartido];

        if (cargo == std::stoi(linha[INDICE_CARGO])) {
            bool deferido = std::stoi(linha[INDICE_DEFERIDO]) == 2 || std::stoi(linha[INDICE_DEFERIDO]) == 16;
            TipoDestinoVotos tipoDstVts = TipoDestinoVotos::getTipoDestinoVotos(linha[INDICE_TIPO_DST_VTS]);

            if (!deferido && tipoDstVts != TipoDestinoVotos::VALIDO_LEGENDA) {
                return;
            }

            int nCandidato = std::stoi(linha[INDICE_N_CANDIDATO]);
            std::string nomeCandidato = linha[INDICE_NOME_CANDIDATO];
            bool eleito = std::stoi(linha[INDICE_ELEITO]) == 2 || std::stoi(linha[INDICE_ELEITO]) == 3;
            Genero genero = Genero::getGenero(std::stoi(linha[INDICE_GENERO]));
            Data dataNasc = linha[INDICE_DATA_NASC].empty() ? Data() : Data::parseData(linha[INDICE_DATA_NASC], "dd/MM/yyyy");

            candidatos[nCandidato] = Candidato(nCandidato, nomeCandidato, partido, deferido, eleito, genero, tipoDstVts, dataNasc);
        }
    } catch (std::exception& e) {
        throw LeituraDeArquivoException("Erro ao converter um número durante a criação da eleição", e);
    }
}
