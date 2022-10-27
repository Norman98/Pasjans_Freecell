#include <iostream>                 
#include <windows.h>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

struct karta {
	char kolor;                  	//	p->pik; t->trefl; k->karo; c->kier;
	char figura;                  	//	A < 2 < 3 < 4 < 5 < 6 < 7 < 8 < 9 < T < J < Q < K;
	int ranga;						//  ranga karty od 1 do 13
};

class pasjans
{
public:

	void polestartowe()
	{
		fillDeck();
		tasowanie();
		gra();
	}

private:
	int _cards[52];

	void blad()
	{
		cout << "Ruch jest niezgodny z zasadami gry."; getch();
	}

	void pasek()
	{
		cout << "-------------------------------" << endl;
	}
	void fillDeck()
	{
		for (int c = 0; c < 52; c++)
			_cards[c] = c;
	}

	void tasowanie()
	{
		srand(time(NULL));
		int cc = 52, nc, lc;
		while (cc)
		{
			nc = rand() % cc;
			lc = _cards[--cc];
			_cards[cc] = _cards[nc];
			_cards[nc] = lc;
		}
	}

	void gra()
	{
		//char* suit = "PTKC";
		char* suit = "\x03\x04\x05\x06";
		char* symb = "A23456789TJQK";

		vector<karta> kolumna[8];
		stack<karta> docelowa[4];                   //tablica stosów pola docelowego
		stack<karta> pomoc[4];                      // tablica stosów pola pomocniczego

		int numer_kolumny = 0;
		for (int c = 51; c >= 0; c--)
		{
			karta k;
			k.kolor = suit[_cards[c] % 4];
			k.figura = symb[_cards[c] % 13];
			k.ranga = _cards[c] % 13;

			kolumna[numer_kolumny % 8].push_back(k);

			numer_kolumny++;
		}

		char pole1, pole2;
		int numer1, numer2;

		do {
			system("cls");	                  // odświerzanie konsoli

			pasek();
			cout << " P1 P2 P3 P4        D1 D2 D3 D4" << endl;
			pasek();

			for (int c = 0; c < 4; c++)
			{
				if (pomoc[c].empty())	cout << "   ";
				else
				{
					cout << " " << pomoc[c].top().figura << pomoc[c].top().kolor;
				}
			}
			cout << "       ";
			for (int c = 0; c < 4; c++)
			{
				if (docelowa[c].empty())	cout << "   ";
				else
				{
					cout << " " << docelowa[c].top().figura << docelowa[c].top().kolor;
				}
			}
			cout << endl << endl;
			pasek();
			cout << " G1  G2  G3  G4  G5  G6  G7  G8 " << endl;
			pasek();

			int j = 0, d = 0;
			for (int c = 100; c >= 0; c--)
			{
				if (j >= kolumna[d].size())
				{
					cout << "    ";
				}
				else
				{
					cout << " " << kolumna[d][j].figura << kolumna[d][j].kolor << " ";
				}
				if (++d == 8)
				{
					cout << endl;
					d = 0;
					j++;
				}
			}

			cout << endl << "Pole, z ktorego chcesz przeniesc karte (np. G3):";
			cin >> pole1 >> numer1;
			cout << "Pole, na ktore chcesz przeniesc karte (np. P1):";
			cin >> pole2 >> numer2;

			numer1--;
			numer2--;

			//SPRAWDZENIE POPRAWNOSCI DANYCH.
			if (((pole1 == 'G' && numer1 <= 8) || (pole1 == 'P' && numer1 <= 4)) && ((pole2 == 'G' && numer2 <= 8) || (pole2 == 'P' && numer2 <= 4) || (pole2 == 'D' && numer2 <= 4)))
			{
				if (pole1 == 'G')
				{
					if (pole2 == 'G')				//PRZENIESIENIE KARTY Z POLA GRY NA INNE POLE GRY.
					{
						if (kolumna[numer2].empty())
						{
							kolumna[numer2].push_back(kolumna[numer1].back());
							kolumna[numer1].pop_back(); continue;
						}
						if (((kolumna[numer1].back().kolor == '\x03' || kolumna[numer1].back().kolor == '\x04') &&
							(kolumna[numer2].back().kolor == '\x05' || kolumna[numer2].back().kolor == '\x06')) ||
							((kolumna[numer1].back().kolor == '\x05' || kolumna[numer1].back().kolor == '\x06') &&
								(kolumna[numer2].back().kolor == '\x03' || kolumna[numer2].back().kolor == '\x04')) &&
							kolumna[numer1].back().ranga + 1 == kolumna[numer2].back().ranga)
						{
							kolumna[numer2].push_back(kolumna[numer1].back());
							kolumna[numer1].pop_back(); continue;
						}
						else { blad(); continue; }
					}
					if (pole2 == 'P')				//PRZENIESIENIE KARTY Z POLA GRY NA POLE POMOCY.
					{
						if (pomoc[numer2].empty())
						{
							pomoc[numer2].push(kolumna[numer1].back());
							kolumna[numer1].pop_back(); continue;
						}
						else { blad(); continue; }
					}
					if (pole2 == 'D')		 //PRZENIESIENIE KARTY Z POLA GRY DO GRUPY DOCELOWEJ.
					{
						if (docelowa[numer2].empty() && kolumna[numer1].back().figura == 'A')
						{
							docelowa[numer2].push(kolumna[numer1].back());
							kolumna[numer1].pop_back(); continue;
						}

						if (kolumna[numer1].back().kolor == docelowa[numer2].top().kolor &&
							kolumna[numer1].back().ranga == docelowa[numer2].top().ranga + 1)
						{
							docelowa[numer2].push(kolumna[numer1].back());
							kolumna[numer1].pop_back(); continue;
						}
						else { blad(); continue; }
					}
				}

				if (pole1 == 'P')
				{
					if (pole2 == 'G')				//PRZENIESIENIE KARTY Z POLA POMOCY NA INNE POLE GRY.
					{
						if (kolumna[numer2].empty())
						{
							kolumna[numer2].push_back(pomoc[numer1].top());
							pomoc[numer1].pop(); continue;
						}
						if (((pomoc[numer1].top().kolor == '\x03' || pomoc[numer1].top().kolor == '\x04') &&
							(kolumna[numer2].back().kolor == '\x05' || kolumna[numer2].back().kolor == '\x06')) ||
							((pomoc[numer1].top().kolor == '\x05' || pomoc[numer1].top().kolor == '\x06') &&
								(kolumna[numer2].back().kolor == '\x03' || kolumna[numer2].back().kolor == '\x04')) &&
							pomoc[numer1].top().ranga + 1 == kolumna[numer2].back().ranga)
						{
							kolumna[numer2].push_back(pomoc[numer1].top());
							pomoc[numer1].pop(); continue;
						}
						else { blad(); continue; }
					}
					if (pole2 == 'P')				//PRZENIESIENIE KARTY Z POLA POMOCY NA POLE POMOCY.
					{
						if (pomoc[numer2].empty())
						{
							pomoc[numer2].push(pomoc[numer1].top());
							pomoc[numer1].pop(); continue;
						}
						else { blad(); continue; }
					}
					if (pole2 == 'D')		 //PRZENIESIENIE KARTY Z POLA POMOCY DO GRUPY DOCELOWEJ.
					{
						if (docelowa[numer2].empty() && pomoc[numer1].top().figura == 'A')
						{
							docelowa[numer2].push(pomoc[numer1].top());
							pomoc[numer1].pop(); continue;
						}

						if (pomoc[numer1].top().kolor == docelowa[numer2].top().kolor &&
							pomoc[numer1].top().ranga == docelowa[numer2].top().ranga + 1)
						{
							docelowa[numer2].push(pomoc[numer1].top());
							pomoc[numer1].pop(); continue;
						}
						else { blad(); continue; }
					}
				}
			}
			else { blad(); continue; }

		} while (docelowa[0].size() != 13 && docelowa[1].size() != 13 && docelowa[2].size() != 13 && docelowa[3].size() != 13);         // koniec gry gdy pola docelowe zostaną wypełnione

		cout << "WYGRALES!" << endl;

	}
};

int main()
{
	pasjans freecell;

	freecell.polestartowe();

	return 0;
}