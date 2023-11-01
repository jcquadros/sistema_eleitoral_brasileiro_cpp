#include "CSVReader.h"

CSVReader::CSVReader(string path){
    this->path = path;
    file.open(path);
}

CSVReader::CSVReader()
{
}

void CSVReader::setPath(string path)
{
    this->path = path;
    file.open(path);
}

bool CSVReader::hasNext(){
    return file.peek() != EOF;
}

string CSVReader::next(){
    string line;
    getline(file, line);
    return line;
}

vector<string> CSVReader::nextAsVector(){
    string line = this->next();
    string token;
    vector<string> result;
    stringstream ss(line);
    
    while(getline(ss, token, ',')){
        result.push_back(token);
    }

    return result;
}

void CSVReader::close(){
    file.close();
}

