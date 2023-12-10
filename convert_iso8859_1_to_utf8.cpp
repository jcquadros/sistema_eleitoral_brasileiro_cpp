#include <iostream>
#include <fstream>
#include <string>

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

int main()
{
    ifstream in("arquivo.txt"); // assumindo um arquivo em ISO-8859-1 que contém a palavra João
    string s;
    in >> s; // esta string s está codificada em ISO-8859-1
    string sConvertida = iso_8859_1_to_utf8(s);
    // usaremos a string convertida a partir de agora
    cout << "String convertida: " << sConvertida << endl; // assumindo que a saída será UTF-8
    // se imprimir a string codificada originalmente em ISO--8859-1
    // teremos problemas
    cout << "String não convertida: " << s << endl;
    // a comparação também deve ser feita com a string convertida:
    cout << "(sConvertida==\"João\") é avaliada para: " << (sConvertida=="João") << endl;
    // pois teríamos problemas com a não convertida:
    cout << "(s==\"João\") é avaliada para: " << (s=="João") << endl;

}