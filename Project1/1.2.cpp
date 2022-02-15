//1.2.cpp           ФАЙЛ С ФУНКЦИЯМИ
#include"1.2.h"
typedef struct STUDENT {
public:
	char* FirstName; // ИМЯ
	char* LastName; // ФАМИЛИЯ
	char* Surname; // ОТЧЕСТВО
	int GroupeNumber; // НОМЕР ГРУППЫ
	int Marks[5]; // УСПЕВАЕМОСТЬ

	STUDENT(const char* fn="None", const char* ln="None", const char* sn="None", int g=0, int* m=0) {
		FirstName = new char[strlen(fn) + 1];
		strcpy(FirstName, fn);
		LastName = new char[strlen(ln)+1];
		strcpy(LastName, ln);
		Surname = new char[strlen(sn) + 1];
		strcpy(Surname, sn);
		GroupeNumber = g;
		if (m != 0) {
			for (register short unsigned i=0; i < 5; i++) {
				Marks[i] = m[i];
			}
		}
		else
			for (register short unsigned i=0; i < 5; i++) {
				Marks[i] = 0;
			}
	}

	~STUDENT() {
		delete[] LastName;
		delete[] FirstName;
		delete[] Surname;
	}

	STUDENT(STUDENT& st) {
		FirstName = new char[strlen(st.FirstName) + 1];
		strcpy(FirstName, st.FirstName);
		LastName = new char[strlen(st.LastName) + 1];
		strcpy(LastName, st.LastName);
		Surname = new char[strlen(st.LastName) + 1];
		strcpy(Surname, st.LastName);
		GroupeNumber = st.GroupeNumber;
		for (register short unsigned i=0; i < 5; i++) {
			Marks[i] = st.Marks[i];
		}
	}
	STUDENT operator= (const STUDENT& st) {
		FirstName = new char[strlen(st.FirstName) + 1];
		strcpy(FirstName, st.FirstName);
		LastName = new char[strlen(st.LastName) + 1];
		strcpy(LastName, st.LastName);
		Surname = new char[strlen(st.LastName) + 1];
		strcpy(Surname, st.LastName);
		GroupeNumber = st.GroupeNumber;
		for (register short unsigned i=0; i < 5; i++) {
			Marks[i] = st.Marks[i];
		}
		return *this;
	}
	void PrintInFile(FILE*out) {
		int c;
		///1
		c = (size_t)strlen(FirstName) + 1;
		fwrite(&c, sizeof(int), 1, out);
		fwrite(FirstName, sizeof(char), c,out);
		/////2
		c = (size_t)strlen(LastName) + 1;
		fwrite(&c, sizeof(int), 1, out);
		fwrite(LastName, sizeof(char), c, out);
		/////3
		c = (size_t)strlen(Surname) + 1;
		fwrite(&c, sizeof(int), 1, out);
		fwrite(Surname, sizeof(char), c, out);
		//////4
		fwrite(&GroupeNumber, sizeof(int), 1, out);
		//////5
		for (int i = 0; i < size(Marks); i++) {
			fwrite(&Marks[i], sizeof(int), 1, out);
		}
	}
	void ReadFromFile(FILE* in) {
		int c;
		//////1
		fread(&c, sizeof(int), 1, in);
		FirstName = new char[c];
		fread(FirstName, sizeof(char), c, in);
		//////2
		fread(&c, sizeof(int), 1, in);
		LastName = new char[c];
		fread(LastName, sizeof(char), c, in);
		//////3
		fread(&c, sizeof(int), 1, in);
		Surname = new char[c];
		fread(Surname, sizeof(char), c, in);
		///////4
		fread(&GroupeNumber, sizeof(int), 1, in);
		///////5
		for (int i = 0; i < size(Marks); i++) {
			fread(&Marks[i], sizeof(int), 1, in);
		}

	}
	void Info() {
		cout.width(20);
		cout << LastName << " " << FirstName[0] << ". " << Surname[0] << ".";
		cout.width(20);
		cout << GroupeNumber;
		cout.width(20);
		cout << Marks[0] << ", " << Marks[1] << ", " << Marks[2] << ", " << Marks[3] << ", " << Marks[4] << ". " << endl;
	}
}STUDENT; // Структура студент

////////// Переменные
static STUDENT* undergraduate; // структура для хранения данных о студентах
static STUDENT* tmp; // структура для хранения временных данных(нужно для сортировки)
static int CountStudent = 0; // Количество студентов
extern HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем дескриптор консоли
static int ActiveMenu = 4;


//////////// Функции для меню

static void GotoY( short y, short x=25){
	SetConsoleCursorPosition(hStdOut, { x,y });
}
extern void ConsoleCursorVisible(bool show, short size) {
	CONSOLE_CURSOR_INFO CursorInfo;
	CursorInfo.bVisible = show;
	CursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &CursorInfo);
}
static void ConsoleTextColor(int &n) {
	if (n++==ActiveMenu){
		SetConsoleTextAttribute(hStdOut, 80);
	}
	else {
		SetConsoleTextAttribute(hStdOut, 15);
	}
}
static void ConsoleTextColorSort(int& n, int am) {
	if (n++ == am) {
		SetConsoleTextAttribute(hStdOut, 80);
	}
	else {
		SetConsoleTextAttribute(hStdOut, 15);
	}
}
extern void pointer() {
	char ch;
	ch = _getch();
	if (ch == -32) ch = _getch(); // Отлавливаем стрелочки
	switch (ch)
	{
	case ESC:
		exit(0);
	case DOWN:
		if (ActiveMenu < 12)
			ActiveMenu++;
		break;
	case UP:
		if (ActiveMenu > 4)
			ActiveMenu--;
		break;
	case ENTRY:
		switch (ActiveMenu) {
		case 4:
			CLEAN
			CinInfoAboutStudent();
			ClEANCONSOLE
			PAUSE
			break;
		case 5:
			CLEAN
			PrintInfoAboutStudent();
			PAUSE
			break;
		case 6:
			CLEAN

			SortStudent();
			PAUSE
			break;
		case 7:
			CLEAN

			InfoAboutBestStudent();
			PAUSE
			break;
		case 8:
			CLEAN
			DeleteInfoAboutStedent();
			PAUSE
			break;
		case 9:
			CLEAN
			DeleteInfoAboutOneStudent();
			PAUSE
			break;
		case 10:
			CLEAN
			ReadInfoFromFile();
			PAUSE
			break;
		case 11:
			CLEAN
			WriteInfoInFile();
			PAUSE
			break;
		}
		break;
	default:
		break;
	}
}
extern void menu() {
	int n = 4; // для перехода по строкам меню
	//////////
	CLEAN
	cout << "+-----------------------------------------------------------------------------------------+" << endl << "|";
	cout.width(50);
	cout << "Меню";
	cout.setf(ios::right);
	cout.width(40);
	cout << "|" << endl;
	cout << "+-----------------------------------------------------------------------------------------+" << endl;
	GotoY(n);
	ConsoleTextColor(n);
	cout << "1. Ввод данных о студенте с клавитуре;"<<endl;
	GotoY(n);
	ConsoleTextColor(n);
	cout << "2. Вывод данных о студентах;" << endl;
	GotoY(n);
	ConsoleTextColor(n);
	cout << "3. Сортировка данных по параметру;" << endl;
	GotoY(n);
	ConsoleTextColor(n);
	cout << "4. Вывести информацию о лучших студентах, с оценках 8 и 9;" << endl;
	GotoY(n);
	ConsoleTextColor(n);
	cout << "5. Отчистить данные о студентах;" << endl;
	GotoY(n);
	ConsoleTextColor(n);
	cout << "6. Удалить данные об студенте ;" << endl;
	GotoY(n);
	ConsoleTextColor(n);
	cout << "7. Прочитать данные о студентах с файла;" << endl;
	GotoY(n);
	ConsoleTextColor(n);
	cout << "8. Записать данные о студентах в файл" << endl;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
}

///////////// Вспомогательные функции

static void DinamicAllocate() {
	tmp = new STUDENT[CountStudent];
	for (register int i = 0; i < CountStudent-1; i++) {
		tmp[i] = undergraduate[i];
	}
	delete[] undergraduate;
	undergraduate = tmp;
}
static char* CoutString() {

	char c;
	int len = 1;
	char* str = new char[0];
	while ((c = cin.get()) != '\n')
	{
		char* temp = new char[len + 1];

		for (int i = 0; i < len - 1; i++) {
			temp[i] = str[i];
		}
		temp[len - 1] = c;
		temp[len] = '\0';
		delete[] str;
		str = temp;
		len++;
	}
	return str;
}
static void InfoClassification() {
	CLEAN
		cout.width(30);
	cout << "Фамилия и Инициалы";
	cout.width(24);
	cout << "Номер группы";
	cout.width(29);
	cout << "5 оценок студента" << endl;
	for (register int i = 0; i < 85; i++)
		cout << "_";
	cout << endl;
}
static void SortLastNameStudent() {
	STUDENT temp;
	for (register int i = 0; i < CountStudent; i++) {
		for (register int j = 0; j < CountStudent-1; j++) {
			if (strcmp(undergraduate[j].LastName, undergraduate[j + 1].LastName)>0) {
				temp = undergraduate[j];
				undergraduate[j] = undergraduate[j+1];
				undergraduate[j + 1] = temp;
			}
		}
	}
}
static void SortGroupeNumber() {
	STUDENT temp;
	for (register int i = 0; i < CountStudent; i++) {
		for (register int j = 0; j < CountStudent - 1; j++) {
			if (undergraduate[j].GroupeNumber > undergraduate[j + 1].GroupeNumber) {
				temp = undergraduate[j];
				undergraduate[j] = undergraduate[j + 1];
				undergraduate[j + 1] = temp;
			}
		}
	}
}
static float MiddleRes(int * s) {
	float sum=0;
	for (register int i = 0; i < 5; i++) {
		sum +=(float) *s;
		s++;
	}
	return sum / 5;
}
static void SortArtigmetic() {
	STUDENT temp;
	for (register int i = 0; i < CountStudent; i++) {
		for (register int j = 0; j < CountStudent - 1; j++) {
			if (MiddleRes(undergraduate[j].Marks) > MiddleRes(undergraduate[j + 1].Marks)) {
				temp = undergraduate[j];
				undergraduate[j] = undergraduate[j + 1];
				undergraduate[j + 1] = temp;
			}
		}
	}
}
static char* FindEndSymbol(char* str, int s) {
	char* p = NULL;
	while (*str != '\0') {
		if (*str == s) {
			p = str;
		}
		str++;
	}
	return p;
}
static bool FileExtension(char* str, int* s) {
	char* p = FindEndSymbol(str, 92); //    ' / '
	int i = 0;

	if (p != NULL) {
		i = p - str + 1;
	}

	int flag = 0;
	for (i; i < strlen(str); i++) {
		if (str[i] == '.') {
			flag = i;
			i = strlen(str);
		}
	}

	*s = flag;
	if (flag == 0) {

		return false;
	}
	return true;

}
static char* AddExtension(char* str) {
	int i = 0;
	if (FileExtension(str, &i) == true) { // стрираем всё что находится после '.' и её тоже 
		char* tmp = new char[i + 1];
		for (int j = 0; j < i; j++) {
			tmp[j] = str[j];
		}
		tmp[i] = '\0';
		delete[] str;
		str = tmp;
	}
	char* tmp = new char[strlen(str) + 1];
	int j = 0;
	for (j; j < strlen(str); j++) {
		tmp[j] = str[j];
	}
	tmp[j++] = '.';
	tmp[j++] = 't';
	tmp[j++] = 'x';
	tmp[j++] = 't';
	tmp[j] = '\0';
	delete[] str;
	str = tmp;
	return str;
}
static void DinamicDelete(int n) {
	CountStudent--;
	tmp = new STUDENT[CountStudent];
	int i = 0;
	for (i = 0; i < n-1; i++) 
	{
		tmp[i] = undergraduate[i];
	}
	for (i; i < CountStudent; i++) {
		tmp[i] = undergraduate[i + 1];
	}
	delete[] undergraduate;
	undergraduate = tmp;
	
}
static void PointerSort(int& actmenu, bool &flag) {
	char ch;
	ch = _getch();
	if (ch == -32) ch = _getch(); // Отлавливаем стрелочки
	switch (ch)
	{
	case ESC:
		flag = false;
		return;
	case DOWN:
		if (actmenu < 3)
			actmenu++;
		break;
	case UP:
		if (actmenu > 1)
			actmenu--;
		break;
	case ENTRY:
		switch (actmenu) {
		case 1:
			SortLastNameStudent();
			flag = false;
			break;
		case 2:
			SortGroupeNumber();
			flag = false;
			break;
		case 3:
			SortGroupeNumber();
			flag = false;
			break;
		}
		break;
	default:
		break;
	}
}
static void MenuSort(const int actmenu) {
	cout << "Выберите поля, по которому надо сделать сортировку:" << endl;
	int Ypos = 1;
	GotoY(Ypos,10);
	ConsoleTextColorSort(Ypos, actmenu);
	cout << "\t1) Фамилия" << endl;
	GotoY(Ypos, 10);
	ConsoleTextColorSort(Ypos, actmenu);
	cout << "\t2) Учебная группа" << endl;
	GotoY(Ypos, 10);
	ConsoleTextColorSort(Ypos, actmenu);
	cout << "\t3) Средний балл" << endl;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY); //цвет текста основного
}
//////////////// основные функции

extern void CinInfoAboutStudent() {
	CountStudent++;
	DinamicAllocate();
	cout << "Введите фамилию "<<CountStudent <<"-ого студента: " << endl;
	undergraduate[CountStudent - 1].LastName = CoutString();
	cout << "Введите имя " << CountStudent << "-ого студента: " << endl;
	undergraduate[CountStudent - 1].FirstName = CoutString();
	cout << "Введите отчество " << CountStudent << "-ого студента: " << endl;
	undergraduate[CountStudent - 1].Surname = CoutString();
	cout << "Введите группу " << CountStudent << "-ого студента: " << endl;
	undergraduate[CountStudent - 1].GroupeNumber = getValue(undergraduate[CountStudent - 1].GroupeNumber);
	cout << "Введите 5 оценок " << CountStudent << "-ого студента: " << endl;
	for (register short unsigned i = 0; i < 5; i++) {
		cout <<"\t" << i + 1 << ": ";
		undergraduate[CountStudent - 1].Marks[i] = getValue(undergraduate[CountStudent - 1].Marks[i]);
	}

} 
extern void PrintInfoAboutStudent() {
	if (CountStudent == 0) {
		cout << "Сначало нужно ввести данные" << endl;
		return;
	}
	InfoClassification();
	for (register int i = 0; i < CountStudent; i++) {
		cout << i + 1 << ":";
		undergraduate[i].Info();
	}
}
extern void DeleteInfoAboutStedent() {
	if (CountStudent == 0) {
		cout << "Сначало нужно ввести данные" << endl;
	}
	else {
		delete[] undergraduate;
		CountStudent = 0;
	}
	cout << "Отчистка завершена" << endl;

}
extern void WriteInfoInFile(){
	
	if (CountStudent == 0) {
		cout << "Сначало нужно ввести данные" << endl;
		return;
	}
	cout << "Введите название файла(можно без расширения)" << endl;
	char* str = CoutString();
	str = AddExtension(str);
	FILE* out = fopen(str, "wb");
	
	if (out == NULL) {
		cout << "ФАЙЛ НЕ МОЖЕТ БЫТЬ ОТКРЫТ!!!" << endl;
		exit(0);
	}
	fwrite(&CountStudent, sizeof(int), 1, out);
	for (int i = 0; i < CountStudent; i++) {
		undergraduate[i].PrintInFile(out);
	}
	cout << "Запись успешно завершена!" << endl;
	fclose(out);
	
}
extern void ReadInfoFromFile(){
	cout << "Введите название файла(можно без расширения)" << endl;
	char* str = CoutString();
	str = AddExtension(str);
	FILE* in = fopen(str, "rb");
	if (in == NULL) {
		cout << "ДАННЫЙ ФАЙЛ НЕ НАЙДЕН!!!" << endl;
		return;
	}
	fread(&CountStudent, sizeof(int), 1, in);
	undergraduate = new STUDENT[CountStudent];
	for (int i = 0; i < CountStudent; i++) {
		undergraduate[i].ReadFromFile(in);
	}
	cout << "Чтение успешно завершено!" << endl;
	fclose(in);
}
extern void InfoAboutBestStudent() {
	if (CountStudent == 0) {
		cout << "Сначало нужно ввести данные" << endl;
			return;
	}
	register int flag = 0;
	for (register int i = 0; i < CountStudent; i++) {
		int j = 0;
		for (j; j < 5 && (undergraduate[i].Marks[j] == 8 || undergraduate[i].Marks[j] == 9); j++) {}
		if (j == 5) {
			flag++;
			if (flag == 1) {
				InfoClassification();
			}
			undergraduate[i].Info();
		}
	}
	if (flag == 0) {
		cout << "Нет студентов только с оценками 8 и 9" << endl;
	}
}
extern void SortStudent() {
	if (CountStudent == 0) {
		cout << "Сначало нужно ввести данные" << endl;
		return;
	}
	int ActMenuSort = 1;
	bool flag = true;
	while (flag) {
		CLEAN
		MenuSort(ActMenuSort);
		PointerSort(ActMenuSort, flag);
	}
	cout << "Сортировка завершена!!!" << endl;
}
extern void DeleteInfoAboutOneStudent() {
	PrintInfoAboutStudent();
	cout <<endl<< "Введите номер студента для удаления" << endl;
	int n;
	do {
		n = getValue(n);
	} while (n > CountStudent || n < 0);
	DinamicDelete(n);
	cout << "Удаление завершено!" << endl;
	ClEANCONSOLE
}
////////////// 


