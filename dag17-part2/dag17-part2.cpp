#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <list>
#include <queue>

#include "../matrix_new/matrix.h"
using namespace std;


class vertex {
public:
	int i;
	int j;
	char dir;
	int aantal;

public:
	friend bool compare(const vertex& a, const vertex& b);
	vertex(int i, int j, char d, int a) : i(i), j(j), dir(d), aantal(a) {}
	void mark_neighbours();

};


matrix<int> m;
map<vertex, int, bool(*)(const vertex& a, const vertex& b)> dist_map;
set < vertex, bool(*)(const vertex& a, const vertex& b)> visited;
priority_queue<vertex, vector<vertex>, bool(*)(const vertex& a, const vertex& b)> todo;
//list<vertex> todo;

bool compare(const vertex& a, const vertex& b) {
	if (a.i < b.i)
		return true;
	if (a.i == b.i && a.j < b.j)
		return true;
	if (a.i == b.i && a.j == b.j && a.aantal < b.aantal)
		return true;
	if (a.i == b.i && a.j == b.j && a.aantal == b.aantal && a.dir < b.dir)
		return true;
	return false;
}

void vertex::mark_neighbours() {
	
	int dist = dist_map[*this];

		//mark downwards
	if (4 <= aantal && aantal < 10) {		
		vertex v(i + 1, j, 'D', aantal + 1);
		if(m.isInRange(i+1,j) && visited.count(v)== 0 && dir == 'D'){
			int d = dist + m[i + 1][j];
			if (dist_map.count(v) == 0) {
				dist_map[v] = d;
				todo.push(v);
			}
			else {
				if(d < dist_map[v]) dist_map[v] = d;
			}
		}
	}
	if (4 <= aantal && aantal <= 10) {
		vertex v(i + 4, j, 'D', 4);
		if (m.isInRange(i + 4, j) && dir != 'D' && dir != 'U' && visited.count(v) == 0) {
			int d = dist + m[i+1][j] + m[i + 2][j] + m[i + 3][j] +  m[i + 4][j];
			if (dist_map.count(v) == 0) {
				dist_map[v] = d;
				todo.push(v);
			}
			else {
				if (d < dist_map[v]) dist_map[v] = d;
			}
		}
	}

	//mark upwards
	if (4 <= aantal && aantal < 10) {
		vertex v(i - 1, j, 'U', aantal + 1);
		if (m.isInRange(i - 1, j) && visited.count(v) == 0 && dir == 'U') {
			int d = dist + m[i - 1][j];
			if (dist_map.count(v) == 0) {
				dist_map[v] = d;
				todo.push(v);
			}
			else {
				if(d < dist_map[v]) dist_map[v] = d;
			}
		}
	}
	if (4 <= aantal && aantal <= 10) {
		vertex v(i - 4, j, 'U', 4);
		if (m.isInRange(i - 4, j) && dir != 'D' && dir != 'U' && visited.count(v) == 0) {
			int d = dist + m[i - 1][j] + m[i - 2][j] + m[i - 3][j] + m[i - 4][j]; 
			if (dist_map.count(v) == 0) {
				dist_map[v] = d;
				todo.push(v);
			}
			else {
				if(d < dist_map[v]) dist_map[v] = d;
			}
		}
	}

	//mark left
	if (4 <= aantal && aantal < 10) {
		vertex v(i, j - 1, 'L', aantal + 1);
		if (m.isInRange(i , j - 1) && visited.count(v) == 0 && dir == 'L') {
			int d = dist + m[i ][j - 1];
			if (dist_map.count(v) == 0) {
				dist_map[v] = d;
				todo.push(v);
			}
			else {
				if(d < dist_map[v]) dist_map[v] = d;
			}
		}
	}
	if (4 <= aantal && aantal <= 10) {
		vertex v(i , j - 4, 'L', 4);
		if (m.isInRange(i , j - 4) && dir != 'L' && dir != 'R' && visited.count(v) == 0) {
			int d = dist + m[i ][j - 1] + m[i ][j - 2] + m[i][j - 3] + m[i ][j - 4];
			if (dist_map.count(v) == 0) {
				dist_map[v] = d;
				todo.push(v);
			}
			else {
				if(d < dist_map[v]) dist_map[v] = d;
			}
		}
	}

	//mark right
	if (4 <= aantal && aantal < 10) {
		vertex v(i, j + 1, 'R', aantal + 1);
		if (m.isInRange(i, j + 1) && visited.count(v) == 0 && dir == 'R') {
			int d = dist + m[i][j + 1];
			if (dist_map.count(v) == 0) {
				dist_map[v] = d;
				todo.push(v);
			}
			else {
				if (d < dist_map[v]) dist_map[v] = d;
			}
		}
	}
	if (4 <= aantal && aantal <= 10) {
		vertex v(i, j + 4, 'R', 4);
		if (m.isInRange(i, j + 4) && dir != 'L' && dir != 'R' && visited.count(v) == 0) {
			int d = dist + m[i][j + 1] + m[i][j + 2] + m[i][j + 3] + m[i][j + 4];
			if (dist_map.count(v) == 0) {
				dist_map[v] = d;
				todo.push(v);
			}
			else {
				if (d < dist_map[v]) dist_map[v] = d;
			}
		}
	}	
}

int main() {
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	matrix<char> temp_matrix;
	input >> temp_matrix;
	int rows = temp_matrix.getRows();
	int cols = temp_matrix.getCols();
	m = matrix<int>(rows, cols, 0);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			m[i][j] = temp_matrix[i][j] - '0';

	dist_map = map<vertex, int, bool(*)(const vertex& a, const vertex& b)>(compare);
	visited = set < vertex, bool(*)(const vertex& a, const vertex& b)>(compare);
	todo = priority_queue<vertex, vector<vertex>, bool(*)(const vertex& a, const vertex& b)>
		([](const vertex& a, const vertex& b) { return dist_map[a] > dist_map[b]; });
	
	todo.push(vertex(0, 0, 'X', 10));

	int aantal = 0;
	while (!todo.empty()) {
		aantal++;
		//todo.sort([](const vertex a, const vertex& b) { return dist_map[a] < dist_map[b]; });
		vertex v = todo.top();
		todo.pop();
		//cout << aantal << ": " << v.i << " " << v.j << " " << v.dir << " " <<  v.aantal << " " << dist_map[v] << endl;
		
		if (v.i == rows - 1 && v.j == cols - 1) {
			cout << ">>>>>>>>>>" << dist_map[v] << endl;
			break;
		}
		v.mark_neighbours();
		auto x =visited.insert(v);
	}
}



