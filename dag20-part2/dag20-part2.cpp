
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <deque>
using namespace std;

struct signal {
	bool is_high;
	string from;
	string to;

	signal(bool b, string f, string t) : is_high(b), from(f), to(t) {}

	friend ostream& operator<<(ostream& os, const signal& s) {
		os << s.from << (s.is_high ? " -high -> " : " -low -> ") << s.to;
		return os;
	}
};

deque<signal> thequeue;

class module {
public:
	string name;
	vector<string> destination_modules;
	virtual void handle_pulse(signal s) = 0;
	virtual void send() = 0;
	virtual void add_reciever(string reciever) {}
	friend ostream& operator<< (ostream& os, const module& m) {
		os << "?" << m.name << " -> ";
		for (string s : m.destination_modules)
			os << s << ", ";
		return os;
	}

};

class flipflop : public module {
	bool is_on = false; //true is on, false is off


	void handle_pulse(signal s) {
		if (!s.is_high) {
			is_on = !is_on;
			send();
		}
	}

	void send() {
		for (string dest : destination_modules)
			thequeue.push_back(signal(is_on, name, dest));
	}
};

class conjunctionn : public module {
	map<string, bool> memory;
	vector<string> recievers;

	void handle_pulse(signal s) {
		memory[s.from] = s.is_high;
		send();
	}

	void send() {
		bool b = true;
		for (auto it = memory.begin(); it != memory.end(); it++)
			b = b && it->second;
		bool signal_to_send = !b;
		for (string dest : destination_modules)
			thequeue.push_back(signal(signal_to_send, name, dest));
	}

	void add_reciever(string s) {
		recievers.push_back(s);
		memory[s] = false;
	}
};

class broadcast : public module {
	bool signal_to_send;
	void handle_pulse(signal s) {
		signal_to_send = s.is_high;
		send();
	}

	void send() {
		for (string dest : destination_modules)
			thequeue.push_back(signal(signal_to_send, name, dest));
	}
};



int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	map<string, module*> modules;

	string line;
	while (getline(input, line)) {
		module *m;
		istringstream iss(line);
		string s;
		iss >> s;
		if (s[0] == '%') {
			m = new flipflop();
			m->name = s.substr(1);
		}
		else if (s[0] == '&') {
			m = new conjunctionn();
			m->name = s.substr(1);
		}
		else {
			m = new broadcast();
			m->name = s;
		}
		iss >> s; // pijltje
		while (iss >> s) {
			if (s.back() == ',')
				s.pop_back();
			m->destination_modules.push_back(s);
		}
		modules[m->name] = m;
	}

	for (auto it = modules.begin(); it != modules.end(); it++)
		for (string s : it->second->destination_modules)
			if (modules.count(s) > 0)
				modules[s]->add_reciever(it->first);

	for (int i = 0; i < 10000; i++) {
		thequeue.push_back(signal(false, "button", "broadcaster"));
		while (!thequeue.empty()) {
			signal s = thequeue.front();
			if (s.to == "nr" && s.is_high) {
				cout << "after " << i + 1 << " presses " << "nr recieves ";
				cout << "high" << " from " << s.from << endl;
			}
			thequeue.pop_front();
			//cout << s << endl;
			if (modules.count(s.to) > 0) {
				module* dest = modules[s.to];
				dest->handle_pulse(s);
			}
		}

	}
}
