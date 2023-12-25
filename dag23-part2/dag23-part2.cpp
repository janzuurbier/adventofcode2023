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
map<pair<tile, tile>, int> dist_map;

class path {
public:
	vector<tile> tiles;
	int length = 0;

	bool contains(const tile& t)const {
		for (const tile& tt : tiles)
			if (tt == t)
				return true;
		return false;
	}

	void append(const tile& t, int delta = 1) {
		if (!tiles.empty())
			length += delta;
		tiles.push_back(t);
	}

	int get_length() {
		return tiles.size();
	}

	tile& back() {
		return tiles[tiles.size() - 1];
	}

	friend ostream& operator<<(ostream& os, const path& p) {
		for (tile t : p.tiles)
			os << "(" << t.first << ", " << t.second << ") ";
		return os;
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

	vector<tile> tiles;


	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			int aantal = 0;
			if (m.isInRange(i + 1, j) && m[i + 1][j] != '#')
				aantal++;
			if (m.isInRange(i - 1, j) && m[i - 1][j] != '#')
				aantal++;
			if (m.isInRange(i, j + 1) && m[i][j + 1] != '#')
				aantal++;
			if (m.isInRange(i, j - 1) && m[i][j - 1] != '#')
				aantal++;
			if (aantal != 2 && m[i][j] != '#')
				tiles.push_back(tile(i, j));
		}

	for (tile t : tiles) {
		int i = t.first;
		int j = t.second;
		vector<path> paths;
		if (m.isInRange(i + 1, j) && m[i + 1][j] != '#') {
			path p; p.append(tile(i, j)); p.append(tile(i + 1, j)); paths.push_back(p);
		}
		if (m.isInRange(i - 1, j) && m[i - 1][j] != '#') {
			path p; p.append(tile(i, j)); p.append(tile(i - 1, j)); paths.push_back(p);
		}
		if (m.isInRange(i, j + 1) && m[i][j + 1] != '#') {
			path p; p.append(tile(i, j)); p.append(tile(i, j + 1)); paths.push_back(p);
		}
		if (m.isInRange(i, j - 1) && m[i][j - 1] != '#') {
			path p; p.append(tile(i, j)); p.append(tile(i, j - 1)); paths.push_back(p);
		}

		for (path p : paths) {
			tile start = p.tiles[0];
			tile t = p.back();
			int i = t.first;
			int j = t.second;
			bool gereed = false;
			while (!gereed) {
				if (m.isInRange(i + 1, j) && m[i + 1][j] != '#' && !p.contains(tile(i + 1, j))) {
					p.append(tile(i + 1, j)); i++;
				}
				else if (m.isInRange(i - 1, j) && m[i - 1][j] != '#' && !p.contains(tile(i - 1, j))) {
					p.append(tile(i - 1, j)); i--;
				}
				else if (m.isInRange(i, j + 1) && m[i][j + 1] != '#' && !p.contains(tile(i, j + 1))) {
					p.append(tile(i, j + 1)); j++;
				}
				else if (m.isInRange(i, j - 1) && m[i][j - 1] != '#' && !p.contains(tile(i, j - 1))) {
					p.append(tile(i, j - 1)); j--;
				}

				for (const tile& tt : tiles)
					if (tt.first == p.back().first && tt.second == p.back().second) {
						gereed = true;
						break;
					}
			}
			dist_map[pair<tile, tile>(start, p.back())] = p.length;
			cout << "(" << start.first << ", " << start.second << ")";
			cout << "(" << p.back().first << ", " << p.back().second << ")";
			cout << ": " << dist_map[pair<tile, tile>(start, p.back())] << endl;
		}
	}

	map<tile, vector<tile>> connected_tiles;
	for (tile t : tiles)
		for (tile tt : tiles)
			if (dist_map.count(pair<tile, tile>(t, tt)) == 1)
				connected_tiles[t].push_back(tt);

	deque<path> paths;
	path p;
	p.append(tile(0, 1));
	paths.push_back(p);
	int max = 0;
	while (!paths.empty()) {
		path p = paths.front();
		paths.pop_front();
		tile t = p.tiles.back();
		if (t == tile(rows - 1, cols - 2)) {
			//cout << p.length << "   " << p.tiles.size() << endl;
			if (p.length > max)
				max = p.length;
		}
		else for (tile tt : connected_tiles[t])
			if (!p.contains(tt)) {
				path q = p;
				q.append(tt, dist_map[pair<tile, tile>(q.back(), tt)]);
				paths.push_back(q);
			}
	}
	cout << ">>>>>>>>> " << max;
}


