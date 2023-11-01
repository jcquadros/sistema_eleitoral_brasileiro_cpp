#if !defined(DATE_H)
#define DATE_H
#include <string>
using namespace std;

class Date{
    int day;
    int month;
    int year;
public:
    Date();
    Date(int day, int month, int year);
    int compare(Date date);
    string toString();
    bool isValid();
};

#endif // DATE_H
