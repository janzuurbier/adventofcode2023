// dag04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	int sum = 0;

	string line;
	while (getline(input, line)) {
		int pos1 = line.find(':');
		int pos2 = line.find('|');
		string line1 = line.substr(pos1 + 2, pos2 - pos1 - 2);
		string line2 = line.substr(pos2 + 1);
		stringstream in1(line1);
		int x;
		set<int> winning_numbers;
		while (in1 >> x) {
			winning_numbers.insert(x);
		}
		stringstream in2(line2);
		int aantal = 0;
		while (in2 >> x) {
			if (winning_numbers.count(x) > 0)
				aantal++;
		}
		if (aantal > 0) {
			int waarde = 1;
			for (int i = 1; i < aantal; i++)
				waarde *= 2;
			sum += waarde;
		}
	}
	cout << sum << endl;
}