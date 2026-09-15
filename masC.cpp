#include "masC.h"
#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;

masC::masC() : pz(nullptr), l(0) {}

masC::masC(const masC& z) : masB(z) {
    l = z.l;
    if (l == 0) pz = nullptr;
    else {
        pz = new clerk[l];
        for (int i = 0; i < l; ++i) pz[i] = z.pz[i];
    }
}

masC::~masC() {
    delete[] pz;
}

masC& masC::operator=(const masC& z) {
    if (this == &z) return *this;
    masB::operator=(z);      // присваивание частей masA и masB
    delete[] pz;
    l = z.l;
    if (l == 0) pz = nullptr;
    else {
        pz = new clerk[l];
        for (int i = 0; i < l; ++i) pz[i] = z.pz[i];
    }
    return *this;
}

void masC::findEmployee() {
    delete[] pz; pz = nullptr; l = 0;
    if (n == 0) {
        cout << "Исходный массив пуст.\n";
        return;
    }
    string date;
    cout << "Введите дату приёма (ДД.ММ.ГГГГ): ";
    cin >> date;
    clerk* temp = new clerk[n];
    int foundCount = 0;
    for (int i = 0; i < n; ++i) {
        if (px[i].person.hireDate == date) {
            temp[foundCount++] = px[i];
        }
    }
    if (foundCount > 0) {
        l = foundCount;
        pz = new clerk[l];
        for (int i = 0; i < l; ++i) pz[i] = temp[i];
    }
    delete[] temp;
    cout << "Поиск завершён. Найдено записей: " << l << "\n";
}

void masC::sortByDeptThenPosition() {
    if (l < 2) return;
    for (int i = 0; i < l - 1; ++i)
        for (int j = 0; j < l - i - 1; ++j)
            if (pz[j].deptNumber > pz[j + 1].deptNumber ||
                (pz[j].deptNumber == pz[j + 1].deptNumber && pz[j].position > pz[j + 1].position))
                swap(pz[j], pz[j + 1]);
}

void masC::sortByFIO() {
    for (int i = 0; i < l - 1; ++i)
        for (int j = 0; j < l - i - 1; ++j)
            if (pz[j].person.fio > pz[j + 1].person.fio)
                swap(pz[j], pz[j + 1]);
}

void masC::clearResults() {
    delete[] pz;
    pz = nullptr;
    l = 0;
}

ostream& operator<<(ostream& out, const masC& z) {
    if (z.l == 0) {
        out << "Результаты поиска пусты.\n";
        return out;
    }
    string border = string(145, '=');
    out << border << endl;
    out << "  № | " << padRight("Полное ФИО", 30) << " | " << padRight("Дата", 10)
        << " | " << padLeft("Таб.№", 8) << " | " << padLeft("Отдел", 8)
        << " | " << padRight("Должность", 20) << " | " << padLeft("Оклад (руб.)", 12) << " |\n";
    out << border << endl;
    for (int i = 0; i < z.l; ++i)
        out << " " << padLeft(to_string(i + 1), 2) << z.pz[i] << endl;
    out << border << endl;
    return out;
}