// dag17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <queue>
#include "../matrix_new/matrix.h"
using namespace std;

matrix<char> m;




matrix<map<string, int>> hist;
set<tuple<int, int, string>> marked;
queue<tuple<int, int, string>> todo;

int main()
{
	ifstream input("C:\\Users\\Jan\\Desktop\\input.txt");
	if (!input) {
		cout << "file not found" << endl;
		return 1;
	}

	input >> m;
	int rows = m.getRows();
	int cols = m.getCols();
	
	hist = matrix<map<string,int>>(rows, cols, map<string, int>());
	hist[0][0][""] = 0;
	
	marked.emplace(0, 0, "");
	todo.emplace(0, 0, "");
	
	
	string p_min = "";
	int aantal = 0;
	while (!todo.empty() ) {
		aantal++;
		tuple<int, int, string> t = todo.front();
		todo.pop();
		int i = get<0>(t);
		int j = get<1>(t);
		string p = get<2>(t);
		
		
		
		int min = 1000;
		int i_min = -1;
		int j_min = -1;
		string p_min = "";

			if (m.isInRange(i - 1, j) )  {
				string q = p;
				int d = hist[i][j][q] + (m[i - 1][j] - '0');
				char r = q.size() > 0 ? q.back() : 'x';
				if (q != "UUU" && r != 'D') {
					q += 'U';
					if (q.size() > 3) q = q.substr(1);
					if (marked.find(tuple<int, int, string>(i - 1, j, q)) == marked.end()) {
						auto it = hist[i - 1][j].find(q);
						if (it == hist[i - 1][j].end())
							hist[i - 1][j][q] = d;
						else if (d < hist[i - 1][j][q])
							hist[i - 1][j][q] = d;
						if(d <= hist[i - 1][j][q]){
							todo.emplace(i - 1, j, q);
							if (d < min) {
								i_min = i - 1;
								j_min = j;
								p_min = q;
							}
						}
						
					}
				}
			}


			if (m.isInRange(i + 1, j)  )  {
				string q = p;

				int d = hist[i][j][q] + (m[i + 1][j] - '0');


				char r = q.size() > 0 ? q.back() : 'x';
				if (q != "DDD" && r != 'U') {
					q += 'D';
					if (q.size() > 3) q = q.substr(1);
					if (marked.find(tuple<int, int, string>(i + 1, j, q)) == marked.end()) {
						auto it = hist[i + 1][j].find(q);
						if (it == hist[i + 1][j].end())
							hist[i + 1][j][q] = d;
						else if (d < hist[i + 1][j][q])
							hist[i + 1][j][q] = d;
						if (d <= hist[i + 1][j][q]) {
							todo.emplace(i + 1, j, q);
							if (d < min) {
								i_min = i + 1;
								j_min = j;
								p_min = q;
							}
						}
					}
				}

			}

			if (m.isInRange(i, j - 1) ) {
				string q = p;

				int d = hist[i][j][q] + (m[i][j - 1] - '0');

				char r = q.size() > 0 ? q.back() : 'x';
				if (q != "LLL" && r != 'R') {
					q += 'L';
					if (q.size() > 3) q = q.substr(1);
					if (marked.find(tuple<int, int, string>(i, j - 1, q)) == marked.end()) {
						auto it = hist[i][j - 1].find(q);
						if (it == hist[i][j - 1].end())
							hist[i][j - 1][q] = d;
						else if (d < hist[i][j - 1][q])
							hist[i][j - 1][q] = d;
						if (d <= hist[i][j - 1][q]) {
							todo.emplace(i, j - 1, q);
							if (d < min) {
								i_min = i;
								j_min = j - 1;
								p_min = q;
							}
						}
					}
				}

			}

			if (m.isInRange(i, j + 1) )  {
				string q = p;

				int d = hist[i][j][q] + (m[i][j + 1] - '0');

				char r = q.size() > 0 ? q.back() : 'x';
				if (q != "RRR" && r != 'L') {
					q += 'R';
					if (q.size() > 3) q = q.substr(1);
					if (marked.find(tuple<int, int, string>(i, j + 1, q)) == marked.end()) {
						auto it = hist[i][j + 1].find(q);
						if (it == hist[i][j + 1].end())
							hist[i][j + 1][q] = d;
						else if (d < hist[i][j + 1][q])
							hist[i][j + 1][q] = d;
						if (d <= hist[i][j + 1][q]) {
							todo.emplace(i, j + 1, q);
							if (d < min) {
								i_min = i;
								j_min = j + 1;
								p_min = q;
							}
						}
					}
				}



			}
			if (i_min != -1)
				marked.emplace(i_min, j_min, p_min);
		

			//}//for i j
			

		}//drie maal
		



	
	//int mindist = 1000;
	for (auto it : hist[rows - 1][cols - 1])
		cout << it.first << ' ' << it.second << endl;
	//cout << aantal << ": " << mindist << endl;
	
	
}
