#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

using namespace std;

struct data {
	int day, month, year;
};

struct info {
	char fio[30];
	struct data birthday;
	char gender;
	float weight;
	char rank[30];
	char team[30];
};

struct spisok {
	info inf;
	struct spisok* prev, * next;
};

struct info fillInfo();
void addItem(spisok*& Top, spisok*& Bottom, info _info, int& countItems);
void printList(spisok* Top, int& countItems);
void writeTxtFile(spisok* Top, string path, int& countItems);
void readTxtFile(spisok*& Top, spisok*& Bottom, string path, int& countItems);
void printMenu(int& pos);
void writeBinFile(spisok* Top, string path, int& countItems);
void readBinFile(spisok*& Top, spisok*& Bottom, string path, int& countItems);
void delItem(spisok*& Top, spisok*& Bottom, int& countItems, int pos);
void replaceInfo(spisok* Top, int index, int& countItems);
void sortGroup(spisok* Top, spisok* Bottom, int& countItems);
void findFio(spisok* Top, char _fio[30], int& countItems);
void findGirlsAndBoys(spisok* Top, int& countItems);


int main() {

	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	spisok* Top = NULL, * Bottom = NULL;
	int countItems = 0;

	int posMenu = 1;

	system("cls");
	readBinFile(Top, Bottom, "std.dat", countItems);
	system("pause");

	while (true) {
		int s, s1;
		system("cls");
		printMenu(posMenu);
		s = _getch();
		if (s == 224) {
			int s1 = _getch();
			if (s1 == 72) {
				if (posMenu == 1) posMenu = 10;
				else --posMenu;
			}
			else if (s1 == 80) {
				if (posMenu == 10) posMenu = 1;
				else ++posMenu;
			}
		}
		else if (s == 13) {
			switch (posMenu)
			{
			case 1: {
				system("cls");
				string path;
				cout << "Введите путь: ";
				cin >> path;
				readTxtFile(Top, Bottom, path, countItems);
			}break;
			case 2: {
				system("cls");
				addItem(Top, Bottom, fillInfo(), countItems);
			}break;
			case 3: {
				system("cls");
				printList(Top, countItems);
				system("pause");
			}break;
			case 4: {
				system("cls");
				findGirlsAndBoys(Top, countItems);
				system("pause");
			}break;
			case 5: {
				char fio[30];
				system("cls");
				cout << "Введите ФИО для поиска: ";
				cin >> fio;
				while (cin.peek() != '\n') {
					char tmp[15];
					cin >> tmp;
					strcat(fio, " ");
					strcat(fio, tmp);
				}
				findFio(Top, fio, countItems);
				system("pause");
			}break;
			case 6: {
				system("cls");
				sortGroup(Top, Bottom, countItems);
				system("pause");
			}break;
			case 7: {
				system("cls");
				int index;
				cout << "Введите номер записи для замены: ";
				cin >> index;
				replaceInfo(Top, index, countItems);
				system("pause");
			}break;
			case 8: {
				system("cls");
				int pos;
				cout << "Введите номер записи: ";
				cin >> pos;
				delItem(Top, Bottom, countItems, pos);
			}break;
			case 9: {
				system("cls");
				string path;
				cout << "Введите путь: ";
				cin >> path;
				writeTxtFile(Top, path, countItems);
			}break;
			case 10: {
				writeBinFile(Top, "std.dat", countItems);
				return 0;
			}break;
			}
		}
	}

	return 0;
}

struct info fillInfo() {
	info temp;
	cout << "Введите ФИО спортсмена: ";
	cin >> temp.fio;
	while (cin.peek() != '\n') {
		char tmp[15];
		cin >> tmp;
		strcat(temp.fio, " ");
		strcat(temp.fio, tmp);
	}

	cout << "Введите дату рождения: ";
	cin >> temp.birthday.day >> temp.birthday.month >> temp.birthday.year;
	cout << "Введите пол [М | Ж]: ";
	cin >> temp.gender;
	cout << "Введите вес: ";
	cin >> temp.weight;
	cout << "Введите спортивный разряд: ";
	cin >> temp.rank;
	while (cin.peek() != '\n') {
		char tmp[15];
		cin >> tmp;
	    strcat(temp.rank, " ");
		strcat(temp.rank, tmp);
	}
	cout << "Введите название команды: ";
	cin >> temp.team;
	while (cin.peek() != '\n') {
		char tmp[15];
		cin >> tmp;
		strcat(temp.team, " ");
		strcat(temp.team, tmp);
	}
	return temp;
}

void addItem(spisok*& Top, spisok*& Bottom, info _info, int& countItems) {
	if (Top == NULL) {
		spisok* temp = new spisok;
		temp->inf = _info;
		temp->prev = temp;
		temp->next = temp;
		Top = Bottom = temp;
		++countItems;
	}
	else {
		spisok* temp = new spisok;
		temp->inf = _info;
		temp->next = Top;
		temp->prev = Bottom;
		Bottom->next = temp;
		Bottom = temp;
		Top->prev = Bottom;
		++countItems;
	}
}

void printList(spisok* Top, int& countItems) {
	cout << "|             ФИО             |Д-а рожд. | Пол |  Вес  |     Спортивный разряд       |       Название команды      |" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------" << endl;
	spisok* temp = Top;
	for (int i = 0; i < countItems; ++i) {
		cout.setf(ios::left);
		cout << '"'; cout << setw(29) << temp->inf.fio;
		cout << '"'; cout << setw(2) << temp->inf.birthday.day; cout << '.'; cout << setw(2) << temp->inf.birthday.month; cout << '.';
		cout << setw(2) << temp->inf.birthday.year;
		cout << '"'; cout << setw(5) << temp->inf.gender;
		cout << '"'; cout << setw(7) << temp->inf.weight;
		cout << '"'; cout << setw(29) << temp->inf.rank;
		cout << '"'; cout << setw(29) << temp->inf.team; cout << '"' << endl;
		temp = temp->next;
	}
}

void writeTxtFile(spisok* Top, string path, int& countItems) {
	if (Top == NULL) {
		system("cls");
		cout << "Пустой список" << endl;
		system("pause");
		return;
	}
	else {
		ofstream out(path, ios::out);
		spisok* temp = Top;
		for (int i = 0; i < countItems-1; ++i) {
			out.setf(ios::left);
			out << '"'; out << setw(29) << temp->inf.fio;
			out << '"'; out << setw(2) << temp->inf.birthday.day; out << '.'; out << setw(2) << temp->inf.birthday.month; out << '.';
			out << setw(2) << temp->inf.birthday.year;
			out << '"'; out << setw(5) << temp->inf.gender;
			out << '"'; out << setw(7) << temp->inf.weight;
			out << '"'; out << setw(29) << temp->inf.rank;
			out << '"'; out << setw(29) << temp->inf.team; out << '"' << endl;
			temp = temp->next;
		}
		temp = temp->next;
		out.setf(ios::left);
		out << '"'; out << setw(29) << temp->inf.fio;
		out << '"'; out << setw(2) << temp->inf.birthday.day; out << '.'; out << setw(2) << temp->inf.birthday.month; out << '.';
		out << setw(2) << temp->inf.birthday.year;
		out << '"'; out << setw(5) << temp->inf.gender;
		out << '"'; out << setw(7) << temp->inf.weight;
		out << '"'; out << setw(29) << temp->inf.rank;
		out << '"'; out << setw(29) << temp->inf.team; out << '"';
		
		out.close();
	}
}

void readTxtFile(spisok*& Top, spisok*& Bottom, string path, int& countItems) {
	ifstream input(path, ios::in);
	while (!input.eof()) {
		info temp;
		char str[118];
		input.getline(str, 118);
		int i = 1;
		char el = str[i++];
		while (el != '"') {
			temp.fio[i - 2] = el;
			el = str[i++];
			if ((temp.fio[i - 3] == ' ') && (temp.fio[i - 4] == ' ')) break;
		}
		temp.fio[i - 4] = '\0';
		while (el == ' ' || el == '"') el = str[i++];
		int numb = 0;
		numb = 0;
		while ((el != ' ') && (el != '.')) {
			numb = numb * 10 + (el - '0');
			el = str[i++];
		}
		temp.birthday.day = numb;
		el = str[i++];
		numb = 0;
		while ((el != ' ') && (el != '.')) {
			numb = numb * 10 + (el - '0');
			el = str[i++];
		}
		temp.birthday.month = numb;
		el = str[i++];
		numb = 0;
		while (el == ' ' || el == '.') el = str[i++];
		while ((el != ' ') && (el != '"')) {
			numb = numb * 10 + (el - '0');
			el = str[i++];
		}
		temp.birthday.year = numb;
		el = str[i++];
		temp.gender = el;
		el = str[i++];
		while (el == ' ' || el == '"') el = str[i++];
		char temp1[7];
		while ((el != ' ') && (el != '"')) {
			temp1[i - 49] = el;
			el = str[i++];
		}
		temp1[i - 49] = '\0';
		temp.weight = atof(temp1);
		while (el == ' ' || el == '"') el = str[i++];
		while (el != '"') {
			temp.rank[i - 57] = el;
			el = str[i++];
		}
		temp.rank[i - 57] = '\0';
		while (el == ' ' || el == '"') el = str[i++];
		while (el != '"') {
			temp.team[i - 87] = el;
			el = str[i++];
			if ((temp.team[i - 88] == ' ') && (temp.team[i - 89] == ' ')) break;
		}
		temp.team[i - 89] = '\0';
		addItem(Top, Bottom, temp, countItems);
	}
	input.close();
}

void printMenu(int& pos) {
	if (pos == 1) {
		cout << "==> " << "Создание из текстового файла" << endl;
		cout << "    " << "Добавление элемента в список" << endl;
		cout << "    " << "Вывод списка на экран" << endl;
		cout << "    " << "Нахождение для каждой группы 5 старших девушек и 5 тяжелых юношей" << endl;
		cout << "    " << "Поиск по ФИО" << endl;
		cout << "    " << "Сортировка списка по командам " << endl;
		cout << "    " << "Редактирование записи" << endl;
		cout << "    " << "Удаление записи" << endl;
		cout << "    " << "Запись списка в текстовый файл" << endl;
		cout << "    " << "Выход" << endl;
	}
	else if (pos == 2) {
		cout << "    " << "Создание из текстового файла" << endl;
		cout << "==> " << "Добавление элемента в список" << endl;
		cout << "    " << "Вывод списка на экран" << endl;
		cout << "    " << "Нахождение для каждой группы 5 старших девушек и 5 тяжелых юношей" << endl;
		cout << "    " << "Поиск по ФИО" << endl;
		cout << "    " << "Сортировка списка по командам " << endl;
		cout << "    " << "Редактирование записи" << endl;
		cout << "    " << "Удаление записи" << endl;
		cout << "    " << "Запись списка в текстовый файл" << endl;
		cout << "    " << "Выход" << endl;
	}
	else if (pos == 3) {
		cout << "    " << "Создание из текстового файла" << endl;
		cout << "    " << "Добавление элемента в список" << endl;
		cout << "==> " << "Вывод списка на экран" << endl;
		cout << "    " << "Нахождение для каждой группы 5 старших девушек и 5 тяжелых юношей" << endl;
		cout << "    " << "Поиск по ФИО" << endl;
		cout << "    " << "Сортировка списка по командам " << endl;
		cout << "    " << "Редактирование записи" << endl;
		cout << "    " << "Удаление записи" << endl;
		cout << "    " << "Запись списка в текстовый файл" << endl;
		cout << "    " << "Выход" << endl;
	}
	else if (pos == 4) {
		cout << "    " << "Создание из текстового файла" << endl;
		cout << "    " << "Добавление элемента в список" << endl;
		cout << "    " << "Вывод списка на экран" << endl;
		cout << "==> " << "Нахождение для каждой группы 5 старших девушек и 5 тяжелых юношей" << endl;
		cout << "    " << "Поиск по ФИО" << endl;
		cout << "    " << "Сортировка списка по командам " << endl;
		cout << "    " << "Редактирование записи" << endl;
		cout << "    " << "Удаление записи" << endl;
		cout << "    " << "Запись списка в текстовый файл" << endl;
		cout << "    " << "Выход" << endl;
	}
	else if (pos == 5) {
		cout << "    " << "Создание из текстового файла" << endl;
		cout << "    " << "Добавление элемента в список" << endl;
		cout << "    " << "Вывод списка на экран" << endl;
		cout << "    " << "Нахождение для каждой группы 5 старших девушек и 5 тяжелых юношей" << endl;
		cout << "==> " << "Поиск по ФИО" << endl;
		cout << "    " << "Сортировка списка по командам " << endl;
		cout << "    " << "Редактирование записи" << endl;
		cout << "    " << "Удаление записи" << endl;
		cout << "    " << "Запись списка в текстовый файл" << endl;
		cout << "    " << "Выход" << endl;
	}
	else if (pos == 6) {
		cout << "    " << "Создание из текстового файла" << endl;
		cout << "    " << "Добавление элемента в список" << endl;
		cout << "    " << "Вывод списка на экран" << endl;
		cout << "    " << "Нахождение для каждой группы 5 старших девушек и 5 тяжелых юношей" << endl;
		cout << "    " << "Поиск по ФИО" << endl;
		cout << "==> " << "Сортировка списка по командам " << endl;
		cout << "    " << "Редактирование записи" << endl;
		cout << "    " << "Удаление записи" << endl;
		cout << "    " << "Запись списка в текстовый файл" << endl;
		cout << "    " << "Выход" << endl;
	}
	else if (pos == 7) {
		cout << "    " << "Создание из текстового файла" << endl;
		cout << "    " << "Добавление элемента в список" << endl;
		cout << "    " << "Вывод списка на экран" << endl;
		cout << "    " << "Нахождение для каждой группы 5 старших девушек и 5 тяжелых юношей" << endl;
		cout << "    " << "Поиск по ФИО" << endl;
		cout << "    " << "Сортировка списка по командам " << endl;
		cout << "==> " << "Редактирование записи" << endl;
		cout << "    " << "Удаление записи" << endl;
		cout << "    " << "Запись списка в текстовый файл" << endl;
		cout << "    " << "Выход" << endl;
	}
	else if (pos == 8) {
		cout << "    " << "Создание из текстового файла" << endl;
		cout << "    " << "Добавление элемента в список" << endl;
		cout << "    " << "Вывод списка на экран" << endl;
		cout << "    " << "Нахождение для каждой группы 5 старших девушек и 5 тяжелых юношей" << endl;
		cout << "    " << "Поиск по ФИО" << endl;
		cout << "    " << "Сортировка списка по командам " << endl;
		cout << "    " << "Редактирование записи" << endl;
		cout << "==> " << "Удаление записи" << endl;
		cout << "    " << "Запись списка в текстовый файл" << endl;
		cout << "    " << "Выход" << endl;
	}
	else if (pos == 9) {
		cout << "    " << "Создание из текстового файла" << endl;
		cout << "    " << "Добавление элемента в список" << endl;
		cout << "    " << "Вывод списка на экран" << endl;
		cout << "    " << "Нахождение для каждой группы 5 старших девушек и 5 тяжелых юношей" << endl;
		cout << "    " << "Поиск по ФИО" << endl;
		cout << "    " << "Сортировка списка по командам " << endl;
		cout << "    " << "Редактирование записи" << endl;
		cout << "    " << "Удаление записи" << endl;
		cout << "==> " << "Запись списка в текстовый файл" << endl;
		cout << "    " << "Выход" << endl;
	}
	else if (pos == 10) {
		cout << "    " << "Создание из текстового файла" << endl;
		cout << "    " << "Добавление элемента в список" << endl;
		cout << "    " << "Вывод списка на экран" << endl;
		cout << "    " << "Нахождение для каждой группы 5 старших девушек и 5 тяжелых юношей" << endl;
		cout << "    " << "Поиск по ФИО" << endl;
		cout << "    " << "Сортировка списка по командам " << endl;
		cout << "    " << "Редактирование записи" << endl;
		cout << "    " << "Удаление записи" << endl;
		cout << "    " << "Запись списка в текстовый файл" << endl;
		cout << "==> " << "Выход" << endl;
	}
}

void writeBinFile(spisok* Top, string path, int& countItems) {
	if (Top == NULL) {
		system("cls");
		cout << "Список пуст" << endl;
		system("pause");
		return;
	}
	else {
		ofstream out(path, ios::binary);
		spisok* temp = Top;
		for (int i = 0; i < countItems; ++i) {
			out.write((const char*) & (temp->inf), sizeof(info));
			temp = temp->next;
		}
		out.close();
	}
}

void readBinFile(spisok*& Top, spisok*& Bottom, string path, int& countItems) {
	ifstream input(path, ios::binary);
	if (!input) {
		cout << "Возникла ошибка при открытии бинарного фала" << endl;
		return;
	}
	while (!input.eof()) {
		info temp;
		input.read((char*)&temp, sizeof(info));
		addItem(Top, Bottom, temp, countItems);
	}
	input.close();
	delItem(Top, Bottom, countItems, countItems);
}

void delItem(spisok*& Top, spisok*& Bottom, int& countItems, int pos) {
	if (Top == NULL) {
		system("cls");
		cout << "Пустой список" << endl;
		system("pause");
		return;
	}
	else if (pos > countItems) {
		cout << "Нет такой записи" << endl;
		system("pause");
		return;
	}
	else {
		spisok* temp = Top;
		for (int i = 1; i < pos; ++i) temp = temp->next;
		if (countItems == 1) {
			delete temp;
			Top = Bottom = NULL;
			--countItems;
		}
		else if (countItems == 2) {
			temp->prev->next = temp->prev;
			temp->prev->prev = temp->prev;
			Top = Bottom = temp->prev;
			delete temp;
			--countItems;
		}
		else {
			if (temp == Top) {
				Top->next->prev = Bottom;
				Bottom->next = Top->next;
				delete temp;
				Top = Bottom->next;
				--countItems;
			}
			else if (temp == Bottom) {
				Bottom->prev->next = Top;
				Top->prev = Bottom->prev;
				delete Bottom;
				Bottom = Top->prev;
				--countItems;
			}
			else {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				--countItems;
			}
		}
	}
}

void replaceInfo(spisok* Top, int index, int& countItems) {
	if (Top == NULL) {
		cout << "Пустой список" << endl;
		return;
	}
	else if (index > countItems || index < 1) {
		cout << "Нет такой записи" << endl;
		return;
	}
	else {
		cout << "Замена содержимого записи" << endl;
		spisok* temp = Top;
		for (int i = 1; i < index; ++i) temp = temp->next;
		info tempInfo;
		tempInfo = fillInfo();
		temp->inf = tempInfo;
	}
}

void sortGroup(spisok* Top, spisok* Bottom, int& countItems) {
	if (Top == NULL) {
		cout << "Пустой список" << endl;
		system("pause");
		return;
	}
	else {
		spisok* temp = Top;
		for (int i = 0; i < countItems - 2; ++i) {
			spisok* temp1 = temp->next;
			for (int j = i + 1; j < countItems; ++j) {
				if ((strcmp(temp->inf.team, temp1->inf.team) > 0)) {
					info tmp = temp->inf;
					temp->inf = temp1->inf;
					temp1->inf = tmp;
				}
				temp1 = temp1->next;
			}
			temp = temp->next;
		}
	}
	cout << "Сортировка выполнена" << endl;
}

void findFio(spisok* Top, char _fio[30], int& countItems) {
	if (Top == NULL) {
		cout << "Пустой список" << endl;
		system("pause");
		return;
	}
	spisok* temp = Top;
	for (int i = 0; i < countItems; ++i) {
		if (strcmp(temp->inf.fio, _fio) == 0) {
			cout.setf(ios::left);
			cout << '"'; cout << setw(29) << temp->inf.fio;
			cout << '"'; cout << setw(2) << temp->inf.birthday.day; cout << '.'; cout << setw(2) << temp->inf.birthday.month; cout << '.';
			cout << setw(2) << temp->inf.birthday.year;
			cout << '"'; cout << setw(5) << temp->inf.gender;
			cout << '"'; cout << setw(7) << temp->inf.weight;
			cout << '"'; cout << setw(29) << temp->inf.rank;
			cout << '"'; cout << setw(29) << temp->inf.team; cout << '"' << endl;
		}
		temp = temp->next;
	}
}

void findGirlsAndBoys(spisok* Top, int& countItems) {
	if (Top == NULL) {
		cout << "Пустой список" << endl;
		return;
	}
	int count = 1;
	spisok* temp = Top->next;
	char teams[100][30];
	strcpy(teams[0], Top->inf.team);
	for (int i = 0; i < countItems - 1; ++i) {
		bool find = false;
		for (int j = 0; j < count; ++j) {
			if (strcmp(temp->inf.team, teams[j]) == 0) {
				find = true;
			}
			if (find) {
				break;
			}
			else continue;
		}
		if (!find) {
			strcpy(teams[count++], temp->inf.team);
		}
		temp = temp->next;
	}

	for (int i = 0; i < count; ++i) {
		int countGirls = 0;
		info tempGroupGirls[100];
		temp = Top;
		for (int j = 0; j < countItems; ++j) {
			if ((strcmp(temp->inf.team, teams[i]) == 0) && (temp->inf.gender == 'Ж')) {
				tempGroupGirls[countGirls++] = temp->inf;
			}
			temp = temp->next;
		}
		for (int j = 0; j < countGirls - 1; ++j) {
			for (int h = j + 1; h < countGirls; ++h) {
				if (tempGroupGirls[h].birthday.year < tempGroupGirls[j].birthday.year || ((tempGroupGirls[h].birthday.year == tempGroupGirls[j].birthday.year)
					&& (tempGroupGirls[h].birthday.month < tempGroupGirls[j].birthday.month)) || ((tempGroupGirls[h].birthday.year == tempGroupGirls[j].birthday.year)
						&& (tempGroupGirls[h].birthday.month == tempGroupGirls[j].birthday.month) && (tempGroupGirls[h].birthday.day < tempGroupGirls[j].birthday.day))) {
					info tmp = tempGroupGirls[j];
					tempGroupGirls[j] = tempGroupGirls[h];
					tempGroupGirls[h] = tmp;
				}
			}
		}
		int countMans = 0;
		info tempGroupMans[100];
		temp = Top;
		for (int j = 0; j < countItems; ++j) {
			if ((strcmp(temp->inf.team, teams[i]) == 0) && (temp->inf.gender == 'М')) {
				tempGroupMans[countMans++] = temp->inf;
			}
			temp = temp->next;
		}
		for (int j = 0; j < countMans - 1; ++j) {
			for (int h = j + 1; h < countMans; ++h) {
				if (tempGroupMans[h].weight > tempGroupMans[j].weight) {
					info tmp = tempGroupMans[j];
					tempGroupMans[j] = tempGroupMans[h];
					tempGroupMans[h] = tmp;
				}
			}
		}

		cout << "Группа " << teams[i] << endl;
		if (countGirls == 0) {
			cout << "    Нет девушек в команде" << endl;
		}
		else {
			cout << "    Девушки:" << endl;
			for (int k = 0; k < countGirls; ++k) {
				if (k > 4) break;
				cout.setf(ios::left);
				cout << "        ";
				cout << '"'; cout << setw(29) << tempGroupGirls[k].fio;
				cout << '"'; cout << setw(2) << tempGroupGirls[k].birthday.day; cout << '.'; cout << setw(2) << tempGroupGirls[k].birthday.month; cout << '.';
				cout << setw(2) << tempGroupGirls[k].birthday.year;
				cout << '"'; cout << setw(5) << tempGroupGirls[k].gender;
				cout << '"'; cout << setw(7) << tempGroupGirls[k].weight;
				cout << '"'; cout << setw(29) << tempGroupGirls[k].rank;
				cout << '"'; cout << setw(29) << tempGroupGirls[k].team; cout << '"' << endl;
			}
		}
		if (countMans == 0) {
			cout << "    Нет юношей в команде" << endl;
		}
		else {
			cout << "    Юноши:" << endl;
			for (int k = 0; k < countMans; ++k) {
				if (k > 4) break;
				cout.setf(ios::left);
				cout << "        ";
				cout << '"'; cout << setw(29) << tempGroupMans[k].fio;
				cout << '"'; cout << setw(2) << tempGroupMans[k].birthday.day; cout << '.'; cout << setw(2) << tempGroupMans[k].birthday.month; cout << '.';
				cout << setw(2) << tempGroupMans[k].birthday.year;
				cout << '"'; cout << setw(5) << tempGroupMans[k].gender;
				cout << '"'; cout << setw(7) << tempGroupMans[k].weight;
				cout << '"'; cout << setw(29) << tempGroupMans[k].rank;
				cout << '"'; cout << setw(29) << tempGroupMans[k].team; cout << '"' << endl;
			}
		}
		cout << endl;
	}
}