//1.2.h   БИБЛИОТЕКА С БИБЛИОТЕКАМИ И ПРОТОТИПОМ ФУНКЦИЯМИ + ОПРЕДЕЛЕНИЕ ШАБЛОННОЙ ФУНКЦИИ
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<locale>
#define CLEAN system("cls"); // отчистка консоли
#define ClEANCONSOLE cin.clear(); cin.ignore(32767, '\n');
#define PAUSE system("pause");
using namespace std;

template<typename T>
T getValue(T& b)
{
	while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{
		cin >> b;

		if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
		{
			cin.clear(); // то возвращаем cin в 'обычный' режим работы
			cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			cout << endl << "Ошибка, попробуйте ещё раз: ";
		}
		else // если всё хорошо, то возвращаем a
			return b;
	}
}
extern void DeleteInfoAboutStedent();
extern void PrintInfoAboutStudent();
extern void CinInfoAboutStudent();
extern void menu();
extern void InfoAboutBestStudent();
extern void SortStudent();