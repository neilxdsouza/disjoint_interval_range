
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>


#include "interval_range.h"

using std::map;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;
using std::string;
using std::pair;
using std::min;
using std::max;
using std::cin;

int main()
{
	int seed, n_tests;
	cin >> n_tests;
	for (int j = 0; j < n_tests; ++j) {
		cin >> seed;
		struct disjoint_interval_range dir1;
		vector <pair<int, int> > v_p;
		for (int i = 0; i < 1000; ++i) {
			int i_s, i_e;
			cin >> i_s >> i_e;
			v_p.push_back(pair<int, int>(i_s, i_e));
			dir1.add_to_range(i_s, i_e);
		}
		cout << "seed : " << seed << endl;
		for (int i = 0; i < v_p.size(); ++i) {
			cout << " " << v_p[i].first << " - " <<
				v_p[i].second ;
		}
		cout << endl;
		cout << "disj range is: "
			<< dir1.print() << endl;
	}
}
