#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct studentD {
    char surname[50];
    char name[50];
    bool sex;
    int course;
    char group[10];
};

struct studentT {
    string surname;
    string name;
    int year;
};

void RW(const vector<studentD>& students) {
    ofstream file("INFO.dat", ios::binary);
    for (const auto& student : students) {
        file.write(reinterpret_cast<const char*>(&student), sizeof(studentD));
    }
    file.close();
}

vector<studentD> RD() {
    vector<studentD> students;
    ifstream file("INFO.dat", ios::binary);
    studentD student;
    while (file.read(reinterpret_cast<char*>(&student), sizeof(studentD))) {
        students.push_back(student);
    }
    file.close();
    return students;
}

void RW(const vector<studentT>& students) {
    ofstream file("INFO.txt");
    for (const auto& student : students) {
        file << student.surname << " " << student.name << " " << student.year << endl;
    }
    file.close();
}

vector<studentT> RD(bool textMode) {
    vector<studentT> students;
    ifstream file("INFO.txt");
    studentT student;
    while (file >> student.surname >> student.name >> student.year) {
        students.push_back(student);
    }
    file.close();
    return students;
}

bool compareByAge(const studentT& a, const studentT& b) {
    return a.year < b.year;
}

int main()
{
    setlocale(LC_ALL, "uk-UA");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n(0);
    vector<studentD> studentsD;
    vector<studentT> studentsT;

    while (true)
    {
        cout << "Меню\n";
        cout << "1 - запис у файл INFO.dat\n";
        cout << "2 - читання з файлу INFO.dat\n";
        cout << "3 - запис у файл INFO.txt\n";
        cout << "4 - читання з файлу INFO.txt\n";
        cout << "5 - вихід\n";

        cin >> n;
        switch (n)
        {
        case 1:
            studentsD = {
                {"Сидоренко", "Іван", true, 1, "КІ-23-1"},
                {"Ковальчук", "Олександр", true, 1, "КІ-23-2"},
                {"Мельник", "Анна", false, 2, "КІ-22-1"},
                {"Петренко", "Ольга", false, 1, "КІ-23-1"},
                {"Шевченко", "Дмитро", true, 3, "КІ-21-2"},
                {"Іваненко", "Марія", false, 1, "КІ-23-2"},
                {"Тарасенко", "Сергій", true, 2, "КІ-22-2"},
                {"Бондаренко", "Наталія", false, 4, "КІ-20-1"},
                {"Кравченко", "Андрій", true, 2, "КІ-22-1"},
                {"Гаврилюк", "Вікторія", false, 1, "КІ-23-1"}
            };
            RW(studentsD);
            break;
        case 2:
            studentsD = RD();
            for (studentD st : studentsD)
            {
                if (st.sex)
                    cout << st.surname << " " << st.name << " " << st.course << " " << st.group << endl;
            }
            break;
        case 3:
            studentsT = {
                {"Сидоренко", "Іван", 1987},
                {"Ковальчук", "Олександр", 1992},
                {"Мельник", "Анна", 1995},
                {"Петренко", "Ольга", 1989},
                {"Шевченко", "Дмитро", 1990},
                {"Іваненко", "Марія", 1993},
                {"Тарасенко", "Сергій", 1985},
                {"Бондаренко", "Наталія", 1991},
                {"Кравченко", "Андрій", 1988},
                {"Гаврилюк", "Вікторія", 1994}
            };
            RW(studentsT);
            break;
        case 4:
            studentsT = RD(true);
            sort(studentsT.begin(), studentsT.end(), compareByAge);
            for (studentT st : studentsT)
            {
                cout << st.surname << " " << st.name << " " << st.year << endl;
            }
            break;
        case 5:
            return 0;
        default:
            cout << "Неправильний вибір";
            break;
        }
    }
}