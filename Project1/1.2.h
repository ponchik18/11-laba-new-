//1.2.h   БИБЛИОТЕКА С БИБЛИОТЕКАМИ И ПРОТОТИПОМ ФУНКЦИЯМИ + ОПРЕДЕЛЕНИЕ ШАБЛОННОЙ ФУНКЦИИ
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<locale>
#include<windows.h>
#include<string>
#include<conio.h>
#include <fstream>
#define UP 72
#define DOWN 80
#define ENTRY 13
#define ESC 27
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
extern HANDLE hStdOut;
extern void DeleteInfoAboutStedent();
extern void PrintInfoAboutStudent();
extern void CinInfoAboutStudent();
extern void menu();
extern void InfoAboutBestStudent();
extern void SortStudent();
extern void ConsoleCursorVisible(bool show, short size);
extern void pointer();
extern void WriteInfoInFile();
extern void ReadInfoFromFile();
extern void DeleteInfoAboutOneStudent();