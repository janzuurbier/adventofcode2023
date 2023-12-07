// dag07-part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	case 'J': return 1;
	case 'T': return 10;
	default: return ch - '0';
	}
}

class Hand {
private:
	string cards;
	int bid;
	string type;

public:
	Hand(string c, int b): cards(c), bid(b), type("") {
		
		//sort cards but keep original sequence
		string temp1 = cards;
		sort(temp1.begin(), temp1.end());

		

		//remove jokers
		string temp = "";
		int aantal_jokers = 0;
		for (int i = 0; i < 5; i++) {
			if (temp1[i] == 'J') {
				aantal_jokers++;
			}
			else {
				temp += temp1[i];
			}
		}

		//calculate type
		int n = 1;
		if (aantal_jokers < 3) {
			for (int i = 0; i < temp.size() - 2; i++) {
				if (temp[i] == temp[i + 1])
					n++;
				else {
					type += char(n) + '0';
					n = 1;
				}
			}
			if (temp[temp.size() - 2] == temp[temp.size() - 1]) {
				n++;
				type += char(n) + '0';
			}
			else {
				type += char(n) + '0';
				type += '1';
			}
			sort(type.begin(), type.end(), [](int a, int b) {return a > b; });
			
			type[0] += aantal_jokers;
		}
		if (aantal_jokers == 3) {
			if (temp[0] == temp[1]) {
				type = "5";
			}
			else {
				type = "41";
			}
		}
		if (aantal_jokers >= 4) {
			type = "5";
		}
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
	sort(hands.begin(), hands.end(), is_weaker_than);
	cout << endl;

	uint64_t winning_bid = 0;
	for (int rank = 0; rank < hands.size(); rank++)
		winning_bid += (rank + 1) * hands[rank].get_bid();
	cout << winning_bid << endl;

}
