#if !defined(DATA_H)
#define DATA_H

#include <string>
using namespace std;

class Data {
    int dia;
    int mes;
    int ano;

  public:
    Data(const int &dia, const int &mes, const int &ano);
    Data(string &data);
    const int &getDia() const;
    const int &getMes() const;
    const int &getAno() const;
    bool isLessThan(Data &data) const;
    // numero de anos entre duas datas
    int numeroAnos(Data &data) const;
    int numeroDias(Data &data) const;

  private:
    int ehBissexto(int &ano) const;
    int numeroDiasMes(int &mes, int &ano) const;
};

#endif // DATA_H
