#if !defined(CANDIDATO_H)
#define CANDIDATO_H

#include <string>
using namespace std;

#include "data.h"

enum class Genero { MASCULINO = 2, FEMININO = 4 };
enum class TipoDestinoVotos { VALIDO_LEGENDA, VALIDO_NOMINAL, INVALIDO };

class Partido;

class Candidato {
    int numero;
    string nome;
    Partido *partido;
    bool deferido;
    bool eleito;
    Genero genero;
    TipoDestinoVotos tipoDestinoVotos;
    Data dataNascimento;
    int votosNominais;

  public:
    Candidato(const int &numero, const string &nome, Partido *partido, const bool &deferido, const bool &eleito, const Genero &genero,
              const TipoDestinoVotos &tipoDestinoVotos, const Data &dataNascimento);
    Candidato();
    const int &getNumero() const;
    const string &getNome() const;
    Partido *getPartido() const;
    const bool &isDeferido() const;
    const bool &isEleito() const;
    const int &getVotosNominais() const;
    const Genero &getGenero() const;
    const TipoDestinoVotos &getTipoDestinoVotos() const;
    const Data &getDataNascimento() const;
    void setVotosNominais(int votosNominais);
    void addVotosNominais(int votosNominais);
    bool operator>(const Candidato &candidato) const;
    bool operator==(const Candidato &candidato) const;
    bool operator<(const Candidato &candidato) const;
};

#endif // CANDIDATO_H
