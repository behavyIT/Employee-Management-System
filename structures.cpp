#include "structures.h"
#include <iomanip>
#include <limits>
#include <sstream>
using namespace std;

int getVisibleLen(const string& str) {
    int len = 0;
    for (unsigned char c : str) {
        if ((c & 0xC0) != 0x80) len++;
    }
    return len;
}

string padRight(const string& str, int width) {
    int len = getVisibleLen(str);
    return str + string(max(0, width - len), ' ');
}

string padLeft(const string& str, int width) {
    int len = getVisibleLen(str);
    return string(max(0, width - len), ' ') + str;
}

bool clerk::operator<(const clerk& other) const {
    if (deptNumber != other.deptNumber)
        return deptNumber < other.deptNumber;
    return position < other.position;
}

bool clerk::operator>(const clerk& other) const {
    return other < *this;
}

istream& operator>>(istream& in, clerk& z) {
    cout << "Полное ФИО: ";
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(in, z.person.fio);
    cout << "Дата приёма (ДД.ММ.ГГГГ): ";
    in >> z.person.hireDate;
    cout << "Табельный номер: ";
    in >> z.tabNumber;
    cout << "Номер отдела: ";
    in >> z.deptNumber;
    cout << "Должность: ";
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(in, z.position);
    cout << "Оклад (руб.): ";
    in >> z.salary;
    return in;
}

ostream& operator<<(ostream& out, const clerk& z) {
    stringstream ss;
    ss << fixed << setprecision(2) << z.salary;
    string sal = ss.str();
    out << " | " << padRight(z.person.fio, 30)
        << " | " << padRight(z.person.hireDate, 10)
        << " | " << padLeft(to_string(z.tabNumber), 8)
        << " | " << padLeft(to_string(z.deptNumber), 8)
        << " | " << padRight(z.position, 20)
        << " | " << padLeft(sal, 12) << " |";
    return out;
}