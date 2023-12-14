// dag14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "../matrix/matrix.h"
#include <vector>
#include <map>
const int ROWS = 10;
const int COLS = 10;

matrix<char, ROWS, COLS> m('.');

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	ofstream output("C:\\Users\\Jan\\Desktop\\output.txt");

	input >> m;

	for (int j = 0; j < COLS; j++)
		for(int i = 1; i < ROWS; i++) {
			int r = i;
			while ( r > 0 && m[r][j] == 'O' && m[r - 1][j] == '.') {
				m[r][j] = '.';
				m[r - 1][j] = 'O';
				r--;
			}
			
		}
	output << m << endl;

	int sum = 0;
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++) {
			if (m[i][j] == 'O')
				sum += (ROWS - i) ;
		}

	cout << endl << sum << endl;

}

