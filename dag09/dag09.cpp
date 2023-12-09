// dag09.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

void reduce(vector<int>& v) {
	for (int i = 0; i < v.size() - 1; i++)
		v[i] = v[i+1] - v[i];
	v.pop_back();
}

bool is_all_zero(const vector<int>& v) {
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
	vector<vector<int>> rijen;
	while (getline(input, line)) {
		vector<int> v;
		istringstream in(line);
		int waarde;
		while (in >> waarde)
			v.push_back(waarde);
		rijen.push_back(v);
	}

	vector<int> last_values;
	for (vector<int> v : rijen) {
		while (!is_all_zero(v)) {
			int last = v.back();
			last_values.push_back(last);
			reduce(v);
		}
	}

	int sum = 0;
	for (int i : last_values)
		sum += i;
	cout << sum << endl;
}
