// dag02-part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

char get_separator(string s) {
	char ch = s[s.size() - 1];
	if (ch == ';' || ch == ',')
		return ch;
	return '\0';
}

string remove_separator(string s) {
	if (get_separator(s))
		return s.substr(0, s.size() - 1);
	else
		return s;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;
	int gamenr = 0;
	int sum_powers = 0;
	
	while (getline(input, line)) {
		gamenr++;
		size_t pos = line.find(":");
		line = line.substr(pos + 2);
		stringstream in(line);
		int maxred = 0;
		int maxgreen = 0;
		int maxblue = 0;
		int number;
		string kleur;
		while (in >> number >> kleur) {
			char separator = get_separator(kleur);
			kleur = remove_separator(kleur);
			if (kleur == "red" && number > maxred)
				maxred = number;
			if (kleur == "blue" && number > maxblue)
				maxblue = number;
			if (kleur == "green" && number > maxgreen)
				maxgreen = number;
		}
		int power = maxred * maxblue*maxgreen;
		maxred = 0;
		maxgreen = 0;
		maxblue = 0;
		sum_powers += power;
	}
	cout << sum_powers << endl;
}