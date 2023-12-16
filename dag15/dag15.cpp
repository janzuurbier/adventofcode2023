// dag15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int myhash(string s) {
	uint8_t current_value = 0;
	for (char ch : s) {
		current_value += (uint8_t)ch;
		current_value *= 17;
	}
	return current_value;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	uint64_t sum = 0;
	string s;
	while (getline(input, s, ',')) {
		sum += myhash(s);
		//cout << s << " becomes " << myhash(s) << endl;	
	}
	cout << sum << endl;
}
