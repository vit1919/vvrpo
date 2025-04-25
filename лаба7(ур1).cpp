#include <iostream>

#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Student {
    string name;
    int group;
    int physics;
    int math;
    int inf;
    double average;
};
//ВОТ ИЗМЕНЕНИЕ
//ВОТ ИЗМЕНЕНИЕ В САМОМ GITHUB
void studentData(Student& data) {
    cout << "Введите имя: ";
    cin.ignore();
    getline(cin, data.name);

    cout << "Группа: ";
    cin >> data.group;

    cout << "Оценка по физике: ";
    cin >> data.physics;

    cout << "Оценка по математике: ";
    cin >> data.math;

    cout << "Оценка по информатике: ";
    cin >> data.inf;

    data.average = (data.physics + data.math + data.inf) / 3.0;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Student x;
    string file = "myfile.txt";
    ofstream studentFile;
    ifstream studentRead;
    int choice;

    while (true) {
        cout << "\n1. Создать 2. Просмотр 3. Добавить 4. Индивидуальное задание 5. Изменить 6. Удалить 7. Сортировать 8. Выход" << endl;
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {

        case 1:
            studentFile.open(file);
            if (!studentFile.is_open()) {
                cout << "Ошибка при открытии файла!" << endl;
            }
            else {
                cout << "Файл создан." << endl;
            }
            studentFile.close();
            break;

        case 2:
            studentRead.open(file);
            if (!studentRead.is_open()) {
                cout << "Ошибка при открытии файла!" << endl;
            }
            else {
                string str;
                while (getline(studentRead, str)) {
                    cout << str << endl;
                }
            }
            studentRead.close();
            break;

        case 3:
            studentFile.open(file, ios::app);
            if (!studentFile.is_open()) {
                cout << "Ошибка при открытии файла!" << endl;
            }
            else {
                studentData(x);
                studentFile << x.name << " "
                    << x.group << " "
                    << x.physics << " "
                    << x.math << " "
                    << x.inf << " "
                    << x.average << endl;
            }
            studentFile.close();
            break;

        case 4: {
            studentRead.open(file);
            if (!studentRead.is_open()) {
                cout << "Ошибка при открытии файла!" << endl;
            }
            else {
                cout << "Студенты с оценками >= 8:" << endl;
                while (studentRead >> x.name >> x.group >> x.physics >> x.math >> x.inf >> x.average) {
                    if (x.physics >= 8 && x.math >= 8 && x.inf >= 8) {
                        cout << x.name << " " << x.group << " "
                            << x.physics << " " << x.math << " "
                            << x.inf << " " << x.average << endl;
                    }
                }
            }
            studentRead.close();
            break;
        }

        case 5: {
            studentRead.open(file);
            if (!studentRead.is_open()) {
                cout << "Ошибка при открытии файла!" << endl;
                break;
            }

            string input;
            cout << "Введите имя студента для изменения: ";
            cin >> input;
            cin.ignore();

            vector<Student> students;
            bool found = false;

            while (studentRead >> x.name >> x.group >> x.physics >> x.math >> x.inf >> x.average) {
                students.push_back(x);
            }
            studentRead.close();

            for (int i = 0; i < students.size(); ++i) {
                if (students[i].name == input) {
                    found = true;
                    cout << "Студент найден. Введите новые данные:" << endl;
                    studentData(students[i]);
                    break;
                }
            }

            if (!found) {
                cout << "Студент не найден." << endl;
            }
            else {
                studentFile.open(file, ios::trunc);
                if (!studentFile.is_open()) {
                    cout << "Ошибка при открытии файла для записи!" << endl;
                    break;
                }

                for (int i = 0; i < students.size(); i++) {
                    studentFile << students[i].name << " "
                        << students[i].group << " "
                        << students[i].physics << " "
                        << students[i].math << " "
                        << students[i].inf << " "
                        << students[i].average << endl;
                }

                studentFile.close();
                cout << "Данные студента обновлены." << endl;
            }
            break;
        }

        case 6: {
            string nameToDelete;
            cout << "Введите имя студента, которого хотите удалить: ";
            cin.ignore();
            getline(cin, nameToDelete);

            studentRead.open(file);
            if (!studentRead.is_open()) {
                cout << "Ошибка при открытии файла!" << endl;
                break;
            }

            vector<Student> students;
            bool found = false;

            while (studentRead >> x.name >> x.group >> x.physics >> x.math >> x.inf >> x.average) {
                if (x.name != nameToDelete) {
                    students.push_back(x);
                }
                else {
                    found = true;
                }
            }
            studentRead.close();

            if (!found) {
                cout << "Студент не найден." << endl;
            }
            else {
                studentFile.open(file, ios::trunc);
                for (int i = 0; i < students.size(); ++i) {
                    studentFile << students[i].name << " " << students[i].group << " "
                        << students[i].physics << " " << students[i].math << " "
                        << students[i].inf << " " << students[i].average << endl;
                }
                studentFile.close();
                cout << "Студент успешно удален." << endl;
            }
            break;
        }

        case 7: {
            cout << "Выберите тип сортировки: 1. По имени 2. По среднему баллу" << endl;
            int sortChoice;
            cin >> sortChoice;

            studentRead.open(file);
            if (!studentRead.is_open()) {
                cout << "Ошибка при открытии файла!" << endl;
                break;
            }

            vector<Student> students;
            while (studentRead >> x.name >> x.group >> x.physics >> x.math >> x.inf >> x.average) {
                students.push_back(x);
            }
            studentRead.close();

            int n = students.size();

            if (sortChoice == 1) {
                for (int i = 0; i < n - 1; ++i) {
                    for (int j = 0; j < n - i - 1; ++j) {
                        if (students[j].name > students[j + 1].name) {
                            Student temp = students[j];
                            students[j] = students[j + 1];
                            students[j + 1] = temp;
                        }
                    }
                }
                cout << "Студенты отсортированы по имени (A-Z)." << endl;
            }
            else if (sortChoice == 2) {
                for (int i = 0; i < n - 1; ++i) {
                    for (int j = 0; j < n - i - 1; ++j) {
                        if (students[j].average < students[j + 1].average) {
                            Student temp = students[j];
                            students[j] = students[j + 1];
                            students[j + 1] = temp;
                        }
                    }
                }
                cout << "Студенты отсортированы по среднему баллу (по убыванию)." << endl;
            }
            else {
                cout << "Некорректный выбор." << endl;
                break;
            }

            studentFile.open(file, ios::trunc);
            if (!studentFile.is_open()) {
                cout << "Ошибка при открытии файла для записи!" << endl;
                break;
            }

            for (int i = 0; i < students.size(); ++i) {
                studentFile << students[i].name << " "
                    << students[i].group << " "
                    << students[i].physics << " "
                    << students[i].math << " "
                    << students[i].inf << " "
                    << students[i].average << endl;
            }

            studentFile.close();
            break;
        }

        case 8:
            cout << "Выход из программы." << endl;
            return 0;

        default:
            cout << "Некорректный выбор." << endl;
            break;
        }
    }
}
