#pragma once
#ifndef MATRIXH
#define MATRIXH

#include <vector>
#include <iostream>
#include <sstream>
using namespace std;


template <class T>
class matrix {
private:
	vector<vector<T>> values;
	int rows = 0;
	int cols = 0;
	T temp;

public:
	matrix() {}

	matrix(int rows, int cols, T t) : rows(rows), cols(cols) {
		vector<T> v;
		for (int j = 0; j < cols; j++)
			v.push_back(t);
		for (int i = 0; i < rows; i++)
			values.push_back(v);		
	}


	matrix(const matrix& m) {
		rows = m.rows;
		cols = m.cols;
		for (int i = 0; i < rows; i++)
			values.push_back(vector<T>());
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				values[i].push_back ( m.values[i][j] );
	}

	vector<T>& operator[](const int n) {
		return values[n];
	}


	friend ostream& operator<<(ostream& os, const matrix& m) {
		for (int i = 0; i < m.rows; i++) {
			for (int j = 0; j < m.cols; j++) {
				os << m.values[i][j] << " ";
			}
			os << endl;
		}
		return os;
	}

	friend istream& operator>>(istream& is, matrix& m) {
		m.rows = 0;
		m.cols = 0;
		m.values.clear();
		string line;
		while (getline(is, line)) {
			m.rows++;
			vector<T> v;
			istringstream in(line);
			while (in >> m.temp) {
				v.push_back(m.temp);
			}
			m.values.push_back(v);
		}
		m.cols = m.values[0].size();
		return is;
	}


	matrix& operator=(const matrix& m) {
		rows = m.rows;
		cols = m.cols;
		values.clear();
		for (int i = 0; i < rows; i++)
			values.push_back(vector<T>());
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				values[i].push_back(m.values[i][j]);
		return *this;
	}

	bool operator==(const matrix& m)const {
		if (rows != m.rows) return false;
		if (cols != m.cols) return false;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (values[i][j] != m.values[i][j]) {
					return false;
				}
		return true;
	}

	bool isInRange(int i, int j) const {
		return 0 <= i && i < rows && 0 <= j && j < cols;
	}

	int getRows() {
		return rows;
	}

	int getCols() {
		return cols;
	}
};

#endif // !MATRIXH