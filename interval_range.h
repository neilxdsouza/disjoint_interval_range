#ifndef disjoint_interval_range_h
#define disjoint_interval_range_h

#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <algorithm>

enum IntervalMergeStrategy {
	SWALLOW,
	COALESCE
};

struct disjoint_interval_range {
	std::map<int, int> range_start_index_map;
	std::map<int, int> range_end_index_map;
	std::map<int,int> range_index_to_start;
	std::map<int,int> range_index_to_end;
	void add_to_range(int start, int end);
	std::map<int, IntervalMergeStrategy> intersects(int start, int end);
	std::string print();
	std::vector<std::pair<int,int>> get_intervals();
	void do_consistency_check();
	std::string debug_print();
};

#endif /* disjoint_interval_range_h */
