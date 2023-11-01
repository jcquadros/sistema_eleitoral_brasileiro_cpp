#if !defined(CSV_READER_H)
#define CSV_READER_H

#include <string>
using namespace std;
#include <fstream>
#include <vector>
#include <sstream>

class CSVReader{
    string path;
    ifstream file;
public:
    CSVReader(string path);
    CSVReader();
    void setPath(string path);
    bool hasNext();
    string next();
    vector<string> nextAsVector();
    void close();
};

#endif // CSV_READER_H
