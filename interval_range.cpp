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

/*
enum IntervalMergeStrategy {
	SWALLOW,
	COALESCE
};

struct disjoint_interval_range {
	map<int, int> range_start_index_map;
	map<int, int> range_end_index_map;
	vector<int> range_index_to_start;
	vector<int> range_index_to_end;
	void add_to_range(int start, int end);
	map<int, IntervalMergeStrategy> intersects(int start, int end);
	string print();
};

*/

map<int, IntervalMergeStrategy> disjoint_interval_range::intersects(int start, int end)
{
	string fn (__PRETTY_FUNCTION__);
	//cout << "ENTER " << fn << " start: " << start << ", end: " << end << endl;
	map<int, IntervalMergeStrategy> res;
	map<int, int>::iterator it_lb_st = range_start_index_map.lower_bound(start);
	if (it_lb_st == range_start_index_map.begin()) {
		int idx_lb_st = it_lb_st->second;
		// cout << "lower bound of start: " << range_index_to_start[idx_lb_st] << endl;
		if (range_index_to_end[idx_lb_st] < start || range_index_to_start[idx_lb_st] > end) {
			// does not intersect
			//cout << "does not intersect: " 
			//	<< range_index_to_start[idx_lb_st] << " - " << range_index_to_end[idx_lb_st]
			//	<< "| merge :" << SWALLOW
			//	<< endl;
		} else {
			res[idx_lb_st] =  COALESCE;
			// cout << "INFO: " << fn
			// 	<< " case it_lb_st == range_start_index_map.begin(): " 
			// 	<< start << " - " << end 
			// 	<< " intersects with idx_lb_st: "
			// 	<< range_index_to_start[idx_lb_st]
			// 	<< " - " 
			// 	<< range_index_to_end[idx_lb_st]
			// 	<< "| merge :" << COALESCE
			// 	<< endl;
		}
	} 
	//else {
	//	--it_lb_st;
	//}
	else if (it_lb_st != range_start_index_map.end() ) {
		//cout << "INFO: " << fn
		//	<< " case it_lb_st != range_start_index_map.end(): " 
		//	<< endl;
		--it_lb_st;
		int idx_lb_st = it_lb_st->second;
		//cout << "lower bound of start: " << range_index_to_start[idx_lb_st] << endl;
		if (range_index_to_end[idx_lb_st] < start) {
			// does not intersect
			// cout << "does not intersect: " 
			// 	<< range_index_to_start[idx_lb_st] << " - " << range_index_to_end[idx_lb_st]
			// 	<< "| merge :" << SWALLOW
			// 	<< endl;
		} else {
			res[idx_lb_st] =  COALESCE;
			// cout << start << " - " << end 
			// 	<< " intersects with idx_lb_st: "
			// 	<< range_index_to_start[idx_lb_st]
			// 	<< " - " 
			// 	<< range_index_to_end[idx_lb_st]
			// 	<< "| merge :" << COALESCE
			// 	<< endl;
		}
	} else /* (it_lb_st == range_start_index_map.end() ) */ {
		if (range_start_index_map.size() == 1) {
			it_lb_st == range_start_index_map.begin();
		} else {
			// TODO - create a test case for this and handle here
			//cerr << "unhandled case dying ..." << endl;
			//exit(1);
			// https://stackoverflow.com/questions/46640199/decrement-of-end-of-stdmap
			it_lb_st = std::prev(range_start_index_map.end());
		}
		int idx_lb_st = it_lb_st->second;
		// cout << "lower bound of start: " << range_index_to_start[idx_lb_st] << endl;
		if (range_index_to_end[idx_lb_st] < start || range_index_to_start[idx_lb_st] > end) {
			// does not intersect
			// cout << "does not intersect: " 
			// 	<< range_index_to_start[idx_lb_st] << " - " << range_index_to_end[idx_lb_st]
			// 	<< "| merge :" << SWALLOW
			// 	<< endl;
		} else {
			res[idx_lb_st] =  COALESCE;
			// cout << "INFO: " << fn
			// 	<< " case it_lb_st == range_start_index_map.begin(): " 
			// 	<< start << " - " << end 
			// 	<< " intersects with idx_lb_st: "
			// 	<< range_index_to_start[idx_lb_st]
			// 	<< " - " 
			// 	<< range_index_to_end[idx_lb_st]
			// 	<< "| merge :" << COALESCE
			// 	<< endl;
		}
	}
	map<int, int>::iterator it_ub_st = range_start_index_map.upper_bound(start);
	if (it_ub_st != range_start_index_map.end()) {
		int idx_ub_st = it_ub_st->second;
		// cout << "upper_bound bound of start: " << range_index_to_start[idx_ub_st] << endl;
	}


	// cout << "matching ranges in between : "; 
	for (map<int, int>::iterator it = range_start_index_map.lower_bound(start);
		it != range_start_index_map.lower_bound(end); ++it) {
		int idx_rng = it->second;
		// cout << ", " << range_index_to_start[idx_rng] << " - " << range_index_to_end[idx_rng];
			//<< endl;
		//res.push_back(idx_rng);
		if ( (range_index_to_start[idx_rng] <= start && range_index_to_end[idx_rng] <= end)  ||
		     (range_index_to_start[idx_rng] >= start && range_index_to_end[idx_rng] >= end)
		   ) {
			res[idx_rng] =  COALESCE;
		} else if (range_index_to_start[idx_rng] > start && range_index_to_end[idx_rng] < end) {
			res[idx_rng] =  SWALLOW;
		}
	}
	//cout << endl;


	map<int, int>::iterator it_lb_end = range_end_index_map.lower_bound(end);
	map<int, int>::iterator it_ub_end = range_end_index_map.upper_bound(end);

	if (it_ub_end != range_end_index_map.end() ) {
		int idx_ub_end = it_ub_end->second;
		if (range_index_to_start[idx_ub_end] > end  || 
		    range_index_to_end[idx_ub_end] < start
		    ) {
			// does not intersect
		} else {
			res[idx_ub_end] = COALESCE;
			// cout << start << " - " << end 
			// 	<< " intersects with idx_ub_end: " << idx_ub_end
			// 	<< " :  " 
			// 	<< range_index_to_start[idx_ub_end]
			// 	<< " - " 
			// 	<< range_index_to_end[idx_ub_end]
			// 	<< endl;
		}
	}


	//cout << "start range - from upper bound of start to lower bound of end" << endl;
	//for (map<int, int > :: iterator it1 = it_ub_st; it1 != it_lb_end; ++it1) {
	//	cout << it1->first;
	//}
	//cout << "EXIT " << fn << " start: " << start << ", end: " << end 
	//	<< ", res.size(): " << res.size()
	//	<< endl;
	return res;
}

vector<pair<int,int>> disjoint_interval_range:: get_intervals()
{
	vector<pair<int,int>> res;
	for (map<int, int> :: iterator it = range_start_index_map.begin();
			it != range_start_index_map.end(); ++it) {
		int i = it -> second;
		res.push_back(pair<int, int>(range_index_to_start[i], range_index_to_end[i]));
	}
	return res;
}

string disjoint_interval_range::print()
{
	stringstream s;
	for (map<int, int> :: iterator it = range_start_index_map.begin();
			it != range_start_index_map.end(); ++it) {
		//cout << "index for range start: " << it->first << endl;
		int i = it -> second;
		s << ", " << range_index_to_start[i] << " - " << range_index_to_end[i];
	}
	return s.str();
}

string disjoint_interval_range::debug_print()
{
	stringstream s;
	for (map<int, int> :: iterator it = range_start_index_map.begin();
			it != range_start_index_map.end(); ++it) {
		//cout << "index for range start: " << it->first << endl;
		int i = it -> second;
		s << ", " << i << " : " << range_index_to_start[i] << " - " << range_index_to_end[i];
	}
	return s.str();
}

void disjoint_interval_range::add_to_range(int start, int end)
{
	int n1 = start, n2 = end;
	if (n1 > n2) {
		start = n2, end = n1;
	}
	string fn (__PRETTY_FUNCTION__);
	cout << "ENTER " << fn << " start: " << start << ", end: " << end << endl;
	if (range_index_to_start.size() == 0) {
		cout << "INFO : " <<  fn << " case 1 - if range_index_to_start.size() == 0" << endl;
		//range_index_to_start.push_back(start);
		//range_index_to_end.push_back(end);
		range_index_to_start[0] = start;
		range_index_to_end[0] = end;
		range_start_index_map[start] = 0;
		range_end_index_map[end] = 0;
	} else {
		// cout << "INFO : " <<  fn << " case 2  - else : range_index_to_start.size() != 0" << endl;
		// for now - just add until we fix the intersection logic 
		map<int, IntervalMergeStrategy> res = intersects(start, end);
		if (res.size() == 0) {
			cout << "INFO " << " case 2 a - intersects => res.size() == 0" << endl;
			map<int, int>::reverse_iterator it_r = range_index_to_start.rbegin();
			int index = it_r->first+1;
			range_index_to_start[index] = start;
			range_index_to_end[index] = end;
			range_start_index_map[start] = index;
			range_end_index_map[end] = index;
		} else {
			cout << "INFO " << fn << " case 2 b - intersects => res.size() != 0, it is: "
				<< res.size() << endl;
			cout << "INFO " << fn << " n intersecting ranges: " << res.size() 
				<< ", range_index_to_start.size(): " << range_index_to_start.size()
				<< ", range_index_to_end.size(): " << range_index_to_end.size()
				<< endl;
			int n_coalesce = 0;
			vector<pair<int, IntervalMergeStrategy>*> indexes;
			int new_start = start, new_end = end;
			cout << "INFO " << fn << " new_start: " << new_start << ", new_end: " << new_end << endl;
			cout << "INFO " << "the ranges are: " ;
			for (map<int, IntervalMergeStrategy>::iterator it = 
					res.begin(); it != res.end(); ++it) {
				//if (it->first > range_index_to_start.size() -1 || it->first > range_index_to_end.size() - 1) {
				//	cerr << " internal error in intersects ... dying " << endl;
				//	exit(1);
				//}
				cout << ", idx: " << it->first << " | "  << range_index_to_start[it->first] << " - " << range_index_to_end[it->first] 
				 	<< "| merge strategy : " << it->second
					;
				indexes.push_back(new pair<int, IntervalMergeStrategy>(it->first,it->second));
				if (it->second == COALESCE) {
					// cout << 
					++n_coalesce;
					if (range_index_to_start[it->first] < new_start) {
						new_start = range_index_to_start[it->first];
						cout << " updated new_start: " << new_start << endl;
					}
					if (range_index_to_end[it->first] > new_end) {
						new_end = range_index_to_end[it->first];
						cout << " updated new_end: " << new_end << endl;
					}
				}
			}
			int n_deletions = res.size() - 1; // we keep only the lowest in the 
							  // intersection and delete the rest
			cout << "n deletions : " << n_deletions;
			cout << "new_start: " << new_start << ", new_end: " << new_end << endl;
			//cout << endl;
			if (n_coalesce > 2) {
				cerr << "dying as this should never happen" << endl;
				exit(1); // die
			}
			
			// delete the rest
			cout   << "Before deletion: "
				<< "range_index_to_start.size(): " << range_index_to_start.size()
				<< ", range_index_to_end.size(): " << range_index_to_end.size()
				<< ", range_start_index_map.size(): " << range_start_index_map.size()
				<< ", range_end_index_map.size(): " << range_end_index_map.size()
				<< endl;
			cout << "ranges before deletion: " << debug_print() << endl;
			// update the indexes of all items in the map, 
			// which lie after the deletion to point to the new index
			//for (int i = indexes.size() ; i < range_index_to_start.size(); ++i) {
			//	int map_start_key = range_index_to_start[i];
			//	int map_end_key   = range_index_to_end[i];
			//	int prev_index_st = range_start_index_map[map_start_key];
			//	cout << "adjusting indexes, prev_index_st: " << prev_index_st
			//		//<< ", prev_index_end: " << prev_index_end
			//		<< endl;
			//	range_start_index_map[map_start_key] = prev_index_st - n_deletions;
			//	range_end_index_map[map_end_key] = prev_index_st - n_deletions;
			//}
			//cout << "START : Summary of modifications" << endl;
			//for (int i = indexes.size() - 1; i >= 1; i--) {
			//	cout << "erase index : " << i << endl;
			//	for (int j = i; i-1>=1 && j > indexes[i-1]->first; --j) {
			//		cout << "decrement index in map: " << j << endl;
			//	}
			//}
			//cout << "END : Summary of modifications" << endl;

			for (int i = indexes.size() - 1; i >= 1; i--) {
				// erase the other ranges
				int idx = indexes[i]->first;
				int prev_start = range_index_to_start[idx];
				int prev_end = range_index_to_end[idx];
				cout << "erasing vec index : " << idx 
					<< ", prev_start: " << prev_start
					<< ", prev_end: " << prev_end
					<< endl;
				range_start_index_map.erase(prev_start);
				range_end_index_map.erase(prev_end);
				range_index_to_start.erase(idx);
				range_index_to_end.erase(idx);
				cout   << "After deletion: "
					<< "range_index_to_start.size(): " << range_index_to_start.size()
					<< ", range_index_to_end.size(): " << range_index_to_end.size()
					<< ", range_start_index_map.size(): " << range_start_index_map.size()
					<< ", range_end_index_map.size(): " << range_end_index_map.size()
					<< endl;
			}
			cout << "range_index_to_start.size(): " << range_index_to_start.size()
				<< "range_index_to_end.size(): " << range_index_to_end.size()
				<< endl;
			pair<int, IntervalMergeStrategy> & i1 = * indexes[0];
			// keep the lowest index 
			{
				int idx = indexes[0]->first;
				cout << "keeping range at index: " << idx 
					<< "new_start: " << new_start
					<< "new_end: " << new_end
					<< endl;
				int prev_start = range_index_to_start[idx];
				int prev_end = range_index_to_end[idx];
				range_index_to_start[idx] = new_start;
				range_index_to_end[idx] = new_end;
				range_start_index_map.erase(prev_start);
				range_end_index_map.erase(prev_end);
				range_start_index_map[new_start]= idx;
				range_end_index_map[new_end] = idx;
				cout << "after modifying last index" << 
					", range_index_to_start.size(): " << range_index_to_start.size() ;
				cout << ", range_index_to_end.size(): " << range_index_to_end.size() ;
				cout << ", range_start_index_map.size(): " << range_start_index_map.size(); 
				cout << ", range_end_index_map.size(): " << range_end_index_map.size() 
				 	<< endl;
			}

			if (n_coalesce > 2) {
				// we have a serious problem - it should be max 2
				cerr << "n_coalesce should never exceed 2" << endl;
			}
		}
	}
	do_consistency_check();
	cout << "EXIT " << fn << " start: " << start << ", end: " << end << endl;
}

void disjoint_interval_range::do_consistency_check()
{
	string fn (__PRETTY_FUNCTION__);
	cout << "ENTER " << fn << endl;
	cout << "print: " << debug_print() << endl;
	vector<string> errors;
	if (! (
		(range_start_index_map.size() == range_end_index_map.size()) &&
		(range_end_index_map.size() == range_index_to_start.size()) &&
		(range_index_to_start.size() == range_index_to_end.size())
	      ) ) {
		//cerr << "ERR " << " inconsistency in " << fn << endl; 
		errors.push_back("all elements not of the same size");
		stringstream ss;
		ss << " range_start_index_map.size(): "
			<< range_start_index_map.size()
			<< ", range_end_index_map.size(): "
			<< range_end_index_map.size()
			<< ", range_index_to_start.size(): "
			<< range_index_to_start.size()
			<< ", range_index_to_end.size(): "
			<< range_index_to_end.size()
			<< endl;
		errors.push_back(ss.str());
	}

	//for (map<int, int> :: iterator it = range_start_index_map.begin();
	//		it != range_start_index_map.end(); ++it) {
	//	if (it->second > range_index_to_start.size() - 1) {
	//		stringstream s;
	//		s << "index in range_start_index_map: "
	//			<< it->second
	//			<<  "  > range_index_to_start.size() - 1";
	//		errors.push_back(s.str());
	//	}
	//	if (it->second > range_index_to_end.size() - 1) {
	//		stringstream s;
	//		s << "index in range_start_index_map: "
	//			<< it->second << "> range_index_to_end.size() - 1";
	//		errors.push_back(s.str());
	//	}
	//}

	//for (map<int, int> :: iterator it = range_end_index_map.begin();
	//		it != range_end_index_map.end(); ++it) {
	//	if (it->second > range_index_to_start.size() - 1) {
	//		errors.push_back("index in range_start_index_map > range_index_to_start.size() - 1");
	//	}
	//	if (it->second > range_index_to_end.size() - 1) {
	//		errors.push_back("index in range_end_index_map > range_index_to_end.size() - 1");
	//	}
	//}
	if (errors.size() > 0 ) {
		cerr << "consistency check failed ... exiting" 
			<< endl;
		for (int i = 0; i < errors.size(); ++i) {
			cerr << errors[i] << endl;
		}
		exit(1);
	}
	cout << "EXIT " << fn << endl;
}

#if IncludeMain
int main()
{
	int n_tests = 0, n_passed = 0;
	map<string, bool> test_results;

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
		//dir1.add_to_range(8,10);
		map<int, IntervalMergeStrategy> res = dir1.intersects(4,7);
		if (res.size() == 1) {
			int i1 = res.begin()->first;
			int r_start = dir1.range_index_to_start[i1];
			int r_end = dir1.range_index_to_end[i1];
			if (!(r_start == 3 && r_end == 5)) {
				++n_tests;
				test_results[tname] = false;
				cout << "failed " << tname 
					<< "expected : 3 - 5 "
					<< ", actual: " << r_start << " - " << r_end
					<< endl;
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
		string tname("test intersection  - 2nd range intersects with first range");
		struct disjoint_interval_range dir1;
		dir1.add_to_range(0,50);
		map<int, IntervalMergeStrategy> res = dir1.intersects(11,91);
		if (res.size() == 1) {
			int i1 = res.begin()->first;
			int r_start = dir1.range_index_to_start[i1];
			int r_end = dir1.range_index_to_end[i1];
			if (!(r_start == 0 && r_end == 50)) {
				++n_tests;
				test_results[tname] = false;
				cout << "failed " << tname 
					<< "expected : 0 - 50 "
					<< ", actual: " << r_start << " - " << r_end
					<< endl;
			} else {
				//++n_passed; ++n_tests;
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
		dir1.add_to_range(11,91);
		string s1 = dir1.print();
		if (!(s1 == ", 0 - 91")) {
			++n_tests;
			test_results[tname] = false;
			cout << "failed " << tname 
				<< "expected : 0 - 91 "
				<< ", actual: " << s1
				<< endl;
		} else {
			++n_passed; ++n_tests;
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
			int r_start = dir1.range_index_to_start[i1];
			int r_end = dir1.range_index_to_end[i1];
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
		string tname("new interval left end point < existing interval, new interval right point lies inbetween existing interval");
		struct disjoint_interval_range dir1;
		//-200780 - -156837, -140903 - 201742
		//dir1.add_to_range(-140903,  201742);
		//dir1.add_to_range(-200780, -156837);
		//dir1.add_to_range(-170833,  147775);
		//dir1.add_to_range(-61391 ,  54904 );

		dir1.add_to_range( -29941   , 37999 );
		dir1.add_to_range( -114105  , -62356 );
		dir1.add_to_range( -200780  , -156837 );
		dir1.add_to_range( -137348  , 110197 );
		dir1.add_to_range( -88995   , 131001 );
		dir1.add_to_range( -57697   , 174641 );
		dir1.add_to_range( 48168    , 136366 );
		dir1.add_to_range( -91103   , -46336 );
		dir1.add_to_range( 42069    , 142846 );
		dir1.add_to_range( -80495   , 189045 );
		dir1.add_to_range( -140903  , 159845 );
		dir1.add_to_range( -20743   , 198818 );
		dir1.add_to_range( -48887   , 201742 );
		dir1.add_to_range( -170833  , 147775 );


		string s = dir1.print();
		cout << " after add : " << s << endl;
		if (s == string(", 1 - 5")) {
			++n_passed; ++n_tests;
		} else {
			++n_tests;
			cout << "failed " << tname << endl;
			test_results[tname] = false;
		}
	}

	{
		string tname("test add range ");
		cout << "BEGIN ****" << tname << "****" << endl;
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
				<< ", actual: " << s
				<< ", expected " << ", 1 - 21"
				<< endl;
		}
		cout << "END ****" << tname << "****" << endl;
	}

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

	{
		string tname("input by fuzzer - fails consistency check");
		struct disjoint_interval_range dir1;
		//-200780 - -156837, -140903 - 201742
		//dir1.add_to_range(-140903,  201742);
		//dir1.add_to_range(-200780, -156837);
		//dir1.add_to_range(-170833,  147775);
		//dir1.add_to_range(-61391 ,  54904 );
		dir1.add_to_range(-134865  , -57339 );
		dir1.add_to_range(51318    , 175882);
		dir1.add_to_range(109885   , 202671);
		dir1.add_to_range(15088    , 137928);
		dir1.add_to_range(-204843  , -181589);
		dir1.add_to_range(-50443   , -17649);
		dir1.add_to_range(-70151   , 104548);


		string s = dir1.print();
		cout << " after add : " << s << endl;
		if (s == string(", 1 - 5")) {
			++n_passed; ++n_tests;
		} else {
			++n_tests;
			cout << "failed " << tname << endl;
			test_results[tname] = false;
		}
	}


	{

		string tname("input by fuzzer - fails consistency check");
		struct disjoint_interval_range dir1;

		dir1.add_to_range( -9089   , -1327 );
		dir1.add_to_range( -9493   ,  509 );
		dir1.add_to_range( -17596  , -13615 );
		dir1.add_to_range( 9854    ,  13690 );
		dir1.add_to_range( -7222   , -2237 );
		dir1.add_to_range( -17413  , -2789 );
		dir1.add_to_range( 18477   ,  20576 );
		dir1.add_to_range( -5486   ,  8243 );
		dir1.add_to_range( -19742  , -16537 );
		dir1.add_to_range( -15508  ,  12257 );

		string s = dir1.print();
		cout << " after add : " << s << endl;
		if (s == string(", 1 - 5")) {
			++n_passed; ++n_tests;
		} else {
			++n_tests;
			cout << "failed " << tname << endl;
			test_results[tname] = false;
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

#endif /* IncludeMain */
