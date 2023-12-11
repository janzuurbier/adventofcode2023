// dag10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <fstream>
#include <sstream>
#include "../matrix/matrix.h"
using namespace std;
//const int ROWS = 5;
//const int COLS = 5;
const int ROWS = 140;
const int COLS = 140;

matrix<char, ROWS, COLS> m('.');

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	input >> m;
	
	int start_row = 0, start_col = 0;
	for (int i = 0; i < COLS; i++)
		for (int j = 0; j < ROWS; j++)
			if (m[j][i] == 'S') {
				start_col = i;
				start_row = j;
			}
	
	int length = 0;
	int col = start_col;
	int row = start_row;
	int dir_x = 0, dir_y = 0;
	if (m[row][col + 1] == '-' || m[row][col + 1] == '7' || m[row][col + 1] == 'J') {
		dir_x = 1;
		dir_y = 0;
	}
	else if (m[row + 1][col] == '|' || m[row + 1][col] == 'L' || m[row + 1][col] == 'J') {
		dir_x = 0;
		dir_y = 1;
	}
	else if (m[row][col - 1] == '-' || m[row][col + 1] == 'L' || m[row][col + 1] == 'F') {
		dir_x = -1;
		dir_y = 0;
	}
	else if (m[row - 1][col] == '|' || m[row + 1][col] == 'F' || m[row + 1][col] == '7') {
		dir_x = 0;
		dir_y = -1;
	}
	col += dir_x;
	row += dir_y;

	while (col != start_col || row != start_row) {
		switch (m[row][col]) {
		case '-':  break;
		case '|':  break;
		case '7':
			if (dir_x == 1 && dir_y == 0) {
				dir_x = 0;
				dir_y = 1;
			}
			else if (dir_x == 0 && dir_y == -1) {
				dir_x = -1;
				dir_y = 0;
			}
			break;
		case 'J':
			if (dir_x == 0 && dir_y == 1) {
				dir_x = -1;
				dir_y = 0;
			}
			else if (dir_x == 1 && dir_y == 0) {
				dir_x = 0;
				dir_y = -1;
			}
			break;
		case 'F':
			if (dir_x == 0 && dir_y == -1) {
				dir_x = 1;
				dir_y = 0;
			}
			else if (dir_x == -1 && dir_y == 0) {
				dir_x = 0;
				dir_y = 1;
			}
			break;
		case 'L':
			if (dir_x == 0 && dir_y == 1) {
				dir_x = 1;
				dir_y = 0;
			}
			else if (dir_x == -1 && dir_y == 0) {
				dir_x = 0;
				dir_y = -1;
			}
			break;
		}
		col += dir_x;
		row += dir_y;
		length++;
	}

	cout << (length + 1) /2 << endl;
}