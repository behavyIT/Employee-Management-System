#include "masB.h"
#include <iostream>
#include <iomanip>
using namespace std;

masB::masB() : py(nullptr), k(0) {}

masB::masB(const masB& z) : masA(z) {
    k = z.k;
    if (k == 0) py = nullptr;
    else {
        py = new PosInfo[k];
        for (int i = 0; i < k; ++i) py[i] = z.py[i];
    }
}

masB::~masB() {
    delete[] py;
}

masB& masB::operator=(const masB& z) {
    if (this == &z) return *this;
    masA::operator=(z);       // присваивание базовой части
    delete[] py;
    k = z.k;
    if (k == 0) py = nullptr;
    else {
        py = new PosInfo[k];
        for (int i = 0; i < k; ++i) py[i] = z.py[i];
    }
    return *this;
}

void masB::makePerech() {
    delete[] py; py = nullptr; k = 0;
    if (n == 0) {
        cout << "Исходный массив пуст, перечень не сформирован.\n";
        return;
    }
    PosInfo* temp = new PosInfo[n];
    int countK = 0;
    for (int i = 0; i < n; ++i) {
        bool found = false;
        for (int j = 0; j < countK; ++j) {
            if (temp[j].position == px[i].position) {
                temp[j].count++;
                found = true;
                break;
            }
        }
        if (!found) {
            temp[countK].position = px[i].position;
            temp[countK].count = 1;
            countK++;
        }
    }
    k = countK;
    if (k > 0) {
        py = new PosInfo[k];
        for (int i = 0; i < k; ++i) py[i] = temp[i];
    }
    delete[] temp;
    cout << "Перечень сформирован.\n";
}

void masB::sortPosition() {
    for (int i = 0; i < k - 1; ++i)
        for (int j = 0; j < k - i - 1; ++j)
            if (py[j].position > py[j + 1].position)
                swap(py[j], py[j + 1]);
}

void masB::sortCount() {
    for (int i = 0; i < k - 1; ++i)
        for (int j = 0; j < k - i - 1; ++j)
            if (py[j].count > py[j + 1].count)
                swap(py[j], py[j + 1]);
}

void masB::clearPerech() {
    delete[] py;
    py = nullptr;
    k = 0;
}

ostream& operator<<(ostream& out, const masB& z) {
    if (z.k == 0) {
        out << "Перечень пуст.\n";
        return out;
    }
    string border = string(50, '=');
    out << border << endl;
    out << " | " << padRight("Должность", 30) << " | " << padLeft("Кол-во", 8) << " |\n";
    out << border << endl;
    for (int i = 0; i < z.k; ++i)
        out << " | " << padRight(z.py[i].position, 30)
            << " | " << padLeft(to_string(z.py[i].count), 8) << " |\n";
    out << border << endl;
    return out;
}