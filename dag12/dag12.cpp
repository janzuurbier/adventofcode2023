// dag12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <sstream>
using namespace std;

deque<int> split(string& s){
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


int count(string s, deque<int> v) {
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
	int i = 0;
	while (i < s.size() && s[i] == '.') i++;
	int nr = 0;
	while (i < s.size() && s[i] == '#') { nr++; i++; }
	if (nr > v[0]) {
		return 0;
	}
	if (nr == v[0] ) {
		s = s.substr(i);
		s[0] = '.';
		v.pop_front();
		return count(s, v);
	}
	if (nr < v[0] && s[i] == '.'){
		return 0;
	}
	if (nr == 0 && s[i] == '?') {
		string t = s;
		s[i] = '#';
		t[i] = '.';
		return count(s, v) + count(t, v);
	}
	if (nr < v[0] && s[i] == '?') {
		int j = i;
		while ((s[j] == '?' || s[j] == '#')  && nr < v[0]) {
			s[j] = '#';
			j++;
			nr++;
		}
		return count(s, v);
	}
}


int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
	
	string line;
	int sum = 0;
	while (getline(input, line)) {
		deque<int> v = split(line);
		sum +=  count(line, v);
	}
	cout << ">>>" << sum << endl;
}

