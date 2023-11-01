#include "Date.h"

Date::Date()
{
    this->day = 0;
    this->month = 0;
    this->year = 0;
}

Date::Date(int day, int month, int year)
{
    this->day = day;
    this->month = month;
    this->year = year;
}

int Date::compare(Date date)
{
    if(!this->isValid() || !date.isValid())
        return 0;
    if(this->year != date.year)
        return this->year - date.year;
    if(this->month != date.month)
        return this->month - date.month;
    return this->day - date.day;
}

string Date::toString()
{
    return to_string(this->day) + "/" + to_string(this->month) + "/" + to_string(this->year);
}

bool Date::isValid()
{
    if(this->day < 1 || this->day > 31)
        return false;
    if(this->month < 1 || this->month > 12)
        return false;
    if(this->year < 0)
        return false;
    return true;
}
