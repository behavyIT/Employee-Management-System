#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <string>

struct PERSON {
    std::string fio;
    std::string hireDate;
};

struct clerk {
    PERSON person;
    int tabNumber;
    int deptNumber;
    std::string position;
    double salary;

    bool operator<(const clerk& other) const;
    bool operator>(const clerk& other) const;
    friend std::istream& operator>>(std::istream& in, clerk& z);
    friend std::ostream& operator<<(std::ostream& out, const clerk& z);
};

int getVisibleLen(const std::string& str);
std::string padRight(const std::string& str, int width);
std::string padLeft(const std::string& str, int width);

#endif