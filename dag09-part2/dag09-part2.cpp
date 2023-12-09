// dag09-part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <deque>
using namespace std;

deque<int> reduce(const deque<int>& v) {
	deque<int> w;
	for (int i = 1; i < v.size(); i++)
		w.push_back(v[i] - v[i - 1]);
	return w;
}

bool is_all_zero(const deque<int>& v) {
	for (int i : v)
		if (i != 0)
			return false;
	return true;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;
	vector<deque<int>> rijen;
	while (getline(input, line)) {
		deque<int> v;
		istringstream in(line);
		int waarde;
		while (in >> waarde)
			v.push_back(waarde);
		rijen.push_back(v);
	}

	int sum = 0;
	for (deque<int> v : rijen) {
		vector<int> first_values;
		while (!is_all_zero(v)) {
			int first = v.front();
			first_values.push_back(first);
			v = reduce(v);
		}
		int x = 0;
		for (int i = first_values.size() - 1; i >= 0; i--) {
			x = first_values[i] - x;		
		}
		sum += x;
	}
		
	cout << sum << endl;
}
