// dag12-part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <sstream>
using namespace std;

deque<int> split(string& s) {
	size_t pos = s.find(' ');
	string t = s.substr(pos + 1);
	s = s.substr(0, pos);
	istringstream in(t);
	deque<int> v;
	int i;
	char komma;
	while (in >> i) {
		v.push_back(i);
		in >> komma;
	}
	return v;
}

//can you place 'aantal' # from position 'start'
bool fits_here(const string& s, int aantal, size_t start) {
	if (aantal == 0) return false;
	if (start >= s.size()) return false;
	size_t i = start;
	int j = 1;
	if (i >= s.size()) return false;
	if (i > 0 && s[i - 1] == '#') return false;
	while (s[i] == '#' || s[i] == '?') {
		if (i == s.size()) return false;
		if (j == aantal && (i + 1 == s.size() || s[i + 1] != '#')) return true;
		j++;
		i++;
	}
	return false;
}

//find a position where you can place 'aantal' #.
size_t find(const string& s, int aantal, size_t start = 0) {
	while (start <= s.size() - aantal) {
		if (fits_here(s, aantal, start))
			return start;
		start++;
	}
	return string::npos;
}

// a new recursive funtion that uses multiplication and addition
// in part one I only used addition
// it splits the string in two parts rather than eating from the front
// recursively call de funtion  on both parts
// it is important to calculate te shortest part first
// because if it is zero you don't have to calculate the other part

uint64_t count(string s, deque<int> v) {
	int aantal_vraagtekens = 0;
	int aantal_hekjes_reeds_aanwezig = 0;
	int aantal_hekjes = 0;
	for (char ch : s) {
		if (ch == '?') aantal_vraagtekens++;
		if (ch == '#') aantal_hekjes_reeds_aanwezig++;
	}
	for (int i : v)
		aantal_hekjes += i;
	if (aantal_hekjes > aantal_hekjes_reeds_aanwezig + aantal_vraagtekens) {
		return 0;
	}
	if (aantal_hekjes < aantal_hekjes_reeds_aanwezig) {
		return 0;
	}
	if (aantal_hekjes == 0 && aantal_hekjes_reeds_aanwezig == 0) {
		return 1;
	}

	int max = 0;
	for (int i : v)
		if (i > max) max = i;
	deque<int> posities;
	for (int i = 0; i < v.size(); i++)
		if (v[i] == max)
			posities.push_back(i);
	int thepos = posities[posities.size() / 2];
	deque<int> w;
	for (int i = 0; i < thepos; i++) {
		w.push_back(v[i]);
	}
	for (int i = 0; i <= thepos; i++)
		v.pop_front();

	uint64_t sum = 0;
	uint64_t left_val = 0;
	uint64_t right_val = 0;
	int old_pos = -1;
	while (true) {
		size_t pos = find(s, max, old_pos + 1);
		if (pos == string::npos)
			break;
		old_pos = pos;
		string left = pos > 0 ? s.substr(0, pos - 1) : "";
		string right = pos + max + 1 < s.size() ? s.substr(pos + max + 1) : "";
		if (pos < s.size() / 2) {
			left_val = count(left, w);
			if (left_val > 0)
				right_val = count(right, v);
		}
		else {
			right_val = count(right, v);
			if (right_val > 0)
				left_val = count(left, w);
		}
		sum += left_val * right_val;
	}
	return sum;
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	string line;
	uint64_t sum = 0;
	int aantal = 0;
	while (getline(input, line)) {
		deque<int> v = split(line);
		aantal++;
		cout << aantal << "  ";

		string line1;
		deque<int> v1;
		for (int i = 0; i < 4; i++) line1 += line + "?";
		line1 += line;
		for (int i = 0; i < 5; i++)
			for (int j : v)
				v1.push_back(j);

		uint64_t x = count(line1, v1);
		cout << x << endl;
		sum += x;

	}
	cout << ">>>" << sum << endl;
}

