#ifndef MASA_H
#define MASA_H

#include <iostream>
#include <string>
#include "structures.h"

class masA {
protected:
    clerk* px;
    int n;
public:
    masA();
    masA(const masA& z);
    ~masA();                          // обычный деструктор, не virtual
    masA& operator=(const masA& z);

    void addRecord();
    void deleteRecord();
    void sortByFIO();
    void sortByDeptThenPosition();
    void sortByTabNumber();

    int getN() const { return n; }

    friend std::istream& operator>>(std::istream& in, masA& db);
    friend std::ostream& operator<<(std::ostream& out, const masA& db);
};

#endif