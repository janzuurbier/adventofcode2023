// dag21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <sstream>
#include "..//matrix_new//matrix.h"
#include <set>
using namespace std;

struct plot {
	int row;
	int col;

	plot(int r, int c) : row(r), col(c) {}

	friend bool operator<(const plot& p, const plot& q) { return p.row < q.row || p.row == q.row && p.col < q.col; }
};

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	matrix <char> m;
	input >>  m;
	int rows = m.getRows();
	int cols = m.getCols();

	int r_start = 0;
	int c_start  = 0;
	for(int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			if (m[i][j] == 'S') {
				r_start = i;
				c_start = i;
			}
		}

	set< plot> v;
	v.insert(plot(r_start, c_start));
	set <plot> w;
	for (int i = 0; i < 64; i++) {		
		for (plot p : v) {
			if (m.isInRange(p.row + 1, p.col) && m[p.row + 1][p.col] != '#')
				w.insert(plot(p.row + 1, p.col));
			if (m.isInRange(p.row - 1, p.col) && m[p.row - 1][p.col] != '#')
				w.insert(plot(p.row - 1, p.col));
			if (m.isInRange(p.row, p.col + 1) && m[p.row][p.col + 1] != '#')
				w.insert(plot(p.row , p.col + 1));
			if (m.isInRange(p.row, p.col - 1) && m[p.row][p.col - 1] != '#')
				w.insert(plot(p.row , p.col - 1));	
		}
		v = w;
		w.clear();
		
	}

	cout << v.size() << endl;


}


