#include <iostream>
#include <string>
#include <limits>
#include <locale>
#include <fstream>
#include <iomanip>
#include "masC.h"
using namespace std;

void clearScreen() {
    system("clear");   
}

void pause() {
    cout << "\nНажмите Enter для продолжения...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    setlocale(LC_ALL, "");
    masC c;
    int choice;

    while (true) {
        clearScreen();
        cout << "УПРАВЛЕНИЕ БАЗОЙ ДАННЫХ СОТРУДНИКОВ\n";
        cout << "1.  Загрузить из файла (masA)\n";
        cout << "2.  Вывести на экран (masA)\n";
        cout << "3.  Сохранить в файл (masA)\n";
        cout << "4.  Добавить запись (masA)\n";
        cout << "5.  Удалить запись (masA)\n";
        cout << "6.  Сортировка по ФИО (masA)\n";
        cout << "7.  Сортировка по отделу и должности (masA)\n";
        cout << "8.  Сортировка по табельному номеру (masA)\n";
        cout << "--------------------------------------------------\n";
        cout << "9.  Формирование перечня должностей (masB)\n";
        cout << "10. Вывести перечень на экран (masB)\n";
        cout << "11. Сохранить перечень в файл (masB)\n";
        cout << "12. Сортировка перечня по должности (masB)\n";
        cout << "13. Сортировка перечня по количеству (masB)\n";
        cout << "--------------------------------------------------\n";
        cout << "14. Поиск по дате приема (masC)\n";
        cout << "15. Вывести результаты поиска (masC)\n";
        cout << "16. Сохранить результаты в файл (masC)\n";
        cout << "17. Сортировка результатов по отделу и должности (masC)\n";
        cout << "18. Сортировка результатов по ФИО (masC)\n";
        cout << "--------------------------------------------------\n";
        cout << "19. Проверка конструктора копирования (вся иерархия)\n";
        cout << "20. Проверка оператора присваивания (вся иерархия)\n";
        cout << "--------------------------------------------------\n";
        cout << "0.  Выход\n";
        cout << "==================================================\n";
        cout << "Ваш выбор: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1: {
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;
            ifstream inFile(filename);
            if (inFile) {
                inFile >> (masA&)c;
                c.clearPerech();       // сброс перечня (masB)
                c.clearResults();      // сброс результатов (masC)
                cout << "Успешно.\n";
            } else cout << "Ошибка файла.\n";
            pause(); break;
        }
        case 2:
            cout << (masA&)c;
            pause(); break;
        case 3: {
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;
            ofstream outFile(filename);
            if (outFile) {
                outFile << (masA&)c;
                cout << "Успешно.\n";
            } else cout << "Ошибка файла.\n";
            pause(); break;
        }
        case 4:
            c.addRecord();
            pause(); break;
        case 5:
            c.deleteRecord();
            pause(); break;
        case 6:
            c.masA::sortByFIO();
            cout << "Отсортировано.\n";
            pause(); break;
        case 7:
            c.masA::sortByDeptThenPosition();
            cout << "Отсортировано.\n";
            pause(); break;
        case 8:
            c.masA::sortByTabNumber();
            cout << "Отсортировано.\n";
            pause(); break;
        case 9:
            c.makePerech();
            pause(); break;
        case 10:
            cout << (masB&)c;
            pause(); break;
        case 11: {
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;
            ofstream outFile(filename);
            if (outFile) {
                outFile << (masB&)c;
                cout << "Успешно.\n";
            } else cout << "Ошибка файла.\n";
            pause(); break;
        }
        case 12:
            c.sortPosition();
            cout << "Отсортировано.\n";
            pause(); break;
        case 13:
            c.sortCount();
            cout << "Отсортировано.\n";
            pause(); break;
        case 14:
            c.findEmployee();
            pause(); break;
        case 15:
            cout << c;
            pause(); break;
        case 16: {
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;
            ofstream outFile(filename);
            if (outFile) {
                outFile << c;
                cout << "Успешно.\n";
            } else cout << "Ошибка файла.\n";
            pause(); break;
        }
        case 17:
            c.sortByDeptThenPosition();
            cout << "Отсортировано.\n";
            pause(); break;
        case 18:
            c.sortByFIO();
            cout << "Отсортировано.\n";
            pause(); break;
        case 19: {
            masC b(c);                      // создаём копию
            cout << (masA&)b << (masA&)c;   // masA-части
            cout << (masB&)b << (masB&)c;   // masB-части
            cout << b << c;                 // masC-части
            pause();
            break;
        }
        case 20: {
            masC a, b;
            a = b = c;
            cout << (masA&)c << (masA&)b << (masA&)a;
            cout << (masB&)c << (masB&)b << (masB&)a;
            cout << c << b << a;
            pause();
            break;
        }
        case 0:
            cout << "Выход из программы...\n";
            return 0;
        default:
            cout << "Неверный выбор.\n";
            pause(); break;
        }
    }
}