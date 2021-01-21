#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

int szerokosc;
int dlugosc;
int szybkosc;
int gora;
int dol;
int lewo;
int prawo;
char pole[25][25];
int wspolrzednaXweza;
int wspolrzednaYweza;
int wspolrzednaXjedzenia;
int wspolrzednaYjedzenia;
int dlugosc_weza = 3;
int historiawspolrzednejX[10000];
int historiawspolrzednejY[10000];
int ile_ruchow = 0;
int klawisz;
char kierunek = 'p'; //p-prawo, l-lewo, g-gora, d-dol
char waz = 219;
char jedz = 176;
char rog_pd = 188;
char rog_pg = 187;
char rog_lg = 201;
char rog_ld = 200;
char l_poz = 205;
char l_pion = 186;
//p-pole puste, w - na polu jest waz, j- na polu jest jedzenie

void idzdoxy(int x, int y)
{
	HANDLE hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}

int zle()
{

	cout << "Podales zle wymiary! Mialo byc od 5 do 25!" << endl;
	cout << "Podaj jeszcze raz szerokosc planszy (od 5 do 25): " << endl;
	cin >> szerokosc;
	if (szerokosc < 5 || szerokosc>25) szerokosc = 15;
	cout << "Skoro nie umiesz wybrac szerokosci to Twoja szerokosc planszy wynosi 15" << endl;

	return szerokosc;
}

int zle_1()
{

	cout << "Podales zle wymiary! Mialo byc od 5 do 25!" << endl;
	cout << "Podaj jeszcze raz dlugosc planszy (od 5 do 25): " << endl;
	cin >> dlugosc;
	if (dlugosc < 5 || dlugosc>25) dlugosc = 15;
	cout << "Skoro nie umiesz wybrac dlugosci to Twoja dlugosc planszy wynosi 15" << endl;

	return dlugosc;
}

int main()
{
	cout << "Wybraliscie gre snake!" << endl << "Teraz wybierzcie wymiary planszy, szybkosc weza oraz klawisze, ktorymi bedziecie grali:" << endl;
	cout << "Podaj szerokosc planszy (od 5 do 25):" << endl;
	cin >> szerokosc;
	if (szerokosc < 5 || szerokosc>25) zle();

	cout << "Podaj dlugosc planszy (od 5 do 25):" << endl;
	cin >> dlugosc;
	if (dlugosc < 5 || dlugosc>25) zle_1();

	cout << "Wymiary planszy to: " << szerokosc << "x" << dlugosc << endl;

	cout << "Podaj szybkosc (od 1 do 10):" << endl;
	cin >> szybkosc;
	srand(time(NULL));
	if (szybkosc < 1 || szybkosc>10)
	{
		szybkosc = rand() % 10 + 1;
		cout << "Liczba, ktora wpisales nie znajduje sie w przedziale szybkosci, zatem system wylosowal Twoja szybkosc: " << szybkosc << endl;
	}

	cout << "Nacisnij klawisze, ktorymi chcesz zagrac" << endl;
	cout << "GORA" << endl;
	gora = _getch();
	if (gora == 224) gora = gora + _getch();
	if (gora == 0) gora = gora - _getch();

	cout << "DOL" << endl;
	dol = _getch();
	if (dol == 224) dol = dol + _getch();
	if (dol == 0) dol = dol - _getch();

	cout << "LEWO" << endl;
	lewo = _getch();
	if (lewo == 224) lewo = lewo + _getch();
	if (lewo == 0) lewo = lewo - _getch();

	cout << "PRAWO" << endl;
	prawo = _getch();
	if (prawo == 224) prawo = prawo + _getch();
	if (prawo == 0) prawo = prawo - _getch();


	//nadajemy wartosci 'p' tablicy pole
	for (int i = 0; i < dlugosc; i++)
	{
		for (int j = 0; j < szerokosc; j++)
		{
			pole[j][i] = 'p';
		}
	}

	wspolrzednaXweza = rand() % szerokosc;
	wspolrzednaYweza = rand() % dlugosc;

	pole[wspolrzednaXweza][wspolrzednaYweza] = 'w';

	//losowanie miejsca jedzenia
	do
	{
		wspolrzednaXjedzenia = rand() % szerokosc;
		wspolrzednaYjedzenia = rand() % dlugosc;
	} while (pole[wspolrzednaXjedzenia][wspolrzednaYjedzenia] != 'p'); //wykonuj dopoki pole wylosowane nie jest puste 

	pole[wspolrzednaXjedzenia][wspolrzednaYjedzenia] = 'j';

	system("CLS");

	//rysowanie planszy
	idzdoxy(0, 0); //wroc na poczatek

	//gorna ramka
	cout << rog_lg;
	for (int i = 0; i < szerokosc; i++)
	{
		cout << l_poz << l_poz;
	}
	cout << rog_pg;

	//lewa i prawa ramka
	for (int i = 0; i < dlugosc; i++)
	{
		cout << endl << l_pion;
		for (int j = 0; j < szerokosc; j++)
		{
			if (pole[j][i] == 'p') cout << "  ";
			if (pole[j][i] == 'w') cout << waz << waz;
			if (pole[j][i] == 'j') cout << jedz << jedz;
		}
		cout << l_pion;
	}
	cout << endl;

	//dolna ramka
	cout << rog_ld;
	for (int i = 0; i < szerokosc; i++)
	{
		cout << l_poz << l_poz;
	}
	cout << rog_pd;

	//rozpoczecie gry
	for (;;)
	{
		ile_ruchow++;
		historiawspolrzednejX[ile_ruchow] = wspolrzednaXweza;
		historiawspolrzednejY[ile_ruchow] = wspolrzednaYweza;

		Sleep(1000 / szybkosc); // czekanie przed wykonaniem kolejnych krokow

		if (_kbhit()) //Jesli zostanie nacisniety jakis klawisz to: ...
		{
			klawisz = _getch();
			if (klawisz == 224)klawisz += _getch();
			if (klawisz == 0)klawisz -= _getch();

			if (klawisz == gora && (kierunek == 'l' || kierunek == 'p')) kierunek = 'g';
			if (klawisz == dol && (kierunek == 'l' || kierunek == 'p')) kierunek = 'd';
			if (klawisz == lewo && (kierunek == 'g' || kierunek == 'd')) kierunek = 'l';
			if (klawisz == prawo && (kierunek == 'g' || kierunek == 'd')) kierunek = 'p';
		}

		if (kierunek == 'g') wspolrzednaYweza--;
		if (kierunek == 'd') wspolrzednaYweza++;
		if (kierunek == 'l') wspolrzednaXweza--;
		if (kierunek == 'p') wspolrzednaXweza++;

		//waz przechodzi przez sciany
		if (wspolrzednaXweza == szerokosc) wspolrzednaXweza = 0;
		if (wspolrzednaXweza == -1) wspolrzednaXweza = szerokosc - 1;
		if (wspolrzednaYweza == dlugosc) wspolrzednaYweza = 0;
		if (wspolrzednaYweza == -1) wspolrzednaYweza = dlugosc - 1;

		//Po wpadnieciu w siebie
		if (pole[wspolrzednaXweza][wspolrzednaYweza] == 'w')
		{
			idzdoxy(0, dlugosc + 2);
			cout << endl << "\aKONIEC GRY!" << "dlugosc= " << dlugosc_weza + 1;
			break;
		}

		//Po zjedzeniu 
		if (pole[wspolrzednaXweza][wspolrzednaYweza] == 'j')
		{
			dlugosc_weza++;
			do
			{
				wspolrzednaXjedzenia = rand() % szerokosc;
				wspolrzednaYjedzenia = rand() % dlugosc;
			} while (pole[wspolrzednaXjedzenia][wspolrzednaYjedzenia] != 'p'); //wykonuj dopoki pole wylosowane nie jest puste 

			pole[wspolrzednaXjedzenia][wspolrzednaYjedzenia] = 'j';
			idzdoxy(wspolrzednaXjedzenia * 2 + 1, wspolrzednaYjedzenia + 1);
			cout << jedz << jedz;

		}
		else //kasowanie ogona
		{
			pole[historiawspolrzednejX[ile_ruchow - dlugosc_weza]][historiawspolrzednejY[ile_ruchow - dlugosc_weza]] = 'p';
			idzdoxy(historiawspolrzednejX[ile_ruchow - dlugosc_weza] * 2 + 1, historiawspolrzednejY[ile_ruchow - dlugosc_weza] + 1);
			cout << "  ";
		}
		pole[wspolrzednaXweza][wspolrzednaYweza] = 'w';
		idzdoxy(wspolrzednaXweza * 2 + 1, wspolrzednaYweza + 1);
		cout << waz << waz;

	} //koniec petli for

	_getch();
	return 0;
}