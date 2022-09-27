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
	void pasek()
	{
		cout<<"-------------------------------"<<endl;
	}
    void fillDeck()                                              
    {
    	for (int c = 0; c < 52; c++)
            _cards[c] = c;
    }
 
    void tasowanie()                  
    {
    	srand( time( NULL ) );
    	int cc = 52, nc, lc;
    	while( cc )
    	{
    	    nc = rand() % cc;
    	    lc = _cards[--cc];
    	    _cards[cc] = _cards[nc];
    	    _cards[nc] = lc;
     	}
    }
 
    void gra()
    {
	char* suit = "PTKC";
	char* symb = "A23456789TJQK";
	
    vector<karta> kolumna[8]; 
	stack<karta> docelowa[4];                   //tablica stosów pola docelowego
    stack<karta> pomoc[4];                      // tablica stosów pola pomocniczego
    
	int z = 0, i = 0;
	for( int c = 51; c >= 0; c-- )
	{
		karta k;
		k.kolor =suit[_cards[c] % 4];
		k.figura = symb[_cards[c] %13];
		kolumna[i].push_back(k);
		
		if(i > 3)
		{
			if( ++z == 6 )
			{
				i++;
				z = 0;
			}
		}
		else
		{
    	    if( ++z == 7 )
    	    {
         		i++;
         		z = 0;
    	    }

     	}
    }
    
	char pole1, pole2;
	int numer1, numer2;
	
	do{
		system ("cls");	                  // odœwierzanie konsoli

    int j = 0, d = 0;
	
	pasek();
	cout<<" P1"<<" P2"<<" P3"<<" P4        "<<"D1 "<<"D2 "<<"D3 "<<"D4 "<<endl;
	pasek();

	for( int c = 0; c < 4; c++ )
	{
		if(pomoc[c].empty() )cout<<"   ";
		else
		{
			cout<<" " <<pomoc[c].top().figura << pomoc[c].top().kolor;
		} 
	}
	cout<<"       ";
		for( int c = 0; c < 4; c++ )
	{
		if(docelowa[c].empty())	cout<<"   ";
		else
		{
			cout <<" "<< docelowa[c].top().figura << docelowa[c].top().kolor;
		} 
	}
	cout<<endl<<endl;
	pasek();
	cout<<" G1 "<<" G2 "<<" G3 "<<" G4 "<<" G5 "<<" G6 "<<" G7 "<<" G8 "<<endl;
	pasek();
	
	
	for( int c = 100; c >= 0; c-- )
	{
		if(j >= kolumna[d].size())
		{
			cout<<"    "; 
		}	
		else
		{
     		cout <<" " <<kolumna[d][j].figura << kolumna[d][j].kolor<<" ";
		}
		if(++d == 8)
		{
			cout<<endl;
			d = 0;
			j++;
		}
	}

cout<<endl<<"Rodzaj pola, z ktorego chcesz przeniesc karte (np. G):";
cin>>pole1;
cout<<endl;
cout<<"Nr pola, z ktorego chcesz przeniesc karte (np. 5):";
cin>>numer1;
cout<<endl;
cout<<"Rodzaj pole, na ktore chcesz przeniesc karte (np. G):";
cin>>pole2;
cout<<endl;
cout<<"Nr pola, na ktore chcesz przeniesc karte (np. 5):";
cin>>numer2;
cout<<endl;

numer1--;
numer2--;

	//PRZENIESIENIE KARTY Z POLA GRY.
	if(pole1=='G')
	{
		//PRZENIESIENIE KARTY Z POLA GRY NA INNE POLE GRY.
		if(pole2=='G')
		{
			if(kolumna[numer2].empty())
			{kolumna[numer2].push_back(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
		if(((kolumna[numer1].back().kolor=='K'||kolumna[numer1].back().kolor=='C')&&
		(kolumna[numer2].back().kolor=='P'||kolumna[numer2].back().kolor=='T'))||
		((kolumna[numer1].back().kolor=='P'||kolumna[numer1].back().kolor=='T')&&
		(kolumna[numer2].back().kolor=='K'||kolumna[numer2].back().kolor=='C')))
			{
			if(kolumna[numer1].back().figura=='Q' && kolumna[numer2].back().figura=='K')
			{kolumna[numer2].push_back(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='J' && kolumna[numer2].back().figura=='Q')
			{kolumna[numer2].push_back(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='T' && kolumna[numer2].back().figura=='J')
			{kolumna[numer2].push_back(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='9' && kolumna[numer2].back().figura=='T')
			{kolumna[numer2].push_back(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='8' && kolumna[numer2].back().figura=='9')
			{kolumna[numer2].push_back(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='7' && kolumna[numer2].back().figura=='8')
			{kolumna[numer2].push_back(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='6' && kolumna[numer2].back().figura=='7')
			{kolumna[numer2].push_back(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='5' && kolumna[numer2].back().figura=='6')
			{kolumna[numer2].push_back(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='4' && kolumna[numer2].back().figura=='5')
			{kolumna[numer2].push_back(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='3' && kolumna[numer2].back().figura=='4')
			{kolumna[numer2].push_back(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='2' && kolumna[numer2].back().figura=='3')
			{kolumna[numer2].push_back(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='A' && kolumna[numer2].back().figura=='2')
			{kolumna[numer2].push_back(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}																	
			}
		else
			{cout<<"Ruch jest niezgodny z zasadami gry."; getch();continue;}
		}
	
		//PRZENIESIENIE KARTY Z POLA GRY DO GRUPY POMOCNICZEJ.
		if(pole2=='P')
		{
		if(pomoc[numer2].empty())
			{pomoc[numer2].push(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
		else
			{cout<<"Ruch jest niezgodny z zasadami gry."; getch(); continue;}
		}
	
		//PRZENIESIENIE KARTY Z POLA GRY DO GRUPY DOCELOWEJ.
		if(pole2=='D')
		{
		if(docelowa[numer2].empty()&&kolumna[numer1].back().figura=='A')
			{docelowa[numer2].push(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
		else if (docelowa[numer2].empty()&&kolumna[numer1].back().figura!='A')
			{cout<<"Ruch jest niezgodny z zasadami gry."; getch(); continue;}
		if(kolumna[numer1].back().kolor=docelowa[numer2].top().kolor)
			{
			if(kolumna[numer1].back().figura=='2' && docelowa[numer2].top().figura=='A')
			{docelowa[numer2].push(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='3' && docelowa[numer2].top().figura=='2')
			{docelowa[numer2].push(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='4' && docelowa[numer2].top().figura=='3')
			{docelowa[numer2].push(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='5' && docelowa[numer2].top().figura=='4')
			{docelowa[numer2].push(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='6' && docelowa[numer2].top().figura=='5')
			{docelowa[numer2].push(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='7' && docelowa[numer2].top().figura=='6')
			{docelowa[numer2].push(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='8' && docelowa[numer2].top().figura=='7')
			{docelowa[numer2].push(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='9' && docelowa[numer2].top().figura=='8')
			{docelowa[numer2].push(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='T' && docelowa[numer2].top().figura=='9')
			{docelowa[numer2].push(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='J' && docelowa[numer2].top().figura=='T')
			{docelowa[numer2].push(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='Q' && docelowa[numer2].top().figura=='J')
			{docelowa[numer2].push(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			if(kolumna[numer1].back().figura=='K' && docelowa[numer2].top().figura=='K')
			{docelowa[numer2].push(kolumna[numer1].back());
			kolumna[numer1].pop_back();continue;}
			}
		else
			{cout<<"Ruch jest niezgodny z zasadami gry."; getch(); continue;}
		}
				else
			{cout<<"Ruch jest niezgodny z zasadami gry."; getch(); continue;}
	}
	
	//	PRZENIESIENIE KARTY Z GRUPY POMOCNICZEJ.
	if(pole1=='P')
	{
		//	PRZENIESIENIE KARTY Z GRUPY POMOCNICZEJ NA POLE GRY.
		if(pole2=='G')
		{
		if(kolumna[numer2].empty())
			{kolumna[numer2].push_back(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
		else
		if(docelowa[numer2].empty()&&pomoc[numer1].top().figura!='A')
		
			{cout<<"Ruch jest niezgodny z zasadami gry."; getch(); continue;}
		if(((pomoc[numer1].top().kolor=='K'||pomoc[numer1].top().kolor=='C')&&
		(kolumna[numer2].back().kolor=='P'||kolumna[numer2].back().kolor=='T'))||
		((pomoc[numer1].top().kolor=='P'||pomoc[numer1].top().kolor=='T')&&
		(kolumna[numer2].back().kolor=='K'||kolumna[numer2].back().kolor=='C')))
			{
			if(pomoc[numer1].top().figura=='Q' && kolumna[numer2].back().figura=='K')
			{kolumna[numer2].push_back(pomoc[numer1].top());
			pomoc[numer1].pop(); continue;} 
			if(pomoc[numer1].top().figura=='J' && kolumna[numer2].back().figura=='Q')
				{kolumna[numer2].push_back(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='T' && kolumna[numer2].back().figura=='J')
			{kolumna[numer2].push_back(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='9' && kolumna[numer2].back().figura=='T')
			{kolumna[numer2].push_back(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='8' && kolumna[numer2].back().figura=='9')
			{kolumna[numer2].push_back(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='7' && kolumna[numer2].back().figura=='8')
			{kolumna[numer2].push_back(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='6' && kolumna[numer2].back().figura=='7')
			{kolumna[numer2].push_back(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='5' && kolumna[numer2].back().figura=='6')
			{kolumna[numer2].push_back(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='4' && kolumna[numer2].back().figura=='5')
			{kolumna[numer2].push_back(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='3' && kolumna[numer2].back().figura=='4')
			{kolumna[numer2].push_back(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='2' && kolumna[numer2].back().figura=='3')
			{kolumna[numer2].push_back(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='A' && kolumna[numer2].back().figura=='2')
			{kolumna[numer2].push_back(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}																	
			}
		else
			{cout<<"Ruch jest niezgodny z zasadami gry."; getch(); continue;}
		}
	
		//PRZENIESIENIE KARTY Z GRUPY POMOCNICZEJ DO GRUPY DOCELOWEJ.
		if(pole2=='D')
		{
		if(docelowa[numer2].empty()&&pomoc[numer1].top().figura=='A')
			{docelowa[numer2].push(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
		else
		if(docelowa[numer2].empty()&&pomoc[numer1].top().figura!='A')
			{cout<<"Ruch jest niezgodny z zasadami gry."; getch(); continue;}
		if(pomoc[numer1].top().kolor=docelowa[numer2].top().kolor)
			{
			if(pomoc[numer1].top().figura=='2' && docelowa[numer2].top().figura=='A')
			{docelowa[numer2].push(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='3' && docelowa[numer2].top().figura=='2')
			{docelowa[numer2].push(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='4' && docelowa[numer2].top().figura=='3')
			{docelowa[numer2].push(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='5' && docelowa[numer2].top().figura=='4')
			{docelowa[numer2].push(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='6' && docelowa[numer2].top().figura=='5')
			{docelowa[numer2].push(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='7' && docelowa[numer2].top().figura=='6')
			{docelowa[numer2].push(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='8' && docelowa[numer2].top().figura=='7')
			{docelowa[numer2].push(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='9' && docelowa[numer2].top().figura=='8')
			{docelowa[numer2].push(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='T' && docelowa[numer2].top().figura=='9')
			{docelowa[numer2].push(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='J' && docelowa[numer2].top().figura=='T')
			{docelowa[numer2].push(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='Q' && docelowa[numer2].top().figura=='J')
			{docelowa[numer2].push(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			if(pomoc[numer1].top().figura=='K' && docelowa[numer2].top().figura=='K')
			{docelowa[numer2].push(pomoc[numer1].top());
			pomoc[numer1].pop();continue;}
			}
		else
			{cout<<"Ruch jest niezgodny z zasadami gry."; getch(); continue;}
		}
				else
			{cout<<"Ruch jest niezgodny z zasadami gry."; getch(); continue;}
	}
}while(docelowa[0].size()!=13&&docelowa[1].size()!=13&&docelowa[2].size()!=13&&docelowa[3].size()!=13);         // koniec gry gdy pola docelowe zostan¹ wype³nione

cout<<"WYGRALES!"<<endl;

    }
    int _cards[52];
};

int main ()
{
	pasjans freecell;
    
	freecell.polestartowe();

	return 0;
}

