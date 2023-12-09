// dag09.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

vector<int> reduce(const vector<int>& v) {
	vector<int> w;
	for (int i = 1; i < v.size(); i++)
		w.push_back(v[i] - v[i - 1]);
	return w;
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
			v = reduce(v);
		}
	}

	int sum = 0;
	for (int i : last_values)
		sum += i;
	cout << sum << endl;
}
