#include "data.h"

/**
 * Esta classe representa uma data.
 */
/*
 * Constrói um objeto Data com o dia, mês e ano especificados.
 */
Data::Data(const int &dia, const int &mes, const int &ano) : dia(dia), mes(mes), ano(ano) {}

/**
 * Constrói um objeto Data a partir de uma string no formato DD/MM/AAAA.
 *
 * @param data A string no formato DD/MM/AAAA.
 */
Data::Data(string &data) {
    this->dia = stoi(data.substr(0, 2));
    this->mes = stoi(data.substr(3, 2));
    this->ano = stoi(data.substr(6, 4));
}
/*
 * Constrói um objeto Data com o dia, mês e ano igual a 0.
 */
Data::Data() : dia(0), mes(0), ano(0) {}

/**
 * Obtém o dia da data.
 *
 * @return O dia da data.
 */
const int &Data::getDia() const { return this->dia; }

/**
 * Obtém o mês da data.
 *
 * @return O mês da data.
 */
const int &Data::getMes() const { return this->mes; }

/**
 * Obtém o ano da data.
 *
 * @return O ano da data.
 */
const int &Data::getAno() const { return this->ano; }

/**
 * Obtém a diferença em anos entre esta data e a data especificada.
 *
 * @param data A data a ser comparada.
 * @return A diferença em anos entre esta data e a data especificada.
 */
int Data::numeroAnos(const Data &data) const {
    int anos = 0;
    if (this->ano < data.getAno()) {
        anos = data.getAno() - this->ano;
        if (this->mes > data.getMes()) {
            anos--;
        } else if (this->mes == data.getMes()) {
            if (this->dia > data.getDia()) {
                anos--;
            }
        }
    }
    return anos;
}

/**
 * Compara duas datas.
 *
 * @param data A data a ser comparada.
 * @return `true` se esta data for menor que a data especificada, caso contrário, `false`.
 */
bool Data::operator<(const Data &data) const {
    if (this->ano < data.getAno()) {
        return true;
    } else if (this->ano == data.getAno()) {
        if (this->mes < data.getMes()) {
            return true;
        } else if (this->mes == data.getMes()) {
            if (this->dia < data.getDia()) {
                return true;
            }
        }
    }
    return false;
}
/**
 * Compara duas datas.
 *
 * @param data A data a ser comparada.
 * @return `true` se esta data for igual à data especificada, caso contrário, `false`.
 */
bool Data::operator==(const Data &data) const { return this->ano == data.getAno() && this->mes == data.getMes() && this->dia == data.getDia(); }

/**
 * Compara duas datas.
 *
 * @param data A data a ser comparada.
 * @return `true` se esta data for maior que a data especificada, caso contrário, `false`.
 */
bool Data::operator>(const Data &data) const {
    if (this->ano > data.getAno()) {
        return true;
    } else if (this->ano == data.getAno()) {
        if (this->mes > data.getMes()) {
            return true;
        } else if (this->mes == data.getMes()) {
            if (this->dia > data.getDia()) {
                return true;
            }
        }
    }
    return false;
}
