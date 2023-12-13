// dag13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
using namespace std;

typedef vector<string> matrix_t;

istream& read_matrix(istream& in, matrix_t& m) {
	m.clear();
	string line;
	while (getline(in, line)) {
		if (line.empty()) break;
		m.push_back(line);
	}
	return in;
}

matrix_t rotate_matrix(const matrix_t &m) {
	matrix_t n;
	int cols = m[0].size();
	int rows = m.size();
	for (int i = 0; i < cols; i++)
		n.push_back("");
	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++) {
			n[i] += m[j][i];
		}
	return n;
}

void print_matrix(const matrix_t& m) {
	for (int i = 0; i < m.size(); i++)
		cout << m[i] << endl;
}


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	int row_sum = 0;
	int col_sum = 0;

	matrix_t m;
	while (input) {
		read_matrix(input, m);
		int reflection_line = -1;
		for (int i = 1; i < m.size(); i++) {
			bool is_refl_line = true;
			for (int j = 0; i + j < m.size() && i - j - 1 >= 0; j++)
				if (m[i + j] != m[i - j - 1]){
					is_refl_line = false;
					break;
				}
			if (is_refl_line) {
				reflection_line = i;
				break;
			}
		}
		//cout << reflection_line << endl;
		if(reflection_line > 0)
			row_sum += reflection_line;
		reflection_line = -1;
		matrix_t n = rotate_matrix(m);
		for (int i = 1; i < n.size(); i++) {
			bool is_refl_line = true;
			for (int j = 0; i + j < n.size() && i - j - 1 >= 0; j++)
				if (n[i + j] != n[i - j - 1]) {
					is_refl_line = false;
					break;
				}
			if (is_refl_line) {
				reflection_line = i;
				break;
			}
		}
		//cout << reflection_line << endl;
		if(reflection_line > 0)
			col_sum += reflection_line;
	}

	cout << 100 * row_sum + col_sum << endl;
}
