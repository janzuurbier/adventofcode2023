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
	string p;

public:
	friend bool compare(const vertex& a, const vertex& b); 
	vertex(int i, int j, string p) : i(i), j(j), p(p) {}
	void mark_neighbours(); 		

};


matrix<char> m;
map<vertex, int, bool(*)(const vertex& a, const vertex& b)> dist_map;
set < vertex, bool(*)(const vertex& a, const vertex& b)> visited;
priority_queue<vertex, vector<vertex>, bool(*)(const vertex& a, const vertex& b)> todo;

bool compare(const vertex& a, const vertex& b) {
	if (a.i < b.i)
		return true;
	if (a.i == b.i && a.j < b.j)
		return true;
	if (a.i == b.i && a.j == b.j && a.p < b.p)
		return true;
	return false;
}

void vertex::mark_neighbours() {
	if (p == "") {
		dist_map[vertex(0, 1, "R")] = m[0][1] - '0';
		dist_map[vertex(1, 0, "D")] = m[1][0] - '0';
		todo.push(vertex(0, 1, "R"));
		todo.push(vertex(1, 0, "D"));
		return;
	}
	int dist = dist_map[*this];
	
		
	//mark upward
	{
		bool b = (p.back() != 'D');
		b = b && (p != "UUU");
		b = b && m.isInRange(i - 1, j);
		string q = p;
		if (q.size() == 3) q = q.substr(1);
		q = q + 'U';
		vertex v(i - 1, j, q);
		auto it = visited.find(v);
		b = b && it == visited.end();
		if (b) {
			int d = dist + m[i - 1][j] - '0';
			auto it = dist_map.find(v);
			if (it == dist_map.end()) {
				dist_map[v] = d;
				todo.push(v);
			}
			else if (d < dist_map[v]) {
				dist_map[v] = d;
			}
		}
	}
		
	//mark downwards
	{
		bool b = (p.back() != 'U');
		b = b && (p != "DDD");
		b = b && m.isInRange(i + 1, j);
		string q = p;
		if (q.size() == 3) q = q.substr(1);
		q = q + 'D';
		vertex v(i + 1, j, q);
		auto it = visited.find(v);
		b = b && it == visited.end();
		if (b) {
			int d = dist + m[i + 1][j] - '0';
			auto it = dist_map.find(v);
			if (it == dist_map.end()) {
				dist_map[v] = d;
				todo.push(v);
			}
			else if (d < dist_map[v]) {
				dist_map[v] = d;
			}
		}
	}
		
		//mark right
		
	{
		bool b = (p.back() != 'L');
		b = b && (p != "RRR");
		b = b && m.isInRange(i, j + 1);
		string q = p;
		if (q.size() == 3) q = q.substr(1);
		q = q + 'R';
		vertex v(i, j + 1, q);
		auto it = visited.find(v);
		b = b && it == visited.end();
		if (b) {
			int d = dist + m[i][j + 1] - '0';
			auto it = dist_map.find(v);
			if (it == dist_map.end()) {
				dist_map[v] = d;
				todo.push(v);
			}
			else if (d < dist_map[v]) {
				dist_map[v] = d;
			}
		}
	}
		
	// mark left 
	{
		bool b = (p.back() != 'R');
		b = b && (p != "LLL");
		b = b && m.isInRange(i, j - 1);
		string q = p;
		if (q.size() == 3) q = q.substr(1);
		q = q + 'R';
		vertex v(i, j - 1, q);
		auto it = visited.find(v);
		b = b && it == visited.end();
		if (b) {
			int d = dist + m[i][j - 1] - '0';
			auto it = dist_map.find(v);
			if (it == dist_map.end()) {
				dist_map[v] = d;
				todo.push(v);
			}
			else if (d < dist_map[v]) {
				dist_map[v] = d;
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

	input >> m;
	int rows = m.getRows();
	int cols = m.getCols();

	dist_map = map<vertex, int, bool(*)(const vertex& a, const vertex& b)>(compare);
	visited = set < vertex, bool(*)(const vertex& a, const vertex& b)>(compare);
	todo = priority_queue<vertex, vector<vertex>, bool(*)(const vertex& a, const vertex& b)>
		([](const vertex& a, const vertex& b) { return dist_map[a] > dist_map[b]; });
	todo.push(vertex(0, 0, ""));
	
	int aantal = 0;
	while (!todo.empty() ) {
		aantal++;
		vertex v = todo.top();
		//cout << v.i << " " << v.j << " " << v.p << " " << dist_map[v] << endl;
		todo.pop();
		
		if (v.i == cols - 1 && v.j == rows - 1) {
			cout << dist_map[v] << endl;
			break;
		}
		v.mark_neighbours();
		visited.insert(v);
	}
}


	
