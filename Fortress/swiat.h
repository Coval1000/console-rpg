#pragma once
#include "libs.h"

class Field
{
private:
	int coordX;
	int coordY;

public:
	Obj* tile;
	Field* up;
	Field* down;
	Field* left;
	Field* right;
public:
	int x()
	{
		return coordX;
	}

	int y()
	{
		return coordY;
	}


	Field(int coordX, int coordY, Field* left = NULL, Field* right = NULL, Field* up = NULL, Field* down = NULL)
	{
		this->coordX = coordX;
		this->coordY = coordY;
		this->down = down;
		this->up = up;
		this->left = left;
		this->right = right;

		switch (rand() % 10)
		{
		case 0: //drzewo
			this->tile = new Obj(2);
			break;
		case 1: //góra
			this->tile = new Obj(4);
			break;
		case 2: //woda
			this->tile = new Obj(6);
			break;
		case 3: //piach
			this->tile = new Obj(7);
			break;
		default: //trawa
			this->tile = new Obj(1);
		}
	}
};

class Item
{
public:
	int id;
	int amount;
	char sprite;
	WORD color;



	Item(int id)
	{
		switch (id)
		{
		case 0:
			this->id = 0;
			sprite = ' ';
			color = C_BLACK;
			break;
		case 1:
			this->id = 1;
			sprite = '/';
			color = C_DRED;
			break;
		}
	}
};

class Player
{	
	int possX;
	int possY;
public:
	Field* poss;

	char inventory[40][2];

	int eq(int slot)
	{

			int x = absZnak(slot) % 10;
			int y = absZnak(slot) / 4;
			int sizeX = 0;
			int sizeY = 0;
			int element = 0;
			int elementA = -10;
			char plansza[199];
			char tablica[199];
			WORD kolory[199];

			for (sizeX = 0; sizeX<21; sizeX++) plansza[sizeY * 2 * 22 + sizeX] = ' ';

			for (sizeY = 0; sizeY<4; sizeY++)
			{
				for (sizeX = 0; sizeX < 10; sizeX++, elementA++)
				{
					if(!sizeX) plansza[sizeY * 2 * 22 + sizeX * 2] = ' ';
					if (elementA >= 0)
					{
						plansza[sizeY * 2  * 22 + sizeX * 2 + 1] = inventory[elementA][1] > 10 ? '0' + inventory[elementA][1] / 10 : ' ';
						plansza[sizeY * 2  * 22 + sizeX * 2 + 2] = inventory[y * 10 + x][1] > 0 ? '0' + inventory[y * 10 + x][1] % 10 : '0';
					}
					else
					{
						plansza[sizeY * 2 * 22 + sizeX * 2 + 1] = ' '; 
						plansza[sizeY * 2 * 22 + sizeX * 2 + 2] = ' ';
					}
					
				}
				for (sizeX = 0; sizeX<21; sizeX++) kolory[sizeY * 2 * 22 + sizeX] = C_GREY;

				plansza[sizeY * 2 * 22 + sizeX] = '\n';
				kolory[sizeY * 2 * 22 + sizeX] = C_GREY;

				for (sizeX = 0; sizeX < 10; sizeX++, element++)
				{
					plansza[(sizeY * 2 + 1) * 22 + sizeX * 2] = ' ';
					kolory[(sizeY * 2 + 1) * 22 + sizeX * 2] = C_GREY;

					Item item(inventory[element][0]);
					plansza[(sizeY * 2 + 1) * 22 + sizeX * 2 + 1] = item.sprite;
					kolory[(sizeY * 2 + 1) * 22 + sizeX * 2 + 1] = item.color;
				}
				plansza[(sizeY * 2 + 1) * 22 + sizeX * 2] = ' ';
				kolory[(sizeY * 2 + 1) * 22 + sizeX * 2] = C_GREY;

				plansza[(sizeY * 2 + 1) * 22 + sizeX * 2 + 1] = '\n';
				kolory[(sizeY * 2 + 1) * 22 + sizeX * 2 + 1] = C_GREY;
			}

			for (sizeX = 0; sizeX < 10; sizeX++, elementA++)
			{
				if (!sizeX) plansza[sizeY * 2 * 22 + sizeX * 2] = ' ';
				if (elementA >= 0)
				{
					plansza[sizeY * 2 * 22 + sizeX * 2 + 1] = inventory[elementA][1] > 10 ? '0' + inventory[elementA][1] / 10 : ' ';
					plansza[sizeY * 2 * 22 + sizeX * 2 + 2] = inventory[y * 10 + x][1] > 0 ? '0' + inventory[y * 10 + x][1] % 10 : ' ';
				}

			}
			for (sizeX = 0; sizeX<21; sizeX++) kolory[sizeY * 2 * 22 + sizeX] = C_GREY;

			plansza[sizeY * 2 * 22 + sizeX] = '\n';
			kolory[sizeY * 2 * 22 + sizeX] = C_GREY;

			plansza[sizeY * 2 * 22 + sizeX + 1] = '\0';
			kolory[sizeY * 2 * 22 + sizeX + 1] = C_GREY;
			system("cls");

			while (1)
			{

				strcpy(tablica, plansza);
				tablica[(y * 2) * 22 + x * 2] = 218;
				tablica[(y * 2) * 22 + x * 2 + 1] = 196;
				tablica[(y * 2) * 22 + x * 2 + 2] = 191;
				tablica[(y * 2 + 1) * 22 + x * 2] = 179;
				//tablica[(y * 2 + 1) * 34 + x * 2 + 1] = '@';
				tablica[(y * 2 + 1) * 22 + x * 2 + 2] = 179;
				tablica[(y * 2 + 2) * 22 + x * 2] = 192;
				tablica[(y * 2 + 2) * 22 + x * 2 + 1] = inventory[y * 10 + x][1] > 10 ? '0' + inventory[y * 10 + x][1]/10 : 196;
				tablica[(y * 2 + 2) * 22 + x * 2 + 2] = inventory[y * 10 + x][1] > 0 ? '0' + inventory[y * 10 + x][1] % 10 : 217;

				draw(tablica, kolory);
				char buf = _getch();
				switch (buf)
				{
				case 224:
					buf = _getch();
				default:
					if (buf == 77 && x < 9)
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
					return slot;
				}
			}

		return 0;
	}

	Player()
	{
		for (int i = 0;i<40; i++)
		{
			inventory[i][0] = 0;
			inventory[i][1] = 0;
		}
	}

	~Player()
	{
	}
};

class World 
{
private:
	int sizeX;
	int sizeY;
	PtrTab* zeroPoint;
public:
	int direction;

	Field* active;
	Player* player;



	void move(char direction)
	{
		switch (direction)
		{
		case 'E':
			if (!player->poss->right)
			{
				this->add(player->poss->x()+1, player->poss->y());
			}
			player->poss = (Field*)player->poss->right;
			break;
		case 'W':
			if (!player->poss->left)
			{
				this->add(player->poss->x() - 1, player->poss->y());
			}
			player->poss = (Field*)player->poss->left;
			break;
		case 'N':
			if (!player->poss->up)
			{
				this->add(player->poss->x(), player->poss->y() + 1);
			}
			player->poss = (Field*)player->poss->up;
			break;
		case 'S':
			if (!player->poss->down)
			{
				this->add(player->poss->x(), player->poss->y() - 1);
			}
			player->poss = (Field*)player->poss->down;
			break;
		default:
			break;
		}

		if (!player->poss->right)
		{
			this->add(player->poss->x() + 1, player->poss->y());
			
		}
		if (!player->poss->right->right)
		{
			this->add(player->poss->x() + 2, player->poss->y());
		}
		if (!player->poss->right->up)
		{
			this->add(player->poss->x() + 1, player->poss->y() + 1);
		}
		if (!player->poss->left)
		{
			this->add(player->poss->x() - 1, player->poss->y());
		}
		if (!player->poss->left->left)
		{
			this->add(player->poss->x() - 2, player->poss->y());
		}
		if (!player->poss->left->down)
		{
			this->add(player->poss->x() - 1, player->poss->y() - 1);
		}
		if (!player->poss->up)
		{
			this->add(player->poss->x(), player->poss->y() + 1);
		}
		if (!player->poss->up->up)
		{
			this->add(player->poss->x(), player->poss->y() + 2);
		}
		if (!player->poss->up->left)
		{
			this->add(player->poss->x() - 1, player->poss->y() + 1);
		}
		if (!player->poss->down)
		{
			this->add(player->poss->x(), player->poss->y() - 1);
		}
		if (!player->poss->down->down)
		{
			this->add(player->poss->x(), player->poss->y() - 2);
		}
		if (!player->poss->down->right)
		{
			this->add(player->poss->x() + 1, player->poss->y() - 1);
		}
	}

	void add(int x, int y)
	{
		PtrTab* tabX;
		PtrTab* tabY;
		PtrTab* tabYxN;
		PtrTab* tabYxS;		
		
		tabY = zeroPoint->goFoward(y);
		tabYxN = ((PtrTab*)tabY->next->item)->goFoward(x);
		tabYxS = ((PtrTab*)tabY->prev->item)->goFoward(x);
		tabX = ((PtrTab*)tabY->item)->goFoward(x);
		
		tabX->item = new Field(x, y, (Field*)tabX->prev->item, (Field*)tabX->next->item, (Field*)tabYxN->item, (Field*)tabYxS->item);
		
		if (((Field*)tabX->item)->down) ((Field*)tabX->item)->down->up = (Field*)tabX->item;
		if (((Field*)tabX->item)->up) ((Field*)tabX->item)->up->down = (Field*)tabX->item;
		if (((Field*)tabX->item)->left) ((Field*)tabX->item)->left->right = (Field*)tabX->item;
		if (((Field*)tabX->item)->right) ((Field*)tabX->item)->right->left = (Field*)tabX->item;

	}

	char* area()
	{
		//40x20
		char* area = new char[820];
		int y;
		int x;
		PtrTab* fieldY = zeroPoint;
		PtrTab* fieldX;
		fieldY = fieldY->goFoward(player->poss->y() + 10);
		for (y = 0; y < 20; y++, fieldY = fieldY->prev) //trzeba daæ zabezpieczenie przed pustym wskaŸnikiem
		{
			fieldX = (PtrTab*)fieldY->item;
			fieldX = fieldX->goFoward(player->poss->x() - 20);
			for (x = 0; x < 40; x++, fieldX = fieldX->next)
			{
				if (fieldX->item)
				{
					*(area + x + y * 41) = ((Field*)fieldX->item)->tile->znak;
				}
				else *(area + x + y * 41) = ' ';
			}
			*(area + x + y * 41) = '\n';
		}
		*(area + x + (y-1) * 41) = 0;
		return area;
	}

	WORD* areaColor()
	{
		//40x20
		WORD* area = new WORD[820];
		int y;
		int x;
		PtrTab* fieldY = zeroPoint;
		PtrTab* fieldX;
		fieldY = fieldY->goFoward(player->poss->y() + 10);
		for (y = 0; y < 20; y++, fieldY = fieldY->prev) //trzeba daæ zabezpieczenie przed pustym wskaŸnikiem
		{
			fieldX = (PtrTab*)fieldY->item;
			fieldX = fieldX->goFoward(player->poss->x() - 20);
			for (x = 0; x < 40; x++, fieldX = fieldX->next)
			{
				if (fieldX->item)
				{
					*(area + x + y * 41) = ((Field*)fieldX->item)->tile->kolor;
				}
				else *(area + x + y * 41) = 0x00;
			}
			*(area + x + y * 41) = 0x00;
		}
		*(area + x + (y - 1) * 41) = 0;
		return area;
	}

	World()
	{	
		PtrTab* activeY;
		PtrTab* activeX;
		int posX = 512;
		int posY = 512;
		zeroPoint = NULL;
		for (int i = 0; i < 1024; i++)
		{
			if (!zeroPoint)
			{
				zeroPoint = new PtrTab(NULL, NULL, NULL);
				activeY = zeroPoint;
			}
			else activeY = activeY->addAhead();

			activeY->item = new PtrTab(NULL, NULL, NULL);
			activeX = (PtrTab*)activeY->item;
			for (int j = 0; j < 1024; j++)
			{
				activeX = activeX->addAhead();
			}

		}

		activeY = zeroPoint;
		activeY = activeY->goFoward(512);
		activeX = (PtrTab*)activeY->item;
		activeX = activeX->goFoward(512);
		activeX->item = new Field(512, 512);

		this->add(posX + 1, posY);
		this->add(posX - 1, posY);
		this->add(posX, posY + 1);
		this->add(posX, posY - 1);
		player = new Player;
		player->poss = (Field*)activeX->item;
	}

	~World()
	{
		PtrTab* activeY = zeroPoint;

		((PtrTab*)(activeY->item))->destroyAll();
		do
		{
			activeY = activeY->next;
			((PtrTab*)(activeY->item))->destroyAll();
			
		} while (activeY->next);
		activeY->destroyAll();
	}
};
