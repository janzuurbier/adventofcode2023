// dag11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "../matrix/matrix.h"
#include <set>
using namespace std;

const int ROWS = 140;
const int COLS = 140;
matrix<char, ROWS, COLS> m('.');
int z = 1000000;  //z = 2 for part 1

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	input >> m;

	set<int> row_set;
	for (int i = 0; i < ROWS; i++) {
		bool b = true;
		for (int j = 0; j < COLS; j++) {
			if (m[i][j] == '#') {
				b = false;
				break;
			}
		}
		if (b) row_set.insert(i);
	}

	set<int> col_set;
	for (int j = 0; j < COLS; j++) {
		bool b = true;
		for (int i = 0; i < ROWS; i++) {
			if (m[i][j] == '#') {
				b = false;
				break;
			}
		}
		if (b) col_set.insert(j);
	}

	uint64_t sum = 0;
	for(int i = 0; i < ROWS; i++)
		for(int j = 0; j < COLS; j++){
			if (m[i][j] == '#') {
		
				for (int r = i , dr = 0; r < ROWS; r++, dr += row_set.count(r) > 0 ? z : 1) {
					for (int k = j , dc = 0; k < COLS; k++, dc += col_set.count(k) > 0 ? z : 1) {
						if ((r != i || k != j) && m[r][k] == '#') {
							int afstand = dr + dc;
							sum += afstand;
						}
					}
				}

				for (int r = i + 1 , dr = row_set.count(r) > 0 ? z : 1; r < ROWS; r++, dr += row_set.count(r) > 0 ? z : 1) {
					int dc = 0;
					for (int k = j - 1, dc = col_set.count(k) > 0 ? z : 1; k >= 0; k--, dc += col_set.count(k) > 0 ? z : 1) {
						if ((r != i || k != j) && m[r][k] == '#') {
							int afstand = dr + dc;
							sum += afstand;
						}
					}
				}
			}	
		}

	cout << sum << endl; 
}

