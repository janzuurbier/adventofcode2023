
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class cube {
public:
	int x;
	int y;
	int z;

	friend istream& operator>>(istream& in, cube& c) {
		char komma;
		in >> c.x >> komma >> c.y >> komma >> c.z;
		return in;
	}

	friend ostream& operator<<(ostream& os, const cube& c) {
		char komma = ',';
		os << c.x << komma << c.y << komma << c.z;
		return os;
	}

	bool operator<(const cube& c)const {
		if (z < c.z)
			return true;
		if (z == c.z && x < c.x)
			return true;
		if (z == c.z && x == c.x && y < c.y)
			return true;
		return false;
	}

	bool operator==(const cube& c)const {

		return x == c.x && y == c.y && z == c.z;
	}
};

class brick {
public:
	cube end1;
	cube end2;

	friend istream& operator>>(istream& in, brick& b) {
		char tilde;
		in >> b.end1 >> tilde >> b.end2;
		return in;
	}

	friend ostream& operator<<(ostream& os, const brick& b) {
		char tilde = '~';
		os << b.end1 << tilde << b.end2;
		return os;
	}

	bool operator<(const brick& b) const {
		if (end1 < b.end1)
			return true;
		if (end1 == b.end1 && end2 < b.end2)
			return true;
		return false;
	}

	bool operator==(const brick& b)const {
		return end1 == b.end1 && end2 == b.end2;
	}

	bool could_support(const brick& b) const {
		int min_x, max_x;
		if (end1.x < end2.x) {
			min_x = end1.x;
			max_x = end2.x;
		}
		else {
			min_x = end2.x;
			max_x = end1.x;
		}

		int min_y, max_y;
		if (end1.y < end2.y) {
			min_y = end1.y;
			max_y = end2.y;
		}
		else {
			min_y = end2.y;
			max_y = end1.y;
		}

		int min_x_b, max_x_b;
		if (b.end1.x < b.end2.x) {
			min_x_b = b.end1.x;
			max_x_b = b.end2.x;
		}
		else {
			min_x_b = b.end2.x;
			max_x_b = b.end1.x;
		}

		int min_y_b, max_y_b;
		if (b.end1.y < b.end2.y) {
			min_y_b = b.end1.y;
			max_y_b = b.end2.y;
		}
		else {
			min_y_b = b.end2.y;
			max_y_b = b.end1.y;
		}

		if (min_y_b > max_y || max_y_b < min_y)
			return false;
		if (min_x_b > max_x || max_x_b < min_x)
			return false;
		return true;
	}

	bool supports(const brick& b)const {
		if (b.end1.z != end2.z + 1)
			return false;
		return could_support(b);
	}

};

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	brick b;
	vector<brick> bricks;
	while (input >> b) {
		bricks.push_back(b);
	}

	for (brick& b : bricks) {
		if (b.end1.z > b.end2.z) {
			cube c = b.end1;
			b.end1 = b.end2;
			b.end2 = c;
		}
	}

	sort(bricks.begin(), bricks.end());

	
	bool changed = true;
	while (changed) {
		cout << '.';
		changed = false;
		if (bricks[0].end1.z > 1) {
			bricks[0].end1.z--;
			bricks[0].end2.z--;
			changed = true;
			continue;

		}
		for (int i = 1; i < bricks.size(); i++) {
			bool b = bricks[i].end1.z > 1;
			for (int j = 0; j < i; j++) {
				if (bricks[j].supports(bricks[i]))
					b = false;
			}
			if (b) {
				bricks[i].end1.z--;
				bricks[i].end2.z--;
				changed = true;
			}
		}
	}
	cout << endl;
	
	map<brick, vector<brick>> supported_bricks;
	map<brick, list<brick>> is_supported_by;

	for (const brick& b : bricks) {
		for (const brick& c : bricks) {
			if (b.supports(c)) {
				supported_bricks[b].push_back(c);
				is_supported_by[c].push_back(b);
			}
		}
	}

	int aantal = 0;
	for (brick b : bricks) {
		map<brick, list<brick>> isb = is_supported_by;
		map<brick, vector<brick>> sb = supported_bricks;
		set<brick> v;
		v.insert(b);
		bool changed = true;
		while (changed) {
			changed = false;
			for(brick b : v)
				for (brick bb : sb[b])
					isb[bb].remove(b);
			for (brick b : v)
				for (brick bb : sb[b]) 
					if (isb[bb].size() == 0) {
						if (v.insert(bb).second)
							changed = true;
					}
		}
		aantal += v.size() - 1;
	}
	cout << aantal << endl;	
}

