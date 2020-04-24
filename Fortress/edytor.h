#pragma once
#include "libs.h"

using namespace std;

char* runningFrom()
{
	int pos;
	char* buffer = new char[MAX_PATH];
	::GetModuleFileNameA(NULL, buffer, MAX_PATH);
	for (pos = MAX_PATH; pos >= 0; pos--)
	{
		if (buffer[pos] == '\\')
		{
			buffer[pos] = '\0';
			return buffer;
		}
	}
	return buffer;
}

PtrTab* scan(char *path)
{
	DIR *dir;
	struct dirent *ent;
	PtrTab *files = new PtrTab;
	if ((dir = opendir(path)) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) 
		{
			char *path = new char[260];
			strcpy(path,ent->d_name);
			files = files->addAhead(path);
		}
		closedir(dir);
	}
	else 
	{
		/* could not open directory */
		perror("");
		putchar('\a');
		//return EXIT_FAILURE;
	}
	files = files->goTo(1);
	delete files->prev;
	return files;
}

class Obj
{
private:
	string path;
public:
	string nazwa;
	char znak;
	WORD kolor;
	int kolizja;
	int zniszczalny;
	int pozostalosc;

	Obj(int id = 0)
	{
		set(id);	
	}

	void set(int id = 0)
	{
		switch (id)
		{
		case 0:
			break;
		case 1:
			nazwa = "trawa";
			kolor = 0xAA;
			znak = ' ';
			kolizja = 0;
			zniszczalny = 0;
			pozostalosc = 1;
			break;
		case 2:
			nazwa = "drzewo";
			kolor = 0xA2;
			znak = 6;
			kolizja = 1;
			zniszczalny = 100;
			pozostalosc = 3;
			break;
		case 3:
			nazwa = "pien";
			kolor = 0xA6;
			znak = 'o';
			kolizja = 1;
			zniszczalny = 50;
			pozostalosc = 1;
			break;
		case 4:
			nazwa = "gora";
			kolor = 0xA7;
			znak = 30;
			kolizja = 1;
			zniszczalny = 500;
			pozostalosc = 5;
			break;
		case 5:
			nazwa = "gruz";
			kolor = 0xA8;
			znak = '*';
			kolizja = 1;
			zniszczalny = 75;
			pozostalosc = 1;
			break;
		case 6:
			nazwa = "woda";
			kolor = 0x93;
			znak = '~';
			kolizja = 1;
			zniszczalny = 0;
			pozostalosc = 6;
			break;
		case 7:
			nazwa = "piach";
			kolor = 0x4E;
			znak = 178;
			kolizja = 0;
			zniszczalny = 0;
			pozostalosc = 7;
			break;
		}
	}

	void mine()
	{
		if(zniszczalny)	set(pozostalosc);
	}
};

void edycja(string file, int nowy = 0)
{
	Obj obj;
	obj.nazwa = "nowy";
	obj.znak = '#';
	obj.kolor = C_GREY;
	obj.kolizja = 1;
	obj.zniszczalny = 1;
	obj.pozostalosc = 0;
	Menu edycja("Nazwa: ", "string", &obj.nazwa);
	edycja.add("Znak: ", "char", &obj.znak);
	edycja.add("Kolor: ", "WORD", &obj.kolor);
	edycja.add("Kolizja: ", "int", &obj.kolizja);
	edycja.add("Zniszczalny: ", "int", &obj.zniszczalny);
	edycja.add("Pozostalosc: ", "int", &obj.pozostalosc);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), C_GREY);

	system("cls");
	edycja.print();

	while (1)
	{
		switch (edycja.choose())
		{
		case 1:
			obj.nazwa = imie(obj.nazwa);

			system("cls");
			edycja.print();
			break;
		case 2:
			obj.znak = wyglad(obj.znak);

			system("cls");
			edycja.print();
			break;
		case 3:
			obj.kolor = barwa(obj.kolor);
			edycja.label()->next->kolorItem = obj.kolor;

			system("cls");
			edycja.print();
			break;

		case 4:
			obj.kolizja = !obj.kolizja;

			system("cls");
			edycja.print();
			break;
		case 5:
			obj.zniszczalny = !obj.zniszczalny;

			system("cls");
			edycja.print();
			break;
		case 6:
			//obj.kolizja = !obj.kolizja;
			break;
		case -1:
			return;

		case -2:
		case -3:
			system("cls");
			edycja.print();
			break;

		}
	}
}

void edytor()
{
	Menu menu("Nowy");
	PtrTab* files = NULL;
	string file;
	char *path = runningFrom();
	int lengh = strlen(path);
	path[lengh] = '\\';
	path[lengh + 1] = 't';
	path[lengh + 2] = 'i';
	path[lengh + 3] = 'l';
	path[lengh + 4] = 'e';
	path[lengh + 5] = '\0';


	int len;
	int slength = strlen(path) + 1;
	len = MultiByteToWideChar(CP_ACP, 0, path, slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, path, slength, buf, len);
	std::wstring r(buf);
	delete[] buf;

	if (CreateDirectory(r.c_str(), NULL) ||	ERROR_ALREADY_EXISTS == GetLastError())
	{

	}

	files = scan(path);

	menu.add("*SPACER*");
	if (files)
	{
		while (files->next)
		{
			menu.add((char*)files->item);
			files = files->next;
		}
	}


	while (1)
	{
		system("cls");
		menu.print();
		switch (menu.choose())
		{
		case 1:
			file = path + '\\';
			edycja(file , 1);
			break;
		case -1:
			delete path;
			files->destroyAll();
			return;

		}
	}
}