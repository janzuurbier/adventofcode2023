#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <list>
#include <queue>
#include "../matrix_new/matrix.h"
using namespace std;

typedef  pair<int, int> tile;
class path {
public:
	vector<tile> tiles;
	bool can_go_up = true;

	bool contains(const tile& t) {
		for (tile tt : tiles)
			if (tt == t)
				return true;
		return false;
	}

	void append(tile t) {
		tiles.push_back(t);
	}

	int length() {
		return tiles.size();
	}

};

int main() {
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	matrix<char> m;
	input >> m;
	int rows = m.getRows();
	int cols = m.getCols();

	deque<path> paths;
	path p;
	p.tiles.push_back(tile(0, 1));
	p.can_go_up = true;
	paths.push_back(p);
	while (!paths.empty()) {
		path p = paths.front();
		paths.pop_front();
		tile t = p.tiles.back();
		if (t == tile(rows - 1, cols - 2)) {
			cout << p.length() - 1 << endl;
		}
		int row = t.first;
		int col = t.second;
		if (m.isInRange(row + 1, col) && m[row + 1][col] != '#' &&
			(m[row + 1][col] != '^' || p.can_go_up)) {
			tile t_nieuw = tile(row + 1, col);
			if (!p.contains(t_nieuw)) {
				path q = p;
				q.append(t_nieuw);
				if (m[row + 1][col] == 'v') q.can_go_up = true;
				if (m[row + 1][col] == '^') q.can_go_up = false;
				paths.push_back(q);
			}
		}
		if (m.isInRange(row - 1, col) && m[row - 1][col] != '#' &&
			(m[row - 1][col] != 'v' || p.can_go_up)) {
			tile t_nieuw = tile(row - 1, col);
			if (!p.contains(t_nieuw)) {
				path q = p;
				q.append(t_nieuw);
				if (m[row - 1][col] == '^') q.can_go_up = true;
				if (m[row - 1][col] == 'v') q.can_go_up = false;
				paths.push_back(q);
			}
		}
		if (m.isInRange(row, col + 1) && m[row][col + 1] != '#' &&
			(m[row][col + 1] != '<' || p.can_go_up)) {
			tile t_nieuw = tile(row, col + 1);
			if (!p.contains(t_nieuw)) {
				path q = p;
				q.append(t_nieuw);
				if (m[row][col + 1] == '>') q.can_go_up = true;
				if (m[row][col + 1] == '<') q.can_go_up = false;
				paths.push_back(q);
			}
		}
		if (m.isInRange(row, col - 1) && m[row][col - 1] != '#' &&
			(m[row][col - 1] != '>' || p.can_go_up)) {
			tile t_nieuw = tile(row, col - 1);
			if (!p.contains(t_nieuw)) {
				path q = p;
				q.append(t_nieuw);
				if (m[row][col - 1] == '<') q.can_go_up = true;
				if (m[row][col - 1] == '>') q.can_go_up = false;
				paths.push_back(q);
			}
		}
	}
}


