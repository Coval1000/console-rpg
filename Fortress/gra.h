#pragma once
#include "libs.h"

int ptg(int a, int b)
{
	if (b == 1) return a;
	else if (b == 0) return 1;
	return a*ptg(a, b - 1);
}

int sumaC(int a, int b)
{
	if (b == 1) return a;
	else if (b == 0) return 0;
	return a + sumaC(a + a, b - 1);
}
/*
void zapis(char *w, struct Player *player, int *xy, float *punkty, int *czas)
{

	int i = 0;
	char trans = 0;
	FILE *zapisz;
	zapisz = fopen("zapis1.txt", "wb");
	fprintf(zapisz, "%d", strlen(w));
	putc(0, zapisz);

	for (i = 0; *(w + i); i++)
	{
		if (*(w + i) == grafika.tlo) trans = 't';
		else if (*(w + i) == grafika.ustawione) trans = 'u';
		else if (*(w + i) == grafika.ramka) trans = 'r';
		else trans = *(w + i);
		fprintf(zapisz, "%c", trans);
	}
	putc(0, zapisz);

	//putc((*player).poss[0], zapisz);
	//putc((*player).poss[1], zapisz);

	putc(*xy, zapisz);
	putc(*(xy + 1), zapisz);

	putc(0, zapisz);
	fprintf(zapisz, "%d", *czas);
	putc(0, zapisz);
	fprintf(zapisz, "%g", *punkty);
	putc(0, zapisz);
	putc(0, zapisz);
	fclose(zapisz);
	return;
}

char *wczyt(char *w, struct Player *player, int *xy, float *punkty, int *czas)
{
	FILE *wczytaj;
	wczytaj = fopen("zapis1.txt", "rb");
	if (wczytaj)
	{
		int i = 0;
		char trans = 1;

		for (trans = getc(wczytaj); trans; trans = getc(wczytaj)) i = (trans - 48) + i * 10;

		void *tmp = w;
		if (tmp = realloc(w, i * sizeof(char) + 1))
		{
			w = (char*)tmp;
		}
		else
		{
			system("cls");
			cout << "\aB\210ad pami\251ci";
			return w;
		}

		*punkty = 0;
		*czas = 0;

		i = 0;
		do
		{

			fscanf(wczytaj, "%c", &trans);
			switch (trans)
			{
			case 't':
				*(w + i) = grafika.tlo;
				break;
			case 'u':
				*(w + i) = grafika.ustawione;
				break;
			case 'r':
				*(w + i) = grafika.ramka;
				break;
			default:
				*(w + i) = trans;
			}
			i++;
		} while (*(w + i - 1));

		//(*player).poss[0] = getc(wczytaj);
		//(*player).poss[1] = getc(wczytaj);


		xy[0] = getc(wczytaj);
		xy[1] = getc(wczytaj);

		getc(wczytaj);

		for (trans = getc(wczytaj); trans; trans = getc(wczytaj)) *czas = (trans - 48) + (*czas) * 10;
		*czas = (clock() / CLOCKS_PER_SEC) - *czas;

		i = 0;
		while (trans = getc(wczytaj))
		{
			if (!i && trans != '.')
			{
				*punkty = (trans - 48) + (*punkty) * 10;
			}
			else if (i && trans != '.')
			{
				*punkty = (trans - 48)*(1. / (float)ptg(10, i)) + (*punkty);
				i++;
			}
			else i++;
		}

		i = 0;
		SMALL_RECT windowSize = { 0, 0, xy[0] + 1, xy[1] + 5 };
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
		COORD bufferSize = { xy[0] + 1 + 1, xy[1] + 5 + 1 };
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
		fclose(wczytaj);
	}
	else
	{
		SMALL_RECT windowSize1 = { 0, 0, 45, 20 };
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize1);
		COORD bufferSize1 = { 46, 21 };
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize1);
		system("cls");
		printf("\aNie uda\210o si\251 za\210adowa\206 stanu gry!\nNacisnij dowolny klawisz, \276eby kontynuowa\206");
		_getch();
		SMALL_RECT windowSize2 = { 0, 0, xy[0] + 1, xy[1] + 5 };
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize2);
		COORD bufferSize2 = { xy[0] + 1 + 1, xy[1] + 5 + 1 };
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize2);
	}
	return w;
}
*/
void komunikat(char *tlo, int *xy, char *tekst, int pX, int pY, char w, int ramka)
{
	int iX = 0;
	int iY = 0;
	int t;
	int m = 0;
	if (xy[0] < strlen(tekst))return;
	switch (w)
	{
	case 'L':
		for (t = -1; t<2; t++)
		{
			for (m = 0;; m++)
			{
				*(tlo + ((xy[1] / 2) + pY + t) * (xy[0] + 1) + m + pX) = grafika.h;
			}
		}
		for (m = 0; tekst[m]; m++)
		{
			*(tlo + ((xy[1] / 2) + pY) * (xy[0] + 1) + m + pX) = tekst[m];
		}
		break;


	case 'P':
		for (m = 0; tekst[m]; m++)
		{
			*(tlo + ((xy[1] / 2) + pY) * (xy[0] + 1) + xy[0] - strlen(tekst) + m + pX) = tekst[m];
		}
		break;

	case 'S':
		if (ramka)
		{
			for (t = -1; t < 2; t++)
			{
				switch (t)
				{
				case -1:
					*(tlo + ((xy[1] / 2) + pY + t) * (xy[0] + 1) + (xy[0] / 2) - strlen(tekst) / 2 + pX - 1) = grafika.gl;
					break;
				case 0:
					*(tlo + ((xy[1] / 2) + pY + t) * (xy[0] + 1) + (xy[0] / 2) - strlen(tekst) / 2 + pX - 1) = grafika.v;
					break;
				case 1:
					*(tlo + ((xy[1] / 2) + pY + t) * (xy[0] + 1) + (xy[0] / 2) - strlen(tekst) / 2 + pX - 1) = grafika.dl;
					break;
				}
				for (m = 0; tekst[m]; m++)
				{
					*(tlo + ((xy[1] / 2) + pY + t) * (xy[0] + 1) + (xy[0] / 2) - strlen(tekst) / 2 + m + pX) = grafika.h;
				}
				switch (t)
				{
				case -1:
					*(tlo + ((xy[1] / 2) + pY + t) * (xy[0] + 1) + (xy[0] / 2) - strlen(tekst) / 2 + m + pX) = grafika.gp;
					break;
				case 0:
					*(tlo + ((xy[1] / 2) + pY + t) * (xy[0] + 1) + (xy[0] / 2) - strlen(tekst) / 2 + m + pX) = grafika.v;
					break;
				case 1:
					*(tlo + ((xy[1] / 2) + pY + t) * (xy[0] + 1) + (xy[0] / 2) - strlen(tekst) / 2 + m + pX) = grafika.dp;
					break;
				}
			}
		}
		for (m = 0; tekst[m]; m++)
		{
			*(tlo + ((xy[1] / 2) + pY) * (xy[0] + 1) + (xy[0] / 2) - strlen(tekst) / 2 + m + pX) = tekst[m];
		}
		break;
	}
}

int input()
{
	if (_kbhit())
	{
		int buf = _getch();
		if (buf == inPut || !buf)
		{
			buf = _getch();
			buf += 256;
		}
		return (int)buf;
	}
}

void gra(Wynik **tWynikow, struct Sterowanie *ster)
{
	World world;

	int timePopr = clock() / (CLOCKS_PER_SEC);
	int time = 0;
	float punkty = 0;

	int mining = 0;

	COORD tmpsize = { 260, 300 };
	COORD bufferSize = { 50, 27 };
	SMALL_RECT konsola = { 0, 0, 49 , 26 };

	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &konsola);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

	char* map;
	WORD* mapC;
	int cykl = 0;
	drawRama(41, 21);
	drawRama(2, 21, 42);

	int trigger = 0;

	while (1)
	{
		if (_kbhit())
		{
			int pauza = 0;
			int input = 0;
			char buf = _getch();
			if (buf == inPut || !buf)
			{
				buf = _getch();
				input = 1;
			}

			if (input == ster->wPrawoPair && buf == ster->wPrawo)
			{
				world.direction = 0;
				if (!world.player->poss->right->tile->kolizja)
				{
					world.move('E');
				}
			}
			else if (input == ster->wLewoPair && buf == ster->wLewo)
			{
				world.direction = 2;
				if (!world.player->poss->left->tile->kolizja)
				{
					world.move('W');
					
				}
			}
			else if (input == ster->wGorePair && buf == ster->wGore) 
			{
				world.direction = 1;
				if (!world.player->poss->up->tile->kolizja)
				{
					world.move('N');
				}
			}
			else if (input == ster->wDolPair && buf == ster->wDol)
			{
				world.direction = 3;
				if (!world.player->poss->down->tile->kolizja)
				{
					world.move('S');
				}
			}
			else if (input == ster->zapisPair && buf == ster->zapis)
			{
				trigger = 1;
			}
			else if (input == ster->wczytaniePair && buf == ster->wczytanie)
			{

			}
			else if (input == ster->pauzaPair && buf == ster->pauza)
			{
				pauza = (clock() / (CLOCKS_PER_SEC));
				_getch();
				timePopr += (clock() / (CLOCKS_PER_SEC)) - pauza;
			}
			else if (input == ster->nowyPair && buf == ster->nowy)
			{
				struct Kursor kursor;
				kursor.pozycja = 0;
				unsigned char x = 0;
				unsigned char y = 0;
				int ilosc;
				char buffor = 0;
				while (buffor != 13)
				{
					COORD tmpsize = { 260, 300 };
					SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
					COORD bufferSize = { 35, 21 };
					SMALL_RECT konsola = { 0, 0, 34 , 20 };
					SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &konsola);
					SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
					system("cls");
					printf("Wynik gry niestandardowej nie jest zapisywany na tablicy wynik\242w.\n UWAGA! okno konsoli nie mo\276e by\206 \nwi\251ksze ni\276 ekran. Powoduje to \nb\210\251de wy\230wietlanie zbyt du\276ych map\n\n");
					ilosc = 0;
					printf("%cX: %d\n", grafika.lewy * !(kursor.pozycja - ilosc), x); ilosc++;
					printf("%cY: %d\n", grafika.lewy * !(kursor.pozycja - ilosc), y); ilosc++;
					switch (buffor = _getch())
					{
					case 27:
						return;
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						if (!kursor.pozycja)
						{
							if (buffor - '0' + x * 10 > 255) x = 255;
							else x = buffor - '0' + x * 10;
						}
						else
						{
							if (buffor - '0' + y * 10 > 255) x = 255;
							else y = buffor - '0' + y * 10;
						}
						break;
					case 8:
						if (!kursor.pozycja && x > 0)
						{
							x = x / 10;
						}
						else if (y > 0)
						{
							y = y / 10;
						}
						break;

					case 72:
						if (kursor.pozycja > 0)
						{
							kursor.pozycja--;
						}
						break;

					case 80:
						if (kursor.pozycja < ilosc - 1)
						{
							kursor.pozycja++;
						}
						break;

					case 224:

						switch (_getch())
						{
						case 72:
							if (kursor.pozycja > 0)
							{
								kursor.pozycja--;
							}
							break;

						case 80:
							if (kursor.pozycja < ilosc - 1)
							{
								kursor.pozycja++;
							}
							break;
						}
						break;
					}
				}
				if (!x || !y)
				{
					return;
				}
				timePopr = clock() / CLOCKS_PER_SEC;
				punkty = 0;
			}
			else if (buf == 'e')
			{
				world.player->eq(0);
				drawRama(41, 21);
				drawRama(2, 21, 42);
			}
			switch (buf)
			{
			case 27:
				pauza = (clock() / (CLOCKS_PER_SEC));
				do
				{
					if (buf == 't')
					{
						return;
					}
					buf = _getch();
				} while (buf != 'n');
				timePopr += (clock() / (CLOCKS_PER_SEC)) - pauza;
				break;
			}
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			switch (world.direction)
			{
			case 0:
				if (mining == world.player->poss->right->tile->zniszczalny)
				{
					world.player->poss->right->tile->mine();
					clearMiningProgress(20, 43, 1);
					mining = 0;
					if (trigger)
					{
						trigger = 0;
					}
					int slot = 0;
					do
					{
						if ((world.player->inventory[slot][0] == 1 || !world.player->inventory[slot][0]) && world.player->inventory[slot][1] < 99)
						{
							world.player->inventory[slot][0] = 1;
							world.player->inventory[slot][1]++;
							break;
						}
						else slot++;
					} while (slot<40);
				}
				else if (world.player->poss->right->tile->zniszczalny)
				{
					drawMiningProgress(world.player->poss->right->tile->zniszczalny, mining, 20, 43, 1);
					mining++;
				}
				break;
			case 1:
				if (mining == world.player->poss->up->tile->zniszczalny)
				{
					world.player->poss->up->tile->mine();
					clearMiningProgress(20, 43, 1);
					mining = 0;
				}
				else if (world.player->poss->up->tile->zniszczalny)
				{
					drawMiningProgress(world.player->poss->up->tile->zniszczalny, mining, 20, 43, 1);
					mining++;
				}
				break;
			case 2:
				if (mining == world.player->poss->left->tile->zniszczalny)
				{
					world.player->poss->left->tile->mine();
					clearMiningProgress(20, 43, 1);
					mining = 0;
				}
				else if (world.player->poss->left->tile->zniszczalny)
				{
					drawMiningProgress(world.player->poss->left->tile->zniszczalny, mining, 20, 43, 1);
					mining++;
				}
				break;
			case 3:
				if (mining == world.player->poss->down->tile->zniszczalny)
				{
					world.player->poss->down->tile->mine();
					clearMiningProgress(20, 43, 1);
					mining = 0;
				}
				else if (world.player->poss->down->tile->zniszczalny)
				{
					drawMiningProgress(world.player->poss->down->tile->zniszczalny, mining, 20, 43, 1);
					mining++;
				}
				break;
			}
		}
		else if(mining)
		{
			mining = 0;
			clearMiningProgress(20, 43, 1);
		}

		map = world.area();
		*(map + 10 * 40 + 30) = 1;
		mapC = world.areaColor();
		*(mapC + 10 * 40 + 30) = 0xA0;


		if (cykl > 12)
		{
			switch (world.direction)
			{
			case 0:
				*(map + 10 * 41 + 21) = 'X';
				break;
			case 1:
				*(map + 9 * 41 + 20) = 'X';
				break;
			case 2:
				*(map + 10 * 41 + 19) = 'X';
				break;
			case 3:
				*(map + 11 * 41 + 20) = 'X';
				break;
			}
			if(cykl == 25) cykl = 0;
		}

		draw(map, mapC, 1, 1);
		delete map;
		delete mapC;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		time = (clock() / (CLOCKS_PER_SEC)) - timePopr;
		//gotoxy(0, 45);
		cout << "\n\nWynik:" << punkty << endl;
		time >= 60 ? cout << "Czas: " << time / 60 << "min " <<time % 60 << "s" << endl : cout << "Czas: " << time << "s" << endl;
		cout << "ESC aby wyjsc\n";
		Sleep(20);
		cykl++;
	}
	return;
}
