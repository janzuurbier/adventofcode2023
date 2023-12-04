// dag04-part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
using namespace std;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	vector<int> aantal_goed_per_kaart;

	string line;
	int aantal_regels = 0;
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
		aantal_goed_per_kaart.push_back(aantal);
		aantal_regels++;
	}
	vector<int> aantal_kaarten;
	for (int i = 0; i < aantal_regels; i++)
		aantal_kaarten.push_back(1);
	for (int i = 0; i < aantal_regels; i++) {
		for (int j = 1; j <= aantal_goed_per_kaart[i]; j++)
			if (i + j < aantal_regels)
				aantal_kaarten[i + j] += aantal_kaarten[i];
	}
	int sum = 0;
	for (int i = 0; i < aantal_regels; i++) {
		cout << aantal_kaarten[i] << endl;
		sum += aantal_kaarten[i];
	}
	cout << ">>>>" << sum << endl;
}