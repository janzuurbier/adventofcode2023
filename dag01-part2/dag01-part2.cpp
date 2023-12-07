// dag01-part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
using namespace std;


string cijfers[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };


int calibration_value(string s) {
	int min_pos = 1000;
	int min_val = 0;

	for (char ch = '1'; ch <= '9'; ch++) {
		int pos = s.find(ch);
		if (pos != string::npos &&  pos < min_pos) {
			min_pos = pos;
			min_val = ch - '0';
		}
	}
	for (int i = 1; i < 10; i++) {
		int pos = s.find(cijfers[i]);
		if (pos != string::npos &&  pos < min_pos) {
			min_pos = pos;
			min_val = i;
		}
	}
	int max_pos = -1;
	int max_val = 0;
	for (char ch = '1'; ch <= '9'; ch++) {
		int pos = s.rfind(ch);
		if (pos != string::npos && pos > max_pos) {
			max_pos = pos;
			max_val = ch - '0';
		}
	}
	for (int i = 1; i < 10; i++) {
		int pos = s.rfind(cijfers[i]);
		if (pos != string::npos && pos > max_pos) {
			max_pos = pos;
			max_val = i;
		}
	}

	return 10 * min_val + max_val;
}



int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	int sum = 0;
	string line;
	while (getline(input, line)) {
		int val = calibration_value(line);
		sum += val;
	}
	cout << endl << sum << endl;
}