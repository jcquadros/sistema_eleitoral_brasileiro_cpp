#include "data.h"

Data::Data(const int &dia, const int &mes, const int &ano) : dia(dia), mes(mes), ano(ano) {}

// fazer tratamento de exceção depois
Data::Data(string &data) {
    this->dia = stoi(data.substr(0, 2));
    this->mes = stoi(data.substr(3, 2));
    this->ano = stoi(data.substr(6, 4));
}

Data::Data() : dia(0), mes(0), ano(0) {}

const int &Data::getDia() const { return this->dia; }

const int &Data::getMes() const { return this->mes; }

const int &Data::getAno() const { return this->ano; }

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

bool Data::operator<(const Data& data) const {
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

bool Data::operator==(const Data& data) const {
    return this->ano == data.getAno() && this->mes == data.getMes() && this->dia == data.getDia();
}

bool Data::operator>(const Data& data) const {
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


