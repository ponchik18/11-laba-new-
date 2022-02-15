//1.1.cpp            ОСНОВНОЙ ФАЙЛ

#include"1.2.h"

int main() {
	setlocale(0, "RUS");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY); //цвет текста основного
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	SetConsoleTitle(L"STUDENT");
	ConsoleCursorVisible(false, 100); //убираем курсор в консоли
	while (true)
	{
		CLEAN
		menu();
		pointer();
	}
	return 0;
}
