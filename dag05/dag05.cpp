// dag05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
using namespace std;

typedef array<int64_t, 3> triple;
typedef vector<triple> transformation_map;
typedef vector<transformation_map> map_series;

triple read_triple(string line) {
	istringstream in(line);
	triple t;
	in >> t[0] >> t[1] >> t[2];
	return t;
}

transformation_map read_map(ifstream& in) {
	transformation_map tm;
	string line;
	getline(in, line);
	while (getline(in, line)) {
		tm.push_back(read_triple(line));
		if (line.size() == 0)
			break;
	}
	return tm;
}

int64_t transform(int64_t i, transformation_map tm) {
	for (triple t : tm) {
		if (i >= t[1] && i < t[1] + t[2])
			return t[0] + i - t[1];
	}
	return i;
}

int64_t get_location(int64_t i, map_series ms) {
	for (transformation_map tm : ms) 
		i = transform(i, tm);
	return i;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	map_series ms;
	vector<int64_t> seeds;

	string line;
	getline(input, line);
	string s;
	int64_t i;
	istringstream in(line);
	in >> s;
	while (in >> i)
		seeds.push_back(i);

	getline(input, line);

	while (input) {
		transformation_map tm = read_map(input);
		ms.push_back(tm);
	}

	int64_t min_location = INT64_MAX;
	for (int64_t seed : seeds) {
		int64_t location = get_location(seed, ms);
		if (location < min_location)
			min_location = location;
	}
	cout << min_location << endl;
	return 0;
}



