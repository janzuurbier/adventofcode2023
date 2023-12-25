// dag19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <set>
#include <algorithm>
#include <list>
using namespace std;

class rule {
public:
	string dest;
	char letter;
	char op;
	int val;

	bool eval(char ch, int val)const {
		if (ch != letter)
			return false;
		if (op == '>')
			return val > this->val;
		if (op == '<')
			return val < this->val;
		return true;
	}

	string get_dest() {
		return dest;
	}

	rule(string s) {
		letter = s[0];
		op = s[1];
		size_t pos = s.find(':');
		val = stoi(s.substr(2, pos - 1));
		dest = s.substr(pos + 1);
	}
};

class workflow {
public:
	vector<rule> rules;
	string default_dest;
	string key;

	workflow(string s) {
		size_t pos1 = 0;
		while (true) {
			size_t pos2 = s.find(',', pos1);
			if (pos2 == string::npos) break;
			string r = s.substr(pos1, pos2 - pos1);
			rules.push_back(rule(s.substr(pos1, pos2 - pos1)));
			pos1 = pos2 + 1;
		}
		default_dest = s.substr(pos1);
	}

	workflow() {}

	bool operator<(const workflow& w)const {
		return key < w.key;
	}
};

class part {
public:
	int x;
	int m;
	int a;
	int s;

	part(int x, int m, int a, int s) : x(x), m(m), a(a), s(s) {}

	bool apply_rule(const rule& r) {
		return r.eval('x', x) || r.eval('m', m) || r.eval('a', a) || r.eval('s', s);
	}

	string apply_workflow(const workflow& w) {
		for (const rule& r : w.rules) {
			if (this->apply_rule(r))
				return r.dest;
		}
		return w.default_dest;
	}

};

class conditie {
public:
	int min_x = 1;
	int max_x = 4000;
	int min_a = 1;
	int max_a = 4000;
	int min_m = 1;
	int max_m = 4000;
	int min_s = 1;
	int max_s = 4000;

	void kleiner_dan(char ch, int to) {
		switch (ch) {
		case 'x':
			if (to < max_x)
				max_x = to;
			break;
		case 'm':
			if (to < max_m)
				max_m = to;
			break;
		case 'a':
			if (to < max_a)
				max_a = to;
			break;
		case 's':
			if (to < max_s)
				max_s = to;
			break;
		}
	}

	void groter_dan(char ch, int from) {
		switch (ch) {
		case 'x':
			if (from > min_x)
				min_x = from;
			break;
		case 'm':
			if (from > min_m)
				min_m = from;
			break;
		case 'a':
			if (from > min_a)
				min_a = from;
			break;
		case 's':
			if (from > min_s)
				min_s = from;
			break;
		}
	}

	friend ostream& operator<<(ostream& os, const conditie& c) {
		os << "x ligt tussen " << c.min_x << " en " << c.max_x << endl;
		os << "m ligt tussen " << c.min_m << " en " << c.max_m << endl;
		os << "a ligt tussen " << c.min_a << " en " << c.max_a << endl;
		os << "s ligt tussen " << c.min_s << " en " << c.max_s << endl;
		return os;
	}

	void en(const conditie& c) {
		min_x = min_x > c.min_x ? min_x : c.min_x;
		min_m = min_m > c.min_m ? min_m : c.min_m;
		min_a = min_a > c.min_a ? min_a : c.min_a;
		min_s = min_s > c.min_s ? min_s : c.min_s;
		max_x = max_x < c.max_x ? max_x : c.max_x;
		max_m = max_m < c.max_m ? max_m : c.max_m;
		max_a = max_a < c.max_a ? max_a : c.max_a;
		max_s = max_s < c.max_s ? max_s : c.max_s;
	}
};

class condities {
public:
	list<conditie> l;

	condities(const condities& cs) : l(cs.l) {}

	condities() {}


	void add(const condities& cs) {
		for (const conditie& c : cs.l)
			add(c);
	}

	void add(const conditie& c) {
		l.push_back(c);

	}

	condities en(const conditie& c) {
		for (conditie& a : l)
			a.en(c);
		return *this;
	}

};

map<string, set<workflow> >find_workflows;

condities find_condities(string dest) {
	if (dest == "in") {
		condities cs;
		cs.add(conditie());
		return cs;
	}

	condities ret;
	set<workflow> wfs = find_workflows[dest];


	for (const workflow& w : wfs) {
		condities thecondities = find_condities(w.key);


		conditie c;
		for (rule r : w.rules) {
			if (r.dest == dest) {
				conditie d = c;
				if (r.op == '<')
					d.kleiner_dan(r.letter, r.val - 1);
				else
					d.groter_dan(r.letter, r.val + 1);
				condities anothercondities = thecondities;
				anothercondities.en(d);
				ret.add(anothercondities);
			}
			if (r.op == '<')
				c.groter_dan(r.letter, r.val);
			else
				c.kleiner_dan(r.letter, r.val);
		}
		if (w.default_dest == dest) {
			for (rule r : w.rules)
				if (r.op == '<')
					c.groter_dan(r.letter, r.val);
				else
					c.kleiner_dan(r.letter, r.val);
			thecondities.en(c);
			ret.add(thecondities);
		}
	}
	return ret;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	map<string, workflow> workflow_map;
	vector<workflow> workflows;

	string line;
	while (getline(input, line)) {
		if (line.size() == 0) break;
		size_t pos = line.find('{');
		string key = line.substr(0, pos);
		string value = line.substr(pos + 1);
		value.pop_back();
		workflow w = workflow(value);
		w.key = key;
		workflow_map[key] = w;
		workflows.push_back(w);
	}

	for (const workflow& w : workflows) {
		find_workflows[w.default_dest].insert(w);
		for (rule r : w.rules)
			find_workflows[r.dest].insert(w);
	}

	condities thecondities = find_condities("A");

	uint64_t sum = 0;
	for (const conditie& c : thecondities.l) {
		uint64_t prd = 1;
		prd *= (c.max_x - c.min_x + 1);
		prd *= (c.max_m - c.min_m + 1);
		prd *= (c.max_a - c.min_a + 1);
		prd *= (c.max_s - c.min_s + 1);
		sum += prd;
	}
	cout << sum << endl;

	condities thecondities1 = find_condities("R");

	uint64_t sum1 = 0;
	for (const conditie& c : thecondities1.l) {
		uint64_t prd = 1;
		prd *= (c.max_x - c.min_x + 1);
		prd *= (c.max_m - c.min_m + 1);
		prd *= (c.max_a - c.min_a + 1);
		prd *= (c.max_s - c.min_s + 1);
		sum1 += prd;
	}
	cout << sum1 << endl;
	cout << sum + sum1 << endl;

}

