#ifndef MASC_H
#define MASC_H

#include "masB.h"
#include <string>

class masC : public masB {
protected:
    clerk* pz;
    int l;
public:
    masC();
    masC(const masC& z);
    ~masC();
    masC& operator=(const masC& z);

    void findEmployee();                // запрос даты и заполнение pz
    void sortByDeptThenPosition();      // сортировка результатов по отделу и должности
    void sortByFIO();                   // сортировка результатов по ФИО
    void clearResults();                // очистка результатов поиска

    int getL() const { return l; }

    friend std::ostream& operator<<(std::ostream& out, const masC& z);
};

#endif