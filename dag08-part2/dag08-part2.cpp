// dag08-part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

map<string, pair<string, string>> network;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string instructions;
	getline(input, instructions);
	vector<string> start_nodes;

	string line;
	getline(input, line);

	while (getline(input, line)) {
		string key = line.substr(0, 3);
		string left = line.substr(7, 3);
		string right = line.substr(12, 3);
		network[key] = pair<string, string>(left, right);
		if (key[2] == 'A')
			start_nodes.push_back(key);
	}

	for (string node : start_nodes) {
		cout << "starting from " << node << ": ";
		int n = 0;
		int totalsteps = 0;
		while (true) {
			char instruction = instructions[n];
			if (instruction == 'L')
				node = network[node].first;
			else
				node = network[node].second;
			n++;
			if (n == instructions.size())n = 0;
			totalsteps++;
			if (node[2] == 'Z')
				break;
		}
		cout << totalsteps << " steps to reach " << node << endl;
		int m = n;
		totalsteps = 0;
		while (true) {
			char instruction = instructions[n];
			if (instruction == 'L')
				node = network[node].first;
			else
				node = network[node].second;
			n++;
			if (n == instructions.size())n = 0;
			totalsteps++;
			if (node[2] == 'Z' && n == m)
				break;
		}
		cout << "to reach te same situation again: " << totalsteps << " steps" << endl;
	}
	cout << "now calculate LCM using wolframalfa.com" << endl;
}