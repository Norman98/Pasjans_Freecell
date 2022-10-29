// TODO:

#include <iostream>
#include <windows.h>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

class Patience
{
public:
	void start()
	{
		char wanna_shuffle;
		do
		{
			for (int i = 0; i < 8; i++)
			{
				cascade[i].clear();
			}
			shuffle();
			display();
			cout << "\nIf you want a different starting position of cards, press \"1\", if you want to start the game, press any other sign:\n";
			wanna_shuffle = getch();
		} while (wanna_shuffle == '1');

		gra();
	}

private:
	struct card
	{
		int color; // variable to distinguish card color black or red
		char suit;
		char symbol; //	A < 2 < 3 < 4 < 5 < 6 < 7 < 8 < 9 < T < J < Q < K;
		int rank;	 // rank of the card from 1 to 13
	};
	int cards[52];
	vector<card> cascade[8];   // array of vectors cascades
	stack<card> foundation[4]; // array of stack foundations
	stack<card> help_cell[4];  // array of stack help cells

	void error()
	{
		cout << "Wrong move, try different one.";
		getch();
	}

	void line()
	{
		cout << "-------------------------------" << endl;
	}
	void shuffle()
	{
		card _card;
		int cards_in_deck = 52;
		const char suits[] = "\x03\x04\x05\x06";
		const char symbols[] = "A23456789TJQK";

		// FIXME: do shuffle in one loop instead
		for (int c = 0; c < 52; c++)
		{
			cards[c] = c;
		}

		srand(time(NULL));
		int cc = 52, nc, lc;
		while (cc) // randomizing position of cards in deck
		{
			nc = rand() % cc;
			lc = cards[--cc];
			cards[cc] = cards[nc];
			cards[nc] = lc;
		}

		for (int c = 0; c < 52; c++) // Placing cards in cascades
		{

			_card.suit = suits[cards[c] % 4];
			_card.symbol = symbols[cards[c] % 13];
			_card.rank = cards[c] % 13;

			cascade[c % 8].push_back(_card);
		}
	}
	void display()
	{
		system("cls"); // console refresh

		line();
		cout << " P1 P2 P3 P4        D1 D2 D3 D4" << endl;
		line();

		for (int column = 0; column < 4; column++) // displaying help_cells
		{
			if (help_cell[column].empty())
				cout << "   ";
			else
				cout << " " << help_cell[column].top().symbol << help_cell[column].top().suit;
		}
		cout << "       ";

		for (int column = 0; column < 4; column++) // // displaying foundations
		{
			if (foundation[column].empty())
				cout << "   ";
			else
				cout << " " << foundation[column].top().symbol << foundation[column].top().suit;
		}

		cout << endl;
		line();
		cout << " G1  G2  G3  G4  G5  G6  G7  G8 " << endl;
		line();

		int max_size_cascade = 0;

		for (int i = 0; i < 8; i++) // searching for cascade with the largest size
		{
			if (cascade[i].size() > max_size_cascade)
				max_size_cascade = cascade[i].size();
		}

		for (int column = 0; column < max_size_cascade; column++) // displaying cascades
		{
			for (int row = 0; row < 8; row++)
			{
				if (column >= cascade[row].size())
				{
					cout << "    ";
				}
				else
				{
					cout << " " << cascade[row][column].symbol << cascade[row][column].suit << " ";
				}
			}
			cout << endl;
		}
	}
	void gra()
	{
		char space1, space2;
		int number1, number2, cascade_length_number1, start_of_tableau;

		// Game ends when foundations have filled up FIXME:
		while (foundation[0].size() != 14 && foundation[1].size() != 14 && foundation[2].size() != 14 && foundation[3].size() != 14)
		{
			display();

			cout << endl
				 << "From where do you want to take a card? (e.g. \"G3\"): ";
			cin >> space1 >> number1;
			cout << "Where do you want to put a card? (e.g. \"P1\"): ";
			cin >> space2 >> number2;

			number1--;
			number2--;
			cascade_length_number1 = cascade[number1].size();

			// Input data verification
			if ((((space1 == 'G' && number1 <= 8) || (space1 == 'P' && number1 <= 4)) && number1 > 0) &&
				(((space2 == 'G' && number2 <= 8) || (space2 == 'P' && number2 <= 4) || (space2 == 'D' && number2 <= 4)) && number2 > 0)) // || !(cin.fail())
			{
				if (space1 == 'G' && !cascade[number1].empty())
				{
					switch (space2)
					{
					case 'G': // Moving card from cascade to another cascade
					{
						for (start_of_tableau = cascade_length_number1 - 1; start_of_tableau > 0;)
						{
							if (!((((cascade[number1].at(start_of_tableau).suit == '\x03' || cascade[number1].at(start_of_tableau).suit == '\x04') &&
									(cascade[number1].at(start_of_tableau - 1).suit == '\x05' || cascade[number1].at(start_of_tableau - 1).suit == '\x06')) ||
								   ((cascade[number1].at(start_of_tableau).suit == '\x05' || cascade[number1].at(start_of_tableau).suit == '\x06') &&
									(cascade[number1].at(start_of_tableau - 1).suit == '\x03' || cascade[number1].at(start_of_tableau - 1).suit == '\x04'))) &&
								  cascade[number1].at(start_of_tableau).rank + 1 == cascade[number1].at(start_of_tableau - 1).rank))
							{
								break;
							}
							start_of_tableau--;
						}
						if (cascade[number2].empty())
						{
							for (int i = 0; i < cascade_length_number1 - start_of_tableau; i++)
							{
								cascade[number2].push_back(cascade[number1].at(start_of_tableau));
								cascade[number1].erase(cascade[number1].begin() + start_of_tableau);
							}
							continue;
						}
						else if ((((cascade[number1].at(start_of_tableau).suit == '\x03' || cascade[number1].at(start_of_tableau).suit == '\x04') &&
								   (cascade[number2].back().suit == '\x05' || cascade[number2].back().suit == '\x06')) ||
								  ((cascade[number1].at(start_of_tableau).suit == '\x05' || cascade[number1].at(start_of_tableau).suit == '\x06') &&
								   (cascade[number2].back().suit == '\x03' || cascade[number2].back().suit == '\x04'))) &&
								 cascade[number1].at(start_of_tableau).rank + 1 == cascade[number2].back().rank)
						{
							for (int i = 0; i < cascade_length_number1 - start_of_tableau; i++)
							{
								cascade[number2].push_back(cascade[number1].at(start_of_tableau));
								cascade[number1].erase(cascade[number1].begin() + start_of_tableau);
							}
							continue;
						}
						else
						{
							error();
							continue;
						}
					}
					case 'P': // Moving card from cascades to help_cells
					{
						if (help_cell[number2].empty())
						{
							help_cell[number2].push(cascade[number1].back());
							cascade[number1].pop_back();
							continue;
						}
						else
						{
							error();
							continue;
						}
					}
					case 'D': // Moving card from cascades to foundations
					{

						if (foundation[number2].empty() && cascade[number1].back().symbol == 'A')
						{
							foundation[number2].push(cascade[number1].back());
							cascade[number1].pop_back();
							continue;
						}
						else if (cascade[number1].back().suit == foundation[number2].top().suit &&
								 cascade[number1].back().rank == foundation[number2].top().rank + 1)
						{
							foundation[number2].push(cascade[number1].back());
							cascade[number1].pop_back();
							continue;
						}
						else
						{
							error();
							continue;
						}
					}
					}
				}

				if (space1 == 'P' && !help_cell[number1].empty())
				{
					switch (space2)
					{
					case 'G': // Moving card from help_cells to cascades
					{
						if (cascade[number2].empty())
						{
							cascade[number2].push_back(help_cell[number1].top());
							help_cell[number1].pop();
							continue;
						}
						else if ((((help_cell[number1].top().suit == '\x03' || help_cell[number1].top().suit == '\x04') &&
								   (cascade[number2].back().suit == '\x05' || cascade[number2].back().suit == '\x06')) ||
								  ((help_cell[number1].top().suit == '\x05' || help_cell[number1].top().suit == '\x06') &&
								   (cascade[number2].back().suit == '\x03' || cascade[number2].back().suit == '\x04'))) &&
								 help_cell[number1].top().rank + 1 == cascade[number2].back().rank)
						{
							cascade[number2].push_back(help_cell[number1].top());
							help_cell[number1].pop();
							continue;
						}
						else
						{
							error();
							continue;
						}
					}
					case 'P': // Moving card from help_cell to another help_cell
					{
						if (help_cell[number2].empty())
						{
							help_cell[number2].push(help_cell[number1].top());
							help_cell[number1].pop();
							continue;
						}
						else
						{
							error();
							continue;
						}
					}
					case 'D': // Moving card from help_cells to foundations
					{
						if (foundation[number2].empty() && help_cell[number1].top().symbol == 'A')
						{
							foundation[number2].push(help_cell[number1].top());
							help_cell[number1].pop();
							continue;
						}
						else if (help_cell[number1].top().suit == foundation[number2].top().suit &&
								 help_cell[number1].top().rank == foundation[number2].top().rank + 1)
						{
							foundation[number2].push(help_cell[number1].top());
							help_cell[number1].pop();
							continue;
						}
						else
						{
							error();
							continue;
						}
					}
					}
				}
			}
			else
			{
				error();
				continue;
			}
		}
		display();
		cout << "\n******* YOU WON! *******\n";
		cin.get();
	}
};

int main()
{
	Patience freecell;

	freecell.start();

	return 0;
}