#pragma once
#include "libs.h"

#define C_BLACK 0x00
#define C_DBLUE 0x01
#define C_DGREEN 0x02
#define C_DCYAN 0x03
#define C_DRED 0x04
#define C_DPINK 0x05
#define C_DYELLOW 0x06
#define C_GREY 0x07
#define C_DGREY 0x08
#define C_BLUE 0x09
#define C_GREEN 0x0A
#define C_CYAN 0x0B
#define C_RED 0x0C
#define C_PINK 0x0D
#define C_YELLOW 0x0E
#define C_WHITE 0x0F

using namespace std;

//przesuniecie kursora do xy
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//d - lancuch znakow, c - kolor znaku (c[i] odpowiada d[i], x - pozycja x, y - pozycja y)
void draw(char *d, WORD *c, int x = 0, int y = 0)
{
	gotoxy(x, y);
	int i = 0;
	int l = 0;
	while (*(d + i))
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), *(c + i));
		putchar(*(d + i));
		if (*(d + i) == '\n')
		{
			l++;
			gotoxy(x, l + y);
		}
		i++;
	}
	return;
}

//sizeX - szerokosc, sizeY - wysokosc, x- pozycja x, y - pozycja y
void drawRama(int sizeX, int sizeY, int x = 0, int y = 0)
{
	gotoxy(x, y);
	int i = 0;
	//Kolor konsoli jest zdefinowany jako liczba 8-bitowa gdzie 4 bity odpowiadja za kolor. Kolejno Bright Red Green Blue
	//Pierwsze 4 bity to kolor tla znaku, a kolejne 4 to kolor znaku
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), C_CYAN | (C_GREY<<4)); //Kolor znaku cyan z tlem szarym
	putchar(201); //lewy gorny rog
	for (i = 1; i < sizeX; i++)
	{
		putchar(205);// gorna belka
	}
	putchar(187); //prawy gorny rog
	for (i = 1; i < sizeY; i++)
	{
		gotoxy(x, i);
		putchar(186); //lewa kolumna
		gotoxy(sizeX + x, i);
		putchar(186); //prawa kolumna
	}
	gotoxy(x, i);
	putchar(200); // lewy dolny rog
	for (i = 1; i < sizeX; i++)
	{
		putchar(205); //dolna belka
	}
	putchar(188); //prawy dolny rog
}

void drawMiningProgress(int scale, int passed, int sizeY, int x = 0, int y = 0)
{
  	for (int i = (int)(((float)sizeY / (float)scale)*(float)passed) + 1; i; i--)
	{
		gotoxy(x, y + sizeY - i);
		putchar(178);
	}
}

void clearMiningProgress(int sizeY, int x = 0, int y = 0)
{
	for (int i = sizeY; i; i--)
	{
		gotoxy(x, y + sizeY - i);
		putchar(' ');
	}
}

class PtrTab
{
public:
	void* item;
	PtrTab* next;
	PtrTab* prev;

	PtrTab(void* item = NULL, PtrTab* next = NULL, PtrTab* prev = NULL)
	{
		this->prev = prev;
		this->next = next;
		this->item = item;
	}

	PtrTab* addBehind(void* item = NULL)
	{
		if (prev)
		{
			prev->next = new PtrTab(item, this, prev);
			this->prev = prev->next;
		}
		else this->prev = new PtrTab(item, this, NULL);
		return this->prev;
	}

	PtrTab* addAhead(void* item = NULL)
	{
		if (next)
		{
			next->prev = new PtrTab(item, next, this);
			this->next = next->prev;
		}
		else this->next = new PtrTab(item, NULL, this);
		return this->next;
	}

	PtrTab* goFoward(int n)
	{
		PtrTab* temp;
		temp = this;
		for (int i = 0; i < n; i++)
		{
			temp = temp->next;
		}
		return temp;
	}

	PtrTab* goTo(int n)
	{
		PtrTab* temp;
		temp = this;
		while (temp->prev)
		{
			temp = temp->prev;
		}
		for (int i = 0; i < n; i++)
		{
			temp = temp->next;
		}
		return temp;
	}

	PtrTab* goToEnd()
	{
		PtrTab* temp;
		temp = this;
		while (temp->next)
		{
			temp = temp->next;
		}
		return temp;
	}

	void destroyAll()
	{
		while (this->prev) delete this->prev;
		while (this->next) delete this->next;
		this->~PtrTab();
	}

	~PtrTab()
	{
		delete item;

		if (this->next) next->prev = this->prev;

		if (this->prev) prev->next = this->next;
	}
};

class MenuTab
{
public:
	void* item;
	string type;
	string tekst;
	string posttekst;
	MenuTab* next;
	MenuTab* prev;
	int kolorTekst;
	int kolorItem;
	int kolorPost;

	MenuTab(string tekst, string itemType = "", void* item = NULL, string posttekst = "", MenuTab* next = NULL, MenuTab* prev = NULL)
	{
		this->tekst = tekst;
		this->posttekst = posttekst;
		this->prev = prev;
		this->next = next;
		this->item = item;
		this->type = itemType;
		this->kolorItem = 0x07;
		this->kolorPost = 0x07;
		this->kolorTekst = 0x07;
	}

	MenuTab* addBehind(string tekst, string itemType = "", void* item = NULL, string posttekst = "")
	{
		if (prev)
		{
			prev->next = new MenuTab(tekst, itemType, item, posttekst, this, prev);
			this->prev = prev->next;
		}
		else this->prev = new MenuTab(tekst, itemType, item, posttekst, this, NULL);
		return this->prev;
	}

	MenuTab* addAhead(string tekst, string itemType = "", void* item = NULL, string posttekst = "")
	{
		if (next)
		{
			next->prev = new MenuTab(tekst, itemType, item, posttekst, next, this);
			this->next = next->prev;
		}
		else this->next = new MenuTab(tekst, itemType, item, posttekst, NULL, this);
		return this->next;
	}

	MenuTab* goFoward(int n)
	{
		MenuTab* temp;
		temp = this;
		for (int i = 0; i < n; i++)
		{
			temp = temp->next;
		}
		return temp;
	}

	MenuTab* goTo(int n)
	{
		MenuTab* temp;
		temp = this;
		while (temp->prev)
		{
			temp = temp->prev;
		}
		for (int i = 0; i < n; i++)
		{
			temp = temp->next;
		}
		return temp;
	}

	MenuTab* goToEnd()
	{
		MenuTab* temp;
		temp = this;
		while (temp->next)
		{
			temp = temp->next;
		}
		return temp;
	}

	void destroyAll()
	{
		while (this->prev) delete this->prev;
		while (this->next) delete this->next;
		this->~MenuTab();
	}

	~MenuTab()
	{

		if (this->next) next->prev = this->prev;

		if (this->prev) prev->next = this->next;
	}
};

struct Sterowanie
{
	char wGore;
	char wGorePair;
	char wDol;
	char wDolPair;
	char wLewo;
	char wLewoPair;
	char wPrawo;
	char wPrawoPair;
	char zapis;
	char zapisPair;
	char wczytanie;
	char wczytaniePair;
	char pauza;
	char pauzaPair;
	char nowy;
	char nowyPair;
};

struct Kursor
{
	char aktywny[10];
	char pozycja;
};

char inPut = 224;

struct Grafika
{
	char lewy;
	char prawy;

	char h;
	char v;
	char gl;
	char gp;
	char dl;
	char dp;

	char ramka;
	char tlo;
	char kursor;
	char ustawione;
}grafika;

class Menu
{
private:
	int pozycja;
	int maks;
	MenuTab* element;
public:
	MenuTab* label()
	{
		return element;
	}

	void add(string tekst, string itemType = "", void *item = NULL, string post = "",int miejsce = 0)
	{
		if (!miejsce) (element->goToEnd())->addAhead(tekst, itemType, item, post);
		else (element->goTo(miejsce))->addBehind(tekst, itemType, item, post);
		if(tekst != "*SPACER*") maks++;
	}

	void print()
	{
		int nr = 1;
		MenuTab* current = element;
		do
		{
			if (nr != 1) current = current->next;
			if (current->tekst != "*SPACER*")
			{
				if (pozycja != nr)
				{
					cout << ' ';
				}
				else
				{
					cout << '>';
				}
				cout << nr << '.';

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), current->kolorTekst);
				cout << current->tekst;

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), current->kolorItem);
				if (current->type == "int") cout << *(int*)current->item;
				else if (current->type == "string") cout << *(string*)current->item;
				else if (current->type == "char") cout << *(char*)current->item;
				else if (current->type == "WORD") cout << *(WORD*)current->item;
				else if (current->type != "")cout << "BAD TYPE";

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), current->kolorPost);
				cout << current->posttekst;

				if (pozycja != nr)
				{
					cout << ' ';
				}
				else
				{
					cout << '<';
				}
				cout << endl;
				nr++;
			}
			else cout << std::endl;
		} while (current->next);
	}

	int choose()
	{
		static int stateUP;
		static int stateDN;
		static int time;
		int i;

		if (((clock() / (CLOCKS_PER_SEC / 1000))-time)> 150)
		{
			stateUP = 0;
			stateDN = 0;
		}

		if ((GetAsyncKeyState( VK_DOWN ) & 0x8000) && (pozycja < maks) && !stateDN)
		{
			stateDN = 1;
			stateUP = 0;
			time = clock()/(CLOCKS_PER_SEC / 1000);
			pozycja++;
			return -2;
		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) && (pozycja > 1) && !stateUP)
		{
			stateUP = 1;
			stateDN = 0;
			time = clock() / (CLOCKS_PER_SEC / 1000);
			pozycja--;
			return -3;
		}
		else
		{
			char key;
			switch (key = _getch())
			{
			case '\r':
				return pozycja;
				break;

			case 27:
				return -1;

			default:
				key = key - '0';
				return key > 9 ? -4 : key < 0 ? -4 : key;
			}
		}
	}

	Menu(string tekst, string itemType = "", void *item = NULL, string post = "")
	{
		element = new MenuTab(tekst, itemType, item, post);
		pozycja = 1;
		maks = 1;
	}

	~Menu()
	{
		element->destroyAll();
		delete element;
	}
};

void dRamka()
{
	grafika.h = 205;
	grafika.v = 186;
	grafika.gl = 201;
	grafika.gp = 187;
	grafika.dl = 200;
	grafika.dp = 188;
}
void dZnaki()
{
	grafika.lewy = 175;
	grafika.prawy = 174;
}
void dPlansza()
{
	grafika.ramka = -78;
	grafika.tlo = -80;
	grafika.kursor = '@';
	grafika.ustawione = -79;
}

int absZnak(int a)
{
	return a < 0 ? 256 + a : a;
}

char *znakS(char lit, int p)
{
	static char przycisk[8] = { 0 };
	if (!p)
	{
		switch (lit)
		{
		case 8:
			strcpy(przycisk, "B.SPACE");
			return przycisk;

		case 13:
			strcpy(przycisk, "ENTER");
			return przycisk;

		case 27:
			strcpy(przycisk, "ESC");
			return przycisk;

		case 32:
			strcpy(przycisk, "SPACJA");
			return przycisk;
		}
		przycisk[0] = lit;
		przycisk[1] = 0;
		return przycisk;
	}

	switch (lit)
	{
	case 30:
		strcpy(przycisk, "ALT-A");
		break;

	case 48:
		strcpy(przycisk, "ALT-B");
		break;

	case 59:
		strcpy(przycisk, "F1");
		break;

	case 60:
		strcpy(przycisk, "F2");
		break;

	case 61:
		strcpy(przycisk, "F3");
		break;

	case 62:
		strcpy(przycisk, "F4");
		break;

	case 63:
		strcpy(przycisk, "F5");
		break;

	case 64:
		strcpy(przycisk, "F6");
		break;

	case 65:
		strcpy(przycisk, "F7");
		break;

	case 66:
		strcpy(przycisk, "F8");
		break;

	case 67:
		strcpy(przycisk, "F9");
		break;

	case 68:
		strcpy(przycisk, "F10");
		break;

	case -123:
		strcpy(przycisk, "F11");
		break;

	case -122:
		strcpy(przycisk, "F12");
		break;

	case 71:
		strcpy(przycisk, "Home");
		break;

	case 73:
		strcpy(przycisk, "PgDn");
		break;

	case 79:
		strcpy(przycisk, "End");
		break;

	case 81:
		strcpy(przycisk, "PgDn");
		break;

	case 82:
		strcpy(przycisk, "Insert");
		break;

	case 83:
		strcpy(przycisk, "Delete");
		break;

	case 72:
		strcpy(przycisk, "\30");
		break;

	case 80:
		strcpy(przycisk, "\31");
		break;

	case 75:
		strcpy(przycisk, "\33");
		break;

	case 77:
		strcpy(przycisk, "\32");
		break;

	}


	return przycisk;
}

char wyglad(char znak)
{
	COORD tmpsize = { 80, 300 };
	SMALL_RECT windowSize = { 0, 0, 33, 34 };
	COORD bufferSize = { 34, 35 };

	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

	int x = absZnak(znak) % 16;
	int y = absZnak(znak) / 16;
	int sizeX;
	int sizeY;
	int element = 0;
	char plansza[1123];
	char tablica[1123];

	for (sizeY = 0; sizeY<16; sizeY++)
	{
		for (sizeX = 0; sizeX<33; sizeX++)
		{
			plansza[sizeY * 2 * 34 + sizeX] = ' ';
		}
		plansza[sizeY * 2 * 34 + sizeX] = '\n';
		for (sizeX = 0; sizeX<16; sizeX++, element++)
		{
			plansza[(sizeY * 2 + 1) * 34 + sizeX * 2] = ' ';
			switch (element)
			{
			default:
				plansza[(sizeY * 2 + 1) * 34 + sizeX * 2 + 1] = element;
				break;
			case 0:
			case 7:
			case 8:
			case 9:
			case 10:
			case 13:
				plansza[(sizeY * 2 + 1) * 34 + sizeX * 2 + 1] = ' ';
				break;
			}
		}
		plansza[(sizeY * 2 + 1) * 34 + sizeX * 2] = ' ';
		plansza[(sizeY * 2 + 1) * 34 + sizeX * 2 + 1] = '\n';
	}

	for (sizeX = 0; sizeX<33; sizeX++)
	{
		plansza[sizeY * 2 * 34 + sizeX] = ' ';
	}

	plansza[sizeY * 2 * 34 + sizeX] = '\n';
	plansza[sizeY * 2 * 34 + sizeX + 1] = '\0';
	std::system("cls");

	while (1)
	{

		strcpy(tablica, plansza);
		tablica[(y * 2) * 34 + x * 2] = 218;
		tablica[(y * 2) * 34 + x * 2 + 1] = 196;
		tablica[(y * 2) * 34 + x * 2 + 2] = 191;
		tablica[(y * 2 + 1) * 34 + x * 2] = 179;
		//tablica[(y * 2 + 1) * 34 + x * 2 + 1] = '@';
		tablica[(y * 2 + 1) * 34 + x * 2 + 2] = 179;
		tablica[(y * 2 + 2) * 34 + x * 2] = 192;
		tablica[(y * 2 + 2) * 34 + x * 2 + 1] = 196;
		tablica[(y * 2 + 2) * 34 + x * 2 + 2] = 217;

		COORD coord;
		coord.X = 0;
		coord.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		puts(tablica);
		char buf = _getch();

		switch (buf)
		{
		case 224:
			buf = _getch();
		default:
			if (buf == 77 && x < 15)
			{
				x++;
			}
			else if (buf == 75 && x > 0)
			{
				x--;
			}
			else if (buf == 72 && y > 0)
			{
				y--;
			}
			else if (buf == 80 && y < 15)
			{
				y++;
			}
			break;

		case 13:
			return x + (y * 16 + 1) - 1;
		case 27:
			return znak;
		}
	}
	return 0;
}

int barwa(int kolor)
{
	COORD tmpsize = { 80, 300 };
	SMALL_RECT windowSize = { 0, 0, 33, 34 };
	COORD bufferSize = { 34, 35 };

	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

	int x = absZnak(kolor) % 4;
	int y = absZnak(kolor) / 4;
	int sizeX;
	int sizeY;
	int element = 0;
	WORD elementK = C_BLACK;
	char plansza[91];
	char tablica[91];
	WORD kolory[91];

	for (sizeY = 0; sizeY<4; sizeY++)
	{
		for (sizeX = 0; sizeX<9; sizeX++)
		{
			plansza[sizeY * 2 * 10 + sizeX] = ' ';
			kolory[sizeY * 2 * 10 + sizeX] = 0x07;
		}

		plansza[sizeY * 2 * 10 + sizeX] = '\n';
		kolory[sizeY * 2 * 10 + sizeX] = 0x07;

		for (sizeX = 0; sizeX<4; sizeX++, element++, elementK++)
		{
			plansza[(sizeY * 2 + 1) * 10 + sizeX * 2] = ' ';
			kolory[(sizeY * 2 + 1) * 10 + sizeX * 2] = 0x07;
			switch (element)
			{
			default:
				plansza[(sizeY * 2 + 1) * 10 + sizeX * 2 + 1] = element + '0';
				kolory[(sizeY * 2 + 1) * 10 + sizeX * 2 + 1] = elementK;
				break;
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
				plansza[(sizeY * 2 + 1) * 10 + sizeX * 2 + 1] = element + 'A' - 10;
				kolory[(sizeY * 2 + 1) * 10 + sizeX * 2 + 1] = elementK;
				break;
			}
		}
		plansza[(sizeY * 2 + 1) * 10 + sizeX * 2] = ' ';
		kolory[(sizeY * 2 + 1) * 10 + sizeX * 2] = 0x07;

		plansza[(sizeY * 2 + 1) * 10 + sizeX * 2 + 1] = '\n';
		kolory[(sizeY * 2 + 1) * 10 + sizeX * 2 + 1] = 0x07;
	}

	for (sizeX = 0; sizeX<9; sizeX++)
	{
		plansza[sizeY * 2 * 10 + sizeX] = ' ';
		kolory[sizeY * 2 * 10 + sizeX] = 0x07;
	}

	plansza[sizeY * 2 * 10 + sizeX] = '\n';
	kolory[sizeY * 2 * 10 + sizeX] = 0x07;

	plansza[sizeY * 2 * 10 + sizeX + 1] = '\0';
	kolory[sizeY * 2 * 10 + sizeX + 1] = 0x07;
	system("cls");

	while (1)
	{

		strcpy(tablica, plansza);
		tablica[(y * 2) * 10 + x * 2] = 218;
		tablica[(y * 2) * 10 + x * 2 + 1] = 196;
		tablica[(y * 2) * 10 + x * 2 + 2] = 191;
		tablica[(y * 2 + 1) * 10 + x * 2] = 179;
		//tablica[(y * 2 + 1) * 34 + x * 2 + 1] = '@';
		tablica[(y * 2 + 1) * 10 + x * 2 + 2] = 179;
		tablica[(y * 2 + 2) * 10 + x * 2] = 192;
		tablica[(y * 2 + 2) * 10 + x * 2 + 1] = 196;
		tablica[(y * 2 + 2) * 10 + x * 2 + 2] = 217;

		draw(tablica, kolory);
		char buf = _getch();
		switch (buf)
		{
		case 224:
			buf = _getch();
		default:
			if (buf == 77 && x < 3)
			{
				x++;
			}
			else if (buf == 75 && x > 0)
			{
				x--;
			}
			else if (buf == 72 && y > 0)
			{
				y--;
			}
			else if (buf == 80 && y < 3)
			{
				y++;
			}
			break;

		case 13:
			return x + (y * 4 + 1) - 1;
		case 27:
			return kolor;
		}
	}
	return 0;
}

void sterDef(struct Sterowanie *ster)
{
	(*ster).wGore = 72;
	(*ster).wGorePair = 1;
	(*ster).wDol = 80;
	(*ster).wDolPair = 1;
	(*ster).wLewo = 75;
	(*ster).wLewoPair = 1;
	(*ster).wPrawo = 77;
	(*ster).wPrawoPair = 1;
	ster->zapis = 59;
	ster->zapisPair = 1;
	ster->wczytanie = 60;
	ster->wczytaniePair = 1;
	ster->pauza = ' ';
	ster->pauzaPair = 0;
	ster->nowy = 'n';
	ster->nowyPair = 0;
}

char przypisz(char *key)
{
	cout << "Podaj nowy";
	*key = _getch();
	if (*key != inPut && *key) return 0;
	*key = _getch();
	return 1;
}

void opcje(struct Sterowanie *ster)
{
	COORD tmpsize = { 80, 300 };
	SMALL_RECT windowSize = { 0, 0, 40, 20 };
	COORD bufferSize = { 41, 21 };

	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

	struct Kursor opcje;
	opcje.pozycja = 0;
	int num1 = 0;
	int ilosc = 0;
	while (1)
	{

		ilosc = 0;
		system("cls");
		cout << "Sterowanie\n\n";
		cout << (char)(grafika.lewy * !(opcje.pozycja - ilosc)) << "Przesu\344 w g\242r\251  : " << znakS(ster->wGore, ster->wGorePair) << grafika.prawy * !(opcje.pozycja - ilosc) << endl;	ilosc++;
		cout << grafika.lewy * !(opcje.pozycja - ilosc) << "Przesu\344 w d\242\210   : " << znakS(ster->wDol, ster->wDolPair) << grafika.prawy * !(opcje.pozycja - ilosc) << endl;	ilosc++;
		cout << grafika.lewy * !(opcje.pozycja - ilosc) << "Przesu\344 w lewo  : " << znakS(ster->wLewo, ster->wLewoPair) << grafika.prawy * !(opcje.pozycja - ilosc) << endl;		ilosc++;
		cout << grafika.lewy * !(opcje.pozycja - ilosc) << "Przesu\344 w prawo : " << znakS(ster->wPrawo, ster->wPrawoPair) << grafika.prawy * !(opcje.pozycja - ilosc) << endl;		ilosc++;
		cout << grafika.lewy * !(opcje.pozycja - ilosc) << "Pauza		 : " << znakS(ster->pauza, ster->pauzaPair) << grafika.prawy * !(opcje.pozycja - ilosc) << endl;				ilosc++;
		cout << grafika.lewy * !(opcje.pozycja - ilosc) << "Zapisz gr\251	 : " << znakS(ster->zapis, ster->zapisPair) << grafika.prawy * !(opcje.pozycja - ilosc) << endl;			ilosc++;
		cout << grafika.lewy * !(opcje.pozycja - ilosc) << "Wczytaj gr\251	 : " << znakS(ster->wczytanie, ster->wczytaniePair) << grafika.prawy * !(opcje.pozycja - ilosc) << endl; ilosc++;
		cout << grafika.lewy * !(opcje.pozycja - ilosc) << "Niestandardowa gra	 : " << znakS(ster->nowy, ster->nowyPair) << grafika.prawy * !(opcje.pozycja - ilosc) << endl; ilosc++;
		cout << grafika.lewy * !(opcje.pozycja - ilosc) << "Domy\230lnie sterowanie" << grafika.prawy * !(opcje.pozycja - ilosc) << endl;	ilosc++;
		for (num1 = 0; num1 < 41; num1++) cout << "~";
		cout << "\nWygl\245d\n\n";
		cout << grafika.lewy * !(opcje.pozycja - ilosc) << "Ramka		 : " << grafika.ramka << grafika.prawy * !(opcje.pozycja - ilosc) << endl;				ilosc++;
		cout << grafika.lewy * !(opcje.pozycja - ilosc) << "T\210o		 : " << grafika.tlo << grafika.prawy * !(opcje.pozycja - ilosc) << endl;			ilosc++;
		cout << grafika.lewy * !(opcje.pozycja - ilosc) << "Ustawione	 : " << grafika.ustawione << grafika.prawy * !(opcje.pozycja - ilosc) << endl;			ilosc++;
		cout << grafika.lewy * !(opcje.pozycja - ilosc) << "Klocek		 : " << grafika.kursor << grafika.prawy * !(opcje.pozycja - ilosc) << endl;			ilosc++;
		cout << grafika.lewy * !(opcje.pozycja - ilosc) << "Domy\230lnie" << grafika.prawy * !(opcje.pozycja - ilosc) << endl;	ilosc++;
		cout << grafika.lewy * !(opcje.pozycja - ilosc) << "Powr\242t" << grafika.prawy * !(opcje.pozycja - ilosc) << endl;			ilosc++;
		switch (_getch())
		{
		case 224:
			switch (_getch())
			{
			case 72:
				if (opcje.pozycja > 0)
				{
					opcje.pozycja--;
				}
				break;

			case 80:
				if (opcje.pozycja < ilosc - 1)
				{
					opcje.pozycja++;
				}
				break;
			}
			break;

		case 27:
			return;
			break;

		case '\r':
			switch (opcje.pozycja)
			{
			case 0:
				ster->wGorePair = przypisz(&ster->wGore);
				break;

			case 1:
				ster->wDolPair = przypisz(&ster->wDol);
				break;

			case 2:
				ster->wLewoPair = przypisz(&ster->wLewo);
				break;

			case 3:
				ster->wPrawoPair = przypisz(&ster->wPrawo);
				break;

			case 4:
				ster->pauzaPair = przypisz(&ster->pauza);
				break;

			case 5:
				ster->zapisPair = przypisz(&ster->zapis);
				break;

			case 6:
				ster->wczytaniePair = przypisz(&ster->wczytanie);
				break;

			case 7:
				ster->wczytaniePair = przypisz(&ster->wczytanie);
				break;

			case 8:
				sterDef(ster);
				break;

			case 9:
				grafika.ramka = wyglad(grafika.ramka);
				break;

			case 10:
				grafika.tlo = wyglad(grafika.tlo);
				break;

			case 11:
				grafika.ustawione = wyglad(grafika.ustawione);
				break;

			case 12:
				grafika.kursor = wyglad(grafika.kursor);
				break;

			case 13:
				dPlansza();
				break;

			case 14:
				return;
				break;
			}
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
			SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
		}
	}
	return;
}
