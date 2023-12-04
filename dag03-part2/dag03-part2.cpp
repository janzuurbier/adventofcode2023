// dag03-part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "../matrix/matrix.h"
#include <vector>
#include <set>
#include <map>
//const int ROWS = 10;
//const int COLS = 10;
const int ROWS = 140;
const int COLS = 140;

matrix<char, ROWS, COLS> m('.');
map<int, vector<int>> numbers_adjacent_to_gear;

bool isNumber(int i, int j) {
	return '0' <= m[i][j] && m[i][j] <= '9';
}



int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	input >> m;

	for (int i = 0; i < COLS; i++) {
		int number_to_read = 0;
		set<int> adjacentgears;
		for (int j = 0; j < ROWS; j++) {
			if (isNumber(i, j)) {
				number_to_read = number_to_read * 10 + m[i][j] - '0';
				for (int a = i - 1; a <= i + 1; a++)
					for (int b = j - 1; b <= j + 1; b++)
						if (m.isInRange(a, b) && m[a][b] == '*')
							adjacentgears.insert(a*COLS + b);
			}
			else {
				for (int n : adjacentgears)
					numbers_adjacent_to_gear[n].push_back(number_to_read);
				number_to_read = 0;
				adjacentgears.clear();
			}
		}
		for (int n : adjacentgears)
			numbers_adjacent_to_gear[n].push_back(number_to_read);
		number_to_read = 0;
		adjacentgears.clear();
	}
	int sum = 0;
	for(auto it = numbers_adjacent_to_gear.begin(); it != numbers_adjacent_to_gear.end(); ++it)
		if (it->second.size() == 2) {
			int prd = it->second[0] * it->second[1];
			cout << it->second[0] << '\t' << it->second[1] << '\t' << prd << endl;
			sum += prd;
		}
	cout << sum << endl;



}

