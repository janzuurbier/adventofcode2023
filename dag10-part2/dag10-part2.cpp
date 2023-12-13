// dag10-part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
Walk the loop en copy the loop-cells to a new matrix.
Walk the loop in the new matrix and mark cells left of the path
Those are either on inside or outside.
Floodfill the area and count the number of marked cells.
Maybe it is the outside area that is marked and not the inside area.
Then count cells that are neither marked nor on the path.
*/

#include <iostream>
#include <string>
#include <fstream>
#include "../matrix/matrix.h"
using namespace std;

const int ROWS = 140;
const int COLS = 140;

matrix<char, ROWS, COLS> m('.'); //inputmatrix
matrix<char, ROWS, COLS> n('.');//copy of inputmatrix that only contains the loop

//mark cells in matrix n
void mark(int r, int k) {
	if (n.isInRange(r, k) && n[r][k] == '.') n[r][k] = 'A';
}

void floodfill() {
	for (int i = 0; i < COLS; i++)
		for (int j = 0; j < ROWS; j++) {
			if (n[j][i] == 'A') {
				mark(j, i + 1);
				mark(j + 1, i);
			}
		}
	for (int i = COLS-1; i >= 0; i--)
		for (int j = ROWS - 1; j >= 0; j--) {
			if (n[j][i] == 'A') {
				mark(j - 1, i);
				mark(j, i - 1);
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

	//find start
	int start_row = 0, start_col = 0;
	for (int i = 0; i < COLS; i++)
		for (int j = 0; j < ROWS; j++)
			if (m[j][i] == 'S') {
				start_col = i;
				start_row = j;
			}
	int col = start_col;
	int row = start_row;

	n[row][col] = 'S'; //copy 'start' in matrix n

	int length = 0;
	int dir_x = 0, dir_y = 0;

	//find start diriection
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
	//move in that direction
	col += dir_x;
	row += dir_y;
	int start_dir_x = dir_x;
	int start_dir_y = dir_y;
	
	while (col != start_col || row != start_row) {
		//copy element of the loop to matrix n
		n[row][col] = m[row][col]; 
		//find next dir
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
		//move
		col += dir_x;
		row += dir_y;
		length++;
	}
	cout << "lengte van het pad = " << length + 1 << endl;

	//walk through matrix n and mark cells next to the path on the left side of the path
	row = start_row;
	col = start_col;
	dir_x = start_dir_x;
	dir_y = start_dir_y;
	row += dir_y;
	col += dir_x;
	while (col != start_col || row != start_row) {
		switch (n[row][col]) {
		case '-':
			if (dir_x == 1) {
				mark(row - 1, col); 
			}
			else {
				mark(row + 1, col);  
			}
			break;
		case '|': 
			if (dir_y == 1)
			{
				mark(row, col + 1); 
			}
			else
			{
				mark(row , col - 1); 
			}
			break;
		case '7':
			if (dir_x == 1 && dir_y == 0) {
				dir_x = 0;
				dir_y = 1;
				mark(row - 1, col); mark(row, col + 1);
			}
			else if (dir_x == 0 && dir_y == -1) {
				dir_x = -1;
				dir_y = 0;
			}
			break;
		case 'J':
			if (dir_x == 0 && dir_y == 1) {
				mark(row, col + 1); mark(row + 1, col);
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
				mark(row, col - 1); mark(row - 1, col);
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
				mark(row + 1, col); mark(row, col - 1);
			}
			break;
		}
		col += dir_x;
		row += dir_y;	
	}//while

	floodfill();
	int count_unmarked = 0;
	int count_marked = 0;
	for (int i = 0; i < COLS; i++)
		for (int j = 0; j < ROWS; j++) {
			if (n[j][i] == '.') count_unmarked++;
			if (n[j][i] == 'A') count_marked++;
		}
	
	output << n << endl;
	cout << "marked: " << count_marked << " unmarked: " << count_unmarked << endl;
	cout << "look in output.txt wether marked points are inside or outside the loop" << endl;
}