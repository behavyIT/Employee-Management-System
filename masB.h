#ifndef MASB_H
#define MASB_H

#include "masA.h"
#include <string>

struct PosInfo {
    std::string position;
    int count;
};

class masB : public masA {
protected:
    PosInfo* py;
    int k;
public:
    masB();
    masB(const masB& z);
    ~masB();
    masB& operator=(const masB& z);

    void makePerech();      // формирование перечня должностей
    void sortPosition();    // сортировка перечня по должности
    void sortCount();       // сортировка перечня по количеству
    void clearPerech();     // очистка перечня

    int getK() const { return k; }

    friend std::ostream& operator<<(std::ostream& out, const masB& z);
};

#endif