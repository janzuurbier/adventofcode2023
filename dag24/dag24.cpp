
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

const double MIN = 2E14;
const double MAX = 4E14;

//const double MIN = 7;
//const double MAX = 27;

struct vect3 {
	int64_t x;
	int64_t y;
	int64_t z;

	friend istream& operator>>(istream& is, vect3& v) {
		char komma;
		is >> v.x >> komma >> v.y >> komma >> v.z;
		return is;
	}

	friend ostream& operator<<(ostream& os, const vect3& v) {
		os << v.x << ", " << v.y << ", " << v.z;
		return os;
	}

	 
};

class  hailstone {
public:
	vect3 p;
	vect3 v;

	friend istream& operator>>(istream& is, hailstone& h) {
		char apenstaart;
		is >> h.p >> apenstaart >> h.v;
		return is;
	}

	friend ostream& operator<<(ostream& os, const hailstone& h) {
		os << h.p << " @ " << h.v;
		return os;
	}
};

class vect2 {
public:
	int64_t x;
	int64_t y;

	vect2(int64_t x, int64_t y) : x(x), y(y) {}

	friend double det(const vect2& v, const vect2& w) {
		return (double)v.x*(double)w.y - (double)v.y*(double)w.x;
	}

};

pair<double, double> intersect_xy(const hailstone& h, const hailstone& g) {
	double a = (double) h.v.y * (double)h.p.x - (double)h.v.x * (double)h.p.y;
	double b = (double)g.v.y * (double)g.p.x - (double)g.v.x * (double)g.p.y;
	double d = det(vect2(h.v.y, g.v.y), vect2(-h.v.x, -g.v.x));

	double x =  det(vect2(a, b), vect2(-h.v.x, -g.v.x)) / d;
	double y =  det(vect2(h.v.y, g.v.y), vect2(a, b)) / d;

	return pair<double, double>(x, y);
}

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	vector<hailstone> hailstones;
	hailstone h;
	while (input >> h)
		hailstones.push_back(h);

	for (hailstone h : hailstones)
		cout << h << endl;

	pair<double, double> p = intersect_xy(hailstones[0], hailstones[1]);

	int aantal = 0;
	for(int i = 0 ; i < hailstones.size() - 1; i++)
		for (int j = i + 1; j < hailstones.size(); j++) {
			pair<double, double> p = intersect_xy(hailstones[i], hailstones[j]);
			double t1 = (double)(-hailstones[i].p.x + p.first) / hailstones[i].v.x;
			double t2 = (double)(-hailstones[j].p.x + p.first) / hailstones[j].v.x;
			if (MIN <= p.first && p.first <= MAX && MIN <= p.second && p.second <= MAX && t1 >= 0 && t2 >= 0)
				aantal++;		
		}

	cout << ">>> " << aantal << endl;
}

