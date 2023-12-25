#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <sstream>
#include "..\matrix_new\matrix.h"
#include <set>
#include <iomanip>
using namespace std;

struct plot {
	int row;
	int col;

	plot(int r, int c) : row(r), col(c) {}

	friend bool operator<(const plot& p, const plot& q) { return p.row < q.row || p.row == q.row && p.col < q.col; }
};

int mod(int x, int m) {
	int ret = x % m;
	return ret < 0 ? m + ret : ret;

}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	matrix <char> m;
	input >> m;
	int rows = m.getRows();
	int cols = m.getCols();

	int r_start = 0;
	int c_start = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			if (m[i][j] == 'S') {
				r_start = i;
				c_start = i;
			}
		}

	set< plot> v;
	v.insert(plot(r_start, c_start));
	set <plot> w;
	int oud = 0;
	for (int i = 1; i <= 1000; i++) {
		for (plot p : v) {
			if (m[mod((p.row + 1), rows)][mod(p.col, cols)] != '#')
				w.insert(plot(p.row + 1, p.col));
			if (m[mod(p.row - 1, rows)][mod(p.col, cols)] != '#')
				w.insert(plot(p.row - 1, p.col));
			if (m[mod(p.row, rows)][mod(p.col + 1, cols)] != '#')
				w.insert(plot(p.row, p.col + 1));
			if (m[mod(p.row, rows)][mod(p.col - 1, cols)] != '#')
				w.insert(plot(p.row, p.col - 1));
		}
		v = w;
		w.clear();

		matrix<int> n(19, 19, 0);

		for (const plot& p : v) {
			for (int a = -9; a < 9; a++)
				for (int b = -9; b < 9; b++) {
					if (a * rows <= p.row && p.row < a * rows + rows && b * cols <= p.col && p.col < b * cols + cols)
						n[a + 9][b + 9]++;

				}
		}

		if (i % 131 == 65) {
			cout << i << ": " << v.size() << endl;
			for (int a = 0; a < n.getRows(); a++) {
				for (int b = 0; b < n.getCols(); b++)
					cout << setw(5) << n[a][b];
				cout << endl;
			}
		}
	}

}

