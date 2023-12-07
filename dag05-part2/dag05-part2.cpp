// dag05-part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
		if (line.size() == 0)
			break;
		tm.push_back(read_triple(line));	
	}
	return tm;
}


vector<int64_t> transform(vector<int64_t> ranges, transformation_map tm) {
	vector<int64_t> splitranges;
	for (int i = 0; i < ranges.size(); i += 2) {
		int64_t start = ranges[i];
		int64_t number = ranges[i + 1];
		bool handled = false;
		for (triple t : tm) {					
			if (start >= t[1] && start < t[1] + t[2] && start + number  >= t[1] + t[2]) {
				splitranges.push_back(start);
				splitranges.push_back(t[1] + t[2] - start );
				splitranges.push_back(t[1] + t[2] );
				splitranges.push_back(number - (t[1] + t[2] - start ) );
				handled = true;
			}
			else if (start < t[1] && start + number >= t[1] && start + number <= t[1] + t[2]) {
				splitranges.push_back(start);
				splitranges.push_back(t[1] - start);
				splitranges.push_back(t[1]);
				splitranges.push_back(start + number - t[1]);
				handled = true;
			}
			else if (start < t[1] && start + number >= t[1] + t[2]) {
				splitranges.push_back(start);
				splitranges.push_back(t[1] - start);
				splitranges.push_back(t[1]);
				splitranges.push_back(t[2] );
				splitranges.push_back(t[1] + t[2]);
				splitranges.push_back(number - (t[1] - start) - t[2] );
				handled = true;
				break;
			}
		}
		if (!handled) {
			splitranges.push_back(start);
			splitranges.push_back(number);
			handled = true;
		}	
	}
			
	vector<int64_t> transformed_ranges;
	for (int i = 0; i < splitranges.size(); i += 2) {
		bool handled = false;
		for (triple t : tm) {
			if (splitranges[i] >= t[1] && splitranges[i] < t[1] + t[2]) {
				transformed_ranges.push_back(splitranges[i] + t[0] - t[1]);
				transformed_ranges.push_back(splitranges[i + 1]);
				handled = true;
			}
		}
		if (!handled) {
			transformed_ranges.push_back(splitranges[i] );
			transformed_ranges.push_back(splitranges[i + 1]);
		}
	}
	return transformed_ranges;	
}


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	map_series ms;
	vector<int64_t> ranges;

	string line;
	getline(input, line);
	string s;
	int64_t i;
	istringstream in(line);
	in >> s;
	while (in >> i)
		ranges.push_back(i);
	getline(input, line);

	while (input) {
		transformation_map tm = read_map(input);
		ms.push_back(tm);
	}

	
	vector<int64_t> v = ranges;
	for (transformation_map tm : ms) {
		v = transform(v, tm);
		//for (int i = 0; i < v.size(); i += 2)
		//	cout << v[i] << "\t\t" << v[i + 1] << endl;
		//cout << endl;
	}
	
	int64_t min = INT64_MAX;
	for (int i = 0; i < v.size(); i += 2 )
		if (v[i] < min) min = v[i];

	cout << ">>>>" << min << endl;
	return 0;
}