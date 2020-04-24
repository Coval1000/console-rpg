#pragma once
#include "libs.h"

extern  int ptg(int a, int b);

struct Wynik
{
	float wynik;
	int czasGry;
	char imie[15];
};
typedef struct Wynik Wynik;

int lWynikow = 0;

int logT(int a)
{
	if (!(a /= 10))	return 1;
	return 1 + logT(a);
}

string imie(string tekst)
{
	int i = tekst.length();
	char b = 8;
	gotoxy(10 + i, 0);
	do
	{
		if (!(GetAsyncKeyState(VK_UP) & 0x8000) && !(GetAsyncKeyState(VK_DOWN) & 0x8000))
		{
			if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && (i > 0))
			{
				i--;
				gotoxy(10 + i, 0);
				Sleep(150);
			}
			else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && (i < tekst.length()))
			{
				i++;
				gotoxy(10 + i, 0);
				Sleep(150);
			}
			else if ((GetAsyncKeyState(VK_DELETE) & 0x8000) && (i > 0))
			{
				tekst[i] = 0;
				i--;
				_putch(8);
				_putch(' ');
				_putch(8);
				Sleep(150);
			}
			else if(_kbhit() && (b = cin.peek()))
			{
				cin.sync();
				cin.clear();
				if (tekst.length() < 30)
				{
					char tmp;
					char tmp2;
					tmp = b;
					while(tekst[i])
					{
						tmp2 = tekst[i];
						tekst[i] = tmp;
						_putch(tekst[i]);
						tmp = tmp2;
						i++;
					}
					tekst += tmp;									
					_putch(tekst[i]);
					b = 0;

				}
			}
		}
	} while (!(GetAsyncKeyState( VK_RETURN ) & 0x8000));
	return tekst;
}

Wynik *wynikiDodaj(Wynik *tWynikow)
{

	void *tmp = tWynikow;
	if (tmp = realloc(tWynikow, sizeof(Wynik)*(lWynikow + 1)))
	{
		tWynikow = (Wynik*)tmp;
	}
	else
	{
		system("cls");
		printf("\aB\210ad pami\251ci");
		exit(10);
	}
	tWynikow[lWynikow].wynik = 0;
	tWynikow[lWynikow].czasGry = 0;
	tWynikow[lWynikow].imie[0] = 0;
	lWynikow++;
	return tWynikow;
}

void wynikiZapis(Wynik *tWynikow)
{
	int i = 0;
	int j = 0;
	FILE *zapisz;
	zapisz = fopen("wyniki.txt", "wb");
	fprintf(zapisz, "%d", lWynikow);
	putc(0, zapisz);

	for (i = 0; i<lWynikow; i++)
	{
		fprintf(zapisz, "%g", (*(tWynikow + i)).wynik);
		putc(0, zapisz);
		fprintf(zapisz, "%d", (*(tWynikow + i)).czasGry);
		putc(0, zapisz);
		for (j = 0; (*(tWynikow + i)).imie[j]; j++)
		{
			fprintf(zapisz, "%c", (*(tWynikow + i)).imie[j]);
		}
		putc(0, zapisz);
	}
	fclose(zapisz);
	return;
}

Wynik *wynikiWczyt(Wynik *tWynikow)
{
	FILE *wczytaj;
	wczytaj = fopen("wyniki.txt", "rb");
	if (wczytaj)
	{
		int i = 0;
		int j = 0;
		int b = 0;
		char trans = 1;

		for (trans = getc(wczytaj); trans; trans = getc(wczytaj)) i = (trans - 48) + i * 10;

		while (lWynikow<i)
		{
			tWynikow = wynikiDodaj(tWynikow);
			j = 0;
			(*(tWynikow + lWynikow - 1)).wynik = 0;
			(*(tWynikow + lWynikow - 1)).czasGry = 0;
			while (trans = getc(wczytaj))
			{
				if (!j && trans != '.')
				{
					(*(tWynikow + lWynikow - 1)).wynik = (trans - 48) + ((*(tWynikow + lWynikow - 1)).wynik) * 10;
				}
				else if (j && trans != '.')
				{
					(*(tWynikow + lWynikow - 1)).wynik = (trans - 48)*(1. / ptg(10, j)) + (*(tWynikow + lWynikow - 1)).wynik;
					j++;
				}
				else j++;
			}

			for (trans = getc(wczytaj); trans; trans = getc(wczytaj)) (*(tWynikow + lWynikow - 1)).czasGry = (trans - 48) + (*(tWynikow + lWynikow - 1)).czasGry * 10;
			j = 0;
			do
			{
				fscanf(wczytaj, "%c", tWynikow[lWynikow - 1].imie + j);
				j++;
			} while (tWynikow[lWynikow - 1].imie[j - 1]);
		}
		fclose(wczytaj);
	}
	return tWynikow;
}

int wynikiPrownaj(Wynik *wynik, Wynik **tWynikow)
{

	if ((*wynik).wynik > (*tWynikow)[lWynikow - 1].wynik)
	{
		if (!*tWynikow || lWynikow < 10) *tWynikow = wynikiDodaj(*tWynikow);
		int p = lWynikow - 1;//NIE U¯YWAæ FOR(;;) - siedlisko patologii!!!
		while (p >= 0 && (*wynik).wynik >(*tWynikow)[p].wynik)
		{
			if (p < lWynikow - 1)
			{
				(*tWynikow)[p + 1].czasGry = (*tWynikow)[p].czasGry;
				(*tWynikow)[p + 1].wynik = (*tWynikow)[p].wynik;
				strcpy((*tWynikow)[p + 1].imie, (*tWynikow)[p].imie);
			}
			if (p == 0 || (*wynik).wynik < (*tWynikow)[p - 1].wynik)
			{
				(*tWynikow)[p].czasGry = (*wynik).czasGry;
				(*tWynikow)[p].wynik = (*wynik).wynik;
				printf("%d. Miejsce!\nPodaj imie:\n", p + 1);
				//wynik->imie = imie("wynik");
				strcpy((*tWynikow)[p].imie, (*wynik).imie);
				wynikiZapis((*tWynikow));
				return p + 1;
			}
			p--;
		}//siedlisko patologii!!!
	}
	return 0;
}

void wyniki(Wynik *tWynikow)
{
	SMALL_RECT windowSize = { 0, 0, 50, 20 };
	COORD bufferSize = { 51, 21 };
	COORD tmpsize = { 80, 300 };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

	int pozycja = 0;
	int l;
	int b = logT((int)tWynikow[pozycja].wynik);
	system("cls");
	printf("Wyniki\n\n");
	for (pozycja = 0; pozycja<lWynikow; pozycja++)
	{
		printf("%d.", pozycja + 1);
		for (l = 2 - logT(pozycja + 1); l >= 0; l--)_putch(' ');
		printf("%s", tWynikow[pozycja].imie);
		for (l = 15 - strlen(tWynikow[pozycja].imie) + b - logT((int)tWynikow[pozycja].wynik); l >= 0; l--)_putch('.');
		printf("%.fp", tWynikow[pozycja].wynik);
		for (l = 10 - b - logT(tWynikow[pozycja].czasGry / 60); l >= 0; l--)_putch(' ');
		printf("%dmin %s%ds\n", tWynikow[pozycja].czasGry / 60, (tWynikow[pozycja].czasGry % 60) < 10 ? "0" : "", tWynikow[pozycja].czasGry % 60);
	}
	_getch();
}



