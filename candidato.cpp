#include "candidato.h"
/**
 * Esta classe representa um candidato em uma eleição.
 */

/**
 * Constrói um objeto Candidato.
 *
 * @param numero            O número do candidato.
 * @param nome              O nome do candidato.
 * @param partido           O partido do candidato.
 * @param deferido          Indica se o candidato foi deferido.
 * @param eleito            Indica se o candidato foi eleito.
 * @param genero            O gênero do candidato.
 * @param tipoDestinoVotos  O tipo de destino dos votos.
 * @param dataNascimento    A data de nascimento do candidato.
 */
Candidato::Candidato(const int &numero, const string &nome, Partido *partido, const bool &deferido, const bool &eleito, const Genero &genero,
                     const TipoDestinoVotos &tipoDestinoVotos, const Data &dataNascimento)
    : numero(numero), nome(nome), partido(partido), deferido(deferido), eleito(eleito), genero(genero), tipoDestinoVotos(tipoDestinoVotos),
      dataNascimento(dataNascimento), votosNominais(0) {}

Candidato::Candidato() {}

/**
 * Obtém o número do candidato.
 *
 * @return O número do candidato.
 */
const int &Candidato::getNumero() const { return numero; }

/**
 * Obtém o nome do candidato.
 *
 * @return O nome do candidato.
 */
const string &Candidato::getNome() const { return nome; }

/**
 * Obtém o partido do candidato.
 *
 * @return O partido do candidato.
 */
Partido *Candidato::getPartido() const { return partido; }

/**
 * Verifica se o candidato foi deferido.
 *
 * @return `true` se o candidato foi deferido, caso contrário, `false`.
 */
const bool &Candidato::isDeferido() const { return deferido; }

/**
 * Verifica se o candidato foi eleito.
 *
 * @return `true` se o candidato foi eleito, caso contrário, `false`.
 */
const bool &Candidato::isEleito() const { return eleito; }

/**
 * Obtém a quantidade de votos nominais recebidos pelo candidato.
 *
 * @return A quantidade de votos nominais.
 */
const int &Candidato::getVotosNominais() const { return votosNominais; }

/**
 * Obtém o gênero do candidato.
 *
 * @return O gênero do candidato.
 */
const Genero &Candidato::getGenero() const { return genero; }

/**
 * Obtém o tipo de destino dos votos do candidato.
 *
 * @return O tipo de destino dos votos do candidato.
 */
const TipoDestinoVotos &Candidato::getTipoDestinoVotos() const { return tipoDestinoVotos; }

/**
 * Obtém a data de nascimento do candidato.
 *
 * @return A data de nascimento do candidato.
 */
const Data &Candidato::getDataNascimento() const { return dataNascimento; }

/**
 * Define a quantidade de votos nominais recebidos pelo candidato.
 *
 * @param votosNominais A quantidade de votos nominais a ser definida.
 */
void Candidato::setVotosNominais(int votosNominais) { this->votosNominais = votosNominais; }

/**
 * Adiciona votos nominais ao candidato.
 *
 * @param votosNominais A quantidade de votos nominais a serem adicionados.
 */
void Candidato::addVotosNominais(int votosNominais) { this->votosNominais += votosNominais; }

/**
 * Compara dois candidatos.
 *
 * @param candidato O candidato a ser comparado.
 * @return true se o candidato atual tiver mais votos que o candidato passado como parâmetro, ou se tiver a mesma quantidade de votos e uma data de nascimento
 * menor.
 * @return false caso contrário.
 */
bool Candidato::operator>(const Candidato &candidato) const {
    if (this->votosNominais > candidato.getVotosNominais()) {
        return true;
    } else if (this->votosNominais == candidato.getVotosNominais()) {
        return this->dataNascimento.operator<(candidato.getDataNascimento());
    }
    return false;
}

/**
 * Compara dois candidatos.
 *
 * @param candidato O candidato a ser comparado.
 * @return true se o candidato atual tiver a mesma quantidade de votos que o candidato passado como parâmetro, e se tiver a mesma data de nascimento.
 * @return false caso contrário.
 */
bool Candidato::operator==(const Candidato &candidato) const {
    return this->votosNominais == candidato.getVotosNominais() && this->dataNascimento.operator==(candidato.getDataNascimento());
}

/**
 * Compara dois candidatos.
 *
 * @param candidato O candidato a ser comparado.
 * @return true se o candidato atual tiver menos votos que o candidato passado como parâmetro, ou se tiver a mesma quantidade de votos e uma data de nascimento
 * maior.
 * @return false caso contrário.
 */
bool Candidato::operator<(const Candidato &candidato) const {
    if (this->votosNominais < candidato.getVotosNominais()) {
        return true;
    } else if (this->votosNominais == candidato.getVotosNominais()) {
        return this->dataNascimento.operator>(candidato.getDataNascimento());
    }
    return false;
}