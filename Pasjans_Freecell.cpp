// TODO: koniec porgramu w złym momencie, nie kończy się, zrobić funkcję nie void

#include <iostream>
#include <windows.h>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

struct karta
{
	char kolor;
	char figura; //	A < 2 < 3 < 4 < 5 < 6 < 7 < 8 < 9 < T < J < Q < K;
	int ranga;	 //  ranga karty od 1 do 13
};

class pasjans
{
public:
	void start()
	{
		char czy_chcesz_przetasowac;
		do
		{
			for (int i = 0; i < 8; i++)
			{
				kolumna[i].clear();
			}
			przetasuj();
			wyswietlanie();
			cout << "\nJesli chcesz przetasowac karty i rozmiescic je na nowo nacisnij 1, jesli chcesz zaczac gre z widocznym ukladem nacisnij inny znak";
			cin >> czy_chcesz_przetasowac;
		} while (czy_chcesz_przetasowac == '1');

		gra();
	}

private:
	int _cards[52];
	vector<karta> kolumna[8]; // tablica wektorow pola gry
	stack<karta> docelowa[4]; // tablica stosow pola docelowego
	stack<karta> pomoc[4];	  // tablica stosow pola pomocniczego

	void blad()
	{
		cout << "Ruch jest niezgodny z zasadami gry.";
		getch();
	}

	void pasek()
	{
		cout << "-------------------------------" << endl;
	}
	void przetasuj()
	{
		char suit[] = "\x03\x04\x05\x06";
		char symb[] = "A23456789TJQK";
		{
			for (int c = 0; c < 52; c++)
				_cards[c] = c;
		}
		srand(time(NULL));
		int cc = 52, nc, lc;
		while (cc)
		{
			nc = rand() % cc;
			lc = _cards[--cc];
			_cards[cc] = _cards[nc];
			_cards[nc] = lc;
		}
		for (int c = 0; c <= 51; c++) // stworzenie kart i umieszczenie ich w kolumnach pola startowego
		{
			karta k;
			k.kolor = suit[_cards[c] % 4];
			k.figura = symb[_cards[c] % 13];
			k.ranga = _cards[c] % 13;

			kolumna[c % 8].push_back(k);
		}
	}
	void wyswietlanie()
	{
		system("cls"); // odświerzanie konsoli

		pasek();
		cout << " P1 P2 P3 P4        D1 D2 D3 D4" << endl;
		pasek();

		// wyswietlanie pola pomocy
		for (int c = 0; c < 4; c++)
		{
			if (pomoc[c].empty())
				cout << "   ";
			else
			{
				cout << " " << pomoc[c].top().figura << pomoc[c].top().kolor;
			}
		}
		cout << "       ";
		// wyswietlanie pola docelowego
		for (int c = 0; c < 4; c++)
		{
			if (docelowa[c].empty())
				cout << "   ";
			else
			{
				cout << " " << docelowa[c].top().figura << docelowa[c].top().kolor;
			}
		}
		cout << endl;
		pasek();
		cout << " G1  G2  G3  G4  G5  G6  G7  G8 " << endl;
		pasek();

		int max_size_kolumn = 0;

		// szukanie kolumny o najwiekszym rozmiarze
		for (int i = 0; i < 8; i++)
		{
			if (kolumna[i].size() > max_size_kolumn)
				max_size_kolumn = kolumna[i].size();
		}
		// wyswietlanie pola gry
		for (int j = 0; j < max_size_kolumn; j++)
		{
			for (int c = 0; c < 8; c++)
			{
				if (j >= kolumna[c].size())
				{
					cout << "    ";
				}
				else
				{
					cout << " " << kolumna[c][j].figura << kolumna[c][j].kolor << " ";
				}
			}
			cout << endl;
		}
	}
	void gra()
	{
		char pole1, pole2;
		int numer1, numer2, rozmiar_kolumny_numer1, poczatek_drabinki;

		while (docelowa[0].size() != 14 && docelowa[1].size() != 14 && docelowa[2].size() != 14 && docelowa[3].size() != 14) // koniec gry gdy pola docelowe zostaną wypełnione
		{
			wyswietlanie();

			cout << endl
				 << "Pole, z ktorego chcesz przeniesc karte (np. G3):";
			cin >> pole1 >> numer1;
			cout << "Pole, na ktore chcesz przeniesc karte (np. P1):";
			cin >> pole2 >> numer2;

			numer1--;
			numer2--;
			rozmiar_kolumny_numer1 = kolumna[numer1].size();

			// SPRAWDZENIE POPRAWNOSCI DANYCH.
			if (((pole1 == 'G' && numer1 <= 8) || (pole1 == 'P' && numer1 <= 4)) && ((pole2 == 'G' && numer2 <= 8) || (pole2 == 'P' && numer2 <= 4) || (pole2 == 'D' && numer2 <= 4))) // || !(cin.fail())
			{
				if (pole1 == 'G' && !kolumna[numer1].empty())
				{
					if (pole2 == 'G') // PRZENIESIENIE KARTY Z POLA GRY NA INNE POLE GRY.
					{
						for (poczatek_drabinki = rozmiar_kolumny_numer1 - 1; poczatek_drabinki > 0;)
						{
							if (!((((kolumna[numer1].at(poczatek_drabinki).kolor == '\x03' || kolumna[numer1].at(poczatek_drabinki).kolor == '\x04') &&
									(kolumna[numer1].at(poczatek_drabinki - 1).kolor == '\x05' || kolumna[numer1].at(poczatek_drabinki - 1).kolor == '\x06')) ||
								   ((kolumna[numer1].at(poczatek_drabinki).kolor == '\x05' || kolumna[numer1].at(poczatek_drabinki).kolor == '\x06') &&
									(kolumna[numer1].at(poczatek_drabinki - 1).kolor == '\x03' || kolumna[numer1].at(poczatek_drabinki - 1).kolor == '\x04'))) &&
								  kolumna[numer1].at(poczatek_drabinki).ranga + 1 == kolumna[numer1].at(poczatek_drabinki - 1).ranga))
							{
								break;
							}

							poczatek_drabinki--;
						}
						if (kolumna[numer2].empty())
						{
							for (int i = 0; i < rozmiar_kolumny_numer1 - poczatek_drabinki; i++)
							{
								kolumna[numer2].push_back(kolumna[numer1].at(poczatek_drabinki));
								kolumna[numer1].erase(kolumna[numer1].begin() + poczatek_drabinki);
							}
						}
						else if ((((kolumna[numer1].at(poczatek_drabinki).kolor == '\x03' || kolumna[numer1].at(poczatek_drabinki).kolor == '\x04') &&
								   (kolumna[numer2].back().kolor == '\x05' || kolumna[numer2].back().kolor == '\x06')) ||
								  ((kolumna[numer1].at(poczatek_drabinki).kolor == '\x05' || kolumna[numer1].at(poczatek_drabinki).kolor == '\x06') &&
								   (kolumna[numer2].back().kolor == '\x03' || kolumna[numer2].back().kolor == '\x04'))) &&
								 kolumna[numer1].at(poczatek_drabinki).ranga + 1 == kolumna[numer2].back().ranga)
						{
							for (int i = 0; i < rozmiar_kolumny_numer1 - poczatek_drabinki; i++)
							{
								kolumna[numer2].push_back(kolumna[numer1].at(poczatek_drabinki));
								kolumna[numer1].erase(kolumna[numer1].begin() + poczatek_drabinki);
							}
						}
						else
						{
							blad();
							continue;
						}
					}
					if (pole2 == 'P') // PRZENIESIENIE KARTY Z POLA GRY NA POLE POMOCY.
					{
						if (pomoc[numer2].empty())
						{
							pomoc[numer2].push(kolumna[numer1].back());
							kolumna[numer1].pop_back();
							continue;
						}
						else
						{
							blad();
							continue;
						}
					}
					if (pole2 == 'D') // PRZENIESIENIE KARTY Z POLA GRY DO GRUPY DOCELOWEJ.
					{

						if (docelowa[numer2].empty() && kolumna[numer1].back().figura == 'A')
						{
							docelowa[numer2].push(kolumna[numer1].back());
							kolumna[numer1].pop_back();
							continue;
						}
						else if (kolumna[numer1].back().kolor == docelowa[numer2].top().kolor &&
								 kolumna[numer1].back().ranga == docelowa[numer2].top().ranga + 1)
						{
							docelowa[numer2].push(kolumna[numer1].back());
							kolumna[numer1].pop_back();
							continue;
						}
						else
						{
							blad();
							continue;
						}
					}
				}

				if (pole1 == 'P' && !pomoc[numer1].empty())
				{
					if (pole2 == 'G') // PRZENIESIENIE KARTY Z POLA POMOCY NA INNE POLE GRY.
					{
						if (kolumna[numer2].empty()) // tu problem!!!
						{
							kolumna[numer2].push_back(pomoc[numer1].top());
							pomoc[numer1].pop();
							continue;
						}
						else if ((((pomoc[numer1].top().kolor == '\x03' || pomoc[numer1].top().kolor == '\x04') &&
								   (kolumna[numer2].back().kolor == '\x05' || kolumna[numer2].back().kolor == '\x06')) ||
								  ((pomoc[numer1].top().kolor == '\x05' || pomoc[numer1].top().kolor == '\x06') &&
								   (kolumna[numer2].back().kolor == '\x03' || kolumna[numer2].back().kolor == '\x04'))) &&
								 pomoc[numer1].top().ranga + 1 == kolumna[numer2].back().ranga)
						{
							kolumna[numer2].push_back(pomoc[numer1].top());
							pomoc[numer1].pop();
							continue;
						}
						else
						{
							blad();
							continue;
						}
					}
					if (pole2 == 'P') // PRZENIESIENIE KARTY Z POLA POMOCY NA POLE POMOCY.
					{
						if (pomoc[numer2].empty())
						{
							pomoc[numer2].push(pomoc[numer1].top());
							pomoc[numer1].pop();
							continue;
						}
						else
						{
							blad();
							continue;
						}
					}
					if (pole2 == 'D') // PRZENIESIENIE KARTY Z POLA POMOCY DO GRUPY DOCELOWEJ.
					{
						if (docelowa[numer2].empty() && pomoc[numer1].top().figura == 'A')
						{
							docelowa[numer2].push(pomoc[numer1].top());
							pomoc[numer1].pop();
							continue;
						}
						else if (pomoc[numer1].top().kolor == docelowa[numer2].top().kolor &&
								 pomoc[numer1].top().ranga == docelowa[numer2].top().ranga + 1)
						{
							docelowa[numer2].push(pomoc[numer1].top());
							pomoc[numer1].pop();
							continue;
						}
						else
						{
							blad();
							continue;
						}
					}
				}
			}
			else
			{
				blad();
				continue;
			}
		}
		wyswietlanie();
		cout << "\n*******WYGRALES*******!\n"
			 << endl;
		system("PAUSE");
	}
};

int main()
{
	pasjans freecell;

	freecell.start();

	return 0;
}