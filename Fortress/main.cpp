#include "libs.h"


typedef struct Wynik Wynik;

int main()
{
	SetConsoleTitle(TEXT("Fortress"));

	SMALL_RECT windowSize = { 0, 0, 20, 20 };
	COORD bufferSize = { 21, 21 };
	COORD tmpsize = { 260, 300 };


	struct Sterowanie ster;
	sterDef(&ster);
	dRamka();
	dZnaki();
	dPlansza();

	struct Wynik *tWynikow;
	tWynikow = (Wynik*)malloc(sizeof(Wynik));
	tWynikow = wynikiWczyt(tWynikow);

	Menu menu("Gra");
	menu.add("Opcje");
	menu.add("Wynik");
	menu.add("Edytor");

	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), tmpsize);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &windowSize);
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

	menu.print();
	while (1)
	{
		switch (menu.choose())
		{
		case -1:
			exit(0);
			break;

		case 1:
			gra(&tWynikow, &ster);
			break;

		case 2:
			opcje(&ster);
			break;

		case 3:
			wyniki(tWynikow);
			break;

		case 4:
			edytor();
			break;

		case -2:
		case -3:
			system("cls");
			menu.print();
			break;

		default:
			break;

		}

	}
	return 0;
}

//polskie znaki
/*
206 - æ c
210 - ³ l
230 - œ s
242 - ó o
245 - ¹ a
251 - ê e
253 - Ÿ z'
276 - ¿ z
344 - ñ n
*/

//kopia zapasowa void gra()
/*
void gra()
{
struct Player player;
player.poss[0] = 1;
player.poss[1] = 1;

int xy[2] = { 12, 12 };
char *mapB;
char *map;
map = createMap(xy[0], xy[1], xy, &player);
mapB = malloc(strlen(map));
strcpy(mapB, map);
int time = 0;

while (1)
{
if (_kbhit())
{
char buf = _getch();
switch (buf)
{
case 224:
buf = _getch();
default:
if (buf == ster.wPrawo &&		map[player.poss[1] * (xy[1] + 1) + player.poss[0] + 1] != sciana)
{
player.poss[0]++;
}
else if (buf == ster.wLewo &&	map[player.poss[1] * (xy[1] + 1) + player.poss[0] - 1] != sciana)
{
player.poss[0]--;
}
else if (buf == ster.wGore &&	map[(player.poss[1] - 1) * (xy[1] + 1) + player.poss[0]] != sciana)
{
player.poss[1]--;
}
else if (buf == ster.wDol &&	map[(player.poss[1] + 1) * (xy[1] + 1) + player.poss[0]] != sciana)
{
player.poss[1]++;
}
break;

case 27:
return;

case 'z':
zapis(map, &player, xy);
break;

case 'w':
map = wczyt(map, &player, xy);
break;

case 'n':

map = createMap(10, 10, xy, &player);
break;
}
}
strcpy(map, mapB);
*(map + player.poss[1] * (xy[0] + 1) + player.poss[0]) = '@';
draw(map);
time = clock() / (CLOCKS_PER_SEC);
printf("Czas: %ds\nESC aby wyjsc", time, xy[0], xy[1]);
Sleep(50);
}
return;
}*/
