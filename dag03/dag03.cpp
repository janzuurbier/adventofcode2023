// dag03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "../matrix/matrix.h"
#include <vector>
#include <map>
//const int ROWS = 10;
//const int COLS = 10;
const int ROWS = 140;
const int COLS = 140;

matrix<char, ROWS, COLS> m('.');

bool isNumber(int i, int j) {
	return '0' <= m[i][j] && m[i][j] <= '9'; 
}

bool isAdjacentToSymbol(int r, int k) {
	for (int i = r - 1; i <= r + 1; i++)
		for (int j = k - 1; j <= k + 1; j++)
			if (m.isInRange(i, j) && !isNumber(i, j) && m[i][j] != '.')
				return true;
	return false;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	

	

	input >> m;

	int sum = 0;
	for (int i = 0; i < COLS; i++) {
		int number_to_read = 0;
		bool adjacent = false;
		for (int j = 0; j < ROWS; j++) {
			if (isNumber(i, j)) {
				number_to_read = number_to_read * 10 + m[i][j] - '0';
				adjacent = adjacent || isAdjacentToSymbol(i, j);
			}
			else {
				if (adjacent)
					sum += number_to_read;
				if(number_to_read != 0)
					cout << number_to_read << '\t' << adjacent << endl;
				number_to_read = 0;
				adjacent = false;
				
			}
		}
		if (adjacent)
			sum += number_to_read;
		if (number_to_read != 0)
			cout << number_to_read << '\t' << adjacent << endl;
		number_to_read = 0;
		adjacent = false;
	}

	cout << endl << sum << endl;

}

