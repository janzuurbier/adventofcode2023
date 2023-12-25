// dag20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

##include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

class module {
	string name;
	virtual void hande_pulse(bool high, string from) = 0;
	virtual void send();
	vector<string> output_modules;
};

class flipflop :public module {
	bool is_on = false; //true is on, false is off

	void handle_pulse(bool signal, string from) {
		if (!signal) {
			if (is_on)
			is_on = !is_on;
		}
		send();
	}

	void send() {

	};
		

	
};

class conjunction : public module {
	map<string, bool> memory;
	vector<string> recievers;

	void handle_pulse(bool signal, string from) {
		memory[from] = signal;
	}
};

class broadcast : public module {
	bool signal_to_send;
	void handle_pulse(bool signal, string from) {
		signal_to_send = signal;
	}
};



int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}
}
