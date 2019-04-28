#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using std::map;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;
using std::string;
using std::pair;

enum IntervalMergeStrategy {
	SWALLOW,
	COALESCE
};

struct disjoint_interval_range {
	map<int, int> range_start_index_map;
	map<int, int> range_end_index_map;
	vector<int> range_start;
	vector<int> range_end;
	void add_to_range(int start, int end);
	map<int, IntervalMergeStrategy> intersects(int start, int end);
	string print();
};

map<int, IntervalMergeStrategy> disjoint_interval_range::intersects(int start, int end)
{
	string fn = __PRETTY_FUNCTION__;
	cout << "ENTER " << fn << " start: " << start << ", end: " << end << endl;
	map<int, IntervalMergeStrategy> res;
	map<int, int>::iterator it_lb_st = range_start_index_map.lower_bound(start);
	if (it_lb_st == range_start_index_map.begin()) {
		int idx_lb_st = it_lb_st->second;
		cout << "lower bound of start: " << range_start[idx_lb_st] << endl;
		if (range_end[idx_lb_st] < start || range_start[idx_lb_st] > end) {
			// does not intersect
			cout << "does not intersect: " 
				<< range_start[idx_lb_st] << " - " << range_end[idx_lb_st]
				<< "| merge :" << SWALLOW
				<< endl;
		} else {
			res[idx_lb_st] =  COALESCE;
			cout << start << " - " << end 
				<< " intersects with idx_lb_st: "
				<< range_start[idx_lb_st]
				<< " - " 
				<< range_end[idx_lb_st]
				<< "| merge :" << COALESCE
				<< endl;

		}
	} 
	//else {
	//	--it_lb_st;
	//}
	else if (it_lb_st != range_start_index_map.end() ) {
		--it_lb_st;
		int idx_lb_st = it_lb_st->second;
		cout << "lower bound of start: " << range_start[idx_lb_st] << endl;
		if (range_end[idx_lb_st] < start) {
			// does not intersect
			cout << "does not intersect: " 
				<< range_start[idx_lb_st] << " - " << range_end[idx_lb_st]
				<< "| merge :" << SWALLOW
				<< endl;
		} else {
			res[idx_lb_st] =  COALESCE;
			cout << start << " - " << end 
				<< " intersects with idx_lb_st: "
				<< range_start[idx_lb_st]
				<< " - " 
				<< range_end[idx_lb_st]
				<< "| merge :" << COALESCE
				<< endl;

		}
	}
	map<int, int>::iterator it_ub_st = range_start_index_map.upper_bound(start);
	if (it_ub_st != range_start_index_map.end()) {
		int idx_ub_st = it_ub_st->second;
		cout << "upper_bound bound of start: " << range_start[idx_ub_st] << endl;
	}


	cout << "matching ranges in between : "; 
	for (map<int, int>::iterator it = range_start_index_map.lower_bound(start);
		it != range_start_index_map.lower_bound(end); ++it) {
		int idx_rng = it->second;
		cout << ", " << range_start[idx_rng] << " - " << range_end[idx_rng];
			//<< endl;
		//res.push_back(idx_rng);
		if ( (range_start[idx_rng] <= start && range_end[idx_rng] <= end)  ||
		     (range_start[idx_rng] >= start && range_end[idx_rng] >= end)
		   ) {
			res[idx_rng] =  COALESCE;
		} else if (range_start[idx_rng] > start && range_end[idx_rng] < end) {
			res[idx_rng] =  SWALLOW;
		}
	}
	cout << endl;


	map<int, int>::iterator it_lb_end = range_end_index_map.lower_bound(end);
	map<int, int>::iterator it_ub_end = range_end_index_map.upper_bound(end);
	if (it_ub_end != range_end_index_map.end() ) {
		int idx_ub_end = it_ub_end->second;
		if (range_start[idx_ub_end] > end) {
			// does not intersect
		} else {
			res[idx_ub_end] = COALESCE;
			cout << start << " - " << end 
				<< " intersects with idx_ub_end: " << idx_ub_end
				<< " :  " 
				<< range_start[idx_ub_end]
				<< " - " 
				<< range_end[idx_ub_end]
				
				<< endl;
		}
	}


	//cout << "start range - from upper bound of start to lower bound of end" << endl;
	//for (map<int, int > :: iterator it1 = it_ub_st; it1 != it_lb_end; ++it1) {
	//	cout << it1->first;
	//}
	cout << "EXIT " << fn << " start: " << start << ", end: " << end << endl;
	return res;
}

string disjoint_interval_range::print()
{
	stringstream s;
	for (int i = 0; i < range_start.size(); ++i) {
		s << ", " << range_start[i] << " - " << range_end[i];
	}
	return s.str();
}

void disjoint_interval_range::add_to_range(int start, int end)
{
	if (range_start.size() == 0) {
		range_start.push_back(start);
		range_end.push_back(end);
		range_start_index_map[start] = range_start.size()-1;
		range_end_index_map[end] = range_end.size()-1;
	} else {
		// for now - just add until we fix the intersection logic 
		map<int, IntervalMergeStrategy> res = intersects(start, end);
		if (res.size() == 0) {
			range_start.push_back(start);
			range_end.push_back(end);
			range_start_index_map[start] = range_start.size()-1;
			range_end_index_map[end] = range_end.size()-1;
		} else {
			cout << "n intersecting ranges: " << res.size() << endl;
			int n_coalesce = 0;
			vector<pair<int, IntervalMergeStrategy>*> indexes;
			cout << "they are: " ;
			int new_start = start, new_end = end;
			cout << "new_start: " << new_start << ", new_end: " << new_end << endl;
			for (map<int, IntervalMergeStrategy>::iterator it = 
					res.begin(); it != res.end(); ++it) {
				cout << ", " << range_start[it->first] << " - " << range_end[it->first] 
					<< "| merge strategy : " << it->second;
				indexes.push_back(new pair<int, IntervalMergeStrategy>(it->first,it->second));
				if (it->second == COALESCE) {
					++n_coalesce;
					if (range_start[it->first] < start) {
						new_start = range_start[it->first];
						cout << "updated new_start: " << new_start << endl;
					}
					if (range_end[it->first] > new_end) {
						new_end = range_end[it->first];
						cout << "updated new_end: " << new_end << endl;
					}
				}
			}
			cout << "new_start: " << new_start << ", new_end: " << new_end << endl;
			cout << endl;
			if (n_coalesce > 2) {
				cerr << "dying as this should never happen" << endl;
				exit(1); // die
			}
			
			// delete the rest
			cout   << "Before deletion: "
				<< "range_start.size(): " << range_start.size()
				<< ", range_end.size(): " << range_end.size()
				<< ", range_start_index_map.size(): " << range_start_index_map.size()
				<< ", range_end_index_map.size(): " << range_end_index_map.size()
				<< endl;
			for (int i = indexes.size() - 1; i >= 1; i--) {
				// erase the other ranges
				int idx = indexes[i]->first;
				int prev_start = range_start[idx];
				int prev_end = range_end[idx];
				cout << "erasing vec index : " << idx 
					<< ", prev_start: " << prev_start
					<< ", prev_end: " << prev_end
					<< endl;
				range_start_index_map.erase(prev_start);
				range_end_index_map.erase(prev_end);
				range_start.erase(range_start.begin()+idx);
				range_end.erase(range_end.begin()+idx);
				cout   << "After deletion: "
					<< "range_start.size(): " << range_start.size()
					<< ", range_end.size(): " << range_end.size()
					<< ", range_start_index_map.size(): " << range_start_index_map.size()
					<< ", range_end_index_map.size(): " << range_end_index_map.size()
					<< endl;
			}
			cout << "range_start.size(): " << range_start.size()
				<< "range_end.size(): " << range_end.size()
				<< endl;
			pair<int, IntervalMergeStrategy> & i1 = * indexes[0];
			// keep the lowest index 
			{
				int idx = indexes[0]->first;
				int prev_start = range_start[idx];
				int prev_end = range_end[idx];
				range_start[idx] = new_start;
				range_end[idx] = new_end;
				range_start_index_map.erase(prev_start);
				range_end_index_map.erase(prev_end);
				range_start_index_map[idx]= start;
				range_end_index_map[idx] = end;
			}

			if (n_coalesce > 2) {
				// we have a serious problem - it should be max 2
				cerr << "n_coalesce should never exceed 2" << endl;
			}
		}
	}
}


int main()
{
	int n_tests = 0, n_passed = 0;
	map<string, bool> test_results;
	/*
	{
		string tname("only 1 interval");
		struct disjoint_interval_range dir1;
		dir1.add_to_range(3,5);
		string s = dir1.print();
		if (s == string(", 3 - 5")) {
			++n_passed; ++n_tests;
			test_results[tname] = true;
		} else {
			cout << "failed " << tname << endl;
			++n_tests;
			test_results[tname] = false;
		}
	}

	{
		string tname("test intersection 1");
		struct disjoint_interval_range dir1;
		dir1.add_to_range(3,5);
		dir1.add_to_range(8,10);
		map<int, IntervalMergeStrategy> res = dir1.intersects(6,7);
		if (res.size() == 0) {
			++n_passed; ++n_tests;
		} else {
			++n_tests;
			cout << "failed " << tname << endl;
			test_results[tname] = false;
		}
	}


	{
		string tname("test intersection intersects with start lower bound");
		struct disjoint_interval_range dir1;
		dir1.add_to_range(3,5);
		dir1.add_to_range(8,10);
		map<int, IntervalMergeStrategy> res = dir1.intersects(4,7);
		if (res.size() == 1) {
			int i1 = res.begin()->first;
			int r_start = dir1.range_start[i1];
			int r_end = dir1.range_end[i1];
			if (!(r_start == 3 && r_end == 5)) {
				++n_tests;
				test_results[tname] = false;
				cout << "failed " << tname << endl;
			} else {
				++n_passed; ++n_tests;
			}
		} else {
			++n_tests;
			cout << "failed " << tname 
				<< " expected intersections : " 
				<< 1
				<< " actual: " << res.size()
				<< endl;
			test_results[tname] = false;
		}
	}

	{
		string tname("test intersection intersects with end upper bound");
		struct disjoint_interval_range dir1;
		dir1.add_to_range(3,5);
		dir1.add_to_range(8,10);
		map<int, IntervalMergeStrategy> res = dir1.intersects(6,9);
		if (res.size() == 1) {
			int i1 = res.begin()->first;
			int r_start = dir1.range_start[i1];
			int r_end = dir1.range_end[i1];
			if (!(r_start == 8 && r_end == 10)) {
				++n_tests;
				test_results[tname] = false;
				cout << "failed " 
					<< tname 
					<< "r_start, actual : " << r_start
					<< ", expected: " << 8
					<< "r_end, actual : " << r_end
					<< ", expected: " << 8
					<< endl;
			} else {
				++n_passed; ++n_tests;
			}
		} else {
			++n_tests;
			cout << "failed " << tname 
				<< ", size, actual : " << res.size()
				<< ", expected: " << 1
				<< endl;
			test_results[tname] = false;
		}
	}

	{
		string tname("test intersection intersects with lower upper and range in between ");
		struct disjoint_interval_range dir1;
		dir1.add_to_range(1,2);
		dir1.add_to_range(3,5);
		dir1.add_to_range(7,9);
		dir1.add_to_range(11,13);
		dir1.add_to_range(15,17);
		dir1.add_to_range(19,21);
		map<int, IntervalMergeStrategy> res = dir1.intersects(4,16);
		if (res.size() == 4) {
			++n_passed; ++n_tests;
		} else {
			++n_tests;
			cout << "failed " << tname
				<< ", size: " << res.size()
				<< endl ;
			test_results[tname] = false;
		}
	}

	{
		string tname("test intersection coalesce 1 ranges left endpoint matches  ");
		struct disjoint_interval_range dir1;
		dir1.add_to_range(1,2);
		dir1.add_to_range(3,5);
		dir1.add_to_range(7,9);
		dir1.add_to_range(11,13);
		dir1.add_to_range(15,17);
		dir1.add_to_range(19,21);
		map<int, IntervalMergeStrategy> res = dir1.intersects(3,6);
		if (res.size() == 1) {
			++n_passed; ++n_tests;
		} else {
			++n_tests;
			cout << "failed " << tname
				<< ", size: " << res.size()
				<< endl ;
			test_results[tname] = false;
		}
	}

	{
		string tname("test intersection coalesce 1 range right endpoint matches  ");
		struct disjoint_interval_range dir1;
		dir1.add_to_range(1,2);
		dir1.add_to_range(3,5);
		dir1.add_to_range(7,9);
		dir1.add_to_range(11,13);
		dir1.add_to_range(15,17);
		dir1.add_to_range(19,21);
		map<int, IntervalMergeStrategy> res = dir1.intersects(4,5);
		if (res.size() == 1) {
			++n_passed; ++n_tests;
		} else {
			++n_tests;
			cout << "failed " << tname
				<< ", size: " << res.size()
				<< endl ;
			test_results[tname] = false;
		}
	}




	{
		string tname("2 disjoint intervals");
		struct disjoint_interval_range dir1;
		dir1.add_to_range(3,5);
		dir1.add_to_range(7,10);

		string s = dir1.print();
		if (s == string(", 3 - 5, 7 - 10")) {
			++n_passed; ++n_tests;
		} else {
			++n_tests;
			cout << "failed " << tname << endl;
			test_results[tname] = false;
		}
	}

	{
		string tname("test add range ");
		struct disjoint_interval_range dir1;
		dir1.add_to_range(1,2);
		dir1.add_to_range(3,5);
		dir1.add_to_range(7,9);
		dir1.add_to_range(11,13);
		dir1.add_to_range(15,17);
		dir1.add_to_range(19,21);
		dir1.add_to_range(1,21);
		string s = dir1.print();
		if (s == ", 1 - 21") {
			++n_passed; ++n_tests;
		} else {
			++n_tests;
			test_results[tname] = false;
			cout << "failed " << tname
				<< ", expected " << ", 1 - 21"
				<< endl;
		}
	}
	*/

	/*
	{
		string tname("test add range 3");
		struct disjoint_interval_range dir1;
		dir1.add_to_range(1,2);
		dir1.add_to_range(3,5);
		dir1.add_to_range(7,9);
		dir1.add_to_range(11,13);
		dir1.add_to_range(15,17);
		dir1.add_to_range(19,21);
		dir1.add_to_range(3,16);
		string s = dir1.print();
		string expected(", 1 - 2, 3 - 17, 19 - 21");
		if (s == expected) {
			++n_passed; ++n_tests;
		} else {
			++n_tests;
			test_results[tname] = false;
			cout << "failed " << tname
				<< ", expected " << expected
				<< ", actual : " << s 
				<< endl;
		}
	}
	*/

	{
		string tname("test add range - range order in vector should not matter, the map order defines it");
		struct disjoint_interval_range dir1;
		dir1.add_to_range(19,21);
		dir1.add_to_range(1,2);
		dir1.add_to_range(11,13);
		dir1.add_to_range(3,5);
		dir1.add_to_range(7,9);
		dir1.add_to_range(15,17);
		dir1.add_to_range(3,16);
		string s = dir1.print();
		string expected(", 1 - 2, 3 - 17, 19 - 21");
		if (s == expected) {
			++n_passed; ++n_tests;
		} else {
			++n_tests;
			test_results[tname] = false;
			cout << "failed " << tname
				<< ", expected " << expected
				<< ", actual : " << s 
				<< endl;
		}
	}

	cout << "n_tests: " << n_tests << ", n_passed: " << n_passed 
		<< ", pass perc: "
		<< (double) n_passed / n_tests * 100 << " % " 
		<< endl;

	if (test_results.size() > 0) {
		cout << "Failed Test Report" << endl;
		for (map<string, bool> ::iterator it = test_results.begin(); it != test_results.end();
				++it) {
			if (it->second == false) {
				cout << it -> first << endl;
			}
		}
	} else {
		cout << "All " << n_tests << " tests passed" << endl;
	}

}


