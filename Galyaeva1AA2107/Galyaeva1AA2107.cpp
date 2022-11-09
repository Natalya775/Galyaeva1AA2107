#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

int GetCorrectNumber(int min, int max)
{
    int x;
    while ((cin>>x).fail() || x<min || x>max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введите число (" << min << "-" << max<<"):";
    } 
    return x;
}

struct Pipe
{
    float length;
    float diameter;
    bool sign;
};

struct CS
{
    string name="none";
    double amount;
    double amountworking;
    float efficiency;
};

bool PipeExist = false;
bool CSExist = false;

bool IsPipeCorrect(double d)
{
    return d > 0;
}

bool IsAmountCorrect(double a)
{
    return (a >= 0);
}

bool IsEfficiencyCorrect(int e)
{
    return e >= 0;
}

bool IsSignCorrect(bool e)
{
    return (e==true)||(e==false)||(trunc(e) != e);
}

void InputPipe(Pipe& p)
{
    cout << "Введите длину трубы: ";
    cin >> p.length;
    while (cin.fail() || !IsPipeCorrect(p.length)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Данные не верные, длина должна быть положительным числом: ";
        cin >> p.length;
    }
    cout << "Введите диаметр трубы: ";
    cin >> p.diameter;
    while (cin.fail() || !IsPipeCorrect(p.diameter)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Данные не верные, диаметр должен быть положительным числом: ";
        cin >> p.diameter;
    }
    cout << "Введите состояние трубы\n";
    cout << "В работе: введите 1, в ремонте :введите 0: ";
    cin >> p.sign;
    while (cin.fail() || !IsSignCorrect(p.sign)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Данные не верные, введите 1 или 0: ";
        cin >> p.sign;
    }
    PipeExist = true;

}
void InputCS(CS& c)
{
    cout << "Введите имя КС: ";
    getline(cin >> ws, c.name);
    cout << "Введите количество цехов: ";
    cin >> c.amount;
    while (cin.fail()|| (trunc(c.amount) != c.amount) || !IsAmountCorrect(c.amount)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Данные не верные, количество цехов должно быть целым положительным числом: ";
        cin >> c.amount;
    }
    cout << "Введите количество цехов в работе: ";
    cin >> c.amountworking;
    while (cin.fail() || !IsAmountCorrect(c.amountworking)|| (c.amount<c.amountworking)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Данные не верные, количество рабочих цехов должно быть целым положительным числом, не превышающим общее число цехов: ";
        cin >> c.amountworking;
    }
    cout << "Введите эффективность: ";
    cin >> c.efficiency;
    while (cin.fail() || !IsEfficiencyCorrect(c.efficiency)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Данные не верные, эффективность должна быть неотрицательным числом: ";
        cin >> c.efficiency;
    }

    CSExist = true;
}

void Review(Pipe& p, CS& c) {
    if (PipeExist == true) {
        cout << "Длина трубы: " << p.length;
        cout << "\nДиаметр трубы: " << p.diameter;
        if (p.sign == 1) {
            cout << "\nСостояние трубы: в работе\n";
        }
        else if (p.sign == 0) {
            cout << "\nСостояние трубы: в ремонте\n";
        }
    }
    if (CSExist == true) {
        cout << "Имя КС: " << c.name;
        cout << "\nКоличество цехов: " << c.amount;
        cout << "\nЦехов в работе: " << c.amountworking;
        cout << "\nЭффективность: " << c.efficiency << "\n";
    }
}

void EditPipe(Pipe& p)
{
    if (PipeExist == true) {
        if (p.sign == 1) {
            cout << "\nСостояние трубы: в работе\n";
        }
        else if (p.sign == 0) {
            cout << "\nСостояние трубы: в ремонте\n";
        }
        cout << "Введите состояние трубы\n";
        cout << "В работе: введите 1, в ремонте :введите 0: ";
        cin >> p.sign;
        while (cin.fail() || !IsSignCorrect(p.sign)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Данные не верные, введите 1 или 0: ";
            cin >> p.sign;
        }
    }
    else
        cout << "Сначала добавьте трубу!\n";
}

void EditCS(CS& c) {
    if (CSExist == true) {
        cout << "Количество цехов в работе: " << c.amountworking << " из " << c.amount;
        cout << "\nИзмените количество цехов в работе: ";
        cin >> c.amountworking;
        while (cin.fail() || !IsAmountCorrect(c.amountworking) || (c.amount < c.amountworking)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Данные не верные, количество рабочих цехов должно быть целым положительным числом, не превышающим общее число цехов: ";
            cin >> c.amountworking;
        }
    }
    else
        cout << "Сначала добавьте КС!\n";
}

void Save(Pipe& p, CS& c)
{
    ofstream fout;
    fout.open("laba.txt", ios::out);
    if (PipeExist == true) {
        if (fout.is_open())
        {
            fout << "Труба:\n ";
            fout << p.length << "\n";
            fout << p.diameter << "\n";
            fout << p.sign << "\n";
        }
    }
    if (CSExist == true) {
        if (fout.is_open())
        {
            fout << "КС:\n ";
            fout << c.name << "\n";
            fout << c.amount << "\n";
            fout << c.amountworking << "\n";
            fout << c.efficiency << "\n";
        }
    }
    cout << "Файл записан\n";
    fout.close();
}

void LoadPipeCorrect(Pipe& p) {
    if ((p.length <= 0) || (p.diameter <= 0) || (p.sign != 0) || (p.sign != 1))
        cout << "Данные в файлы указаны неправильно!\n";
}
void LoadCSCorrect(CS& c) {
    if ((c.name=="none") || (c.amount < 0) || (c.amountworking < 0)|| (c.amount < c.amountworking)||(c.efficiency<0))
        cout << "Данные в файлы указаны неправильно!\n";
}

void Load(Pipe& p, CS& c)
{
    string file;
    ifstream fin;
    fin.open("laba.txt", ios::in);
    string tmp;
    fin >> file;
    if (fin.is_open() & (file == "Труба:"))
    {
        fin >> p.length;
        fin >> p.diameter;
        fin >> p.sign;
        fin >> file;
        PipeExist = true;
        LoadPipeCorrect(p);
    }
    if (fin.is_open()& (file == "КС:"))
    {
        fin >> c.name;
        fin >> c.amount;
        fin >> c.amountworking;
        fin >> c.efficiency;
        CSExist = true;
        LoadCSCorrect(c);
}
    cout << "Данные из файла загружены!\n";
    fin.close();
}



void PrintMenu()
{
    cout << "1. Добавить трубу" << endl
        << "2. Добавить КС" << endl
        << "3. Просмотр всех объектов" << endl
        << "4. Редактировать трубу" << endl
        << "5. Редактировать КС" << endl
        << "6. Сохранить в файл" << endl
        << "7. Загрузить из файла" << endl
        << "0. Выйти" << endl
        << "Выберите действие: ";
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Pipe p;
    CS c;
    while (1)
    {
        PrintMenu();
        switch (GetCorrectNumber(0,7))
        {
        case 1:
        {
            InputPipe(p);
            break;
        }
        case 2:
        {
            InputCS(c);
            break;
        }
        case 3:
        {
            Review(p,c);
            break;
        }
        case 4:
        {
            EditPipe(p);
            break;
        }
        case 5:
        {
            EditCS(c);
            break;
        }
        case 6:
        {
            Save(p,c);
            break;
        }
        case 7:
        {
            Load(p,c);
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "Ошибка" << endl;
        }
        }
    }
    return 0;
}