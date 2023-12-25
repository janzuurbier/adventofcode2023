#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <deque>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

map<string, set<string>> wiring_map;
struct wire;
map<wire, int> intensity;

struct wire {
	string a;
	string b;

	wire(string p, string q) {
		if (p < q) {
			a = p;
			b = q;
		}
		else {
			a = q;
			b = p;
		}
	}

	friend bool operator<(const wire& v, const wire& w) {
		return v.a < w.a || v.a == w.a && v.b < w.b;
	}
};

set<string> find_group(string s) {
	set<string> group;
	deque<string> d;
	d.push_back(s);
	group.insert(s);
	while (!d.empty()) {
		string s = d.front();
		d.pop_front();
		for (string t : wiring_map[s]) {
			if (group.insert(t).second) {
				d.push_back(t);
			}
		}
	}
	return group;
}

void remove_connection(const wire& w) {
		wiring_map[w.a].erase(wiring_map[w.a].find(w.b));
		wiring_map[w.b].erase(wiring_map[w.b].find(w.a));
		cout << "removed " << w.a << "-" << w.b << endl;
}


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;
	while (getline(input, line)) {
		istringstream is(line);
		string s;
		is >> s;
		s = s.substr(0, 3);
		string t;
		while (is >> t) {
			wiring_map[s].insert(t);
			wiring_map[t].insert(s);
		}
	}

	vector<string> components;
	for (auto it = wiring_map.begin(); it!= wiring_map.end(); it++)
		components.push_back(it->first);
	set<wire> connections;
	for (auto it = wiring_map.begin(); it != wiring_map.end(); it++) {
		string a = it->first;
		for (string b : it->second) {
			connections.insert(wire(a, b));
		}
			
	}

	cout << components.size() << endl;
	cout << connections.size() << endl;

	for(string a : components){
		deque<string> d;
		set<string> visited;
		d.push_back(a);
		visited.insert(a);
		while (!d.empty()) {
			string s = d.front();
			d.pop_front();
			for (string t : wiring_map[s]) {
				if (visited.insert(t).second) {
					d.push_back(t);
					intensity[wire(s, t)]++;
				}
			}
		}
	}

	vector<wire> wires;
	for (wire w : connections)
		wires.push_back(w);
	sort(wires.begin(), wires.end(), [](const wire& v, const wire& w) {return intensity[v] > intensity[w]; });
	for (int i = 0; i < 10; i++)
		cout << wires[i].a << "-" << wires[i].b << ": " << intensity[wires[i]] << endl;
	
	remove_connection(wires[0]);
	remove_connection(wires[1]);
	remove_connection(wires[2]);

	int group_size = find_group(components.front()).size();
	cout << group_size * (components.size() - group_size) << endl;

	
}

