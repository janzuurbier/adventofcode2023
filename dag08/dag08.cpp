// dag08.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
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

	string line;
	getline(input, line);

	while (getline(input, line)) {
		string key = line.substr(0, 3);
		string left = line.substr(7, 3);
		string right = line.substr(12, 3);
		network[key] = pair<string, string>(left, right);
	}
	string node = "AAA";
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
		if (node == "ZZZ")
			break;
		
	}

	cout << totalsteps  << endl;

}



