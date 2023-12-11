// dag10-part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
#include <string>
#include <fstream>
#include "../matrix/matrix.h"
using namespace std;
//const int ROWS = 10;
//const int COLS = 20;
const int ROWS = 140;
const int COLS = 140;

matrix<char, ROWS, COLS> m('.');
matrix<char, ROWS, COLS> n('.');

//only matrix n will marked
void mark_A(int r, int k) {
	if (n.isInRange(r, k) && n[r][k] == '.') n[r][k] = 'A';
}

void mark_B(int r, int k) {
	if (n.isInRange(r, k) && n[r][k] == '.') n[r][k] = 'B';
}

void fill_points() {
	for (int i = 0; i < COLS; i++)
		for (int j = 0; j < ROWS; j++) {
			if (n[j][i] == 'A') {
				mark_A(j, i + 1);
				mark_A(j + 1, i);
			}
			if (n[j][i] == 'B') {
				mark_B(j, i + 1);
				mark_B(j + 1, i);
			}
		}
	for (int i = COLS-1; i >= 0; i--)
		for (int j = ROWS - 1; j >= 0; j--) {
			if (n[j][i] == 'A') {
				mark_A(j - 1, i);
				mark_A(j, i - 1);
			}
			if (n[j][i] == 'B') {
				mark_B(j - 1, i);
				mark_B(j, i - 1);
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
	ofstream output("C:\\Users\\Jan\\Desktop\\output.txt");

	input >> m;

	int start_row = 0, start_col = 0;
	for (int i = 0; i < COLS; i++)
		for (int j = 0; j < ROWS; j++)
			if (m[j][i] == 'S') {
				start_col = i;
				start_row = j;
			}
	int col = start_col;
	int row = start_row;

	n[row][col] = 'S';
	int length = 0;
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
	else if (m[row + 1][col] == '|' || m[row + 1][col] == 'F' || m[row + 1][col] == '7') {
		dir_x = 0;
		dir_y = -1;
	}
	col += dir_x;
	row += dir_y;
	int start_dir_x = dir_x;
	int start_dir_y = dir_y;
	
	while (col != start_col || row != start_row) {
		n[row][col] = m[row][col];
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
	cout << "lengte van het pad = " << length + 1 << endl;

	//matrix n only contains path
	row = start_row;
	col = start_col;
	dir_x = start_dir_x;
	dir_y = start_dir_y;
	row += dir_y;
	col += dir_x;
	
	while (col != start_col || row != start_row) {
		n[row][col] = m[row][col];
		switch (n[row][col]) {
		case '-':
			if (dir_x == 1) {
				mark_A(row - 1, col); mark_B(row + 1, col); 
			}
			else {
				mark_A(row + 1, col); mark_B(row - 1, col); 
			}
			break;
		case '|': 
			if (dir_y == 1)
			{
				mark_A(row, col + 1); mark_B(row , col - 1);
			}
			else
			{
				mark_A(row , col - 1); mark_B(row , col + 1);
			}
			break;
		case '7':
			if (dir_x == 1 && dir_y == 0) {
				dir_x = 0;
				dir_y = 1;
				mark_A(row - 1, col); mark_A(row, col + 1);
			}
			else if (dir_x == 0 && dir_y == -1) {
				dir_x = -1;
				dir_y = 0;
				mark_B(row, col + 1); mark_B(row - 1, col);
			}
			break;
		case 'J':
			if (dir_x == 0 && dir_y == 1) {
				mark_A(row, col + 1); mark_A(row + 1, col);
				dir_x = -1;
				dir_y = 0;
			}
			else if (dir_x == 1 && dir_y == 0) {
				dir_x = 0;
				dir_y = -1;
				mark_B(row + 1, col); mark_B(row, col + 1);
			}
			break;
		case 'F':
			if (dir_x == 0 && dir_y == -1) {
				dir_x = 1;
				dir_y = 0;
				mark_A(row, col - 1); mark_A(row - 1, col);
			}
			else if (dir_x == -1 && dir_y == 0) {
				dir_x = 0;
				dir_y = 1;
				mark_B(row - 1, col); mark_B(row, col - 1);
			}
			break;
		case 'L':
			if (dir_x == 0 && dir_y == 1) {
				dir_x = 1;
				dir_y = 0;
				mark_B(row, col - 1); mark_B(row + 1, col);
			}
			else if (dir_x == -1 && dir_y == 0) {
				dir_x = 0;
				dir_y = -1;
				mark_A(row + 1, col); mark_A(row, col - 1);
			}
			break;
		}
		
		col += dir_x;
		row += dir_y;
			
	}

	fill_points();
	int countB = 0;
	int countA = 0;
	for (int i = 0; i < COLS; i++)
		for (int j = 0; j < ROWS; j++) {
			if (n[j][i] == 'B') countB++;
			if (n[j][i] == 'A') countA++;
		}
	
	output << n << endl;
	cout << "A: " << countA << " B: " << countB << endl;
	cout << "look in output.txt wether A or B is inside the loop" << endl;
}