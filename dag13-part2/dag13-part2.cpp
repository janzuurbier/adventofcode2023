// dag13-part2.cpp: This file contains the 'main' function. Program execution begins and ends there.
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

//the reflectionline must be different than other
int find_horizontal_reflection_line(const matrix_t& m, int other = -1) {
	int reflection_line = -1;
	for (int i = 1; i < m.size(); i++) {
		bool is_refl_line = true;
		for (int j = 0; i + j < m.size() && i - j - 1 >= 0; j++)
			if (m[i + j] != m[i - j - 1]) {
				is_refl_line = false;
				break;
			}
		if (is_refl_line && i != other) {
			reflection_line = i;
			break;
		}
	}
	return reflection_line;
}

//the reflectionline must be different than other
int find_vertical_reflection_line(const matrix_t& m, int other = -1) {
	int reflection_line = -1;
	matrix_t n = rotate_matrix(m);
	for (int i = 1; i < n.size(); i++) {
		bool is_refl_line = true;
		for (int j = 0; i + j < n.size() && i - j - 1 >= 0; j++)
			if (n[i + j] != n[i - j - 1]) {
				is_refl_line = false;
				break;
			}
		if (is_refl_line && i != other) {
			reflection_line = i;
			break;
		}
	}
	return reflection_line;
}

void flip(char& ch) {
	if (ch == '.')
		ch = '#';
	else
		ch = '.';
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
		print_matrix(m);
		cout << endl;
		int h_old = find_horizontal_reflection_line(m);
		int v_old = find_vertical_reflection_line(m);

		int rows = m.size();
		int cols = m[0].size();
		int h = h_old;
		int v = v_old;
		for (int i = 0; i < rows &&  (h == h_old || h < 0) && (v == v_old || v < 0); i++)
			for (int j = 0; j < cols && (h == h_old || h < 0) && (v == v_old || v < 0); j++) {
				flip(m[i][j]);
				h = find_horizontal_reflection_line(m, h_old);
				v = find_vertical_reflection_line(m, v_old);
				flip(m[i][j]);
			}
		if (h > 0 && h != h_old)
			row_sum += h;
		if (v > 0 && v != v_old)
			col_sum += v;
		cout << h_old << " " << v_old << endl;
		cout << h << "  " << v << endl;
		cout << endl;
	}

	cout << 100 * row_sum + col_sum << endl;
}
