// dag07.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int strength(char ch) {
	switch (ch) {
	case 'A': return 14;
	case 'K': return 13;
	case 'Q': return 12;
	case 'J': return 11;
	case 'T': return 10;
	default: return ch - '0';
	}
}

class Hand {
private:
	string cards; //e.g. "A2KKJ"
	int bid;
	string type; //"5", "41", "32", "311", "221", "2111", "11111"

public:
	Hand(string c, int b): cards(c), bid(b), type("") {

		//sort cards but keep orignal sequence
		string temp = cards;
		sort(temp.begin(), temp.end());

		//calculate type
		int n = 1;
		for (int i = 0; i < 3; i++) {
			if (temp[i] == temp[i + 1])
				n++;
			else {
				type += char(n) + '0';
				n = 1;
			}
		}
		if (temp[3] == temp[4]) {
			n++;
			type += char(n) + '0';
		}
		else {
			type += char(n) + '0';
			type += '1';
		}		
		
		sort(type.begin(), type.end(), [](int a, int b) {return a > b; });
		
	}

	int get_bid()const {
		return bid;
	}

	friend bool is_weaker_than(const Hand& a, const Hand& b);

	friend ostream& operator<<(ostream& os, const Hand& h);


};

ostream&  operator<<(ostream& os, const Hand& h) {
	os << h.cards << " " << h.bid << " " << h.type;
	return os;
}

bool is_weaker_than(const Hand& a, const Hand& b) {
	if (a.type < b.type)
		return true;
	if (a.type > b.type)
		return false;
	for (int i = 0; i < 5; i++) {
		if (strength(a.cards[i]) < strength(b.cards[i]))
			return true;
		if (strength(a.cards[i]) > strength(b.cards[i]))
			return false;
	}
	return false;
}

	int main()
	{
		ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
		if (!input) {
			cout << "file not found" << endl;
			return 1;
		}

		vector<Hand> hands;
		string cards;
		int bid;
		while (input >> cards >> bid) {
			hands.push_back(Hand(cards, bid));
		}
		for (const Hand& h : hands)
			cout << h << endl;

		sort(hands.begin(), hands.end(), is_weaker_than);
		

		uint64_t winning_bid = 0;
		for (int rank = 0; rank < hands.size(); rank++)
			winning_bid += (rank+1) * hands[rank].get_bid();
		cout << winning_bid << endl;

	}
