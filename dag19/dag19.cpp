// dag19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

class rule {
public:
	string dest;
	char letter;
	char op;
	int val;

	bool eval(char ch, int val) {
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

	workflow(string s) {
		size_t pos1 = 0;
		while (true) {
			size_t pos2 = s.find( ',', pos1);
			if (pos2 == string::npos) break;
			string r = s.substr(pos1, pos2 - pos1);
			rules.push_back(rule(s.substr(pos1, pos2 - pos1)));
			pos1 = pos2 + 1;
		}
		default_dest = s.substr(pos1 );
	}

	workflow() {}
};

class part {
public:
	int x;
	int m;
	int a;
	int s;

	bool apply_rule(rule r) {
		return r.eval('x', x) || r.eval('m', m) || r.eval('a', a) || r.eval('s',s);
	}

	string apply_workflow(workflow w) {
		for (rule r : w.rules) {
			if (this->apply_rule(r))
				return r.dest;
		}
		return w.default_dest;
	}

};


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	map<string, workflow> workflow_map;

	string line;
	while (getline(input, line)) {
		if (line.size() == 0) break;
		size_t pos = line.find('{');
		string key = line.substr(0, pos);
		string value = line.substr(pos + 1);
		value.pop_back();
		workflow w = workflow(value);
		workflow_map[key] = w;
	}

	int64_t sum = 0;
	while (getline(input, line)) {
		istringstream iss(line);
		part p;
		char ch;
		int i;
		iss >> ch >> ch>>ch;
		iss >> p.x;
		iss >> ch >> ch >> ch;
		iss >> p.m;
		iss >> ch >> ch >> ch;
		iss >> p.a;
		iss >> ch >> ch >> ch;
		iss >> p.s;
		string s = p.apply_workflow(workflow_map["in"]);
		while (s != "A"  && s != "R") {
			s = p.apply_workflow(workflow_map[s]);
		}
		if (s == "A") {
			sum += p.x + p.m + p.a + p.s;
		}		 
	}
	cout << sum << endl;


}

