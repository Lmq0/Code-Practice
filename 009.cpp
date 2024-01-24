#define ERROW -1;
#define _CRT_SECURE_NO_WARNINGS
#include<iostream> 
#include<cmath>
#include<string.h>
using namespace std;
const char For_Suit_Display[4][10] = { "Spade","Diamond","Club","Heart" };
const char for_NUM_Display[13][3] = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };

struct Poker
{
	int suit;//1 Spade 2 Diamond 3 Club 4 Heart
	int num;
	Poker* front=NULL ;
	Poker* next=NULL ;
};
typedef Poker* PokerDeck;
PokerDeck Append(PokerDeck &OriginalDeck,int Append_Suit,int Append_Num)
{
	PokerDeck p = OriginalDeck;
	if (p == NULL)
	{
		p = (PokerDeck)malloc(sizeof(Poker));
		if (!p)exit(0);
		p->suit = Append_Suit;
		p->num = Append_Num;
		OriginalDeck = p;
		p->next = NULL;
		p->front = NULL;
	}
	else
	{
		while (p->next != NULL)
		{
			p = p->next;
		}
		PokerDeck q = (PokerDeck)malloc(sizeof(Poker));
		if (!q)exit(0);
		q->suit = Append_Suit;
		q->num = Append_Num;
		q->front = p;
		q->next = NULL;
		p->next = q;
	}

	return OriginalDeck;
}
PokerDeck Revert(PokerDeck& OriginalDeck)
{
	if (OriginalDeck == NULL || OriginalDeck->next == NULL)
	{
		return OriginalDeck;
	}
	PokerDeck head = OriginalDeck;
	PokerDeck tail = OriginalDeck;
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	//
	while (tail->next != head && (tail->next != head->front||head->front==NULL))
	{
		int bridge;
		bridge = head->suit;
		head->suit = tail->suit;
		tail->suit = bridge;

		bridge = head->num;
		head->num = tail->num;
		tail->num = bridge;

		tail = tail->front;
		head = head->next;
	}


	return OriginalDeck;
}
PokerDeck Pop(PokerDeck& OriginalDeck)
{
	if (OriginalDeck == NULL)
	{
		cout << "NULL" << endl;
		return OriginalDeck;
	}
	PokerDeck p = OriginalDeck;
	
	OriginalDeck = OriginalDeck->next;
	cout << For_Suit_Display[p->suit - 1] << " " << for_NUM_Display[p->num-1] << endl;


	free(p);
	return OriginalDeck;
}
PokerDeck Extract(PokerDeck& OriginalDeck, int SortSuit)
{
	if (OriginalDeck == NULL || OriginalDeck->next == NULL)
		return OriginalDeck;

	bool if_extra = false;
	if (OriginalDeck->suit == SortSuit)
	{
		PokerDeck extra= (PokerDeck)malloc(sizeof(Poker));
		if (!extra)exit(0);
		extra->next = OriginalDeck;
		extra->front = NULL;
		extra->suit = -1;
		extra->num = -1;
		OriginalDeck->front = extra;
		OriginalDeck = extra;
		if_extra = true;
	}
	PokerDeck q = OriginalDeck;
	PokerDeck NewDeck = OriginalDeck;
	PokerDeck p = OriginalDeck;

	while (p != NULL)
	{
		PokerDeck for_p_next = p->next;
		if (p->suit == SortSuit)
		{
			
			if (p->front != NULL)
				p->front->next = p->next;
			if (p->next != NULL)
				p->next->front = p->front;
			while (p->num > q->num&& q != OriginalDeck)
			{
				q = q->next;
			}
			p->next = q;
			if (q != NewDeck)
			{
				p->front = q->front;
				q->front->next = p;
			}
			else
			{
				NewDeck = p;
			}
			q->front = p;
			q = NewDeck;


		}
		p= for_p_next;
	}

	if (if_extra)
	{
		if (OriginalDeck->next != NULL)
			OriginalDeck->next->front = OriginalDeck->front;
		if(OriginalDeck->front != NULL)
			OriginalDeck->front->next = OriginalDeck->next;

		free(OriginalDeck);
	}



	OriginalDeck = NewDeck;
	return NewDeck;
}
void PrintOutDeck(PokerDeck DisplayDeck)
{
	if (DisplayDeck == NULL)
	{
		cout << "NULL" << endl;
	}
	else
	{
		PokerDeck p=DisplayDeck;
		while (p != NULL)
		{
			cout << For_Suit_Display[p->suit - 1] << " " << for_NUM_Display[p->num - 1] << endl;
			p = p->next;
		}
	}
}




int main()
{
	int Number_Of_Orders = 0;
	PokerDeck Deck=NULL;
	cin >> Number_Of_Orders;
	while (Number_Of_Orders > 0)
	{
		char Order[15];
		cin >> Order;
		if (strcmp(Order, "Append") == 0)
		{
			char type[10];
			cin >> type;
			char ch[3];
			cin >> ch;
			int number=1;
			if (strcmp(ch, "10") == 0)
			{
				number = 10;
			}
			else if (strcmp(ch, "1") > 0 && strcmp(ch, "9") <= 0)
			{
				number = ch[0] - 48;
			}
			else if (strcmp(ch, "A")==0)
			{
				number = 1;
			}
			else if (strcmp(ch, "J") == 0)
			{
				number = 11;
			}
			else if (strcmp(ch, "Q") == 0)
			{
				number = 12;
			}
			else if (strcmp(ch, "K") == 0)
			{
				number = 13;
			}
			
		    else continue;

			if (strcmp(type, "Heart") == 0)
				Append(Deck, 4, number);
			else if (strcmp(type, "Spade") == 0)
				Append(Deck, 1, number);
			else if (strcmp(type, "Club") == 0)
				Append(Deck, 3, number);
			else if (strcmp(type, "Diamond") == 0)
				Append(Deck, 2, number);
			else continue;
		}
		else if (strcmp(Order, "Pop") == 0)
		{
			Pop(Deck);
		}
		else if (strcmp(Order, "Extract") == 0)
		{
			char type[10];
			cin >> type;
			if (strcmp(type, "Spade") == 0)
				Extract(Deck,1);
			else if (strcmp(type, "Diamond") == 0)
				Extract(Deck, 2);
			else if (strcmp(type, "Club") == 0)
				Extract(Deck, 3);
			else if (strcmp(type, "Heart") == 0)
				Extract(Deck, 4);
			else continue;
		}
		else if (strcmp(Order, "Revert") == 0)
		{
			Revert(Deck);
		}
		else continue;


		Number_Of_Orders--;
	}
	PrintOutDeck(Deck);



	return 0;
}
