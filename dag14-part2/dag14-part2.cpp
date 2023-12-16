// dag14-part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include "../matrix/matrix.h"
#include <vector>
#include <map>
const int ROWS = 100;
const int COLS = 100;

matrix<char, ROWS, COLS> m('.');

void rotate(matrix<char, ROWS, COLS>& m) {
	matrix<char, ROWS, COLS>n = m;
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++) {
			n[j][COLS - 1 - i] =m[i][j] ;
		}
	m = n;
}

void tilt(matrix<char, ROWS, COLS>& m) {
	for (int j = 0; j < COLS; j++)
		for (int i = 1; i < ROWS; i++) {
			int r = i;
			while (r > 0 && m[r][j] == 'O' && m[r - 1][j] == '.') {
				m[r][j] = '.';
				m[r - 1][j] = 'O';
				r--;
			}

		}
}

void cycle(matrix<char, ROWS, COLS>& m) {
	tilt(m);
	for (int i = 0; i < 3; i++) {
		rotate(m);
		tilt(m);
	}
	rotate(m);
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	
	input >> m;

	for (int i = 1; i < 100; i++) {
		cycle(m);
	}

	cout << "find a repetiton in the following numbers " << endl;
	for (int i = 100; i < 150; i++) {
		cycle(m);
		int sum = 0;
		for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < COLS; j++) {
				if (m[i][j] == 'O')
					sum += (ROWS - i);
			}
		cout << "after " << i << " cycles:\t" << sum << endl ;
	}
}

