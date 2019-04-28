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
	std::vector<int> range_start;
	std::vector<int> range_end;
	void add_to_range(int start, int end);
	std::map<int, IntervalMergeStrategy> intersects(int start, int end);
	std::string print();
};

#endif /* disjoint_interval_range_h */
