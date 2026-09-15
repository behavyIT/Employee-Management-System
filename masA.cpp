#include "masA.h"
#include <fstream>
#include <limits>
#include <iomanip>
using namespace std;

masA::masA() : px(nullptr), n(0) {}

masA::masA(const masA& z) {
    n = z.n;
    if (n == 0) px = nullptr;
    else {
        px = new clerk[n];
        for (int i = 0; i < n; ++i) px[i] = z.px[i];
    }
}

masA::~masA() {
    delete[] px;
}

masA& masA::operator=(const masA& z) {
    if (this == &z) return *this;
    delete[] px;
    n = z.n;
    if (n == 0) px = nullptr;
    else {
        px = new clerk[n];
        for (int i = 0; i < n; ++i) px[i] = z.px[i];
    }
    return *this;
}

void masA::addRecord() {
    clerk* newArr = new clerk[n + 1];
    for (int i = 0; i < n; ++i) newArr[i] = px[i];
    delete[] px;
    px = newArr;
    cin >> px[n];
    n++;
    cout << "Запись добавлена.\n";
}

void masA::deleteRecord() {
    if (n == 0) {
        cout << "База пуста!\n";
        return;
    }
    cout << *this;
    int index;
    cout << "Введите номер записи для удаления: ";
    while (!(cin >> index)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка! Введите число: ";
    }
    if (index < 1 || index > n) {
        cout << "Такой записи нет!\n";
        return;
    }
    index--;
    string border = string(145, '=');
    cout << border << endl;
    cout << "УДАЛЯЕТСЯ:" << endl;
    cout << " " << padLeft(to_string(index + 1), 2)
         << " | " << padRight(px[index].person.fio, 30)
         << " | " << padRight(px[index].person.hireDate, 10)
         << " | " << padLeft(to_string(px[index].tabNumber), 8)
         << " | " << padLeft(to_string(px[index].deptNumber), 8)
         << " | " << padRight(px[index].position, 20) << " |\n";
    cout << border << endl;
    cout << "Подтвердить удаление? (Y/N): ";
    char confirm; cin >> confirm;
    if (confirm != 'Y' && confirm != 'y') {
        cout << "Удаление отменено!\n";
        return;
    }
    clerk* newArr = new clerk[n - 1];
    for (int i = 0; i < index; ++i) newArr[i] = px[i];
    for (int i = index + 1; i < n; ++i) newArr[i - 1] = px[i];
    delete[] px;
    px = newArr;
    n--;
    cout << "Запись удалена!\n";
}

void masA::sortByFIO() {
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (px[j].person.fio > px[j + 1].person.fio)
                swap(px[j], px[j + 1]);
}

void masA::sortByDeptThenPosition() {
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (px[j] > px[j + 1])
                swap(px[j], px[j + 1]);
}

void masA::sortByTabNumber() {
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (px[j].tabNumber > px[j + 1].tabNumber)
                swap(px[j], px[j + 1]);
}

istream& operator>>(istream& in, masA& db) {
    delete[] db.px; db.px = nullptr; db.n = 0;
    string line;
    auto trim = [](string& s) {
        if (s.empty()) return;
        s.erase(s.find_last_not_of(" \t\r\n") + 1);
        s.erase(0, s.find_first_not_of(" \t\r\n"));
    };
    while (getline(in, line)) {
        if (line.empty() || line.find('|') == string::npos) continue;
        clerk* tmp = new clerk[db.n + 1];
        for (int i = 0; i < db.n; ++i) tmp[i] = db.px[i];
        delete[] db.px;
        db.px = tmp;
        size_t pos = 0, next;
        next = line.find('|', pos);
        db.px[db.n].person.fio = line.substr(pos, next - pos); trim(db.px[db.n].person.fio);
        pos = next + 1;
        next = line.find('|', pos);
        db.px[db.n].person.hireDate = line.substr(pos, next - pos); trim(db.px[db.n].person.hireDate);
        pos = next + 1;
        next = line.find('|', pos);
        db.px[db.n].tabNumber = stoi(line.substr(pos, next - pos));
        pos = next + 1;
        next = line.find('|', pos);
        db.px[db.n].deptNumber = stoi(line.substr(pos, next - pos));
        pos = next + 1;
        next = line.find('|', pos);
        db.px[db.n].position = line.substr(pos, next - pos); trim(db.px[db.n].position);
        pos = next + 1;
        db.px[db.n].salary = stod(line.substr(pos));
        db.n++;
    }
    return in;
}

ostream& operator<<(ostream& out, const masA& db) {
    if (db.n == 0) {
        out << "База пуста.\n";
        return out;
    }
    string border = string(145, '=');
    out << border << endl;
    out << "  № | " << padRight("Полное ФИО", 30) << " | " << padRight("Дата", 10)
        << " | " << padLeft("Таб.№", 8) << " | " << padLeft("Отдел", 8)
        << " | " << padRight("Должность", 20) << " | " << padLeft("Оклад (руб.)", 12) << " |\n";
    out << border << endl;
    for (int i = 0; i < db.n; ++i)
        out << " " << padLeft(to_string(i + 1), 2) << db.px[i] << endl;
    out << border << endl;
    return out;
}