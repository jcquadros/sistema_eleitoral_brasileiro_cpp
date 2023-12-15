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
    Data();
    const int &getDia() const;
    const int &getMes() const;
    const int &getAno() const;
    int numeroAnos(const Data &data) const;
    bool operator<(const Data& data) const;
    bool operator==(const Data& data) const;
    bool operator>(const Data& data) const;

  
};

#endif // DATA_H
