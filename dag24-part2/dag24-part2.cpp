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

	friend uint64_t det(const vect2& v, const vect2& w) {
		return v.x*w.y - v.y*w.x;
	}

};

pair<double, double> intersect_xy(const hailstone& h, const hailstone& g) {
	double a = (double)h.v.y * (double)h.p.x - (double)h.v.x * (double)h.p.y;
	double b = (double)g.v.y * (double)g.p.x - (double)g.v.x * (double)g.p.y;
	double d = det(vect2(h.v.y, g.v.y), vect2(-h.v.x, -g.v.x));

	double x = det(vect2(a, b), vect2(-h.v.x, -g.v.x)) / d;
	double y = det(vect2(h.v.y, g.v.y), vect2(a, b)) / d;

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

	h = hailstones[0];
	hailstone g = hailstones[1];
	hailstone f = hailstones[2];

	for(int a = 0; a < 300000; a++)
		for (int b = 0; b < 300000 && b != a; b++) {
			uint64_t x = h.p.x + a * h.v.x;
			uint64_t y = h.p.y + a * h.v.y;
			uint64_t z = h.p.z + a * h.v.z;
			uint64_t xx = g.p.x + b * g.v.x;
			uint64_t yy = g.p.y + b * g.v.y;
			uint64_t zz = g.p.z + b * g.v.z;

			
			if ((x - xx) % (a - b) == 0 && (y - yy) % (a - b) == 0 && (z - zz) % (a - b) == 0) {
				uint64_t vx = (x - xx) / (a - b); //must be integer!!!
				uint64_t vy = (y - yy) / (a - b); //must be integer!!!
				uint64_t vz = (z - zz) / (a - b); //must be integer!!!
				uint64_t px = x - a * vx;
				uint64_t py = x - a * vy;
				uint64_t pz = x - a * vz;
				if (det(vect2(px - f.p.x, py - f.p.y), vect2(f.v.x - vx, f.v.y - vy)) == 0
					&& det(vect2(px - f.p.x, pz - f.p.z), vect2(f.v.x - vx, f.v.z - vz)) == 0)
					cout << a << " en " << b << endl;
			}

			

		}

}