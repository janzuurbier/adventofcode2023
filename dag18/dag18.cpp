// dag18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// aoc23dag18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <sstream>
#include "..//matrix_new//matrix.h"
#include <deque>
using namespace std;

void flood_fill(matrix<char>& m, int i, int j) {
	deque<pair<int, int>> dq;
	dq.push_back(pair<int, int>(i, j));
	while (!dq.empty()) {
		pair<int, int> p = dq.front();
		dq.pop_front();
		if (m.isInRange(p.first, p.second) && m[p.first][p.second] == '.') {
			m[p.first][p.second] = 'x';
			dq.push_back(pair<int, int>(p.first + 1, p.second));
			dq.push_back(pair<int, int>(p.first - 1, p.second));
			dq.push_back(pair<int, int>(p.first, p.second + 1));
			dq.push_back(pair<int, int>(p.first, p.second - 1));
		}
	}

}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	
	char dir;
	int steps;
	string color;
	int aantal = 0;
	int min_r = 100000;
	int min_c = 100000;
	int max_r = 0;
	int max_c = 0;
	int r = 0;
	int c = 0;
	
	while (input >> dir >> steps >> color) {
		switch (dir) {
		case 'R':
			c += steps;
			if (c > max_c) max_c = c;

			break;
		case 'L':
			c -= steps;
			if (c < min_c) min_c = c;

			break;
		case 'U':
			r -= steps;
			if (r < min_r) min_r = r;

			break;
		case 'D':
			r += steps;
			if (r > max_r) max_r = r;

		}
	}

	cout << "rows van "<< min_r << " tot " << max_r << endl;
	cout << "cols van " << min_c << " tot " << max_c << endl;

	matrix<char> m(max_r - min_r + 4, max_c - min_c + 4, '.');
	int row = -min_r + 2;
	int col = -min_c + 2;

	input.close();
	input.open("C:\\Users\\Jan\\Desktop\\input.txt");
	while (input >> dir >> steps >> color) {
		int i = 0;
		switch (dir) {
		case 'R':
			while (i < steps) {
				i++;
				col++;
				m[row][col] = '#';
			}

			break;
		case 'L':
			while (i < steps) {
				i++;
				col--;
				m[row][col] = '#';
			}
			break;
		case 'U':
			while (i < steps) {
				i++;
				row--;
				m[row][col] = '#';
			}
			break;
		case 'D':
			while (i < steps) {
				i++;
				row++;
				m[row][col] = '#';
			}
		}
		aantal++;
	}
	cout << m << endl;
	flood_fill(m, 0, 0);
	int aantal_hekjes = 0;
	int aantal_puntjes = 0;
	for (int i = 0; i < m.getRows(); i++)
		for (int j = 0; j < m.getCols(); j++) {
			if (m[i][j] == '#')
				aantal_hekjes++;
			if (m[i][j] == '.')
				aantal_puntjes++;
		}
	cout << aantal_hekjes << " " << aantal_puntjes << " totaal: " << aantal_hekjes + aantal_puntjes << endl;
	
}

