// dag18-part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <sstream>
#include "..//matrix_new//matrix.h"
#include <deque>

using namespace std;

class rechthoek {
public: 
	int row;
	int col;
	int breedte;
	int hoogte;

	rechthoek(int r, int c, int h, int b) 
		: row(r), col(c), hoogte(h), breedte(b) {}

	bool contains(const rechthoek& r)const {
		bool b = r.row >= row && r.col >= col && r.row + r.hoogte <= row + hoogte;
		b = b && r.col + r.breedte <= col + breedte;
		return b;
	}

	uint64_t opp() {
		return (uint64_t)breedte * (uint64_t)hoogte;
	}
};

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

vector<rechthoek> lijnen;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	char letter;
	int getal;
	string code;

	int row = 0;
	int col = 0;
	int max_row = 0;
	int max_col = 0;
	int min_row = 0;
	int min_col = 0;

	while (input >> letter >> getal >> code) {
		string s = code.substr(2, 6);
		int i = stoi(s, nullptr, 16);
		int steps = i / 16;
		switch (i % 16) {
		case 0:
			//dir = 'R'
			lijnen.push_back(rechthoek(row, col, 1, steps + 1));
			col += steps;
			if (col > max_col)
				max_col = col;
			break;
		case 1:
			//dir = 'D' 
			lijnen.push_back(rechthoek(row, col, steps + 1, 1));
			row += steps;
			if (row > max_row)
				max_row = row;
			break;
		case 2:
			//dir = 'L'
			col -= steps;
			lijnen.push_back(rechthoek(row, col, 1, steps));
			if (col < min_col)
				min_col = col;
			break;
		case 3:
			//dir = 'U'
			row -= steps;
			lijnen.push_back(rechthoek(row, col, steps, 1));
			if (row < min_row)
				min_row =row;
			break;
		}
	}

		set<int> horizontaal;
		set<int> verticaal;
		verticaal.insert(min_row - 100);
		verticaal.insert(max_row + 100);
		horizontaal.insert(min_col - 100 );
		horizontaal.insert(max_col + 100 );
		for (rechthoek r : lijnen) {
			horizontaal.insert(r.col);
			horizontaal.insert(r.col + r.breedte );
			verticaal.insert(r.row);
			verticaal.insert(r.row + r.hoogte );
		}

		vector<int> vert;
		vector<int> hor;

		for (int i : horizontaal)
			hor.push_back(i);
		for (int i : verticaal)
			vert.push_back(i);
		

		
		int rows = vert.size() - 1;
		int cols = hor.size() - 1;

		matrix<char> m(rows, cols, '.');

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				rechthoek r(vert[i], hor[j], vert[i + 1] - vert[i], hor[j + 1] - hor[j]);
				for (rechthoek l : lijnen) {
					if (l.contains(r))
						m[i][j] = '#';
				}
			}
		}

		cout << m << endl;

		flood_fill(m, 0, 0);

		cout << m << endl;

		uint64_t sum = 0;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++) 
				if (m[i][j] == '.' || m[i][j] == '#') {
					rechthoek r(vert[i], hor[j], vert[i + 1] - vert[i], hor[j + 1] - hor[j]);
					sum += r.opp();
				}

		cout << sum << endl;



	
}

