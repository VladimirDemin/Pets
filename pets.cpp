#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

struct Pet 
{
    string owner_name;
    string pet_type;
    string name;
    int age;
};

void out(Pet* pet_array, int n)
{
    cout << setw(20) << "Owner name" << setw(20) << "Pet type count" << setw(20) << "Pet name" << setw(20) << "Pet age" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << setw(20) << pet_array[i].owner_name << setw(20) << pet_array[i].pet_type << setw(20) << pet_array[i].name << setw(20) << pet_array[i].age << endl;
    }
}

void count_type(Pet* pet_array, int n)
{

    vector <pair <string, int>> owners_and_types;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (pet_array[j].owner_name > pet_array[j + 1].owner_name)
            {
                swap(pet_array[j], pet_array[j + 1]);
            }
        }
    }

    int types = 1;
    for (int i = 0; i < n; i++) 
    { 
        for (int j = i; j <= n; j++) 
        { 
            while (pet_array[i].owner_name == pet_array[j].owner_name) 
            {
                if (pet_array[i].pet_type != pet_array[j].pet_type)
                {
                    types++;
                    j++;
                }
                else 
                {
                    j++;
                }
            }
            pair <string, int> temp;
            temp.first = pet_array[i].owner_name;
            temp.second = types;
            owners_and_types.push_back(temp);
            i = j;
            types = 1;
        }
    }

    cout << setw(20) << "Owner name" << setw(20) << "Pet type count" << endl;
    for (int i = 0; i < owners_and_types.size(); i++)
    {
        cout << setw(20) << owners_and_types.at(i).first << setw(10) << owners_and_types.at(i).second << endl;
    }
}

void view_owners(Pet* pet_array, int n) 
{
    string new_type;
    cout << "\tВведите вид животного -> ", cin >> new_type;

    new_type.append(",");

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (pet_array[j].pet_type > pet_array[j + 1].pet_type) 
            {
                swap(pet_array[j], pet_array[j + 1]);
            }
        }
    }

    bool included = false;

    for (int i = 0; i < n; i++)
    {
        if (new_type == pet_array[i].pet_type)
        {
            included = true;
            cout << endl << setw(20) << "Owner name" << setw(20) << "Pet type count" << endl;
            while (new_type == pet_array[i].pet_type) 
            {
                cout << setw(20) << pet_array[i].owner_name << setw(10) << pet_array[i].pet_type << endl;
                i++;
            }
        }
    }

    if (!included)
    {
        cout << "Заданный вид животного не найден!\n";
    }

}

void count_names(Pet* pet_array, int  n)
{

    string new_name;
    cout << "\tВведите кличку животного -> ", cin >> new_name;

    new_name.append(",");

    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (new_name == pet_array[i].name)
        {
            counter++;
        }
    }
    cout << "Количество животных с заданной кличкой равно " << counter << endl;

}

void view_ages(Pet* pet_array, int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (pet_array[j].pet_type > pet_array[j + 1].pet_type) 
            {
                swap(pet_array[j], pet_array[j + 1]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        int tmp_max = pet_array[i].age;
        int tmp_min = pet_array[i].age;
        while (pet_array[i].pet_type == pet_array[i + 1].pet_type)
        {
            i++;
            if (pet_array[i].age > tmp_max)
            {
                tmp_max = pet_array[i].age;
            }
            if (pet_array[i].age < tmp_min)
            {
                tmp_min = pet_array[i].age;
            }
        }
        cout << pet_array[i].pet_type << " " << tmp_max << "-- max" << endl;
        cout << pet_array[i].pet_type << " " << tmp_min << "-- min" << endl;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n = 8, key = 0;

    fstream fin;
    Pet* pet_array = new Pet[n];

    do
    {
        cout << "\nВыберите действие [1..5]:";
        cout << "\n1) Прочитать файл";
        cout << "\n2) Подсчёт количества различных видов животных:";
        cout << "\n3) Вывести всех владельцев и клички заданного животного:";
        cout << "\n4) Определить сколько видов животных носит заданную кличку:";
        cout << "\n5) Вывести максимальный и минимальный возрасты для всех видов животных:";
        cout << "\n0) Завершение программы\n-->";
        cin >> key;

        switch (key)
        {
        case 1:
            fin.open("input1.txt", ios_base::in);

            if (!fin)
            {
                cout << "Error istream open!";
            }

            for (int i = 0; i < n; i++)
            {
                fin >> pet_array[i].owner_name;
                fin >> pet_array[i].pet_type;
                fin >> pet_array[i].name;
                fin >> pet_array[i].age;
            }
            fin.close();

            system("cls");
            cout << "\nФайл считан успешно!\n";

            out(pet_array, n);
            break;

        case 2:
            system("cls");
            count_type(pet_array, n);
            break;
        case 3:
            system("cls");
            view_owners(pet_array, n);
            break;
        case 4:
            system("cls");
            count_names(pet_array, n);
            break;
        case 5:
            system("cls");
            view_ages(pet_array, n);
            break;
        }
    } 
    while (key != 0);

    system("pause");

    return 0;
}
