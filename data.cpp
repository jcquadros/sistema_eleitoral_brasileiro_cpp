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

bool Data::isLessThan(Data &data) const {
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

int Data::ehBissexto(int &ano) const { return ((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0)) ? 1 : 0; }

int Data::numeroDiasMes(int &mes, int &ano) const {
    int dias = 0;
    if (mes == 2) {
        dias = 28 + ehBissexto(ano);
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        dias = 30;
    } else {
        dias = 31;
    }
    return dias;
}

int Data::numeroDias(Data &data) const {
    int dias = 0;
    if (isLessThan(data)) {
        int ano = this->ano;
        int mes = this->mes;
        int dia = this->dia;
        while (ano < data.getAno()) {
            dias += 365 + ehBissexto(ano);
            ano++;
        }
        while (mes < data.getMes()) {
            dias += numeroDiasMes(mes, ano);
            mes++;
        }
        dias += data.getDia() - dia;
    }
    return dias;
}
