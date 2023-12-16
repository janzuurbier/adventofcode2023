// dag15-part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
using namespace std;

int myhash(string s) {
	uint8_t current_value = 0;
	for (char ch : s) {
		current_value += (uint8_t)ch;
		current_value *= 17;
	}
	return current_value;
}

typedef list<pair<string, int>> box;
map<int, box> boxes;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string s;
	while (getline(input, s, ',')) {
		if (s[s.size() - 1] == '-') {
			string label = s.substr(0, s.size() - 1);
			box& b = boxes[myhash(label)];
			auto it = b.begin();
			while (it != b.end() && it->first != label) it++;
			if (it != b.end()) b.erase(it);
		}
		else {
			size_t pos = s.find_last_of('=');
			string label = s.substr(0,s.size() - 2);
			int focal_length = stoi(s.substr(pos + 1));
			box& b = boxes[myhash(label)];
			auto it = b.begin();
			while (it != b.end() && it->first != label) it++;
			if (it != b.end()) it = b.erase(it);
			b.emplace(it, label, focal_length);
		}
	}

	uint64_t sum = 0;
	for (auto it1 = boxes.begin(); it1 != boxes.end(); ++it1) {
		
		int p = it1->first + 1;
		int q = 0;
		box b = it1->second;
		for (auto it2 = b.begin(); it2 != b.end(); ++it2) {
			q++;
			sum += p * q * it2->second;
		}
	}
	cout << sum << endl;
}
