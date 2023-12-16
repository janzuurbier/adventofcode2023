// dag16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <set>
#include "../matrix_new/matrix.h"
using namespace std;

enum dir_t {NONE, LEFT, RIGHT, UP, DOWN };

struct beam_head {
	int r;
	int c;
	dir_t dir;

	beam_head(int r, int c, dir_t d) : r(r), c(c), dir(d) {}
};

matrix<char> m;
deque<beam_head> beam_heads;
matrix<set<dir_t>> history;

void go_left(const matrix<char>& m, matrix<set<dir_t>>& h, beam_head& b) {
	if (m.isInRange(b.r, b.c - 1)) {
		auto ret = h[b.r ][b.c - 1].insert(LEFT);
		if(ret.second) beam_heads.push_back(beam_head(b.r,b.c - 1, LEFT));
	}
}

void go_right(const matrix<char>& m, matrix<set<dir_t>>& h,  beam_head& b) {
	if (m.isInRange(b.r, b.c + 1)) {
		auto ret = h[b.r ][b.c + 1].insert(RIGHT);
		if (ret.second) beam_heads.push_back(beam_head(b.r, b.c + 1, RIGHT));
	}
}

void go_up(const matrix<char>& m, matrix<set<dir_t>>& h, beam_head& b) {
	if (m.isInRange(b.r - 1, b.c )) {
		auto ret = h[b.r - 1][b.c ].insert(UP);
		if (ret.second) beam_heads.push_back(beam_head(b.r - 1, b.c, UP));
	}
}

void go_down(const matrix<char>& m, matrix<set<dir_t>>& h, beam_head& b) {
	if (m.isInRange(b.r + 1, b.c )) {
		auto ret = h[b.r + 1][b.c].insert(DOWN);
		if (ret.second) beam_heads.push_back(beam_head(b.r + 1, b.c, DOWN));
	}
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	input >> m;
	int rows = m.getRows();
	int cols = m.getCols();

	history = matrix<set<dir_t>>(rows, cols, set<dir_t>());
	history[0][0].insert(RIGHT);

	beam_heads.push_back(beam_head(0, 0, RIGHT));

	while (!beam_heads.empty()) {
		beam_head b = beam_heads.front();
		beam_heads.pop_front();
		switch (m[b.r][b.c]) {
		case '.':
			switch (b.dir) {
			case UP:
				go_up(m, history, b);
				break;
			case DOWN:
				go_down(m, history, b);
				break;
			case LEFT:
				go_left(m, history, b);
				break;
			case RIGHT:
				go_right(m, history, b);
				break;
			}
			break;
		case '|':
			switch (b.dir) {
			case UP:
				go_up(m, history, b);
				break;
			case DOWN:
				go_down(m, history, b);
				break;
			case LEFT:
				go_up(m, history, b);
				go_down(m, history, b);
				break;
			case RIGHT:
				go_up(m, history, b);
				go_down(m, history, b);
				break;
			}
			break;
		case '-':
			switch (b.dir) {
			case UP:
				go_left(m, history, b);
				go_right(m, history, b);
				break;
			case DOWN:
				go_left(m, history, b);
				go_right(m, history, b);
				break;
			case LEFT:
				go_left(m, history, b);
				break;
			case RIGHT:
				go_right(m, history, b);
				break;
			}
			break;
		case '\\':
			switch (b.dir) {
			case UP:
				go_left(m, history, b);
				break;
			case DOWN:
				go_right(m, history, b);
				break;
			case LEFT:
				go_up(m, history, b);
				break;
			case RIGHT:
				go_down(m, history, b);
				break;
			}
			break;
		case '/':
			switch (b.dir) {
			case UP:
				go_right(m, history, b);
				break;
			case DOWN:
				go_left(m, history, b);
				break;
			case LEFT:
				go_down(m, history, b);
				break;
			case RIGHT:
				go_up(m, history, b);
				break;
			}
		}
	}//while

	int aantal = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (!history[i][j].empty())
				aantal++;
	cout << aantal << endl;
}

	
